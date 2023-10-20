//
// Created by dev on 10/19/2023.
//

#ifndef P4_DATABASE_H
#define P4_DATABASE_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <direct.h>

class database {
public:
    database();
    database(std::string name, std::string path = "", std::string folder = "");
    //~database();
    void set_database_name(std::string name);
    void set_database_path(std::string path);
    void set_database_folder(std::string folder);
    void set_database_binary(bool binary);
    std::string get_database_info();
    void set_database_info(std::string info);
    bool is_read_available();
    void append_database_info(std::string info);
    std::vector<std::string> get_database_rows();
    void set_database_separator(char separator);
    void set_database_info_formatted(std::vector<std::string> row);
    std::vector<std::string> get_database_columns();
    void append_database_info_formatted(std::vector<std::string> row);
    std::vector<std::string> split(std::string row);
private:
    std::string name;
    std::string path;
    std::string folder;
    bool is_named, is_binary;
    char separator, row_separator = '\n';

    std::string concat_database_name();
    void create_database();
    //std::vector<std::string> split(std::string row);
    void create_folder();
    std::string concat_folder_name();
};


#endif //P4_DATABASE_H
