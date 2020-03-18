/*
 * This is the source code of SpecNet project
 *
 * Copyright (c) Dmitriy Bondarenko
 * feel free to contact me: specnet.messenger@gmail.com
 */

#ifndef FILEADAPTER_H
#define FILEADAPTER_H

#include <string>
#include <vector>
#include <experimental/filesystem>
#include <filesystem>
namespace  fs  =  std::experimental::filesystem ;

namespace spec {

struct file_info {
    fs::path path ;
    fs::file_time_type last_write_time ;
   // std::uintmax_t size ;
} typedef t_file_info;

void save_bin(const std::string &dir,  const char *file_name,
                     const char *data, int size);

void save_bin(const char *file_name,
                     const char *data, int size);

std::vector<char> read_bin(const char *file_name);

std::string read_text(const char *file_name);

void save_text(const std::string &dir, const char *file_name,
                      const std::string &text);

bool save_text(const char *file_name,
                      const std::string &text);

void save_text_append(const std::string &dir, const char *file_name,
                      const std::string &text);

void save_text_append(const char *file_name,
                      const std::string &text);

std::string  toFullPath(const std::string &path, const std::string &exe_path) ;
std::string getDir(const std::string  &filePath) ;

std::vector<t_file_info>  file_list(const fs::path  &dir);
void  del_old_files(const std::string  &dir,  unsigned int  keepCount);
bool  file_exists(const char * path)  ;
bool  createSymlink(const std::string  &target,  const std::string  &link);
} // spec

#endif // FILEADAPTER_H
