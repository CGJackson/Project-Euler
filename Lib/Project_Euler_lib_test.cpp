// Runs unit tests on Project_Euler.h functions

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

#include "Project_Euler.h"

using std::vector;  using std::pair; 
using std::equal;
using std::find;    using std::find_if_not;
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

int main(){
    bool all_tests_passed = true;
    
    all_tests_passed &= test_primes_to_n();    


    if(all_tests_passed){
        cout << "All tests passed" << endl;
    }else{
        cout << "Some tests were failed" << endl;
    }
return 0;
}
