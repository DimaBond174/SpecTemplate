/*
 * This is the source code of SpecNet project
 * It is licensed under MIT License.
 *
 * Copyright (c) Dmitriy Bondarenko
 * feel free to contact me: specnet.messenger@gmail.com
 */

#ifndef SPECLOG_H
#define SPECLOG_H

#include "i/ilog.h"
#include <fstream>
#include <mutex>
#include "config/json/configjson.h"
#include <memory>

class SpecLog  :  public ILog  {
 public:
  SpecLog(bool in_cout_to_log, std::shared_ptr<ConfigJSON> in_config);
  bool  start()  override;
  void  stop()  override;
  void  rawLog(const char  *lvl, const std::string &str)  override;
  void  rawCout(const char  *lvl, const std::string &str)  override;
 private:
  std::shared_ptr<ConfigJSON> config;
  std::timed_mutex  loglock;
    /* Protected by loglock: */
  long long  maxLogSize  =  0ll;
  long long  logFiles  =  0ll;
  std::string  logPathBase;
  std::string  logPathDir;
  long long  curLogSize = 0ll;
  std::ofstream  logfs;
  bool cout_to_log;
  bool started = false;

  void  openNextLog();
  void  closeLog();
    /*  \loglock  */
};

#endif // SPECLOG_H
