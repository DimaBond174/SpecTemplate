
//this is for DLL_PUBLIC __attribute__ ((dllexport)):
#define  BUILDING_TESTCLIENT
#include "testclient.h"

void function(int a)
{
  return;
}

TestClient::TestClient()
{

}

void TestClient::foo(int a)
{
    return;
}

int TestClient::getResult(int b)
{
    return b * b;
}

void TestClient::privateMethod()
{
    return;
}
