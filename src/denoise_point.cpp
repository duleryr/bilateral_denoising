#include <stdio.h>
#include <math.h>
#include "Face.hpp"
#include "Vertex.hpp"

std::vector<double> compute_dist( double V1[], double V2[]) {
  std::vector<double> res(3);
  for (int i = 0; i < 3; i++) {
    res[i] = V1[i] - V2[i]; 
  }
  return res;
}

double compute_norme(double V[]) {
  double res = 0.0;
  for (int i = 0; i < 3; i++) {
    res += V[i]*V[i];
  }
  return sqrt(res);
}

double compute_norme(std::vector<double> V) {
  double res = 0.0;
  for (int i = 0; i < 3; i++) {
    res += V[i]*V[i];
  }
  return sqrt(res);
}

//premier argmt: normal (tableau), deuxième : dist(vector)
double compute_produit_scalaire (double V1[], std::vector<double> V2) {
  double res = 0.0;
  for (int i = 0; i < 3; i++) {
    res += V1[i]*V2[i];
  }
  return res;
}

std::vector<Vertex> compute_neighborhood(Vertex V, double rau, std::vector<Vertex> & tableau_sommets) {
  std::vector<Vertex> neighborhood;
  for (uint i = 0; i < tableau_sommets.size(); i++) {
    if (!(tableau_sommets[i] == V)) {
      std::vector<double> dist = compute_dist(V.Coords, tableau_sommets[i].Coords);
      double norme = compute_norme(dist);
      if (norme < rau) {
        neighborhood.push_back(tableau_sommets[i]);
      }
    }
  }
  return neighborhood;
}


int denoise_point(Vertex & V, double rau, std::vector<Vertex> & tableau_sommets, double sigma_c, double sigma_s) {
  std::vector<Vertex> neighborhood = compute_neighborhood(V, rau, tableau_sommets);
  int K = neighborhood.size();
  double sum = 0;
  double normalizer = 0;
  for (int i = 0; i < K; i++) {
    std::vector<double> dist = compute_dist(V.Coords, neighborhood[i].Coords);
    double t = compute_norme(dist);
    double h = compute_produit_scalaire(V.normal, dist);
    double w_c = exp((-t*t)/(2*sigma_c*sigma_c));
    double w_s = exp((-h*h)/(2*sigma_s*sigma_s));
    sum += (w_c * w_s) * h;
    normalizer += w_c * w_s;
  }
  for (int i = 0; i < 3; i++) {
    V.Coords[i] = V.Coords[i] + V.normal[i] * (sum / normalizer);
  }
  return 0;
}
