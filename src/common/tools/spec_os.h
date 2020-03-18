#ifndef SPEC_OS_H
#define SPEC_OS_H
#include "specstack.h"
#include <string>
#include "specstatic.h"


namespace spec {

//struct IPackPromise {
//  std::vector<unsigned char> data;
//  std::promise<std::vector<unsigned char>> prom;
//  IPack  *nextIStack;
//};

constexpr bool isLinux();

//current time in milliseconds:
long long curTimeMs();

bool isEqual(const std::string &lh, unsigned char *rh_data, uint32_t rh_size);
bool isEqualC(const ConstString &lh, unsigned char *rh_data, uint32_t rh_size);
bool isEqual(const ConstString &lh, const std::string &rh);
} // spec
#endif // SPEC_OS_H
