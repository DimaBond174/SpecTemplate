/*
 * This is the source code of SpecNet project
 * It is licensed under MIT License.
 *
 * Copyright (c) Dmitriy Bondarenko
 * feel free to contact me: specnet.messenger@gmail.com
 */

#ifndef IDataCallback_H
#define IDataCallback_H

#include "data_decor.h"

class  IDataCallback  {
 public:
  virtual ~IDataCallback()  {  }
  virtual void onCallResult(Data_Decor *result) = 0;
};
#endif // IDataCallback_H
