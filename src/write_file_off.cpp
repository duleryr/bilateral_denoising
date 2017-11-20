#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <fstream>
#include <vector>
#include "Vertex.hpp"
#include "Face.hpp"

int write_file_off(std::string filename, std::vector<Vertex> & tableau_sommets, std::vector<Face> & tableau_face) {
    std::ofstream fichier(filename.c_str(), std::ios::out | std::ios::trunc);
    if(!fichier) {
        std::cout<<"problème lors de l'ouverture du fichier"<<std::endl;
        return -1;
    }
    fichier << "OFF" << std::endl;
    fichier << tableau_sommets.size() << tableau_face.size() << "0"<< std::endl;
    for (int i = 0; i < tableau_sommets.size(); i++) {
        fichier << tableau_sommets[i].Coords[0] << tableau_sommets[i].Coords[1] << tableau_sommets[i].Coords[2] << std::endl;
    }
    for (int j = 0; i < tableau_face.size(); i++) {
        fichier << "3" << tableau_face[i].V[0] << tableau_face[i].V[1] << tableau_face[i].V[2] << std::endl;
    }
}
