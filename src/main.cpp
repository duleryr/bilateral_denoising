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

std::vector<Vertex> compute_neighborhood(Vertex V, double rau, const DataStructure data) {
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
    std::vector<Vertex> neighborhood = compute_neighborhood(V, rau, data);
    int K = neighborhood.size();
    double sum = 0;
    double normalizer = 0;
    for (int i = 0; i < K; i++) {
        Point dist = V.coords - neighborhood[i].coords;
        double t = Tools::calcNorm(dist);
        double h = Tools::dot(V.normal, dist);
        double w_c = exp((-t*t)/(2*sigma_c*sigma_c));
        double w_s = exp((-h*h)/(2*sigma_s*sigma_s));
        sum += (w_c * w_s) * h;
        normalizer += w_c * w_s;
    }
    V.coords += V.normal * (sum / normalizer);
}

int main(int argc, char **argv) 
{
    std::string input_file;

    double sigma_s = 1;
    double sigma_c = 1.5;

    if (argc >= 2) {
        if (argc == 4) {
            sigma_s = std::stod(argv[2]);
            sigma_c = std::stod(argv[3]);
        }
        input_file = argv[1];
    } else {
        std::cout << "Indiquez le fichier que vous voulez débruiter :\n";
        std::cin >> input_file;
    }

    std::size_t found = input_file.find_last_of("/");
    std::string filename = input_file.substr(found+1);
    found = filename.find_last_of(".");
    filename = input_file.substr(found+1);
    std::cout << filename << std::endl;

    /* Structure de données principale */
    DataStructure data = File_stream::parse_file_off(input_file);  
    data.update_normals();

    double rau = 2*sigma_c;
    int nb_iter = 1;
    for (int j = 0; j < nb_iter; j++) {
        for (uint i = 0; i < data.vertices.size(); i++) {
            denoise_point(data.vertices[i], rau, data, sigma_c, sigma_s);
        }
        data.update_normals();
    }

    std::string output_filename = "OFF_Files_Denoised/" + filename + ".off";

    /* Ecriture dans le fichier de sortie */
    File_stream::write_file_off(output_filename, data);

    return 0;
}

