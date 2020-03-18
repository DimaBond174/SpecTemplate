/*
 * This is the source code of SpecNet project
 *
 * Copyright (c) Dmitriy Bondarenko
 * feel free to contact me: specnet.messenger@gmail.com
 */

#include "fileadapter.h"
#include <fstream>
#include <streambuf>
#include <sys/types.h>
#include "tools/specstatic.h"
#include <algorithm>

#if defined(Windows)
#include <direct.h>
#ifndef PATH_MAX
#define PATH_MAX _MAX_PATH
#endif // !
#endif

bool  spec::createSymlink(const std::string  &target,  const std::string  &link)
{
  std::error_code  ec;
  fs::create_symlink(fs::path(target),  fs::path(link),  ec);
  return !ec;
}

std::vector<spec::t_file_info>  spec::file_list(const fs::path  &dir)
{
  std::vector<t_file_info>  result ;
  for  (const auto  &p  :  fs::recursive_directory_iterator(dir) )  {
    const auto  &path  =  p.path() ;
    if  (fs::is_regular_file(path))
      result.push_back( t_file_info  {
        path, fs::last_write_time(path)
        //,fs::file_size( path )
        } ) ;
    }
    return result ;
}

void  spec::del_old_files(const std::string  &dir,  unsigned int  keepCount)
{
  try  {
    auto&&  flist  =  file_list(dir) ;
    static const auto  cmp_times  =  [] (const t_file_info  &a,  const t_file_info  &b)
      {  return  (a.last_write_time  >  b.last_write_time);  } ;
    std::sort( std::begin( flist ),  std::end( flist ),  cmp_times ) ;
    for  (std::size_t  i  =  flist.size();  i  >  keepCount ;  --i)  {
      fs::remove( flist[i-1].path ) ;
    }
  }  catch  (const std::exception& ) {  }
}  //  del_old_files

bool spec::file_exists(const char * path)
{
  bool  re = false;
  try {
    re  =  fs::exists(path);  //fs::exists(fs::path(path))  ;
  } catch(...) {}
  return re;
}

std::string spec::getDir(const std::string  &filePath)
{
  size_t found  =  filePath.find_last_of("/\\");
  return(filePath.substr(0, found));
}

std::string  spec::toFullPath(const std::string &path, const std::string &exe_path)
{
  std::string  re;
  if  (path.length() > 2)  {
    if('.' == path[0]  &&  '/' == path[1])  {
      re.append(exe_path).append(path.c_str() + 1);
    }  else  {
      re.append(path);
    }
  }
  return re;
}

void spec::save_bin(const std::string &dir, const char *file_name, const char *data, int size)
{
  fs::create_directories(dir);
  std::string to_file(dir);
  to_file.append(file_name);
  save_bin(to_file.c_str(), data, size);
}

void spec::save_bin(const char *file_name, const char *data, int size)
{
  std::ofstream fout(file_name, std::ios::out | std::ios::binary);
  fout.write(data, size);
  fout.close();
  return;
}

std::vector<char> spec::read_bin(const char *file_name)
{
  if (std::ifstream is{ file_name, std::ios::binary | std::ios::ate })
  {
    auto size = is.tellg();
    std::vector<char> vec(static_cast<size_t>(size)); // construct string to stream size
    is.seekg(0);
    if (is.read(&vec[0], size))
    {
      return vec;
    }
  }
  return std::vector<char>();
}


std::string spec::read_text(const char *file_name)
{
  std::string  str;
  if (fs::exists(file_name)) {
    std::ifstream  t(file_name);
    t.seekg(0, std::ios::end);
    str.reserve(static_cast<size_t>(t.tellg()));
    t.seekg(0, std::ios::beg);
    str.assign((std::istreambuf_iterator<char>(t)),
      std::istreambuf_iterator<char>());
  }
  return str;
}

void spec::save_text(const std::string &dir, const char *file_name, const std::string &text)
{
  fs::create_directories(dir);
  std::string to_file(dir);
  to_file.append(file_name);//.append(".txt");
  std::ofstream outfile(to_file);
  outfile.write(text.c_str(), text.length());
  outfile.close();
} //save_text

bool spec::save_text(const char *file_name, const std::string &text)
{
  std::ofstream outfile(file_name);
  outfile.write(text.c_str(), text.length());
  outfile.flush();
  bool re = !outfile.bad();
  outfile.close();
  return re;
}

void spec::save_text_append(const std::string &dir, const char *file_name, const std::string &text)
{
  fs::create_directories(dir);
  std::string to_file(dir);
  to_file.append(file_name);//.append(".txt");
  //std::ofstream  outfile(to_file);
  std::ofstream outfile;
  outfile.open(to_file, std::ios_base::app);
  outfile.write(text.c_str(), text.length());
  outfile.close();
} //save_text

void spec::save_text_append(const char *file_name, const std::string &text)
{
  std::ofstream outfile;
  outfile.open(file_name, std::ios_base::app);
  outfile.write(text.c_str(), text.length());
  outfile.close();
}
