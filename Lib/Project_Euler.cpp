// A Library containing common functions for Project Euler problems

// Contents:
//  primes_to_n(n): returns a vector of all the prime numbers less than or 
//                  equal to n
//  isqrt(n): returns the integer square root of n or -1 if n is not a 
//                  square number.

#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <unordered_map>
#include <array>
#include <utility>
#include <stdexcept>
#include <boost/functional/hash.hpp>

#include "Project_Euler.h"

using std::vector;  using std::array;
using std::set;
using std::pair;    using std::unordered_map;

using project_euler::primes_to_100;

namespace project_euler_internal {

    // Calculates a vector of all prime numbers <= n
    template <typename T>
    set<T> primes_to_n_template(const T n, set<T>&& primes){
        if ( n < 2){
            return set<T>();
        }
        {
            auto p = primes.lower_bound(n);
            if(p != primes.end()){
                return set<T>{primes.begin(), ++p};
            }
        }

        if(primes.empty()){
            primes.emplace_hint(primes.end(),2);
        }

        T offset = *(--primes.end()) + 1;

        vector<bool> is_prime(n+1-offset,true);

        // removes multiples of all primes found so far
        for(auto p:primes){
            for(auto j = offset + p - (offset % p); j <= n; j+=p){
                is_prime[j-offset] = false;
            }
        }

        // Performs main sieve
        T i;
        for(i = offset + ((offset+1) % 2); i*i <= n; i += 2){
            if( is_prime[i-offset] ){
                primes.emplace_hint(primes.end(),i);
                for(T j = 2*i; j < n; j += i){
                    is_prime[j-offset] = false;
                }
            }
        }    

        // Once sieving is complete, adds primes > sqrt(n) to list of primes
        for(;i <= n; i += 2){
            if( is_prime[i-offset] ){
                primes.emplace_hint(primes.end(),i);
            }
        }

        return primes;
    }

    template<typename T>
    set<T> primes_to_n_template(const T n,const set<T>& primes){
        return primes_to_n_template(n, set<T>{primes});
    }

//    template<typename T>
//    vector<pair<T,T>> prime_factors_template(T n, const vector<T>& primes){
//        vector<pair<T,T>> factors();
//        for(auto p: primes){
//            if(n % p == 0){
//                factors.pushback(pair<T,T>(p,1))
//                n /= p
//                while(n % p == 0){
//                    ++(factors.back().second)
//                    n /= p
//                }
//                if(n == 1){
//                    return factors
//                }
//            }
//        }
//        throw std::logic_error(
//                "List of primes did not contain all prime factors of n")
//    }


    template<typename baseType, typename expType>
    baseType ipow_template(baseType base, expType exponent){
        baseType result = 1;
        while(exponent){
            if( exponent & 1){
                result *= base;
            }
            exponent >>= 1;
            base *= base;
        }
        return result;
    }

    #define isqrt_return_on_failure -1

    template<typename intType>
    std::optional<intType> isqrt_template(const intType n){
        if(n == 0)
            return std::optional(0);
        if(n == 1)
            return std::optional(1);

        int bits_in_n = 1;
        intType x = n, t;
        while(x >>= 1){
            ++bits_in_n;
        }
        x = 1 << (bits_in_n/2);
        if(x*x == n){
            return std::optional(x);
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
                return std::optional(x);
            else if(t > n){
                upper_bound = x;
            }
            else {
                lower_bound = x;
            }
            x = (upper_bound + lower_bound) >> 1;
        }
        return std::optional<intType>();
    }

    template<typename intType>
    std::tuple<intType, intType, intType> extended_gcd_template(intType a, intType b){
        if constexpr (std::is_signed<intType>()){
            constexpr intType INTTYPE_MIN = std::numeric_limits<intType>::min();
            if((a == INTTYPE_MIN && b == INTTYPE_MIN) || (a == INTTYPE_MIN && b == 0) || (a == 0 && b == INTTYPE_MIN)){
                throw std::overflow_error("greatest common divisor == -numeric_limits<intType>::min() > numeric_limits<intType>::max()");
            }
        }

        if(a == 0){
            if constexpr(std::is_unsigned<intType>::value){
                return std::make_tuple(b,0,1);
            }
            else{
                return std::make_tuple(std::abs(b),0,project_euler::signum(b));
            }
        }
        if(b == 0){
            if constexpr(std::is_unsigned<intType>::value){
                return std::make_tuple(a,0,1);
            }
            else{
                return std::make_tuple(std::abs(a),project_euler::signum(a),0);
            }
        }
        
        intType r_old,r_current;
        intType s_old,s_current;
        intType t_old,t_current;
        r_old = a;
        r_current = b;

        s_old = 1;
        s_current = 0;
        t_old = 0;
        t_current = 1;
        

        while(r_current){
            intType quotent = r_old / r_current;
            intType r_new = r_old % r_current;

            intType s_new = s_old - quotent * s_current;
            intType t_new = t_old - quotent * t_current;

            r_old = r_current;
            r_current = r_new;

            s_old = s_current;
            s_current = s_new;
            t_old = t_current;
            t_current = t_new;
        }
        
        if constexpr (std::is_signed<intType>::value){
            if (r_old < 0){
                r_old = -r_old;
                s_old = -s_old;
                t_old = -t_old;
            }
        }

        return std::make_tuple(r_old,s_old,t_old);
    }
};

