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

#include "Project_Euler.h"

#define MAX_PRIME 2001000

using std::vector;

const vector<long int> PRIMES = project_euler::primes_to_n(MAX_PRIME);

bool is_prime(long int target){
    PRIMES::const_iterator   upper_index = PRIMES.end(),
                         lower_index = PRIMES.begin();
    if(target == *lower_index)
        return true;
    while( target < *upper_index && target > *lower_index]){
        PRIMES::const_iterator dumby_index = (upper_index-lower_index)/2;
        if(target == *dumby_index){
            return true;
        }
        if(target > *dumby_index){
            lower_index = dumby_index;
        } else {
            upper_index = dumby_index;
        }
    }
    return false;
}

int number_primes_generated(int a, int b){
    int seq_len = 0;

    for(int n = 0;is_prime(n*n+a*n+b);++n){
        ++seq_len;
    }
    return seq_len;
}

int main(){
    
    int a_max,b_max, longest_sequence_length = 0;

    for(int b:PRIMES){
        for(int a = -1000+(b%2); a <= 1000; a += 2){
            int seq_length = number_primes_generated(a,b)
            if(seq_length > longest_sequence_length){
                longest_sequence_length = seq_length;
                a_max = a;
                b_max = b;
            }
        }
        
    }
}
