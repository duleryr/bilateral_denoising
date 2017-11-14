#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <fstream>
#include <vector>
#include "Vertex.hpp"
#include "Face.hpp"

/*Parsing du fichier NGB */

int parse_file_ngb(std::string filename, std::vector<Vertex> & tableau_sommets, std::vector<Face> & tableau_faces) {
  std::ifstream fichier(filename.c_str(), std::ios::in);
  if(!fichier) {
    std::cout<<"problème lors de l'ouverture du fichier"<<std::endl;
    return -1;
  }
  std::string type_fichier;
  fichier >> type_fichier;
  int nb_sommets;
  fichier >> nb_sommets;;
  int nb_faces;
  fichier >> nb_faces;
  
  //on remplit le tableau de sommets avec les coordonnées des sommets et des normales au sommets
  double x = 0.0;
  double y = 0.0;
  double z = 0.0;
  double x_n = 0.0;
  double y_n = 0.0;
  double z_n = 0.0;
  Vertex S;
  for (int i = 0; i < nb_sommets; i++) {
    fichier >> x;
    fichier >> y;
    fichier >> z;
    fichier >> x_n;
    fichier >> y_n;
    fichier >> z_n;;
    S.Coords[0] = x; 
    S.Coords[1] = y;    
    S.Coords[2] = z;
    S.normal[0] = x_n;
    S.normal[1] = y_n;
    S.normal[2] = z_n;
    tableau_sommets.push_back(S);           
  }
  
  //On remplit le tableau de faces avec les indices des sommets la constituant et les indices des faces adjacentes

  int is1 = 0;
  int is2 = 0;
  int is3 = 0;
  int if1 = 0;
  int if2 = 0;
  int if3 = 0;
  Face F;
  for (int i = 0; i < nb_faces; i++) {
    fichier >> is1;
    fichier >> is2;
    fichier >> is3;
    fichier >> if1;
    fichier >> if2;
    fichier >> if3;
    F.V[0] = is1;
    F.V[1] = is2;
    F.V[2] = is3;
    F.F[0] = if1;
    F.F[1] = if2;
    F.F[2] = if3;
    tableau_faces.push_back(F);
  }

  return 0;
}