// Functions that take advantage of the templates are written,
// ensuring that only typesafe versions are avalible in the header

set<int> project_euler::primes_to_n_set(const int n){
    return project_euler_internal::primes_to_n_template(n, primes_to_100<int>());
}

set<long int> project_euler::primes_to_n_set(const long int n){
    return project_euler_internal::primes_to_n_template(n, primes_to_100<long int>());
}

set<long long int> project_euler::primes_to_n_set(const long long int n){
    return project_euler_internal::primes_to_n_template(n, primes_to_100<long long int>());
}

set<unsigned> project_euler::primes_to_n_set(const unsigned n){
    return project_euler_internal::primes_to_n_template(n, primes_to_100<unsigned>());
}

set<long unsigned> project_euler::primes_to_n_set(const long unsigned n){
    return project_euler_internal::primes_to_n_template(n, primes_to_100<long unsigned>());
}

set<long long unsigned> project_euler::primes_to_n_set(
                                                const long long unsigned n){
    return project_euler_internal::primes_to_n_template(n, primes_to_100<long long unsigned>());
}

vector<int> project_euler::primes_to_n(const int n){
    auto p =  project_euler_internal::primes_to_n_template(n, primes_to_100<int>());
    return vector<int>(p.begin(), p.end());
}

vector<long int> project_euler::primes_to_n(const long int n){
    auto p = project_euler_internal::primes_to_n_template(n, primes_to_100<long int>());
    return vector<long int>(p.begin(), p.end());
}

vector<long long int> project_euler::primes_to_n(const long long int n){
    auto p = project_euler_internal::primes_to_n_template(n, primes_to_100<long long int>());
    return vector<long long int>(p.begin(), p.end());
}

vector<unsigned> project_euler::primes_to_n(const unsigned n){
    auto p = project_euler_internal::primes_to_n_template(n, primes_to_100<unsigned>());
    return vector<unsigned>(p.begin(), p.end());
}

vector<long unsigned> project_euler::primes_to_n(const long unsigned n){
    auto p = project_euler_internal::primes_to_n_template(n, primes_to_100<long unsigned>());
    return vector<long unsigned>(p.begin(), p.end());
}

vector<long long unsigned> project_euler::primes_to_n(
                                                const long long unsigned n){
    auto p = project_euler_internal::primes_to_n_template(n, primes_to_100<long long unsigned>());
    return vector<long long unsigned>(p.begin(), p.end());
}

//vector<pair<int,int>> project_euler::prime_factors(int n,const  vector<int>& primes){
//    return project_euler_internal::prime_factors_template(n,primes);
//
//vector<pair<int,int>> project_euler::prime_factors(int n){
//    return project_euler_internal::prime_factors_template(n,
//            project_euler::primes_to_n((int) std::sqrt((float) n)+1));
//}
//
//vector<pair<long,long>> project_euler::prime_factors(long n,const  vector<long>& primes){
//    return project_euler_internal::prime_factors_template(n,primes);
//
//vector<pair<long,long>> project_euler::prime_factors(long n){
//    return project_euler_internal::prime_factors_template(n,
//            project_euler::primes_to_n((long) std::sqrt((float) n)+1));
//}
//
//vector<pair<long long,long long>> project_euler::prime_factors(long long n,const  vector<long long>& primes){
//    return project_euler_internal::prime_factors_template(n,primes);
//
//vector<pair<long long,long long>> project_euler::prime_factors(long long n){
//    return project_euler_internal::prime_factors_template(n,
//            project_euler::primes_to_n((long long) std::sqrt((float) n)+1));
//}
//
//vector<pair<unsigned,unsigned>> project_euler::prime_factors(unsigned n,const  vector<unsigned>& primes){
//    return project_euler_internal::prime_factors_template(n,primes);
//
//vector<pair<unsigned,unsigned>> project_euler::prime_factors(unsigned n){
//    return project_euler_internal::prime_factors_template(n,
//            project_euler::primes_to_n((unsigned) std::sqrt((float) n)+1));
//}
//
//vector<pair<long unsigned,long unsigned>> project_euler::prime_factors(long unsigned n,const  vector<long unsigned>& primes){
//    return project_euler_internal::prime_factors_template(n,primes);
//
//vector<pair<long unsigned,long unsigned>> project_euler::prime_factors(long unsigned n){
//    return project_euler_internal::prime_factors_template(n,
//            project_euler::primes_to_n((long unsigned) std::sqrt((float) n)+1));
//}
//
//vector<pair<long long unsigned,long long unsigned>> project_euler::prime_factors(long long unsigned n,const  vector<long long unsigned>& primes){
//    return project_euler_internal::prime_factors_template(n,primes);
//
//vector<pair<long long unsigned,long long unsigned>> project_euler::prime_factors(long long unsigned n){
//    return project_euler_internal::prime_factors_template(n,
//            project_euler::primes_to_n((long long unsigned) std::sqrt((double) n)+1));
//}

