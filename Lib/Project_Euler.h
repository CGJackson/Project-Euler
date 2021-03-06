#ifndef PROJECT_EULER_HEADER_FILE
#define PROJECT_EULER_HEADER_FILE

// Contains common function for Project Euler problems

#include <vector>
#include <set>
#include <utility>
#include <optional>


namespace project_euler {

    template<typename T>
    inline T signum(T x){
        return (T(0) < x) - (x < T(0));
    }

    template<typename IntType>
    inline std::set<IntType> primes_to_100(){ return std::set<IntType> {2,3,5,7,11,
                                                                              13,17,19,23,29,
                                                                              31,37,41,43,47,
                                                                              53,59,61,67,71,
                                                                              73,79,83,89,97};
                                }
    
    // Returns a set of the prime numbers up to n
    std::set<int> primes_to_n_set(int n);

    std::set<long int> primes_to_n_set(long int n);

    std::set<long long int> primes_to_n_set(long long int n);

    std::set<unsigned> primes_to_n_set(unsigned n);

    std::set<long unsigned> primes_to_n_set(long unsigned n);

    std::set<long long unsigned> primes_to_n_set(long long unsigned n);

    // Returns a vector of the prime numbers up to n
    // exists to support legacy code. New code should use the set versions
    
    std::vector<int> primes_to_n(int n);

    std::vector<long int> primes_to_n(long int n);

    std::vector<long long int> primes_to_n(long long int n);

    std::vector<unsigned> primes_to_n(unsigned n);

    std::vector<long unsigned> primes_to_n(long unsigned n);

    std::vector<long long unsigned> primes_to_n(long long unsigned n);

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

    std::optional<int> isqrt(int n);

    std::optional<long int> isqrt(long int n);

    std::optional<long long int> isqrt(long long int n);

    std::optional<short int> isqrt(short int n);

    std::optional<unsigned> isqrt(unsigned n);

    std::optional<unsigned long> isqrt(unsigned long n);

    std::optional<unsigned long long> isqrt(unsigned long long n);

    std::optional<unsigned short> isqrt(unsigned short n);

    std::tuple<int,int,int> extended_gcd(int a, int b);

    std::tuple<long int, long int, long int> extended_gcd(long int a, long int b);

    std::tuple<long long int, long long int, long long int> extended_gcd(long long int a, long long int b);

    std::tuple<unsigned, unsigned, unsigned> extended_gcd(unsigned a, unsigned b);

    std::tuple<long unsigned, long unsigned, long unsigned> extended_gcd(long unsigned a, long unsigned b);

    std::tuple<long long unsigned, long long unsigned, long long unsigned> extended_gcd(long long unsigned a, long long unsigned b);
}

#include "Pythagorean_Triples.h"

#endif
