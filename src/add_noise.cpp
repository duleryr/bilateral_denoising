#include <iostream>
#include <string>
#include <random>
#include <vector>

double calcul_moyenne(std::vector<double>& tab , int size) {
    double moy = 0;
    for (int i = 0; i < size; i++) {
        moy += tab[i];
    }
    moy /= size;
    return moy;
}

double calcul_deviation(std::vector<double>& tab, int size) {
    double moy_carre = 0;
    for (int i = 0; i < size; i++) {
        moy_carre += pow(tab[i], 2);
    }
    moy_carre /= size;
    double var = moy_carre - pow(calcul_moyenne(tab,size),2);
    double deviation = sqrt(var);
    return deviation;
} 

void gaussian_noise(double mean, double deviation, std::vector<double>& tab, int size) {
    srand(time(NULL));
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(mean, deviation);
    for (int i = 0; i < size; i++) {
        double noise = distribution(generator);
        tab[i] += noise;
    }
}

double frand(double a, double b){
    return ( rand()/(double)RAND_MAX ) * (b-a) + a;
}

void random_noise(double first_value, double amplitude ,std::vector<double>& tab, int size) {
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        double noise = frand(first_value, amplitude);
        tab[i] += noise;
    }
}

void add_noise(std::vector<Vertex> tab_vertices) {
    int nb_vertices = tab_vertices.size();
    std::vector< std::vector<double>> tab_coord;
    tab_coord.push_back(std::vector<double>(nb_vertices));
    tab_coord.push_back(std::vector<double>(nb_vertices));
    tab_coord.push_back(std::vector<double>(nb_vertices));
    for (int i = 0; i < nb_vertices; i++) {
        for (int j = 0; j < 3; j++) {
            tab_coord[j][i] = tab_vertices[i].Coords[j];
        }
    }
  
    for (int i = 0; i < nb_vertices; i++) {
        std::cout<<tab_coord[0][i]<<" "<<tab_coord[1][i]<<" "<<tab_coord[2][i]<<std::endl;
    }

    std::string noisename;
    std::cout << "indiquez le type de bruit (au choix gaussien, aleatoire): \n";
    std::cin >> noisename;
  
    if (noisename == "gaussien") {
        double deviation[3];
        for (int i = 0; i < 3; i++) {
	    std::cout<< "indiquez l'écart type de la composante "<<i<<"\n";
            std::cin >> deviation[i];
            gaussian_noise(0, deviation[i], tab_coord[i], nb_vertices);
        }
    } else if (noisename == "aleatoire") {
        double amplitude[3];
        for (int i = 0; i < 3; i++) {
           std::cout<<"indiquez l'amplitude de la première composante: \n";
           std::cin >> amplitude[i];
           random_noise(0, amplitude[i], tab_coord[i], nb_vertices);
        }
    } else {
        std::cout<< "bruit non valide"<< std::endl;
    }

    for (int i = 0; i < nb_vertices; i++) {
        std::cout<<tab_coord[0][i]<<" "<<tab_coord[1][i]<<" "<<tab_coord[2][i]<<std::endl;
    }

}
