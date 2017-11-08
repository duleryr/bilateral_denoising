import numpy as np

class Vertex:
    """ Classe décrivant les sommets """
    def __init__(self, str_coordinates):
        self.coords = str_coordinates
        self.normal = "0 0 0\n"

class Face:
    """ Classe décrivant les faces en NGB : listFaces contient les 6 descriptifs NGB """
    def __init__(self, list_vertices):
        self.vertices = list_vertices
        self.normal = []

def normalize_v3(arr):
    """ Normalize a numpy array of 3 component vectors shape=(n,3) """
    lens = np.sqrt(arr[0]**2 + arr[1]**2 + arr[2]**2)
    arr[0] /= lens
    arr[1] /= lens
    arr[2] /= lens                
    return arr

def main():
    filename = input("Choose the OFF File you want to convert in NGB : ")
    try:
        f = open("../OFF_Files/" + filename + ".off", 'r')
    except IOError:
        print("Error : cannot open file")
    else:
        """ 
        ---------------- Etape 1 : Parsing du fichier OFF -----------------
        """
        if not (str(f.readline())).startswith("OFF"):
            print("Error : Wrong file format, should start with OFF")
            exit()
        # Parsing des lignes vides / de commentaires avant la ligne de définition du nombre de sommets/faces
        # Parsing du nombre de sommets et de faces
        while True:
            line = str(f.readline().rstrip())
            line_splitted = line.split(" ")
            if (len(line_splitted) == 3 and not line.startswith('#')):
                V = int(line_splitted[0])
                P = int(line_splitted[1])
                if line_splitted[2] != '0':
                    print("Error : Wrong file format, third value should be 0")
                    exit()
                break
        VerticeList = []
        FaceList = []
        # Parsing des coordonnées des sommets
        for i in range(V):
            line = f.readline()
            vertex = Vertex(line)
            VerticeList.append(vertex)
    
        # Parsing des faces
        for i in range(P):
            line_tab = f.readline().rstrip().split(" ")
            # Le premier nombre est inutile : il n'y a que des triangles
            del line_tab[0]
            face = Face(line_tab)
            FaceList.append(face)
        f.close()

        """ 
        ---------------- Etape 2 : Traitement des données -----------------
        """
        # Calcul des normales des faces
        for mainIndex, currentFace in enumerate(FaceList):
            V0 = VerticeList[int(currentFace.vertices[0])].coords.rstrip().split(" ")
            V1 = VerticeList[int(currentFace.vertices[1])].coords.rstrip().split(" ")
            V2 = VerticeList[int(currentFace.vertices[2])].coords.rstrip().split(" ")
            vect1 = [float(V1[0]) - float(V0[0]), float(V1[1]) - float(V0[1]), float(V1[2]) - float(V0[2])]
            vect2 = [float(V2[0]) - float(V0[0]), float(V2[1]) - float(V0[1]), float(V2[2]) - float(V0[2])]
            currentFace.normal = normalize_v3(np.cross(vect2, vect1))

        # Calcul des normales des sommets
        for i in range(V):
            v = []
            for face in FaceList:
                if str(i) in face.vertices:
                    v.append(face.normal)
            tmpNormal = normalize_v3(sum(v))
            VerticeList[i].normal = " ".join(list(map(str, tmpNormal))) + "\n"

        # Obtention des indices des faces voisines
        for mainIndex, currentFace in enumerate(FaceList):
            for j in [(1,2), (0,2), (0,1)]:
                for tmpIndex, tmpFace in enumerate(FaceList):
                    if (mainIndex == tmpIndex):
                        continue
                    if currentFace.vertices[j[0]] in tmpFace.vertices[:3] and currentFace.vertices[j[1]] in tmpFace.vertices[:3]:
                        currentFace.vertices.append(str(tmpIndex))

        """ 
        ----------- Etape 3 : Ecriture dans le fichier de sortie ----------
        """
        output_file = open("../NGB_Files/" + filename + ".ngb", 'w')
        output_file.write("NEIGHBOUR_FILE\n")
        output_file.write(str(V) + " " + str(P) + "\n")

        for i in range(V):
            output_file.write(VerticeList[i].coords)
            output_file.write(VerticeList[i].normal)

        for face in FaceList:
            output_file.write(" ".join(face.vertices) + "\n")

        output_file.close()

main()
