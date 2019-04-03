// Solves project Euler problem 35: Circular Primes
// Find all the prime number below 1,000,000 such that all rotations of
// their digits is also prime

#include <vector>
#include <set>
#include <iostream>

#include "Project_Euler.h"

using std::vector;
using std::set;
using std::cout; 
using std::endl;

template<typename IntType>
IntType rotate_digits(IntType n){
    IntType least_significant_digit = n % 10;
    n /= 10;
    IntType digit_counter = 1;
    while(digit_counter <= n){
        digit_counter *= 10;
        least_significant_digit *= 10;
    }
    return n + least_significant_digit;
}

long count_circular_primes(long limit){
    set<long> primes;
    {
        vector<long> primes_temp = project_euler::primes_to_n(limit);
        primes = set<long>(primes_temp.begin(),primes_temp.end());
    }
    long circular_primes = 0;
    for(auto p_it = primes.begin(); p_it != primes.end();){
        long next = *p_it;
        short cycle_length = 1;
        while((next=rotate_digits(next)) != *p_it){
            auto cycle_it = primes.find(next);
            if(cycle_it != primes.end()){
                ++cycle_length;
                primes.erase(cycle_it);
            }
            else{
                cycle_length = 0;
                break;
            }
        }
        if(cycle_length){
            circular_primes += cycle_length;
        }
        {
            auto temp_it = p_it++;
            primes.erase(temp_it);
        }
    }
    return circular_primes;
}

int main(){
    cout << count_circular_primes(1000000) << " cicular primes found" << endl;
}
