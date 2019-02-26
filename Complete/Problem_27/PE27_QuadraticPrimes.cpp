// SOlves Project Euler problem 27: Quadratic Primes
//
// Find the product of the integers a and b, with |a|,|b| < 1000, such that
// the expression
//      f(n) = n^2 + a*n + b
// produces the longest unbroken sequence of prime numbers, starting from
// n = 0
//########################################################################
//
// f(0) = b prime => b primes, b > 0
//
// f(n) odd regardless of parity of n => parity(a) = parity(b)
//
// f(b) = b*(b+a+1) prime iff a = -b
//
// for a = -b
// f(b-1) = b^2 -2b +1 -b^2 +b +b = 1
//  => 1000^2 +1000*1000 +1000 is an upper bound on primes that can occure
//

#include <vector>
#include <algorithm>
#include <iostream>

#include "Project_Euler.h"

using std::vector;

constexpr long int MAX_PRIME = 2001000;

const vector<long> PRIMES = project_euler::primes_to_n(MAX_PRIME);

// checks if a number less than MAX_PRIME is prime
bool is_prime(long int target){
    return std::binary_search(PRIMES.begin(), PRIMES.end(), target);
}

// Checks the number of primes generated be the quadratic n^2+an+b by 
// plugging in sucsessive values of n, starting from 0. 
int number_primes_generated(int a, int b){
    int seq_len = 0;

    for(int n = 0;is_prime(n*n+a*n+b);++n){
        ++seq_len;
    }
    return seq_len;
}

int main(){
    
    int a_max = -2000; // These values are chosen to be outside the allowed 
    int b_max = -2000; // range, so it is obvious if they are not overriden
    int longest_sequence_length = 0;

    const auto B_IT_MAX = std::upper_bound(PRIMES.begin(),PRIMES.end(),1000);
    for(auto b_it = PRIMES.begin(); b_it != B_IT_MAX ;++b_it){
        int b = *b_it;
        for(int a = -1000-(b%2); a <= 1000; a += 2){
            int seq_length = number_primes_generated(a,b);
            if(seq_length > longest_sequence_length){
                longest_sequence_length = seq_length;
                a_max = a;
                b_max = b;
            }
        }
        
    }

    std::cout << "a = " << a_max << "\nb = " << b_max << "\nlongest sequence length = " << longest_sequence_length << "\nab = " << (a_max*b_max) << std::endl;
}
