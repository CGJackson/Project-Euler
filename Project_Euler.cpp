// A Library containing common functions for Project Euler problems

// Contents:
//  primes_to_n(n): returns a vector of all the prime numbers less than or 
//                  equal to n
//  gcd(m,n): returns the greatest common divisor of m and n

#include <vector>

#include "Project_Euler.h"

using std::vector;

namespace project_euler_internal {

    // Calculates a vector of all prime numbers <= n
    template <typename T>
    vector<T> primes_to_n_template(const T n){

        vector<bool> is_prime(n+1,true);

        vector<T> primes;

        if( n >= 2 ){
            is_prime[0] = false; // 0 and 1 are not prime
            is_prime[1] = false;
            primes.push_back(2);
            for(vector<bool>::iterator two_step = is_prime.begin();
                two_step < is_prime.end(); two_step += 2)
                *two_step = false;
        }
        else{
            return primes; //If n < 2 returns a empty vector
        }

        T i;
        for(i = 3; i*i <= n; i += 2){
            if( is_prime[i] ){
                primes.push_back(i);
                for(T j = 2*i; j < n; j += i)
                    is_prime[j] = false;
            }
        }    

        for(;i <= n; ++i)
            if( is_prime[i] )
                primes.push_back(i);

        return primes;
    }
};

vector<int> project_euler::primes_to_n(const int n){
        return project_euler_internal::primes_to_n_template(n);
    }

vector<long int> project_euler::primes_to_n(const long int n){
        return project_euler_internal::primes_to_n_template(n);
    }

vector<long long int> project_euler::primes_to_n(const long long int n){
        return project_euler_internal::primes_to_n_template(n);
    }

vector<unsigned> project_euler::primes_to_n(const unsigned n){
        return project_euler_internal::primes_to_n_template(n);
    }

vector<long unsigned> project_euler::primes_to_n(const long unsigned n){
        return project_euler_internal::primes_to_n_template(n);
    }

vector<long long unsigned> project_euler::primes_to_n(
                                                const long long unsigned n){
        return project_euler_internal::primes_to_n_template(n);
    }

