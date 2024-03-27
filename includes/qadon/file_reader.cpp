#include "qadon.h"
#include <iostream>


// prototypes
//std::string upper(std::string& line);
//void create_header(std::string class_name, qadon object_template);
//void create_cpp(std::string class_name, qadon object_template);



int main()
{

    qadon header_template("header_template.qadon");
    qadon cpp_template("cpp_template.qadon");

    std::string class_name = "mario";

    create_header(class_name, header_template);
    create_cpp(class_name, cpp_template);
    return 0;
}





void create_header(std::string class_name, qadon object_template)
{
    std::ofstream object( class_name + ".h");
    object_template["line_1"] = "#define " + upper(class_name) + "_H";
    object_template["line_2"] = "#ifndef " + upper(class_name) + "_H";
    object_template["line_5"] = "class " + class_name + " : public GameObject";
    object_template["line_8"] = class_name + "();";
    std::string temp_key;
    for (int i = 1; i <= 11; i++)
    {
        temp_key = "line_" + std::to_string(i);
        object << object_template[temp_key] << std::endl;
    }

    object.close();

}

void create_cpp(std::string class_name, qadon object_template)
{
    std::ofstream object(class_name + ".cpp");
    object_template["line_1"] = "#include " + std::string(1,'"') + class_name + ".h"  + std::string(1,'"');
    object_template["line_4"] = class_name + "::" + class_name + "()";
    object_template["line_9"] = "void " + class_name + "::update(InputEngine& input_engine)";
    std::string temp_key;

    for(int i = 1; i <= 11; i++)
    {
        temp_key = "line_" + std::to_string(i);
        object << object_template[temp_key] << std::endl;

    }
}


std::string upper(std::string& line)
{
    std::string new_line = "";

    for (auto& character : line)
    {
        new_line += toupper(character);
    }

    return new_line;
}