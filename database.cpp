//
// Created by dev on 10/19/2023.
//

#include "database.h"

database::database()
{
    name = "";
    folder = "";
    path = "";
    is_named = false;
    separator = ' ';
}

database::database(std::string name, std::string path, std::string folder)
{
    set_database_name(name);
    set_database_folder(folder);
    set_database_path(path);
    separator = ' ';
}

void database::set_database_name(std::string name)
{
    this->name = name;
    is_named = true;
}

void database::set_database_path(std::string path)
{
    this->path = path;
}

void database::set_database_folder(std::string folder)
{
    this->folder = folder;
}

void database::set_database_binary(bool binary)
{
    is_binary = binary;
}

std::string database::get_database_info()
{
    std::string info;
    std::fstream file;

    if(!is_binary) file.open(concat_database_name(), std::ios::in);
    else file.open(concat_database_name(), std::ios::in | std::ios::binary);

    if(file.is_open()){
        while(!file.eof()) info.push_back(file.get());
    }
    else throw 0;

    return info;
}

void database::set_database_info(std::string info)
{
    std::fstream file;

    if(!is_binary) file.open(concat_database_name(), std::ios::out);
    else file.open(concat_database_name(), std::ios::out | std::ios::binary);

    if(file.is_open()){
        file << info;
    }
    else throw 'A';
}

void database::create_database()
{
    std::fstream file;

    if(is_named){
        create_folder();
        file.open(concat_database_name(),std::ios::out);
        file.close();
    }
}

std::vector<std::string> database::split(std::string row)
{
    int pos = 1;
    std::vector<std::string> splitted;

    for(unsigned int i=0;i<row.length() && pos>=0;i=pos+1){
        pos = row.find(separator,i);
        splitted.push_back(row.substr(i,pos-i));
    }

    return splitted;
}

void database::create_folder()
{
    mkdir(concat_folder_name().c_str());
}

std::string database::concat_folder_name()
{
    std::string folder_name;

    if(path == "" && folder != "") folder_name = folder;
    else if(folder != "") folder_name = path + '/' +folder;

    return folder_name;
}

bool database::is_read_available()
{
    std::fstream file;
    bool correct;
    file.open(concat_database_name(),std::ios::app);
    correct = file.is_open();
    file.close();
    return correct;
}

void database::append_database_info(std::string info)
{
    std::fstream file;

    if(!is_binary) file.open(concat_database_name(), std::ios::app);
    else file.open(concat_database_name(), std::ios::app | std::ios::binary);

    if(file.is_open()){
        file << info;
    }
    else throw 'A';
}

std::vector<std::string> database::get_database_rows()
{
    std::vector<std::string> total_info;
    std::string info;
    std::fstream file;

    if(!is_binary) file.open(concat_database_name(), std::ios::in);
    else file.open(concat_database_name(), std::ios::in | std::ios::binary);

    if(file.is_open()){
        while(!file.eof()){
            std::getline(file,info);
            total_info.push_back(info);
        }
    }
    else throw 0;

    return total_info;
}

void database::set_database_separator(char separator)
{
    this->separator = separator;
}

void database::set_database_info_formatted(std::vector<std::string> row)
{
    std::string formatted_info = "";

    for(unsigned int i=0;i<row.size();i++) formatted_info += row[i]+separator;
    formatted_info.pop_back();

    try{
        set_database_info(formatted_info);
    }
    catch(char){
        throw 'A';
    }
}

std::vector<std::string> database::get_database_columns()
{
    std::vector<std::string> rows, columns, final;
    unsigned int size;

    try{
        rows = get_database_rows();

        for(unsigned int i=0;i<rows.size();i++){
            columns = split(rows[i]);
            size = final.size();
            for(unsigned int j=0;j<columns.size() && size==0;j++){
                final.push_back("");
            }
            for(unsigned int j=0;j<columns.size();j++){
                final[j] += columns[j]+row_separator;
            }
        }
    }
    catch(int){
        throw 0;
    }

    return final;
}

void database::append_database_info_formatted(std::vector<std::string> row)
{
    std::string formatted_info = "";

    for(unsigned int i=0;i<row.size();i++) formatted_info += row[i]+separator;
    formatted_info.pop_back();

    try{
        append_database_info(formatted_info);
    }
    catch(char){
        throw 'A';
    }
}

std::string database::concat_database_name()
{
    std::string database_name = "";

    if(is_named && path == "" && folder == "") database_name = name;
    else if(is_named && path == "") database_name = folder + "/" + name;
    else if(is_named && folder == "") database_name = path + "/" + name;
    else database_name = path + "/" + folder + "/" + name;

    create_folder();

    return database_name;
}
