#ifndef PROJECT_EULER_HEADER_FILE
#define PROJECT_EULER_HEADER_FILE

// Contains common function for Project Euler problems

#include <vector>
#include <cstddef>

namespace project_euler {

    // Returns a vecotr of the prime numbers up to n
    
    std::vector<int> primes_to_n(const int n);

    std::vector<long int> primes_to_n(const long int n);

    std::vector<long long int> primes_to_n(const long long int n);

    std::vector<unsigned> primes_to_n(const unsigned n);

    std::vector<long unsigned> primes_to_n(const long unsigned n);

    std::vector<long long unsigned> primes_to_n(const long long unsigned n);

    // isqrt returns the integer square root of a number, or -1 if the number 
    // is not square
    //
    // For unsigned types in the case of a non-sqare number, isqrt still 
    // returns -1, whih is converted to the maximum size for that type
    // due to the underflow behaviour of unsigned types. This is a safe
    // return value as for x > 1, sqrt(x) < x < MAX_VAL, and MAX_VAL > 1
    // so no number of a given type can have a sqrt of the largest value 
    // for that type.
    
    int isqrt(int n);

    long int isqrt(long int n);

    long long int isqrt(long long int n);

    short int isqrt(short int n);
    
    unsigned isqrt(unsigned n);

    unsigned long isqrt(unsigned long n);

    unsigned long long isqrt(unsigned long long n);

    unsigned short isqrt(unsigned short n);
}
#endif
