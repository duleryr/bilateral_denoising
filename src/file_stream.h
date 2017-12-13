#ifndef FILE_STREAM
#define FILE_STREAM

#include "Data_structure.h"
#include <string>

// Classe gérant la lecture/écriture des fichiers
class File_stream
{
public:
    // Parseur du fichier d'entrée
    static DataStructure parse_file_off(std::string filename);
    // Ecriture dans le fichier de sortie
    static void write_file_off(std::string filename, DataStructure data);
};

#endif
