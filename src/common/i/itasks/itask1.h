#ifndef ITASK1_H
#define ITASK1_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*
 * Get RGB888 image from file
*/
struct ITask1
{
  char filename[512];

  // For protect:
  int  guard; // 16122019

  // Standard:
  static bool isValid(ITask1 *ptr)  {
    if (ptr && 16122019 == ptr->guard) return true;
    return false;
  }

  static ITask1 * newObj(const char *path)  {
      ITask1 *re = static_cast<ITask1 *>(malloc(sizeof(ITask1)));
      memset(re, 0, sizeof(ITask1));
      snprintf ( re->filename, 512, path);
      re->guard = 16122019;
      return re;
  }

  static void  freeObj(ITask1 *ptr)  {
    if (isValid(ptr))
    {
      ptr->guard = 0;
      free(ptr);
    }
  }
};

struct ITask1_Result
{
  //https://stackoverflow.com/questions/5026965/how-to-convert-an-opencv-cvmat-to-qimage
  unsigned char * mat_data;
  int  mat_cols;
  int  mat_rows;

  // For protect:
  int  guard; // 17122019

  // Standard:
  static bool isValid(ITask1_Result *ptr)  {
    if (ptr && 17122019 == ptr->guard) return true;
    return false;
  }

  static ITask1_Result * newObj()  {
      ITask1_Result *re = static_cast<ITask1_Result *>(malloc(sizeof(ITask1_Result)));
      memset(re, 0, sizeof(ITask1_Result));
      re->guard = 17122019;
      return re;
  }

  static void  freeObj(ITask1_Result *ptr)  {
    if (isValid(ptr))
    {
      if (ptr->mat_data) free(ptr->mat_data);
      ptr->guard = 0;
      free(ptr);
    }
  }
};

#endif // ITASK1_H
