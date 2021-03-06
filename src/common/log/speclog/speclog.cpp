/*
 * This is the source code of SpecNet project
 * It is licensed under MIT License.
 *
 * Copyright (c) Dmitriy Bondarenko
 * feel free to contact me: specnet.messenger@gmail.com
 */

#include "speclog.h"

#include <sstream>
#include <iomanip>
#include <ctime>
#include <thread>
#include <iostream>

#if defined(Windows)
#define snprintf sprintf_s
#endif

#include "file/fileadapter.h"
#include "tools/specstatic.h"

SpecLog::SpecLog(bool in_cout_to_log, std::shared_ptr<ConfigJSON> in_config)
  : config(in_config), cout_to_log(in_cout_to_log)
{

}

bool  SpecLog::start()
{
  started  =  false;
    //faux loop
  do  {      
    const std::string  &fullPath  =
        spec::toFullPath(
          config->getStringValue("LogPath").c_str(),
          config->exec_dir
          );
    auto  len  =  fullPath.length();
    if  (len  <  5)  {  break;  }
    const std::string  &dirPath  =  spec::getDir(fullPath);
    fs::create_directories(dirPath);
    long long  max_file_size  =  1024  *  1024
        *  config->getLongValue("LogSizeMB");
    if  (max_file_size  <=  0)  {
      max_file_size  =  1048576  *  5;  //  5 MB
        }
    long long  max_files  =  config->getLongValue("LogFiles");
    if  (max_files  <=  0)  {
      max_files  =  3;
    }
    {
      std::lock_guard<std::timed_mutex>  raii(loglock);
      logPathDir  =  dirPath;
      if  (fullPath.compare(len-5,  4,  ".txt"))  {
        logPathBase  =  fullPath.substr(0,  len  -  4);
      }  else  {
        logPathBase  =  fullPath;
      }
      logFiles  =  max_files;
      maxLogSize  =  max_file_size;
      openNextLog();
    }
    started  =  true;
  }  while  (false);
  return started;
}  //  start

void  SpecLog::closeLog()  {
  try  {
    logfs.close();
    curLogSize  =  0;
  }  catch  (...)  {  }
}

void  SpecLog::openNextLog()  {
  std::string  fileName  =  logPathBase;
  try  {
    closeLog();
        //Delete old files
    spec::del_old_files(logPathDir,  logFiles  -  1);
        //Open new Log file:
    std::string  strTime;
    strTime.reserve(24);
    strTime.resize(24);
    std::time_t  t  =  std::time(nullptr);
    auto  szTime  =  std::strftime(&strTime.front(),  24,  "%Y-%m-%d_%H-%M-%S",  std::localtime(&t));
    strTime.resize(szTime);
    fileName.append(strTime).append(".txt");
    logfs.open(fileName,  std::ofstream::out);
  }  catch  (...)  {
    std::cout  <<  "Error SpecLog::openNextLog() opening file:"  <<  fileName;
  }
}

void  SpecLog::stop()  {
  std::lock_guard<std::timed_mutex>  raii(loglock);
  closeLog();
  started = false;
}

void  SpecLog::rawCout(const char  *lvl, const std::string &str)
{
  if (started && cout_to_log)  {
    rawLog(lvl, str);
  }  else  {
    if  (!str.empty())  {
      std::time_t  t  =  std::time(nullptr);
      std::tm  tm  =  *std::localtime(&t);
      if  (loglock.try_lock_for(std::chrono::milliseconds(DEADLOCK_TIME)))
      {
        std::cout << std::put_time(&tm, "[%Y-%m-%d %H:%M:%S][")
                  <<  lvl  <<  "]["  << std::this_thread::get_id()  << "]:"
                  <<  str <<  std::endl;
        loglock.unlock();
      }  // if mutex
    }  // if str !empty
  }
}

void  SpecLog::rawLog(const char  *lvl,  const std::string  &str)  {
  if  (!str.empty())  {
    std::time_t  t  =  std::time(nullptr);
    std::tm  tm  =  *std::localtime(&t);
    std::stringstream  ss;
    ss  <<  std::put_time(&tm, "[%Y-%m-%d %H:%M:%S][")
      <<  lvl  <<  "]["  << std::this_thread::get_id()  << "]:"
      <<  str <<  std::endl;
    const std::string  &toLog  =  ss.str();
    auto  len  =  toLog.length();
    if  (loglock.try_lock_for(std::chrono::milliseconds(DEADLOCK_TIME)))
    {
      if (started)
      {
        try  {
          curLogSize  +=  len;
          if  (curLogSize  >  maxLogSize)  {
            openNextLog() ;
          }
          if  (logfs.is_open())  {
            logfs  <<  toLog;
  #ifdef DDEBUG
            logfs.flush();
  #endif
          }
        }  catch(...)  {  }
      }
      loglock.unlock();
    }  // if mutex
  }  // if str !empty
}  //  rawLog
