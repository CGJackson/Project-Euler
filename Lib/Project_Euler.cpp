// A Library containing common functions for Project Euler problems

// Contents:
//  primes_to_n(n): returns a vector of all the prime numbers less than or 
//                  equal to n
//  isqrt(n): returns the integer square root of n or -1 if n is not a 
//                  square number.

#include <iostream>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <array>
#include <utility>
#include <stdexcept>
#include <boost/functional/hash.hpp>

#include "Project_Euler.h"

using std::vector;  using std::array;
using std::pair;    using std::unordered_map;

using project_euler::primes_to_100;

namespace project_euler_internal {

    // Calculates a vector of all prime numbers <= n
    template <typename T>
    vector<T> primes_to_n_template(const T n, vector<T>&& primes){
        if(primes.back() >= n){
            auto p = primes.begin();
            while (p != primes.end() && *p <= n){
                ++p;
            }
            return vector<T>{primes.begin(), p};
        }
        if ( n < 2){
            return vector<T>();
        }

        primes.reserve(n/std::log(n));

        if(primes.empty()){
            primes.push_back(2);
        }

        T offset = primes.back()+1;

        vector<bool> is_prime(n+1-offset,true);

        // removes multiples of all primes found so far
        for(auto p:primes){
            for(auto j = offset + p - (offset % p); j <= n; j+=p){
                is_prime[j-offset] = false;
            }
        }
        std::cerr << std::endl;

        // Performs main sieve
        T i;
        for(i = offset + ((offset+1) % 2); i*i <= n; i += 2){
            if( is_prime[i-offset] ){
                primes.push_back(i);
                for(T j = 2*i; j < n; j += i){
                    is_prime[j-offset] = false;
                }
            }
        }    

        // Once sieving is complete, adds primes > sqrt(n) to list of primes
        for(;i <= n; i += 2){
            if( is_prime[i-offset] ){
                primes.push_back(i);
            }
        }

        primes.shrink_to_fit();
        return primes;
    }

    template<typename T>
    vector<T> primes_to_n_template(const T n,const vector<T>& primes){
        return primes_to_n_template(n, vector<T>{primes});
    }


    template<typename IntType>
    class prime_counting_function_template{
    public:
        prime_counting_function_template(): prime_list_val(),prime_list(prime_list_val), pi_cache(),phi_cache(){}

        IntType operator()(IntType x, const vector<IntType>& primes){
            prime_list = &primes;
            return pi_function(x);
        }

        IntType operator()(IntType x){
            IntType primes_to_calculate = x > 10000 ? std::sqrt(x) + 1 : 100;
            prime_list_val = primes_to_n_template(primes_to_calculate, primes_to_100<IntType>());
            prime_list = prime_list_val;
            return pi_function(x);
        }

    private:
        // A list of prime numbers for use in the computation
        // may be stored internally or use an external reference
        vector<IntType> prime_list_val;
        vector<IntType>& prime_list;

        // Many caches
        unordered_map<IntType,IntType> pi_cache;
        unordered_map<pair<IntType,IntType>,IntType,boost::hash<pair<IntType,IntType>>> phi_cache;


        // computes the prime counting funciton, given a list of primes
        IntType pi_function(IntType n){
            if(n <= prime_list.back()){
                if ( n == prime_list.back()){
                    return prime_list.size();
                }
                IntType i = 0;
                while ( prime_list[i] <= n){
                    ++i;
                }
                return i;
            }
            try {
                return pi_cache.at(n);
            }
            catch (const std::out_of_range& e) {
                IntType a = pi_function((IntType) std::sqrt(n));//std::cbrt(n));
                pi_cache[n] = phi(n,a) + a - 1;// - p2(n,m);
                return pi_cache[n];
            }
        }

        // Meissel-Lehmer phi function. Counts the number of natural numbers less
        // than x with no prime factors less than p_a, that is the a th prime
        // number
        IntType phi(IntType x, IntType a){
            if (x <= a){
                return 0;
            }
            if (a == 1){
                return (x/2) + (x % 2); // number of odd nunbers less than x
            }
            else if( a > 1 ){
                try{
                    return phi_cache.at(pair<IntType,IntType>{x,a});
                } catch (const std::out_of_range& e){
                    return phi(x,a-1) - phi(x/prime_list[a-1], a-1);
                }
            }
            else{
                if(x >= 0){
                    return x;
                }
                else throw std::domain_error("cannot take Meissel-Lehmer phi function of a negative number");
            }
        }

        // Meissel-Lehmer p2 function. Counts the number of natural numbers
        // less than m with exactly 2 prime factors, both of which are greater
        // than n.
        IntType p2(IntType m, IntType n){
            if(prime_list[n] >= m){
                return 0;
            }
            IntType upper_lim = pi_function((IntType) std::sqrt(m));
            //std::cerr << "upper lim = " << upper_lim << std::endl;
            IntType tot = 0;
            for(IntType i = n+1; i <= upper_lim; ++i){
                //std::cerr << "args = (" << m << "," << n << ") upper_lim = " << upper_lim << "\ti = " << i << std::endl;
                tot += pi_function((IntType) (m/prime_list[i]));
            }
            return tot - ((upper_lim - n)*(upper_lim + n -1))/2;
        }
    };

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

vector<int> project_euler::primes_to_n(const int n){
    return project_euler_internal::primes_to_n_template(n, primes_to_100<int>());
}

vector<long int> project_euler::primes_to_n(const long int n){
    return project_euler_internal::primes_to_n_template(n, primes_to_100<long int>());
}

vector<long long int> project_euler::primes_to_n(const long long int n){
    return project_euler_internal::primes_to_n_template(n, primes_to_100<long long int>());
}

vector<unsigned> project_euler::primes_to_n(const unsigned n){
    return project_euler_internal::primes_to_n_template(n, primes_to_100<unsigned>());
}

vector<long unsigned> project_euler::primes_to_n(const long unsigned n){
    return project_euler_internal::primes_to_n_template(n, primes_to_100<long unsigned>());
}

vector<long long unsigned> project_euler::primes_to_n(
                                                const long long unsigned n){
    return project_euler_internal::primes_to_n_template(n, primes_to_100<long long unsigned>());
}

int project_euler::prime_counting_function(int n){
    return project_euler_internal::prime_counting_function_template<int>()(n);
}
long project_euler::prime_counting_function(long n){
    return project_euler_internal::prime_counting_function_template<long>()(n);
}
long long project_euler::prime_counting_function(long long n){
    return project_euler_internal::prime_counting_function_template<long long>()(n);
}
unsigned project_euler::prime_counting_function(unsigned n){
    return project_euler_internal::prime_counting_function_template<unsigned>()(n);
}
long unsigned project_euler::prime_counting_function(long unsigned n){
    return project_euler_internal::prime_counting_function_template<long unsigned>()(n);
}
long long unsigned project_euler::prime_counting_function(long long unsigned n){
    return project_euler_internal::prime_counting_function_template<long long unsigned>()(n);
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
