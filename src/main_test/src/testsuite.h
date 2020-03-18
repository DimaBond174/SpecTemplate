#ifndef TESTSUITE_H
#define TESTSUITE_H

#if defined _WIN32 || defined __CYGWIN__
  #ifdef BUILDING_TestSuite
    #ifdef __GNUC__
      #define DLL_PUBLIC __attribute__ ((dllexport))
    #else
      #define DLL_PUBLIC __declspec(dllexport) // Note: actually gcc seems to also supports this syntax.
    #endif
  #else
    #ifdef __GNUC__
      #define DLL_PUBLIC __attribute__ ((dllimport))
    #else
      #define DLL_PUBLIC __declspec(dllimport) // Note: actually gcc seems to also supports this syntax.
    #endif
  #endif
  #define DLL_LOCAL
#else
  #if __GNUC__ >= 4
    #define DLL_PUBLIC __attribute__ ((visibility ("default")))
    #define DLL_LOCAL  __attribute__ ((visibility ("hidden")))
  #else
    #define DLL_PUBLIC
    #define DLL_LOCAL
  #endif
#endif

/*
 * do_Test1
 *  returns 0 on success, or errorcode
 * -----------------------------------
 * Sending big file from client to client
*/
extern "C" DLL_PUBLIC int do_Test1();

//class DLL_PUBLIC TestSuite
// private class:
//class  TestSuite
//{
//public:
//  TestSuite();
//};

#endif // TESTSUITE_H
