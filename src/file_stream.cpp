#include "file_stream.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <vector>
#include "Vertex.h"
#include "Face.h"

// Parseur du fichier d'entrée, retourne un objet DataStructure
DataStructure File_stream::parse_file_off(std::string filename) {
    std::ifstream fichier(filename.c_str(), std::ios::in);
    if(!fichier) {
        std::cout<<"Erreur lors de l'ouverture du fichier d'entrée"<<std::endl;
        exit(1);
    }
    std::string type_fichier;
    fichier >> type_fichier;
    int nb_sommets;
    fichier >> nb_sommets;
    int nb_faces;
    fichier >> nb_faces;
    int tmp;
    fichier >> tmp;

    std::vector<Vertex> tableau_sommets;
    //on remplit le tableau de sommets avec les coordonnées des sommets et des normales au sommets
    for (int i = 0; i < nb_sommets; i++) {
        Vertex S;
        fichier >> S.coords.x;
        fichier >> S.coords.y;
        fichier >> S.coords.z;
        S.neighbours.insert(i);
        tableau_sommets.push_back(S);           
    }

    //On remplit le tableau de faces avec les indices des sommets la constituant et les indices des faces adjacentes
    std::vector<Face> tableau_faces;
    for (int i = 0; i < nb_faces; i++) {
        Face F;
        fichier >> tmp;
        fichier >> F.verticesId[0];
        fichier >> F.verticesId[1];
        fichier >> F.verticesId[2];
        tableau_sommets[F.verticesId[0]].related_faces.push_back(i);
        tableau_sommets[F.verticesId[1]].related_faces.push_back(i);
        tableau_sommets[F.verticesId[2]].related_faces.push_back(i);
        tableau_faces.push_back(F);
    }

    return DataStructure(tableau_sommets, tableau_faces);
}

// Ecriture de la DataStructure dans le fichier de sortie
void File_stream::write_file_off(std::string filename, DataStructure data) {
    std::ofstream fichier(filename.c_str(), std::ios::out | std::ios::trunc);
    if(!fichier) {
        std::cout<<"Erreur lors de l'ouverture du fichier de sortie"<<std::endl;
        return;
    }
    fichier << "OFF" << std::endl;
    fichier << data.vertices.size() << " " << data.faces.size() << " 0"<< std::endl;
    for (uint i = 0; i < data.vertices.size(); i++) {
        fichier << data.vertices[i].coords.x << " " << data.vertices[i].coords.y << " " << data.vertices[i].coords.z << std::endl;
    }
    for (uint i = 0; i < data.faces.size(); i++) {
        fichier << "3 " << data.faces[i].verticesId[0]<< " " << data.faces[i].verticesId[1]<< " " << data.faces[i].verticesId[2] << std::endl;
    }
}
