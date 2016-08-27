#ifndef PROJECT_EULER_HEADER_FILE
#define PROJECT_EULER_HEADER_FILE

// Contains common function for Project Euler problems

#include <vector>

namespace project_euler {

    std::vector<int> primes_to_n(const int n);

    std::vector<long int> primes_to_n(const long int n);

    std::vector<long long int> primes_to_n(const long long int n);

    std::vector<unsigned> primes_to_n(const unsigned n);

    std::vector<long unsigned> primes_to_n(const long unsigned n);

    std::vector<long long unsigned> primes_to_n(const long long unsigned n);

    int gcd(int n, int m);

    long int gcd(long int n, long int m);

    long long int gcd(long long int n,long long int m);

    unsigned gcd(unsigned n, unsigned m);

    long unsigned gcd(long unsigned n, long unsigned m);

    long long unsigned gcd(long long unsigned n,long long unsigned m);
}
#endif
