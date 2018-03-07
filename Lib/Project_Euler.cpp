// A Library containing common functions for Project Euler problems

// Contents:
//  primes_to_n(n): returns a vector of all the prime numbers less than or 
//                  equal to n
//  isqrt(n): returns the integer square root of n or -1 if n is not a 
//                  square number.
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


    #define isqrt_return_on_failure -1

    template<typename intType>
    intType isqrt_template(const intType n){
        if(n == 0)
            return 0;
        if(n == 1)
            return 1;

        int bits_in_n = 1;
        intType x = n, t;
        while(x >>= 1){
            ++bits_in_n;
        }
        x = 1 << (bits_in_n/2);
        if(x*x == n){
            return x;
        }

        intType upper_bound = x, lower_bound = x;
        if(x*x > n){
            lower_bound >>= 1;
            while(lower_bound*lower_bound > n){
                upper_bound >>=1;
                lower_bound >>=1;
            }
            
        }
        else{
            upper_bound <<= 1;
            while(upper_bound*upper_bound < n){
                upper_bound <<= 1;
                lower_bound <<=1;
                
            }
                
        }
        x = (upper_bound+lower_bound) >> 1;
        while(upper_bound-lower_bound > 1){
            t = x*x; 
            if(t == n)
                return x;
            else if(t > n){
                upper_bound = x;
            }
            else {
                lower_bound = x;
            }
            x = (upper_bound + lower_bound) >> 1;
        }
        return isqrt_return_on_failure;
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

int project_euler::isqrt(int n){
    return project_euler_internal::isqrt_template(n);
}

long int project_euler::isqrt(long int n){
    return project_euler_internal::isqrt_template(n);
}

long long int project_euler::isqrt(long long int n){
    return project_euler_internal::isqrt_template(n);
}

short int project_euler::isqrt(short int n){
    return project_euler_internal::isqrt_template(n);
}

unsigned project_euler::isqrt(unsigned n){
    return project_euler_internal::isqrt_template(n);
}

unsigned long project_euler::isqrt(unsigned long n){
    return project_euler_internal::isqrt_template(n);
}

unsigned long long project_euler::isqrt(unsigned long long n){
    return project_euler_internal::isqrt_template(n);
}


unsigned short project_euler::isqrt(unsigned short n){
    return project_euler_internal::isqrt_template(n);
}
