#include <iostream>
#include <string>

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
}

/* Ecriture dans le fichier de sortie */
