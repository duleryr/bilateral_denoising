#include <iostream>
#include <string>
#include <cstddef>
#include <stdio.h>
#include <fstream>
#include <vector>
#include "Tools.h"
#include "Vertex.h"
#include "Face.h"
#include "Data_structure.h"
#include "file_stream.h"

#define DEBUG_DISTANCES false

double compute_sigma_c(std::string type, Vertex V, DataStructure data) {
    if (type == "MoyDistVois") {
        std::vector<double> distance;
        if (DEBUG_DISTANCES) {
            std::cout << "------- Distances ------- " << std::endl;
        }
        for (auto itr = V.neighbours.begin(); itr != V.neighbours.end(); ++itr) {
            double dist = Tools::calcNorm(V.coords - data.vertices[*itr].coords);
            if (DEBUG_DISTANCES) {
                std::cout << "Voisin";
                data.vertices[*itr].coords.print();
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

std::vector<Vertex> compute_distance_neighborhood(Vertex V, double rau, const DataStructure data) {
    std::vector<Vertex> neighborhood;
    for (uint i = 0; i < data.vertices.size(); i++) {
        if (!(data.vertices[i] == V)) {
            double norm = Tools::calcNorm(V.coords - data.vertices[i].coords);
            if (norm < rau) {
                neighborhood.push_back(data.vertices[i]);
            }
        }
    }
    return neighborhood;
}

void denoise_point(Vertex & V, double rau, DataStructure & data, double sigma_c, double sigma_s) {
    std::vector<Vertex> neighborhood = compute_distance_neighborhood(V, rau, data);
    int K = neighborhood.size();
    double sum = 0;
    double normalizer = 0;
    for (int i = 0; i < K; i++) {
        std::cout << "Neighboorhood[i]";
        neighborhood[i].coords.print();
        Point dist = V.coords - neighborhood[i].coords;
        double t = Tools::calcNorm(dist);
        std::cout << "V.normal = ";
        V.normal.print();
        std::cout << "V - Qi = ";
        dist.print();
        double h = Tools::dot(V.normal, dist);
        std::cout << "h = " << h << std::endl;
        double w_c = exp((-t*t)/(2*sigma_c*sigma_c));
        double w_s = exp((-h*h)/(2*sigma_s*sigma_s));
        sum += (w_c * w_s) * h;
        normalizer += w_c * w_s;
    }
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

int main(int argc, char **argv) 
{
    std::string input_file;

    double sigma_s = 1;
    double sigma_c = 1;

    if (argc >= 2) {
        if (argc == 3) {
            sigma_s = std::stod(argv[2]);
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

    std::string output_filename = "OFF_Files_Denoised/" + filename + ".off";

    /* Structure de données principale */
    DataStructure data = File_stream::parse_file_off(input_file); 
    data.compute_topology_neighbours(1);
    data.update_normals();

    std::string calc_sigma_c = "MoyDistVois";

    std::cout << "-----------------------------------------" << std::endl;
    data.display_vertices();
    std::cout << "-----------------------------------------" << std::endl;

    int nb_iter = 1;
    for (int j = 0; j < nb_iter; j++) {
        for (uint i = 0; i < data.vertices.size(); i++) {
            sigma_c = compute_sigma_c(calc_sigma_c, data.vertices[i], data);
            double rau = 2*sigma_c;
            if (DEBUG_DISTANCES) {
                std::cout << sigma_c << " ";
            }
            denoise_point(data.vertices[i], rau, data, sigma_c, sigma_s);
        }
        data.update_normals();
    }

    data.display_vertices();

    /* Ecriture dans le fichier de sortie */
    File_stream::write_file_off(output_filename + calc_sigma_c, data);

    return 0;
}

