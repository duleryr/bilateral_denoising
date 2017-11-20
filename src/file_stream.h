#ifndef FILE_STREAM
#define FILE_STREAM

#include "Data_structure.h"
#include <string>

class File_stream
{
public:
    static DataStructure parse_file_ngb(std::string filename);
    static void write_file_off(std::string filename, DataStructure data);
};

#endif
