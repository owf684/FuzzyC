
#include <string>
#include <fstream>
#include <qadon.h>
#include <map>

class RdohUtil
{
    public:

        void write_rdoh();
        void add_object(std::string object_name);
        void set_rdoh_file_path(std::string file_path);
        void set_object_lib_path(std::string file_path);
        void create_object_files(std::string object_name,std::string current_sprite_file_path);

    private:
        void create_headers(std::ofstream &rdoh_file, qadon object_library);
        void create_init_objects(std::ofstream &rdoh_file, qadon object_library);
        void create_generate_object(std::ofstream &rdoh_file, qadon object_library);
        std::string rdoh_file_path;
        std::string object_lib_path;

};

//prototypes 
