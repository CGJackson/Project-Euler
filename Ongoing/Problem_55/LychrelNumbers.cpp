// Solves Project Euler problem 55 Lychrel numbers
// A Lychrel number is a number that never produces a palindrome after repeatedly summing with its digit reversed 
// counterpart

// The problem is to find all Lychrel numbers below 10,000

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <algorithm>

const int MAX_ITERATIONS = 50; //No non-Lychrel number below 10,000 requires more than 50 iteration to produce a palindrome
const int SEARCH_LIMIT = 10000;
const std::size_t SEARCH_LIMIT_DIGITS = 5;

typedef std::list<int> revnumber;

revnumber itorevnumber(int n){
    revnumber result;
    for(; n > 0;n /= 10 ){
        int c = n % 10;
        result.push_back(c);
    }
    return result;
}

const int BIG_NUMBER = 99999;

int revnumtoi(revnumber n){
    int m = 0, exp = 1;
    if( n.size() > SEARCH_LIMIT_DIGITS){
        return BIG_NUMBER;
    }

    for(auto d = n.rbegin(); d != n.rend();++d){
        m += *d * exp;
        exp *= 10;
    }
    return m;
}

inline bool is_palindrome(revnumber n){
    return std::equal(n.begin(), n.end(), n.rbegin());
}

//return the sum of the number and its digit-reversed counterpart
inline revnumber Lychrel_step(const revnumber *n){
    const int BASE = 10;
    revnumber m;
    int carry = 0;
    auto backward = n->rbegin();
    for(auto forward = n->begin(); forward != n->end(); ++forward,++backward){
        int raw_sum = *forward + *backward + carry;
        if( raw_sum >= BASE ){
            raw_sum -= BASE;
            carry = 1;
        }
        else {
            carry = 0;
        }
        m.push_front(raw_sum);
    }
    if(carry){
        m.push_back(1);
    }
    return m;
}

bool is_Lychrel(int n, std::vector<int> *sequence){
    sequence->push_back(n);
    revnumber ns = itorevnumber(n);
    for(std::size_t i = 0; i < MAX_ITERATIONS; ++i){
        revnumber ms = Lychrel_step(&ns);
        if(is_palindrome(ms)){
            return false;
        }
        if(ms.size() < SEARCH_LIMIT_DIGITS){
                sequence->push_back(revnumtoi(ms));
        }
        ns = ms;
    }
    std::cerr << n << ' ';
    return true;
}

int main(int argc, char **argv){
    int Lychrel_numbers = 0;
    std::vector<bool> number_checked (SEARCH_LIMIT + 1, false);
    for(std::size_t i = 0; i < SEARCH_LIMIT; ++i){
        while(number_checked[i]){
            ++i;
        }
        std::vector<int> sequence;
        if(is_Lychrel(i, &sequence) ){
            Lychrel_numbers += 1;sequence.size();
            std::cerr << Lychrel_numbers << std::endl;
        }else{
        //for(auto n: sequence){
        //    number_checked[n] = true;
        }//}
    }
    std::cout << "\nThe number of Lycrel numbers below " << SEARCH_LIMIT 
              << " is " << Lychrel_numbers << '\n' << std::endl;
}
