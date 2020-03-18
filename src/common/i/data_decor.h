#ifndef Data_Decor_H
#define Data_Decor_H

#include <stdlib.h>
#include <string.h>

/*
  WARNING: all data types used must be:
    - allocated with malloc
    - deallocated with free
   no constructors, no destructors, simple types only.
*/

struct Data_Decor
{
  // Task (write for client, read only for worker):  
  void  *source_data;
  int  type;

  // Result (read/write for all):
  int  res;
  void  *res_data;

  // For SpecStack:
  Data_Decor  *nextIStack;

  // For protect:
  int  guard; // 15122019

  // Standard:
  static bool isValid(Data_Decor *ptr)  {
    if (ptr && 15122019 == ptr->guard) return true;
    return false;
  }

  static Data_Decor * newObj()  {
      Data_Decor *re = static_cast<Data_Decor *>(malloc(sizeof(Data_Decor)));
      memset(re, 0, sizeof(Data_Decor));
      re->guard = 15122019;
      return re;
  }

  static void  freeObj(Data_Decor *ptr)  {
    if (isValid(ptr))
    {
      if (ptr->source_data) {  free(ptr->source_data);  }
      if (ptr->res_data) {  free(ptr->res_data);  }
      ptr->guard = 0;
      free(ptr);
    }
  }
};
#endif //Data_Decor_H
