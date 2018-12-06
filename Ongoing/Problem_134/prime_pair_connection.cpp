// Solve Project Euler problem 134, Prime Pair Connection.
// Let S_i be the smallest number whos last digits are given by the ith prime number and which is divisible by the
// i+1th prime number. Find the sum for S_i such that 5 <= p_i <= 1,000,000
//
// We can write S_i = 10^d(p_i) n + p_i where d(p_i) is the number of digits in p_i. This then reduces the problem
// to finding the smallest n such that S_i = o mod p_(i+1). Substituting the expression for S_i and rearranging 
// gives n = -p_i *(1/10^d(p_i)) mod p_(i+1) where 1/10^d(p_i) is the multiplicative inverse of 10^d(p_i) modulo 
// p_(i+1). As p_(i+1) > 2,5 and prime, it is coprime withh all powers of 10, so the required inverse exists.
// The expression for n mod p_(i+1) gives a single value for 0<n<p_(i+1), which will be the smallest possible n, 
// and so the one which will give us S_i. 
//
// To find 1/10^d(p_i) we use the extended euclidean algorithm to find the integers satifying Bezout's identity for // 10^d(p_i) and p_(i+1). Since these integers are coprime, this has the form  x10^d(p_i) + yp_(i+1) = 1, which 
// gives x 10^d(p_i) = 1 mod p_(i+1), so x = 10^d(p_i).

#include <iostream>
#include <utility>
#include <stdexcept>

using std::cout;    using std::endl;

#include "../../Lib/Project_Euler.h"

using project_euler::extended_gcd; using project_euler::ipow;
using project_euler::primes_to_n;

typedef long int Int_t;

constexpr Int_t LIMIT = 1000000;
constexpr Int_t LOWER_LIMIT = 5;

// Returns the number of decimal digits in n
inline Int_t get_digits(Int_t n){
    Int_t digits = 0;
    while(n != 0){
        ++digits;
        n /= 10;
    }
    return digits;
}

// returns 10^d(n), that is 10 to the power of the number of digits in n.
// Multiplying an intger by this factor and adding n will give a number whos 
// last digits are given by n.
inline Int_t shift_factor(Int_t n){
    return ipow((Int_t) 10,get_digits(n));
}

// Finds the multiplicative inverse of x modulo p. Throws an error if x and p are not coprime.
Int_t find_inverse(Int_t x, Int_t p){
    auto result = extended_gcd(x,p);
    if( std::get<0>(result) != 1){
        throw std::domain_error("Non-coprime integers do not have modulo inverses");
    }
    return std::get<1>(result);
}

//Finds the leading digits 
Int_t leading_digits(Int_t trailing_digits, Int_t modulus){
    Int_t inv_shift_factor = find_inverse(shift_factor(trailing_digits), modulus);
    Int_t non_minimal_solution = trailing_digits*inv_shift_factor;
    return modulus - (non_minimal_solution % modulus); // adding the modulus is needed to correctly take care of the minus sign
}

// Finds the smallest numbers with the last digits given by trailing_digits and divisible by modulus
Int_t smallest_multiple_with_trailing_digits(Int_t trailing_digits,Int_t modulus){
    return leading_digits(trailing_digits,modulus)*shift_factor(trailing_digits) + trailing_digits;
}

int main(){
    const auto PRIMES = primes_to_n((int) 2*LIMIT-2); // There exists at least 1 prime > LIMIT in this range by Bertrand's Postulate.

    long long int total = 0;    
    for (auto prime_iter = PRIMES.begin(); *prime_iter <= LIMIT; ++prime_iter){
        if(*prime_iter < LOWER_LIMIT){
            continue;
        }
        Int_t current_term = smallest_multiple_with_trailing_digits(*prime_iter,*(prime_iter+1));

        if( current_term < 0){
            throw std::overflow_error("S_i > INT_MAX");
        }
        cout << *prime_iter << '\t' <<*(prime_iter+1) << '\t' << current_term << '\n'; 
        total += current_term;
    }

    cout << "\nSum(S_i) = " << total << endl; 
   

    return 0;
}

