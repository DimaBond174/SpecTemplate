/*
 * This is the source code of SpecNet project
 * It is licensed under MIT License.
 *
 * Copyright (c) Dmitriy Bondarenko
 * feel free to contact me: specnet.messenger@gmail.com
 */

#ifndef SPECSTATIC_H
#define SPECSTATIC_H

#include <limits.h>
#include <stdint.h>
#include <cstddef>
#include <string>
#include <utility>
#include <array>

/* SpecNet const: */
#define  GUID_LEN  19
#define  SMAX_GROUPS  100
#define  SMAX_PATH  300
#define  MIN_GUID  1000000000000000000
#define  MAX_SelectRows  50

//uint32                  4294967295
//max                     2147483647
#define SERV_TYPE  1923082018
#define CLI_TYPE    1924082018

/* default times in ms: */
#define  DEADLOCK_TIME  5000
#define  WAIT_TIME  100
constexpr  int64_t  DAY_MILLISEC  =  24  *  60  *  60  *  1000;

/* default array sizes in bytes: */
#define  EPOLL_WAIT_POOL  21
#define  BUF_SIZE  4096

//until about the month counter % 12:
#define  TO12(x)  ((((x)>>31)%12))

/*  Converts string to number
  first  -  poiner to the first character
  len - expected length, its OK if string ends earlier
 */
inline  int64_t  stoll(const char  *first,  int  len)  {
  if (len  >  GUID_LEN)  {
    len  =  GUID_LEN;
  }
  const char  *last  =  first  +  len;
  uint64_t  re  = 0ULL; //  18 446 744 073 709 551 615 = 20
  for (const char *ch  =  first;  *ch  &&  ch<last;  ++ch)  {
    if  (*ch<'0'  ||  *ch>'9')  {  break;  }
      re  =  10 * re  +  *ch  -  '0';
    }
    return  (re  >  LLONG_MAX)?  LLONG_MAX  :  re;
}

/* Prints chars to the string buffer.
  Used for quickly build strings.
  str - chars to be printed
  start - string buffer
  end - end of the string buffer, must be valid for change
*/
inline char  *  printString(const char  *str,  char  *start,  char  *end){
  while  (*str  &&  start < end)  {
    *start  =  *str;
    ++start;
    ++str;
  }
    //if (start<end) { *start =0; }
  *start  =  0;  //  *end must be valid for change
  return start;
}

/* Prints uint64_t to the string buffer.
  Used for quickly build strings.
  n - uint64_t to be printed
  start - string buffer
  end - end of the string buffer, must be valid for change
*/
inline char  *  printULong(uint64_t  n,  char  *start,  char  *end)  {
  if (0==n)  {
    *start ='0';
    ++start;
  }  else  {
    char  buf[24];
    char  *ch  =  buf;
    uint64_t  n1  =  n;
    while  (0!=n1)  {
      *ch  =  n1%10  +  '0';
      ++ch;
      n1  =  n1/10;
    }
    --ch;
    while  (ch>=buf  &&  start<end)  {
      *start  =  *ch;
      ++start;
      --ch;
    }
  }
    //if (start<end) { *start =0; }
  *start  =  0;  //  *end must be valid for change
  return start;
}

/* Constexpr exception free string class.
  Used for static const strings.
*/
class  ConstString  {
 public:
  template<std::size_t N>
  constexpr ConstString(const char (&str)[N])
    :  c_str(str),  size(N - 1) {
  }

  constexpr char operator[](std::size_t  n) {
    return  (n < size)?  c_str[n]  :  '\0';
  }

  char const  *const  c_str;
  //const std::size_t size;
  //const int  size; //SQLite wants int
  const uint32_t  size;
};

///////////////////////////////////////////////////////////////////
/* consexpr unsigned char */
template<unsigned...>struct seq{using type=seq;};
template<unsigned N, unsigned... Is>
struct gen_seq_x : gen_seq_x<N-1, N-1, Is...>{};
template<unsigned... Is>
struct gen_seq_x<0, Is...> : seq<Is...>{};
template<unsigned N>
using gen_seq=typename gen_seq_x<N>::type;

template<size_t S>
using size=std::integral_constant<size_t, S>;

