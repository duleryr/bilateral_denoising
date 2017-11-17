#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include <vector>
#include "Vertex.hpp"
#include "Face.hpp"
#include "parse_file_ngb.cpp"
#include "denoise_point.cpp"
#include "update_normale.cpp"
#include "add_noise.cpp"

/* Parsing du fichier OFF */

/* Calcul de données utiles (normales des faces et des sommets...) */

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

    std::vector<Vertex> tableau_sommets;
    std::vector<Face> tableau_faces;
    parse_file_ngb(filename, tableau_sommets, tableau_faces);  
  
    //première étape : bruiter la surface 
    //  add_noise(tableau_sommets);
 
    double sigma_s = 1;
    double sigma_c = 1.5;
    double rau = 2*sigma_c;
    uint nb_iter = 1;
    for (uint j = 0; j < nb_iter; j++) {
      for (uint i = 0; i < tableau_sommets.size(); i++) {
	denoise_point(tableau_sommets[i], rau,tableau_sommets,sigma_c, sigma_s);
      }
      update_normale(tableau_sommets, tableau_faces);
    }
     
}

/* Ecriture dans le fichier de sortie */
