#ifndef PROJECT_EULER_HEADER_FILE
#define PROJECT_EULER_HEADER_FILE

// Contains common function for Project Euler problems

#include <vector>
#include <utility>


namespace project_euler {

    template<typename T>
    inline T signum(T x){
        return (T(0) < x) - (x < T(0));
    }

    template<typename IntType>
    inline std::vector<IntType> primes_to_100(){ return std::vector<IntType> {2,3,5,7,11,
                                                                              13,17,19,23,29,
                                                                              31,37,41,43,47,
                                                                              53,59,61,67,71,
                                                                              73,79,83,89,97};
                                }

    std::vector<int> primes_to_n(const int n);

    std::vector<long int> primes_to_n(const long int n);

    std::vector<long long int> primes_to_n(const long long int n);

    std::vector<unsigned> primes_to_n(const unsigned n);

    std::vector<long unsigned> primes_to_n(const long unsigned n);

    std::vector<long long unsigned> primes_to_n(const long long unsigned n);

    int prime_counting_function(int);

    long prime_counting_function(long);

    long long prime_counting_function(long long);

    unsigned prime_counting_function(unsigned);

    long unsigned prime_counting_function(long unsigned);

    long long unsigned prime_counting_function(long long unsigned);

//    std::vector<std::pair<int,int>> prime_factors(int, const vector<int>&);
//
//    std::vector<std::pair<int,int>> prime_factors(int);
//
//    std::vector<std::pair<long,long>> prime_factors(long, const vector<long>&);
//
//    std::vector<std::pair<long,long>> prime_factors(long);
//
//    std::vector<std::pair<long long,long long>> prime_factors(long long, const vector<long long>&);
//
//    std::vector<std::pair<long long,long long>> prime_factors(long long);
//
//    std::vector<std::pair<unsigned,unsigned>> prime_factors(unsigned, const vector<unsigned>&);
//
//    std::vector<std::pair<unsigned,unsigned>> prime_factors(unsigned);
//
//    std::vector<std::pair<unsigned long,unsigned long>> prime_factors(unsigned long, const vector<unsigned long>&);
//
//    std::vector<std::pair<unsigned long,unsigned long>> prime_factors(unsigned long);
//
//    std::vector<std::pair<unsigned long long,unsigned long long>> prime_factors(unsigned long long, const vector<unsigned long long>&);
//
//    std::vector<std::pair<unsigned long long,unsigned long long>> prime_factors(unsigned long long);

    int ipow(int base, unsigned exp);

    int ipow(int base, int exp);

    long ipow(long base, unsigned long exp);

    long ipow(long base, long exp);

    long long ipow(long long base, unsigned long long exp);

    long long ipow(long long base, long long exp);

    unsigned ipow(unsigned base, unsigned exp);

    unsigned long ipow(unsigned long base, unsigned long exp);

    unsigned long long ipow(unsigned long long base, unsigned long long exp);

    int isqrt(int n);

    long int isqrt(long int n);

    long long int isqrt(long long int n);

    short int isqrt(short int n);

    unsigned isqrt(unsigned n);

    unsigned long isqrt(unsigned long n);

    unsigned long long isqrt(unsigned long long n);

    unsigned short isqrt(unsigned short n);

    std::tuple<int,int,int> extended_gcd(int a, int b);

    std::tuple<long int, long int, long int> extended_gcd(long int a, long int b);

    std::tuple<long long int, long long int, long long int> extended_gcd(long long int a, long long int b);

    std::tuple<unsigned, unsigned, unsigned> extended_gcd(unsigned a, unsigned b);

    std::tuple<long unsigned, long unsigned, long unsigned> extended_gcd(long unsigned a, long unsigned b);

    std::tuple<long long unsigned, long long unsigned, long long unsigned> extended_gcd(long long unsigned a, long long unsigned b);
}

#include "Pythagorean_Triples.h"

#endif
