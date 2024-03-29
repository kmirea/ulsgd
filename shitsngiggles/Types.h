/* 
 * File:   Types.h
 * Author: chris
 *
 * Created on September 13, 2009, 5:12 PM
 */

#ifndef _SRL_TYPES_H
#define	_SRL_TYPES_H

#include <stdlib.h>
#include <stdint.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <stack>
#include <queue>

#define OPTIONHEADERTYPE u8

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::flush;
using std::vector;
using std::ios;
using std::ifstream;
using std::ofstream;
using std::fstream;
using std::string;
using std::istream;
using std::ostream;
using std::stringstream;
using std::map;
using std::stack;
using std::queue;

typedef char c8;
typedef unsigned char u8;

#define C8_MIN -128
#define C8_MAX 127
#define C8_MAX_ARRAY 256
#define U8_MIN 0
#define U8_MAX 255
#define U8_MAX_ARRAY 256

typedef short s16;
typedef unsigned short u16;

#define S16_MIN -32768
#define S16_MAX 32767
#define S16_MAX_ARRAY 65536
#define U16_MIN 0
#define U16_MAX 65535
#define U16_MAX_ARRAY 65536

typedef int s32;
typedef unsigned int u32;

#define S32_MIN -2147483648
#define S32_MAX 2147483647
#define S32_MAX_ARRAY 4294967296
#define U32_MIN 0
#define U32_MAX 4294967295
#define U32_MAX_ARRAY 4294967296

typedef unsigned long ptr;

#if defined(_MSC_VER)
typedef __int64 s64;
typedef unsigned __int64 u64;
#elif defined(__GNUC__)
typedef int64_t s64;
typedef uint64_t u64;
#endif

#define S64_MIN -9223372036854775808
#define S64_MAX 9223372036854775807
#define S64_MAX_ARRAY 18446744073709551616
#define U64_MIN 0
#define U64_MAX 18446744073709551615
#define U64_MAX_ARRAY 18446744073709551615

typedef float f32;
typedef double f64;
typedef long double fext;


// Used to automatially set pointers to NULL to have consistent value checking
template< typename T >
struct tptr
{
    T PTR;
    tptr(const T& Data = NULL):PTR(Data) {}
    tptr( const tptr<T>& other ):PTR(other.PTR) {}
    
    bool operator < (const tptr& other ) const { return (ptr)PTR < (ptr)other.PTR; }
    bool operator <= ( const tptr& other ) const { return (ptr)PTR <= (ptr)other.PTR; }
    bool operator > ( const tptr& other ) const { return (ptr)PTR > (ptr)other.PTR; }
    bool operator >= ( const tptr& other ) const { return (ptr)PTR >= (ptr)other.PTR; }
    bool operator == (const tptr& other ) const { return (ptr)PTR == (ptr)other.PTR; }
    bool operator != (const tptr& other ) const { return (ptr)PTR != (ptr)other.PTR; }

    bool operator < (const T& other ) const { return PTR < other; }
    bool operator <= (const T& other ) const { return PTR <= other; }
    bool operator > (const T& other ) const { return PTR > other; }
    bool operator >= (const T& other ) const { return PTR >= other; }
    bool operator == (const T& other ) const { return PTR == other; }
    bool operator != ( const T& other ) const { return PTR != other; }

    tptr<T>& operator= ( const tptr<T>& o ) { PTR = o.PTR; return *this; }
    tptr<T>& operator= ( T& o ) { PTR = o; return *this; }

    T *operator->() const { return PTR; }
};

class TimerObject
{
	timeval start_time, end_time, tick_time;
public:
	ptr start_timer();
	ptr stop_timer();
	ptr tick();
	ptr get_start_time() const;
	ptr get_end_time() const;
};

#endif	/* _SRL_TYPES_H */

