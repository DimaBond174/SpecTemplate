/*
 * This is the source code of SpecNet project
 *
 * Copyright (c) Dmitriy Bondarenko
 * feel free to contact me: specnet.messenger@gmail.com
 */

#include "configjson.h"
#include "file/fileadapter.h"
#include "tools/specstatic.h"

ConfigJSON::ConfigJSON()
{}

ConfigJSON::ConfigJSON(
    const std::string& in_exec_dir,
                       FDefConfig in_FDefConfig)
  : fDefConfig(in_FDefConfig), exec_dir (in_exec_dir)
{
  
}

void  ConfigJSON::traverse(TNode  *node) {
  TNode  *cur = node;
  while (cur) {
    switch (cur->type) {
    case 's':
    case 'd':
      if (cur->lenKey>0 && cur->lenData>0) {
        mapConfig.insert(std::make_pair(
          std::string(cur->pKey, cur->lenKey),
          std::string(static_cast<const char *>(cur->pData), cur->lenData)));
      }
      break;
    case 'o':
      traverse(cur);
      break;
    case 'a':

      break;
    default:
      //std::cerr << "Error: ConfigJson::TNode->type=" << cur->type << std::endl;
      break;
    }
    cur = cur->nextNode;
  }
}

bool ConfigJSON::setPath(const std::string& in_jsonPath)
{
  isValid = false;
  jsonPath = spec::toFullPath(in_jsonPath, exec_dir);
  try {
    const std::string &json = spec::read_text(jsonPath.c_str());
    int len = static_cast<int>(json.length());
    if (len > 3)
    {
      mapConfig.clear();
      SpecJson  specJson(json.c_str(), json.length(), false);
      if (specJson.parse()) {
        traverse(specJson.getFirstNode());
        isValid = true;
      }
    }    
  } catch(...) {}
  return isValid;
}

void ConfigJSON::setDefConfig(FDefConfig in_FDefConfig)
{
  fDefConfig = in_FDefConfig;
}

void ConfigJSON::saveToJSON()
{
  if (isValid && mapConfig.size())
  {
    std::string json("{");
    for (auto &&it : mapConfig)
    {
      json.append("\"").append(it.first).append("\":\"")
        .append(it.second).append("\",");
    }
    json[json.length()-1] = '}';
    spec::save_text(jsonPath.c_str(), json);
  }
}

std::string  ConfigJSON::getStringValue(const std::string  &key) {
  auto&&  it_exists = mapConfig.find(key);
  if (it_exists != mapConfig.end()) {
    return  it_exists->second;
  } else {
    return  fDefConfig(key.c_str());
  }
}

long long  ConfigJSON::getLongValue(const std::string  &key) {
  const std::string  &strVal = getStringValue(key);
  long long  re = 0;
  int  len = strVal.length();
  if (len  >  0) {
    re = stoll(strVal.c_str(), len);
  }
  return re;
}

int  ConfigJSON::getIntValue(const std::string  &key)
{
  return static_cast<int>(getLongValue(key));
}

void ConfigJSON::setValue(const std::string &key, const std::string &value)
{
  auto res = mapConfig.emplace(std::make_pair(key, value));
  if (!res.second) mapConfig[key] = value;
  isValid = true; 
  return;
}
