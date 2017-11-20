#ifndef FILE_STREAM
#define FILE_STREAM

class File_stream
{
public:
    static void parse_file_ngb(std::string filename, std::vector<Vertex> & tableau_sommets, std::vector<Face> & tableau_faces);
    static void write_file_off(std::string filename, std::vector<Vertex> & tableau_sommets, std::vector<Face> & tableau_face);
};

#endif
