// Runs unit tests on Project_Euler.h functions

#include <iostream>
#include <vector>
#include <array>
#include <utility>
#include <algorithm>
#include <random>
#include <numeric>
#include <limits>

#include "Project_Euler.h"

using std::vector;  using std::pair; 
using std::tuple;
using std::equal;   using std::array;
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

    auto primes_to_1million = primes_to_n(1000000);
    if( primes_to_1million.size() == 78498 && primes_to_1million.back() < 1000000){
        cout << "primes_to_n(1000000) suceesfully found 78498 numbers less than 1000000" << endl;
    }
    else{
        cout << "primes_to_n(1000000) did not successfully find all prime numbers bellow 1000000\n" 
             << "It found " << primes_to_1million.size() << " \"prime numbers\". The largest was " << primes_to_1million.back() << endl;
        passed_all_tests &= false;
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

bool test_prime_counting_function(){
    using project_euler::prime_counting_function;
    bool all_tests_passed = true;
    cout << "Running tests of prime_counting_function" << endl;
    // Tests for composite integer
    if(prime_counting_function((long long) 50) == 15){
        cout << "prime_counting_function(50) successfully returned 15" <<endl;
    }
    else {
        all_tests_passed &= false;
        cout << "prime_counting_function(50) returned " << prime_counting_function(50) << " rather than 15"<< endl;
    }
    if(prime_counting_function((long long) 1000000) == 78498){
        cout << "prime_counting_function(1000000) successfully returned 78498" <<endl;
    }
    else {
        all_tests_passed &= false;
        cout << "prime_counting_function(1000000) returned " << prime_counting_function(1000000) << " rather than 78498"<< endl;
    }
    // Tests for prime integer
    if(prime_counting_function(1000003) == 6){
        cout << "prime_counting_function(1000003) successfully returned 78499" <<endl;
    }
    else {
        all_tests_passed &= false;
        cout << "prime_counting_function(1000003) returned " << prime_counting_function(1000003) << " rather than 78499" << endl;
    }
    // Test for 1
    if(prime_counting_function(1) == 0){
        cout << "prime_counting_function(1) successfully returned 0" <<endl;
    }
    else {
        all_tests_passed &= false;
        cout << "prime_counting_function(1) returned " << prime_counting_function(1) << endl;
    }
    // Test for 0
    if(prime_counting_function(0) == 0){
        cout << "prime_counting_function(0) successfully returned 0" <<endl;
    }
    else {
        all_tests_passed &= false;
        cout << "prime_counting_function(0) returned " << prime_counting_function(0) << endl;
    }
    // Test for negative number
    if(prime_counting_function(-5) == 0){
        cout << "prime_counting_function(-5) successfully returned 0" <<endl;
    }
    else {
        all_tests_passed &= false;
        cout << "prime_counting_function(-5) returned " << prime_counting_function(-5) << endl;
    }
    cout << endl;
    return all_tests_passed;
}

//bool test_prime_factors(){
//    using project_euler::prime_factors;
//
//
//}

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

bool test_PythagoreanTripleTree(){
    using project_euler::PythagoreanTripleTree;
    
    cout << "Running tests on PythagoreanTripleTree" << endl;    

    bool all_tests_passed = true;

    PythagoreanTripleTree<int> tree;
    
    cout << "Testing initialisation of PythagoreanTripleTree" << endl;

    constexpr array<int,3> expected_first_triple = {3,4,5};
    if( tree.get_first_side() != expected_first_triple[0] ){
        all_tests_passed &= false;
        cout << "For base tree first side not initalised correctly\n";
        cout << "First side: " << tree.get_first_side() << "\tExpected first side: " << expected_first_triple[0] << endl;
    }
    if( tree.get_second_side() != expected_first_triple[1]){
        all_tests_passed &= false;
        cout << "For base tree second side not initalised correctly\n";
        cout << "Second side: " << tree.get_second_side() << "\tExpected second side: " << expected_first_triple[1] << endl;
    }
    if( tree.get_hypotenuse() != 5){
        all_tests_passed &= false;
        cout << "for base tree hypotinuse not initalised correctly\n";
        cout << "hypotinuse: " << tree.get_hypotenuse() << "\tExpected hypotinuse: " << expected_first_triple[2] << endl;
    }
    if( tree.get_parent() != nullptr){
        all_tests_passed &= false;
        cout << "for base tree parent not initalised to nullptr" << endl;
    }

    if(all_tests_passed){
        cout << "Base PythagoreanTripleTree initalised correctly" << endl;
    }

    bool all_child_tests_passed = true;
    cout << "Testing Children created correctly" << endl;
    array<array<int,3>,3> expected_child_triples = {{ {5,12,13},{21,20,29},{15,8,17} }};
    for(unsigned i = 0; i < 3; ++i){
        auto child = tree.get_child(i);
        if(child->get_parent() != &tree){
            all_child_tests_passed &= false;
            cout << "Child " << i << "'s parent pointer did not point to its parent.";
            if(child->get_parent() == nullptr){
                cout << " Pointer was instead null.";
            }
            else{
                cout << " Pointer was not null.";
            }
            cout << endl;
        }
        if(child->get_first_side() != expected_child_triples[i][0]){
            all_child_tests_passed &= false;
            cout << "Child "  << i << " did not have the correct first side\n"
                 << "First side: " << child->get_first_side() << "\tExpected first side: " << expected_child_triples[i][0] << endl;
        }
        if(child->get_second_side() != expected_child_triples[i][1]){
            all_child_tests_passed &= false;
            cout << "Child "  << i << " did not have the correct second side\n"
                 << "Second side: " << child->get_second_side() << "\tExpected second side: " << expected_child_triples[i][1] << endl;
        }
        if(child->get_hypotenuse() != expected_child_triples[i][2]){
            all_child_tests_passed &= false;
            cout << "Child "  << i << " did not have the correct hypotinuse\n"
                 << "Hypotinuse: " << child->get_hypotenuse() << "\tExpected hypotinuse: " << expected_child_triples[i][2] << endl;
        }
    }
    all_tests_passed &= all_child_tests_passed;
    if(all_child_tests_passed){
        cout << "All children created correctly" << endl;
    }

    cout << "Testing construction of arbitrary triple" << endl;
    bool all_constructed_tripe_tests_passed = true;
    constexpr array<int,3> constructed_triple = {6,8,10};
    PythagoreanTripleTree<int> tree2(constructed_triple[0], constructed_triple[1]);
    if( tree2.get_first_side() != constructed_triple[0] ){
        all_constructed_tripe_tests_passed  &= false;
        cout << "For constructed tree first side not initalised correctly\n";
        cout << "First side: " << tree2.get_first_side() << "\tExpected first side: " << constructed_triple[0] << endl;
    }
    if( tree2.get_second_side() != constructed_triple[1]){
        all_constructed_tripe_tests_passed &= false;
        cout << "For constructed tree second side not initalised correctly\n";
        cout << "Second side: " << tree2.get_second_side() << "\tExpected second side: " << constructed_triple[1] << endl;
    }
    if( tree2.get_hypotenuse() != constructed_triple[2]){
        all_constructed_tripe_tests_passed &= false;
        cout << "for constructed tree hypotinuse not initalised correctly\n";
        cout << "hypotinuse: " << tree2.get_hypotenuse() << "\tExpected hypotinuse: " << constructed_triple[2] << endl;
    }
    if( tree2.get_parent() != nullptr){
        all_constructed_tripe_tests_passed &= false;
        cout << "for constructed tree parent not initalised to nullptr" << endl;
    }

    if(all_constructed_tripe_tests_passed){
        cout << "Constructed PythagoreanTripleTree initalised correctly" << endl;
    }

    cout << "Testing tree iterators" << endl;
    bool all_iterator_tests_passed = true;

    cout << "\tTesting hypotenuse iterator" << endl;
    bool all_hypotenuse_iterator_tests_passed = true;
    PythagoreanTripleTree<int>::hypotenuse_iterator hyp_iterator = tree.begin_hypotenuse_iterator();
    if(&(*hyp_iterator) != &tree){
        all_hypotenuse_iterator_tests_passed &= false;
        cout << "dereferencing the hypotenuse iterator before incrementing "
             << "did not return the node that created it." << endl;
    }
    if(hyp_iterator->get_first_side() != tree.get_first_side()){
        all_hypotenuse_iterator_tests_passed &= false;
        cout << "Calling methods via the -> operator on a hypotenuse "
             << "iterator did not give the same result as calling the "
             << "method directly" << endl;
    }
    PythagoreanTripleTree<int>::hypotenuse_iterator hyp_iterator2 = tree.begin_hypotenuse_iterator();
    if(!( hyp_iterator == hyp_iterator2 )){
        all_hypotenuse_iterator_tests_passed &= false;
        cout << "2 unicremented hypotenuse iterators created by the same "
             << "node were not equal to each other" << endl;
    }

    // elements returned by hyp_iterator
    std::vector<PythagoreanTripleTree<int>::child_ptr> expected_iterator_values = {tree.get_child(0),tree.get_child(2), tree.get_child(1)};

    ++hyp_iterator;
    if(!(hyp_iterator != hyp_iterator2)){
        all_hypotenuse_iterator_tests_passed &= false;
        cout << "2 different hypotenuse_iterators evaluated false for != "
             << "operator" << endl;
    }
    hyp_iterator2++;
    if(hyp_iterator != hyp_iterator2){
        all_hypotenuse_iterator_tests_passed &= false;
        cout << "applying the prefix and postfix increment operators did "
             << "not yeild the same result" << endl;
    }
    if(&(*hyp_iterator) != expected_iterator_values[0].get()){
        all_hypotenuse_iterator_tests_passed &= false;
        cout << "Incrementing the hypotenuse iterator did not give the "
             << "did not give the next tree node in order of incrasing "
             << "hypotenuse length" << endl;
    }
    if(&(*(++hyp_iterator)) != expected_iterator_values[1].get()){
        all_hypotenuse_iterator_tests_passed &= false;
        cout << "The prefix increment operator did not return the correct "
                "next value for the hypotenuse  iterator" << endl;
    } 
    if(&(*(hyp_iterator++)) != expected_iterator_values[1].get()){
        all_hypotenuse_iterator_tests_passed &= false;
        cout << "The postfix increment operator did not return the correct "
                "current value for the hypotenuse  iterator" << endl;
    } 
    all_iterator_tests_passed &= all_hypotenuse_iterator_tests_passed;
    
    cout << "\tTesting perimeter iterator" << endl;
    bool all_perimeter_iterator_tests_passed = true;
    PythagoreanTripleTree<int>::perimeter_iterator perim_iterator = tree.begin_perimeter_iterator();
    if(&(*perim_iterator) != &tree){
        all_perimeter_iterator_tests_passed &= false;
        cout << "dereferencing the perimeter iterator before incrementing "
             << "did not return the node that created it." << endl;
    }
    if(perim_iterator->get_first_side() != tree.get_first_side()){
        all_perimeter_iterator_tests_passed &= false;
        cout << "Calling methods via the -> operator on a perimeter "
             << "iterator did not give the same result as calling the "
             << "method directly" << endl;
    }
    PythagoreanTripleTree<int>::perimeter_iterator perim_iterator2 = tree.begin_perimeter_iterator();
    if(!( perim_iterator == perim_iterator2 )){
        all_perimeter_iterator_tests_passed &= false;
        cout << "2 unicremented perimeter iterators created by the same "
             << "node were not equal to each other" << endl;
    }

    // elements returned by perim_iterator
    std::vector<PythagoreanTripleTree<int>::child_ptr> expected_p_iterator_values = {tree.get_child(0),tree.get_child(2), tree.get_child(1)};

    ++perim_iterator;
    if(!(perim_iterator != perim_iterator2)){
        all_perimeter_iterator_tests_passed &= false;
        cout << "2 different perimeter_iterators evaluated false for != "
             << "operator" << endl;
    }
    perim_iterator2++;
    if(perim_iterator != perim_iterator2){
        all_perimeter_iterator_tests_passed &= false;
        cout << "applying the prefix and postfix increment operators did "
             << "not yeild the same result" << endl;
    }
    if(&(*perim_iterator) != expected_p_iterator_values[0].get()){
        all_perimeter_iterator_tests_passed &= false;
        cout << "Incrementing the perimeter iterator did not give the "
             << "did not give the next tree node in order of incrasing "
             << "perimeter length" << endl;
    }
    if(&(*(++perim_iterator)) != expected_p_iterator_values[1].get()){
        all_perimeter_iterator_tests_passed &= false;
        cout << "The prefix increment operator did not return the correct "
                "next value for the perimeter  iterator" << endl;
    } 
    if(&(*(perim_iterator++)) != expected_p_iterator_values[1].get()){
        all_perimeter_iterator_tests_passed &= false;
        cout << "The postfix increment operator did not return the correct "
                "current value for the perimeter  iterator" << endl;
    } 
    all_iterator_tests_passed &= all_perimeter_iterator_tests_passed;
    all_tests_passed &= all_iterator_tests_passed;

    cout << "Testing move constructor" << endl;
    bool all_move_tests_passed = true;
    constexpr unsigned TEST_CHILD = 0, TEST_PARENT_CHILD = 0;
    PythagoreanTripleTree<int>::child_ptr middle_node = tree.get_child(TEST_PARENT_CHILD);
    PythagoreanTripleTree<int>::child_ptr lower_node = middle_node->get_child(TEST_CHILD); //forces middle_node to generate a child

    array<int,3> expected_moved_triple {middle_node->get_first_side(),
                                        middle_node->get_second_side(),
                                        middle_node->get_hypotenuse()};

    PythagoreanTripleTree<int> new_middle_node(std::move(*middle_node));

    if(new_middle_node.get_first_side() != expected_moved_triple[0] ||
       new_middle_node.get_second_side() != expected_moved_triple[1] ||
       new_middle_node.get_hypotenuse() != expected_moved_triple[2]){
        all_move_tests_passed &= false;
        cout << "Moved node did not contain the same triple as the original\n"
             <<"Original triple: " << expected_moved_triple[0] << ", "
                                   << expected_moved_triple[1] << ", "
                                   << expected_moved_triple[2] << "\t"
            << "Moved triple: "    << new_middle_node.get_first_side() << ", "
                                   << new_middle_node.get_second_side() << ", "
                                   << new_middle_node.get_hypotenuse() << endl;
    }

    if(new_middle_node.get_parent() != &tree){
        all_move_tests_passed &= false;
        cout << "Moved node's parent pointer did not point to the old parent\n"
             << "Moved node's parent pointer was " 
             << (new_middle_node.get_parent() == nullptr ? "null" : "not null")
             << endl;
    }
    if(new_middle_node.get_child(TEST_CHILD) != lower_node){
        all_move_tests_passed &= false;
        cout << "Moved node's child pointer does not point to the existing child"
             << " of the original node\n";
    }
    if(lower_node->get_parent() != &new_middle_node){
        all_move_tests_passed &= false;
        cout << "Child node's parent pointer does not point to the moved node\n";
        if(lower_node->get_parent() == nullptr){
            cout << "Child node's parent pointer is null";
        }
        else if(lower_node->get_parent() == middle_node.get()){
            cout << "Child node's parent pointer points to the original parent" ;

        }
        else{
            cout << "Child node;s parent pointer does not point to the original parent"
                 << "and is not null";
        }
        cout << endl;
    }
    //if(tree.get_child(TEST_PARENT_CHILD).get() != &new_middle_node){
    //    all_move_tests_passed &= false;
    //    cout << "Parent's child pointer did not point to the new node\n";
    //    if(tree.get_child(TEST_PARENT_CHILD) == nullptr){
    //        cout << "Parent's child pointer was null";
    //    }
    //    else if(tree.get_child(TEST_PARENT_CHILD) == middle_node){
    //        cout << "Parent's child pointer points to the origninal node";
    //    }
    //    else{
    //        cout << "Parent's child pointer is not null "
    //             << "and does not point to the original child";
    //    }
    //    cout << endl;
    //}
    all_tests_passed &= all_move_tests_passed;

    cout << endl;

    return all_tests_passed;
}

bool extended_gcd_test_case(int a, int b){
    cout << "testing extended_gcd with " << a << " and " << b << endl;
    tuple<int,int,int> results = project_euler::extended_gcd(a,b);
    int gcd = std::get<0>(results);
    int a_coef = std::get<1>(results);
    int b_coef = std::get<2>(results);

    bool all_tests_passed = true;

    if (gcd <= 0){
        cout << "\tgcd, " << gcd << ", of " << a << " and " << b << " not positive\n";
        all_tests_passed &= false;
    }

    if ( a % gcd != 0 ){
        cout << "\tgcd of " << a << " and " << b << ", " << gcd << ", did not divide " << a << "\n";
        all_tests_passed &= false;
    }

    // cheak that the gcd found really is the greatest common divisor of a and b
    if ( b % gcd != 0 ){
        cout << "\tgcd of " << a << " and " << b << ", " << gcd << ", did not divide " << b << "\n";
        all_tests_passed &= false;
    }
    if( gcd == std::numeric_limits<int>::max() ){
        cout << "\tcannot test for divisors greater than gcd == INT_MAX\n";
    } else {
        for(auto i = gcd+1; i <= std::min(std::abs(a),std::abs(b));++i){
            if ( (a % i == 0) && (b % i == 0) ){
                cout << "\t" << i << " is a larger common divisors of " << a << " and " << b << " than the gcd, " << gcd << "\n";
                all_tests_passed &= false;
                break;
            } 
        }
    }

    // cheak Bezout's identity
    if ( a*a_coef + b*b_coef != gcd){
        cout << "\tthe coefficents " << a_coef << " and " << b_coef << " did not satisfy Bezout's identity for " << a << " and " << b << " with greatest common divisor " << gcd << "\n";
        all_tests_passed &= false;
    }

    if (all_tests_passed){
        cout << "\tall tests passed\n";
    }

    cout << std::flush;

    return all_tests_passed;
}

bool test_extended_gcd(){
    bool all_tests_passed = true;
    
    cout << "Testing extended_gcd" << endl;

    cout << "Testing standard behaviour" << endl;
    all_tests_passed &= extended_gcd_test_case(10,15);

    all_tests_passed &= extended_gcd_test_case(20,9);

    all_tests_passed &= extended_gcd_test_case(29,14);

    all_tests_passed &= extended_gcd_test_case(15,45);

    all_tests_passed &= extended_gcd_test_case(3,9);

    all_tests_passed &= extended_gcd_test_case(8,8);

    all_tests_passed &= extended_gcd_test_case(5,5);

    all_tests_passed &= extended_gcd_test_case(1904,5838);

    all_tests_passed &= extended_gcd_test_case(997,2934);

    all_tests_passed &= extended_gcd_test_case(997,1994);

    all_tests_passed &= extended_gcd_test_case(1465,1465);

    cout << "Testing behaviour close to INT_MAX" << endl;
    all_tests_passed &= extended_gcd_test_case(std::numeric_limits<int>::max(),14);

    all_tests_passed &= extended_gcd_test_case(std::numeric_limits<int>::max(),15);

    all_tests_passed &= extended_gcd_test_case(std::numeric_limits<int>::max(),2);

    all_tests_passed &= extended_gcd_test_case(std::numeric_limits<int>::max(),std::numeric_limits<int>::max()-2);

    all_tests_passed &= extended_gcd_test_case(std::numeric_limits<int>::max(),std::numeric_limits<int>::max()-1);

    all_tests_passed &= extended_gcd_test_case(std::numeric_limits<int>::max(),std::numeric_limits<int>::max());

    cout << "Testing negative inputs" << endl;
    all_tests_passed &= extended_gcd_test_case(-1,5);

    all_tests_passed &= extended_gcd_test_case(-10,5);

    all_tests_passed &= extended_gcd_test_case(-10,-5);

    all_tests_passed &= extended_gcd_test_case(10,-5);

    all_tests_passed &= extended_gcd_test_case(std::numeric_limits<int>::min(), 14);

    all_tests_passed &= extended_gcd_test_case(std::numeric_limits<int>::min(), -15);

    all_tests_passed &= extended_gcd_test_case(std::numeric_limits<int>::min(), std::numeric_limits<int>::min()+1);

    all_tests_passed &= extended_gcd_test_case(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

    cout << "Testing 0 inputs" << endl;

    tuple<int,int,int> results = project_euler::extended_gcd(0,29);
    if(results != std::make_tuple(29,0,1)){
        cout << "Calculating the extended gcd of 0 and 29 returned (" << std::get<0>(results) <<"," << std::get<1>(results) << "," << std::get<2>(results) << "instead of (29,0,1)" << endl;
        all_tests_passed &= false;
    }

    results = project_euler::extended_gcd(254,0);
    if(results != std::make_tuple(254,1,0)){
        cout << "Calculating the extended gcd of 254 and 0 returned (" << std::get<0>(results) <<"," << std::get<1>(results) << "," << std::get<2>(results) << ") instead of (254,1,0)" << endl;
        all_tests_passed &= false;
    }

    results = project_euler::extended_gcd(0,0);
    if(results != std::make_tuple(0,0,0)){
        cout << "Calculating the extended gcd of 0 and 0 returned (" << std::get<0>(results) <<"," << std::get<1>(results) << "," << std::get<2>(results) << "instead of (0,0,0)" << endl;
        all_tests_passed &= false;
    }

    cout << "Testing cases which lead to integer overflow" << endl;
    bool error_raised_correctly = false;
    constexpr int int_min = std::numeric_limits<int>::min();
    try{
        project_euler::extended_gcd(int_min, 0);
    } catch (std::overflow_error& oe) {
        error_raised_correctly = true;
    }
    cout << "extended_gcd(INT_MIN,0) "<< (error_raised_correctly ? "did" : "did not") << " correctly throw a std::overflow_error" << endl;
    all_tests_passed &= error_raised_correctly;
    
    error_raised_correctly = false;
    try{
        project_euler::extended_gcd(0, int_min);
    } catch (std::overflow_error& oe ){
        error_raised_correctly = true;
    }
    cout << "extended_gcd(0,INT_MIN) "<< (error_raised_correctly ? "did" : "did not") << " correctly throw a std::overflow_error" << endl;
    all_tests_passed &= error_raised_correctly;
    
    error_raised_correctly = false;
    try{
        project_euler::extended_gcd(int_min, int_min);
    } catch (std::overflow_error& oe) {
        error_raised_correctly = true;
    }
    cout << "extended_gcd(INT_MIN,INT_MIN) "<< (error_raised_correctly ? "did" : "did not") << " correctly throw a std::overflow_error" << endl;
    all_tests_passed &= error_raised_correctly;

    if(all_tests_passed){
        cout << "All tests on extended_gcd passed\n";
    }

    cout << endl;

    return all_tests_passed;
}

int main(){
    bool all_tests_passed = true;
    
    all_tests_passed &= test_primes_to_n();    

    //all_tests_passed &= test_prime_counting_function();

    all_tests_passed &= test_isqrt();

    all_tests_passed &= test_PythagoreanTripleTree();

    all_tests_passed &= test_extended_gcd();

    if(all_tests_passed){
        cout << "\nAll tests passed" << endl;
    }else{
        cout << "\nSome tests were failed" << endl;
    }
return 0;
}
