#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include "Vertex.hpp"
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

   std::ifstream fichier(filename.c_str(), std::ios::in);

   
   fichier.seekg(3,std::ios::beg);
   
   int nb_sommets;
   fichier >> nb_sommets;
   fichier.seekg(4,std::ios::cur);

   Vertex tableau_sommets[nb_sommets];
    
   //on remplit le tableau de sommets avec les coordonnées des différents sommets
   double x = 0.0;
   double y = 0.0;
   double z = 0.0;
   for (int i = 0; i < nb_sommets; i++) {
       fichier >> x;
       fichier >> y;
       fichier >> z;
       tableau_sommets[i].Coords[0] = x;
       tableau_sommets[i].Coords[1] = y;
       tableau_sommets[i].Coords[2] = z;
   }   

   add_noise(tableau_sommets, nb_sommets);
   

}

/* Ecriture dans le fichier de sortie */