template<class T, size_t N>
constexpr size<N> length( T const(&)[N] ) { return {}; }
template<class T, size_t N>
constexpr size<N> length( std::array<T, N> const& ) { return {}; }

template<class T>
using length_t = decltype(length(std::declval<T>()));

constexpr size_t string_size() { return 0; }
template<class...Ts>
constexpr size_t string_size( size_t i, Ts... ts ) {
  return (i?i-1:0) + string_size(ts...);
}
template<class...Ts>
using string_length=size< string_size( length_t<Ts>{}... )>;

template<class...Ts>
using combined_ustring = std::array<unsigned char, string_length<Ts...>{}+1>;

template<class Lhs, class Rhs, unsigned...I1, unsigned...I2>
constexpr const combined_ustring<Lhs,Rhs>
uconcat_impl( Lhs const& lhs, Rhs const& rhs, seq<I1...>, seq<I2...>)
{
    return {{ (unsigned char)lhs[I1]..., (unsigned char)rhs[I2]..., (unsigned char)('\0') }};
}

template<class Lhs, class Rhs>
constexpr const combined_ustring<Lhs,Rhs>
uconcat(Lhs const& lhs, Rhs const& rhs)
{
    return uconcat_impl(lhs, rhs, gen_seq<string_length<Lhs>{}>{}, gen_seq<string_length<Rhs>{}>{});
}

template<class T0, class T1, class... Ts>
constexpr const combined_ustring<T0, T1, Ts...>
uconcat(T0 const&t0, T1 const&t1, Ts const&...ts)
{
    return uconcat(t0, uconcat(t1, ts...));
}

template<class T>
constexpr const combined_ustring<T>
uconcat(T const&t) {
    return uconcat(t, "");
}
constexpr const combined_ustring<>
uconcat() {
    return uconcat("");
}


/*
 * usage:
 * template<typename T>
    class TD;
int main()
{
  {
    // works
    auto constexpr text = uconcat("hi", " ", "there!");
    std::cout << text.data();
    std::cout << text.size();
    TD<decltype(text)> xType;
  }
*/
///////////////////////////////////////////////////////////////////
/* consexpr char */
template<class...Ts>
using combined_string = std::array<char, string_length<Ts...>{}+1>;

template<class Lhs, class Rhs, unsigned...I1, unsigned...I2>
constexpr const combined_string<Lhs,Rhs>
concat_impl( Lhs const& lhs, Rhs const& rhs, seq<I1...>, seq<I2...>)
{
    return {{ lhs[I1]..., rhs[I2]..., '\0' }};
}

template<class Lhs, class Rhs>
constexpr const combined_string<Lhs,Rhs>
concat(Lhs const& lhs, Rhs const& rhs)
{
    return concat_impl(lhs, rhs, gen_seq<string_length<Lhs>{}>{}, gen_seq<string_length<Rhs>{}>{});
}

template<class T0, class T1, class... Ts>
constexpr const combined_string<T0, T1, Ts...>
concat(T0 const&t0, T1 const&t1, Ts const&...ts)
{
    return concat(t0, concat(t1, ts...));
}

template<class T>
constexpr const combined_string<T>
concat(T const&t) {
    return concat(t, "");
}
constexpr const combined_string<>
concat() {
    return concat("");
}

//template<typename A, typename B>
//constexpr auto
//test1(const A& a, const B& b)
//{
//  return concat(a, b);
//}
/*
 * usage:
 * template<typename T>
    class TD;
int main()
{
  {
    // works
    auto constexpr text = concat("hi", " ", "there!");
    std::cout << text.data();
    std::cout << text.size();
    TD<decltype(text)> xType;
  }
*/
///////////////////////////////////////////////////////////////////

#define CONCATE_(X,Y) X##Y
#define CONCATE(X,Y) CONCATE_(X,Y)
#define UNIQUE(NAME) CONCATE(NAME, __LINE__)

struct Static_
{
  template<typename T> Static_ (T lambda) { lambda(); }
  ~Static_ () {}  // to counter unused variable warning
};

#define STATIC static Static_ UNIQUE(block) = [&]() -> void

#endif // SPECSTATIC_H
