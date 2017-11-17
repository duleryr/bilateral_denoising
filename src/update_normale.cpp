std::vector<double> cross_product(const std::vector<double>  V1, const std::vector<double> V2) {
  std::vector<double> res(3);
  res[0] = V1[1]*V2[2] - V1[2]*V2[1];
  res[1] = V1[2]*V2[0] - V2[2]*V1[0];
  res[2] = V1[0]*V2[1] - V1[1]*V2[0];
  return res;
}

std::vector<double> compute_normale_face(const Face & F,std::vector<Vertex> & tableau_sommets) {
  std::vector<double> res(3);
  Vertex V0 = tableau_sommets[F.V[0]];
  Vertex V1 = tableau_sommets[F.V[1]];
  Vertex V2 = tableau_sommets[F.V[2]];
  std::vector<double> dist1 = compute_dist(V1.Coords, V0.Coords);
  std::vector<double> dist2 = compute_dist(V2.Coords, V0.Coords);
  std::vector<double> crossproduct = cross_product(dist1, dist2);
  double norme = compute_norme(crossproduct);
  for (int i = 0; i < 3; i++) {
    res[i] = crossproduct[i] / norme;
  }
  return res;
}

int update_normale(std::vector<Vertex> & tableau_sommets, const std::vector<Face> & tableau_faces) {
  int nb_sommets = tableau_sommets.size();
  int nb_faces = tableau_faces.size();
  std::vector<std::vector<double>> normales_faces;
  for (int i = 0; i < nb_faces; i++) {
    std::vector<double> normale = compute_normale_face(tableau_faces[i], tableau_sommets);
    normales_faces.push_back(normale);
  }
  for (int i = 0; i < nb_sommets; i++) {
    Vertex V = tableau_sommets[i];
    V.normal[0] = 0.0;
    V.normal[1] = 0.0;
    V.normal[2] = 0.0;
    for (int j = 0; j < nb_faces; j++) {
      Face F = tableau_faces[j];
      Vertex V0 = tableau_sommets[F.V[0]];
      Vertex V1 = tableau_sommets[F.V[1]];
      Vertex V2 = tableau_sommets[F.V[2]];
      if ((V == V0) || (V == V1) || (V == V2)) {
        V.normal[0] += normales_faces[j][0];
        V.normal[1] += normales_faces[j][1];
	V.normal[2] += normales_faces[j][2];
	} 
    }
    double norme = compute_norme(V.normal);
    V.normal[0] = V.normal[0]/norme;
    V.normal[1] = V.normal[1]/norme;
    V.normal[2] = V.normal[2]/norme;
  }
  return 0;
}
