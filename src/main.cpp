#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include <vector>
#include "Vertex.hpp"
#include "Face.hpp"
#include "update_normale.cpp"
#include "denoise_point.cpp"
#include "file_stream.h"

int main(int argc, char **argv) 
{
    std::string filename;

    if (argc == 2) {
        filename = argv[1];
    } else {
        std::cout << "Indiquez le nom du fichier que vous voulez parser :\n";
        std::cin >> filename;
        std::cout << filename;
    }

    /* Structure de données */
    std::vector<Vertex> tableau_sommets;
    std::vector<Face> tableau_faces;

    /* Parsing du fichier OFF */
    File_stream::parse_file_ngb(filename, tableau_sommets, tableau_faces);  

    double sigma_s = 1;
    double sigma_c = 1.5;
    double rau = 2*sigma_c;
    uint nb_iter = 1;
    for (uint j = 0; j < nb_iter; j++) {
        for (uint i = 0; i < tableau_sommets.size(); i++) {
            denoise_point(tableau_sommets[i], rau, tableau_sommets, sigma_c, sigma_s);
        }
        update_normale(tableau_sommets, tableau_faces);
    }

    std::string output_filename = "../OFF_Files_Noised/" + filename + "_denoised";

    /* Ecriture dans le fichier de sortie */
    File_stream::write_file_off(output_filename, tableau_sommets, tableau_faces);

    return 0;
}

