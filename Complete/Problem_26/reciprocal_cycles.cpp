#include <thread>
#include <mutex>
#include <vector>
#include <utility>
#include <iostream>

class Result {
    int n = 0;
    int cycle_length = 0;
    std::mutex m;
    public:
        void update_result(int new_n,int new_cycle_length){
            std::lock_guard<std::mutex> lock(m);
            if(new_cycle_length > cycle_length){
                cycle_length = new_cycle_length;
                n = new_n;
            }
        }
        int get_n(){
            std::lock_guard<std::mutex> lock(m);
            return n;
        }
        int get_cycle_length(){
            std::lock_guard<std::mutex> lock(m);
            return cycle_length;
        }
};

int cycle_length(int n){
    if(n % 2 == 0 || n % 5 == 0){ // numbers that are divisable by 2 or 5 do not have a purely-cyclic reciprocal
        return 0;
    }
    short first_carry = 10 % n;
    short cycle_carry = (10*first_carry) % n;
    int cycle_length = 1;
    while(cycle_carry != first_carry){
        ++cycle_length;
        cycle_carry = (10*cycle_carry) % n;
    }
    return cycle_length;
}

void find_longest_cycle(int start, int end, Result& result){
    int longest_cycle = 0;
    int n_longest_cycle = 0;
    for(int i = start; i < end; ++i){
        int length = cycle_length(i);
        if(length > longest_cycle){
            longest_cycle = length;
            n_longest_cycle = i;
        }
    }
    result.update_result(n_longest_cycle,longest_cycle);
}
constexpr int max_N = 1000;
constexpr int thread_count = 4;

int main(){
    std::vector<std::thread> threads(thread_count-1);
    
    int numbers_per_thread = (max_N-1)/thread_count +1;

    Result result;

    for(int i = 0; i < thread_count -1; ++i){
        threads[i] = std::thread(find_longest_cycle,i*numbers_per_thread,(i+1)*numbers_per_thread, std::ref(result));
    }

    find_longest_cycle(numbers_per_thread*(thread_count-1), max_N, result);

    for(auto& thd: threads){
        thd.join();
    }
    
    std::cout << result.get_n()<< std::endl; 
}
