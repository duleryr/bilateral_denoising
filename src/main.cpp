#include <iostream>
#include <string>
#include <cstddef>
#include <stdio.h>
#include <fstream>
#include <vector>
#include "Point.h"
#include "Tools.h"
#include "Vertex.h"
#include "Face.h"
#include "Data_structure.h"
#include "file_stream.h"

#define DEBUG_DISTANCES false
#define SHOW_RESULT false

double compute_sigma_c(std::string type, Vertex V, std::vector<Point> vertices_coords_cpy) {
    if (type == "MoyDistVois") {
        std::vector<double> distance;
        if (DEBUG_DISTANCES) {
            std::cout << "------- Distances ------- " << std::endl;
        }
        for (auto itr = V.neighbours.begin(); itr != V.neighbours.end(); ++itr) {
            double dist = Tools::calcNorm(V.coords - vertices_coords_cpy[*itr]);
            if (DEBUG_DISTANCES) {
                std::cout << "Voisin";
                vertices_coords_cpy[*itr].print();
                std::cout << "Point";
                V.coords.print();
                std::cout << "Distance : " << dist << std::endl;
            }
            distance.push_back(dist);
        }
        std::cout << std::endl;
        return Tools::average(distance);
    }
    return 0.0;
}

double compute_sigma_s(std::string type, Vertex V, std::vector<Point> vertices_coords_cpy) {
    if (type == "MoyDistVois") {
        std::vector<double> distance;
        if (DEBUG_DISTANCES) {
            std::cout << "------- Distances ------- " << std::endl;
        }
        for (auto itr = V.neighbours.begin(); itr != V.neighbours.end(); ++itr) {
            double dist = Tools::calcNorm(V.coords - vertices_coords_cpy[*itr]);
            if (DEBUG_DISTANCES) {
                std::cout << "Voisin";
                vertices_coords_cpy[*itr].print();
                std::cout << "Point";
                V.coords.print();
                std::cout << "Distance : " << dist << std::endl;
            }
            distance.push_back(dist);
        }
        std::cout << std::endl;
        return Tools::standard_deviation(distance);
    }
    return 0.0;
}

std::vector<Point> compute_distance_neighborhood(Vertex V, double rau, const std::vector<Point> coords_cpy) {
    std::vector<Point> neighborhood;
    for (uint i = 0; i < coords_cpy.size(); i++) {
        if (!(coords_cpy[i] == V.coords)) {
            double norm = Tools::calcNorm(V.coords - coords_cpy[i]);
            if (norm < rau) {
                neighborhood.push_back(coords_cpy[i]);
            }
        }
    }
    return neighborhood;
}

void denoise_point(Vertex & V, double rau, std::vector<Point> coords_cpy, double sigma_c, double sigma_s) {
    std::vector<Point> neighborhood = compute_distance_neighborhood(V, rau, coords_cpy);
    int K = neighborhood.size();
    double sum = 0;
    double normalizer = 0;
    for (int i = 0; i < K; i++) {
        std::cout << "Neighboorhood[i]";
        neighborhood[i].print();
        Point dist = V.coords - neighborhood[i];
        double h = Tools::dot(V.normal, dist);
        double t = Tools::calcNorm(dist);

        if (DEBUG_DISTANCES) {
            std::cout << "V.normal = ";
            V.normal.print();
            std::cout << "V - Qi = ";
            dist.print();
            std::cout << "h = " << h << std::endl;
        }

        double w_c = exp((-t*t)/(2*sigma_c*sigma_c));
        double w_s = exp((-h*h)/(2*sigma_s*sigma_s));
        sum += (w_c * w_s) * h;
        normalizer += w_c * w_s;
    }
    V.coords -= V.normal * (sum / normalizer);
    if (DEBUG_DISTANCES) {
        std::cout << "Before" << std::endl;
        V.coords.print();
        std::cout << "Normal = " << std::endl;
        V.normal.print();
        std::cout << "Sum = " << sum << std::endl;
        std::cout << "Normalizer = " << normalizer << std::endl;
        std::cout << "Sum / normalizer = " << sum / normalizer << std::endl;
        V.coords += V.normal * (sum / normalizer);
        std::cout << "After" << std::endl;
        V.coords.print();
        std::cout << std::endl;
    }
}

int main(int argc, char **argv) 
{
    std::string input_file;

    double sigma_s = 1;
    double sigma_c = 1;

    int nb_iter = 3;

    if (argc >= 2) {
        if (argc == 3) {
            nb_iter = std::stoi(argv[2]);
        }
        input_file = argv[1];
    } else {
        std::cout << "Indiquez le fichier que vous voulez débruiter :\n";
        std::cin >> input_file;
    }

    std::size_t found = input_file.find_last_of("/");
    std::string filename = input_file.substr(found+1);
    std::cout << filename << std::endl;
    found = filename.find_last_of(".");
    filename = filename.substr(0,found);
    std::cout << filename << std::endl;

    /* Structure de données principale */
    DataStructure data = File_stream::parse_file_off(input_file); 
    data.compute_topology_neighbours(1);
    data.update_normals();

    std::vector<Point> vertices_coords_cpy;

    for (uint i = 0; i < data.vertices.size(); i++) {
        vertices_coords_cpy.push_back(Point(data.vertices[i].coords));
    }

    std::string calc_sigma = "MoyDistVois";

    std::cout << "-----------------------------------------" << std::endl;
    data.display_vertices();
    std::cout << "-----------------------------------------" << std::endl;

    for (int j = 0; j < nb_iter; j++) {
        for (uint i = 0; i < data.vertices.size(); i++) {
            sigma_c = compute_sigma_c(calc_sigma, data.vertices[i], vertices_coords_cpy);
            sigma_s = compute_sigma_s(calc_sigma, data.vertices[i], vertices_coords_cpy);
            if (DEBUG_DISTANCES) {
                std::cout << "sigma_c = " << sigma_c << std::endl;
            }
            double rau = 2*sigma_c;
            denoise_point(data.vertices[i], rau, vertices_coords_cpy, sigma_c, sigma_s);
        }
        data.update_normals();

        for (uint i = 0; i < data.vertices.size(); i++) {
            vertices_coords_cpy[i] = data.vertices[i].coords;
        }
    }

    if (SHOW_RESULT) {
        std::cout << "-----Résultats obtenus-----" << std::endl;
        data.display_vertices();
    }

    std::string output_filename = "OFF_Files_Denoised/" + filename + "_" + std::to_string(nb_iter) + "_" + std::to_string(sigma_s) + ".off";

    /* Ecriture dans le fichier de sortie */
    File_stream::write_file_off(output_filename, data);

    return 0;
}

