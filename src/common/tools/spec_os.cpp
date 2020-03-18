#include "spec_os.h"
#include <time.h>
#include <string.h>

#if defined(Linux)
constexpr bool spec::isLinux() { return  true; }

#elif defined(Windows)
constexpr bool spec::isLinux() { return  false; }

#endif

//current time in milliseconds:
long long spec::curTimeMs()
{
    struct timespec timeout;
    clock_gettime(CLOCK_REALTIME, &timeout);
    return timeout.tv_sec * 1000 + timeout.tv_nsec/1000000;
}

bool spec::isEqual(const ConstString &lh, const std::string &rh)
{
  const uint32_t  size = static_cast<uint32_t>(lh.size);
  if (size == rh.size())
  {
    return 0 == strncmp(lh.c_str, rh.c_str(), size);
  }
  return false;
}

bool spec::isEqual(const std::string &lh, unsigned char *rh_data, uint32_t rh_size)
{
  if (lh.size() == rh_size)
  {
    const unsigned char *lh_data = reinterpret_cast<const unsigned char *>(lh.data());
    for (uint32_t  i = 0; i < rh_size; ++i)
    {
      if (rh_data[i] != lh_data[i]) return false;
    }
    return true;
  }
  return false;
}

bool spec::isEqualC(const ConstString &lh, unsigned char *rh_data, uint32_t rh_size)
{
  if (static_cast<uint32_t>(lh.size) == rh_size)
  {
    const unsigned char *lh_data = reinterpret_cast<const unsigned char *>(lh.c_str);
    for (uint32_t  i = 0; i < rh_size; ++i)
    {
      if (rh_data[i] != lh_data[i]) return false;
    }
    return true;
  }
  return false;
} //isEqual
