#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include <vector>
#include "Vertex.hpp"
#include "Face.hpp"
#include "parse_file_ngb.cpp"

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

     
}

/* Ecriture dans le fichier de sortie */
