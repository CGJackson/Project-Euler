// Runs unit tests on Project_Euler.h functions

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <random>

#include "Project_Euler.h"

using std::vector;  using std::pair; 
using std::equal;
using std::find;    using std::find_if_not;
using std::default_random_engine;   using std::uniform_int_distribution;
using std::cout;    using std::endl;

// Runs unit test of function primes to n
bool test_primes_to_n(){
    using project_euler::primes_to_n;
    cout << "Running tests on function primes_to_n" << endl;
    bool passed_all_tests = true; // for now...

    const vector<int> primes_less_100 = {2,3,5,7,11,13,17,19,23,29,31,37,41,
                                   43,47,53,59,61,67,71,73,79,83,89,97};

    vector<int> calculated_primes = primes_to_n(100);

    if( primes_less_100.size() == calculated_primes.size() &&
        equal(primes_less_100.begin(), primes_less_100.end(),
              calculated_primes.begin()) ){
        cout << "primes_to_n found all primes < 100 successfully" << endl;
    } else{
        passed_all_tests &= false;
        cout << "primes_to_n failed to find correct primes < 100\n"
             << "Correct Primes < 100" << endl;
        for(auto p:primes_less_100)
            cout << p << " ";
        cout << endl;
        cout << "Primes calculated"<<endl;
        for(auto p:calculated_primes)
            cout << p << " ";
        cout << endl;
    }

    calculated_primes = primes_to_n(0);
    if(calculated_primes.size() > 0){
        passed_all_tests &= false;
        cout << "primes_to_n(0) did not return an empty vector\n";
        cout << "instead it returned" << endl;
        for(auto p:calculated_primes)
            cout << p << " ";
        cout << endl;
    }else
        cout << "primes_to_n(0) suceesfully returned an empty vector"<<endl;

    
    calculated_primes = primes_to_n(1);
    if(calculated_primes.size() > 0){
        passed_all_tests &= false;
        cout << "primes_to_n(1) did not return an empty vector\n";
        cout << "instead it returned" << endl;
        for(auto p:calculated_primes)
            cout << p << " ";
        cout << endl;
    }else
        cout << "primes_to_n(1) suceesfully returned an empty vector"<<endl;

    calculated_primes = primes_to_n(2);
    if(calculated_primes.size() != 1 || calculated_primes[0] != 2){
        passed_all_tests &= false;
        cout << "primes_to_n(2) did not return {2}\n";
        cout << "instead it returned" << endl;
        for(auto p:calculated_primes)
            cout << p << " ";
        cout << endl;
    }else
        cout << "primes_to_n(2) suceesfully returned {2}"<<endl;

    cout << endl;
    return passed_all_tests;
}

// Runs unit tests of function isqrt
bool test_isqrt(){
    using project_euler::isqrt;
    cout << "Running tests of function isqrt"<<endl;
    bool all_tests_passed = true;

    int root, target;

    if(isqrt(0) == 0)
        cout << "isqrt(0) sucessfully returned 0" <<endl;
    else{
        cout << "isqrt(0) returned " << isqrt(0) <<endl;
        all_tests_passed = false;
    }

    if(isqrt(1) == 1)
        cout << "isqrt(1) sucessfully returned 1" <<endl;
    else{
        cout << "isqrt(1) returned " << isqrt(1) <<endl;
        all_tests_passed = false;
    }
        
    default_random_engine generator;
    uniform_int_distribution<int> root_distribution(2,1000);

    bool test_100_random_squares = true;
    for(int i = 0; i < 100; ++i){
        root = root_distribution(generator);
        target = root*root;
        if( isqrt(target) != root){
            cout << "isqrt("<< target <<") did not return "<< root 
                 <<". instead it returned " << isqrt(target) << endl;
            all_tests_passed = false;
            test_100_random_squares = false;
        }
    }
    if(test_100_random_squares){
        cout << "isqrt gave the correct root for 100 random square numbers"
             << " between 4 and 1000000." << endl;
    }

    // The smallest gap between squares > 1 is 9-4=5, this generates a
    // random number smller than that gap
    uniform_int_distribution<int> offset_distribution(1,4);

    bool test_100_random_non_squares = true;
    for(int i = 0; i < 100; ++i){
        root = root_distribution(generator);
        target = root*root + offset_distribution(generator);
        if( isqrt(target) != -1){
            cout << "isqrt("<< target <<") did not return -1" 
                 <<". instead it returned " << isqrt(target) << endl;
            all_tests_passed = false;
            test_100_random_non_squares = false;
        }

    }
    if(test_100_random_non_squares){
        cout << "isqrt gave -1 for 100 random non-square numbers"
             << " between 5 and 1000004." << endl;
    }

    cout << endl;
    return all_tests_passed;

}

int main(){
    bool all_tests_passed = true;
    
    all_tests_passed &= test_primes_to_n();    

    all_tests_passed &= test_isqrt();

    if(all_tests_passed){
        cout << "All tests passed" << endl;
    }else{
        cout << "Some tests were failed" << endl;
    }
return 0;
}
