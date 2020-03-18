/*
 * This is the source code of SpecNet project
 *
 * Copyright (c) Dmitriy Bondarenko
 * feel free to contact me: specnet.messenger@gmail.com
 */

#ifndef ConfigJSON_H
#define ConfigJSON_H
#pragma once
#include <functional>
#include <string>
#include <map>
#include "tools/specjson.h"


using FDefConfig = std::function<std::string(const std::string &)>;

struct ConfigJSON
{
  bool isValid  { false };
  long long  getLongValue(const std::string  &key)  ;
  int  getIntValue(const std::string  &key);
  std::string  getStringValue(const std::string  &key)  ;
  void setValue(const std::string &key, const std::string &value);

  ConfigJSON();
  ConfigJSON(const std::string& in_exec_dir,
             FDefConfig in_FDefConfig);
  virtual ~ConfigJSON() {}

  bool setPath(const std::string& in_jsonPath);
  void setDefConfig(FDefConfig in_FDefConfig);
  virtual void saveToJSON();

  std::string exec_dir;

  FDefConfig fDefConfig;  
  std::string  jsonPath;

  std::map<std::string, std::string>  mapConfig;
  
protected:
  virtual void  traverse(TNode  *node);
};

#endif //ConfigJSON_H