int project_euler::ipow(int base, unsigned exp){
    return project_euler_internal::ipow_template(base,exp);
}

int project_euler::ipow(int base, int exp){
    if(exp < 0){
        throw std::domain_error(
                "Cannot compute the integer power of a negative exponent");
    }
    return project_euler_internal::ipow_template(base,exp);
}

long project_euler::ipow(long base, unsigned long exp){
    return project_euler_internal::ipow_template(base,exp);
}

long project_euler::ipow(long base, long exp){
    if(exp < 0){
        throw std::domain_error(
                "Cannot compute the integer power of a negative exponent");
    }
    return project_euler_internal::ipow_template(base,exp);
}

long long project_euler::ipow(long long base, unsigned long long exp){
    return project_euler_internal::ipow_template(base,exp);
}

long long project_euler::ipow(long long base, long long exp){
    if(exp < 0){
        throw std::domain_error(
                "Cannot compute the integer power of a negative exponent");
    }
    return project_euler_internal::ipow_template(base,exp);
}

unsigned project_euler::ipow(unsigned base, unsigned exp){
    return project_euler_internal::ipow_template(base,exp);
}

unsigned long project_euler::ipow(unsigned long base, unsigned long exp){
    return project_euler_internal::ipow_template(base,exp);
}

unsigned long long project_euler::ipow(unsigned long long base, unsigned long long exp){
    return project_euler_internal::ipow_template(base,exp);
}

std::optional<int> project_euler::isqrt(int n){
    return project_euler_internal::isqrt_template(n);
}

std::optional<long int> project_euler::isqrt(long int n){
    return project_euler_internal::isqrt_template(n);
}

std::optional<long long int> project_euler::isqrt(long long int n){
    return project_euler_internal::isqrt_template(n);
}

std::optional<short int> project_euler::isqrt(short int n){
    return project_euler_internal::isqrt_template(n);
}

std::optional<unsigned> project_euler::isqrt(unsigned n){
    return project_euler_internal::isqrt_template(n);
}

std::optional<unsigned long> project_euler::isqrt(unsigned long n){
    return project_euler_internal::isqrt_template(n);
}

std::optional<unsigned long long> project_euler::isqrt(unsigned long long n){
    return project_euler_internal::isqrt_template(n);
}

std::optional<unsigned short> project_euler::isqrt(unsigned short n){
    return project_euler_internal::isqrt_template(n);
}

std::tuple<int,int,int> project_euler::extended_gcd(int a, int b){
    return project_euler_internal::extended_gcd_template(a,b);
}

std::tuple<long int, long int, long int> project_euler::extended_gcd(long int a, long int b){
    return project_euler_internal::extended_gcd_template(a,b);
}

std::tuple<long long int, long long int, long long int> project_euler::extended_gcd(long long int a, long long int b){
    return project_euler_internal::extended_gcd_template(a,b);
}

std::tuple<unsigned, unsigned, unsigned> project_euler::extended_gcd(unsigned a, unsigned b){
    return project_euler_internal::extended_gcd_template(a,b);
}

std::tuple<long unsigned, long unsigned, long unsigned> project_euler::extended_gcd(long unsigned a, long unsigned b){
    return project_euler_internal::extended_gcd_template(a,b);
}

std::tuple<long long unsigned,long long unsigned,long long unsigned> project_euler::extended_gcd(long long unsigned a, long long unsigned b){
    return project_euler_internal::extended_gcd_template(a,b);
}
