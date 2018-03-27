#ifndef PROJECT_EULER_PYTHAGOREAN_TRIPLES
#define PROJECT_EULER_PYTHAGOREAN_TRIPLES

#include "Project_Euler.h"

#include <cstddef>
#include <array>
#include <list>
#include <algorithm>
#include <memory>
#include <stdexcept>
#include <iterator>

namespace pythagorean_triple_internal {
    template<typename T>
    class PythagoreanTripleTree_IncreasingIterator;

    template<typename T>
    class PythagoreanTripleTree_HypotenuseIterator;

    template<typename T>
    class PythagoreanTripleTree_PerimeterIterator;
}

namespace project_euler{
    template<typename T>
    class PythagoreanTripleTree {
        public:
            typedef std::shared_ptr<PythagoreanTripleTree<T>> child_ptr;
            typedef PythagoreanTripleTree<T>* parent_ptr;
            typedef pythagorean_triple_internal::PythagoreanTripleTree_HypotenuseIterator<T> hypotenuse_iterator;
            typedef pythagorean_triple_internal::PythagoreanTripleTree_PerimeterIterator<T> perimeter_iterator;
            static constexpr char TREE_BRANCHES = 3;
            PythagoreanTripleTree<T>():
                    parent(nullptr),
                    triple{3,4,5},// Smallest Pythagorean triple
                    children{} {
            
            }
            
            PythagoreanTripleTree<T>(T a, T b):
                    parent(nullptr),
                    triple{a,b,isqrt(a*a+b*b)},
                    children{}{

                if( triple[HYPOTENUSE] == -1 ){
                    throw std::invalid_argument(
                "Given values do not form a valid pythagorean triple");
                }
            }

            // Copying tree nodes is forbidden, as it is then ambiguous which version children
            // should regard as their parent
            PythagoreanTripleTree<T>(const PythagoreanTripleTree<T>&) = delete;
            PythagoreanTripleTree<T> operator=(const PythagoreanTripleTree&) = delete;

            PythagoreanTripleTree<T>(PythagoreanTripleTree<T>&& node):
                    parent(node.parent),
                    triple(node.triple),
                    children(node.children){
                for(auto &child: node.children){
                    if(child != nullptr){
                        child->parent = this;
                        child = nullptr;
                    }
                }
                if(node.get_parent() != nullptr){
                    //for(auto &child:(node.parent)->children){
                    //    if(child.get() == &node){
                    //        child = this;
                    //        break;
                    //    }
                    //}
                    node.parent = nullptr;
                }
            }

            // assignemnt is forbidden as triple value is immutable
            PythagoreanTripleTree<T>& operator=(PythagoreanTripleTree&& node) = delete;

            ~PythagoreanTripleTree<T>(){
                for(auto child: children){
                    if(child != nullptr){
                        child->parent = nullptr;
                    }
                }
            }

            T get_first_side() const noexcept{
                return triple[FIRST_SIDE];
            }
            T get_second_side() const noexcept{
                return triple[SECOND_SIDE];
            }
            T get_hypotenuse() const noexcept{
                return triple[HYPOTENUSE];
            }
            child_ptr get_child(std::size_t child)const {
                if(children[child] == nullptr){
                     makechild(child);
                }
                return children[child];
           }
           parent_ptr get_parent() const noexcept{
                return parent;
           }

           hypotenuse_iterator begin_hypotenuse_iterator(){
                return hypotenuse_iterator(*this);
           }

           perimeter_iterator begin_perimitor_iterator(){
                return perimeter_iterator(*this);
           }


        private:
            typedef const PythagoreanTripleTree<T>* const_parent_ptr;
            static constexpr char TRIPLE_SIZE = 3; // No shit...

            static constexpr unsigned char FIRST_SIDE = 0;
            static constexpr unsigned char SECOND_SIDE = 1;
            static constexpr unsigned char HYPOTENUSE = 2;

            parent_ptr parent;
            const std::array<T,TRIPLE_SIZE> triple;
            mutable std::array<child_ptr,TREE_BRANCHES> children;

            static constexpr std::array<std::array<std::array<T,TRIPLE_SIZE>,TRIPLE_SIZE>,TREE_BRANCHES> BRANCH_MATRICES = {{
                {{ {1,-2,2},
                   {2,-1,2},
                   {2,-2,3} }},

                {{ {1,2,2},
                   {2,1,2},
                   {2,2,3} }},

                {{ {-1,2,2},
                   {-2,1,2},
                   {-2,2,3} }},
                }};

            PythagoreanTripleTree<T>(T a, T b, T c, parent_ptr prnt):
                    parent(prnt),
                    triple{a,b,c},
                    children{nullptr,nullptr,nullptr}{
            
            }
            PythagoreanTripleTree<T>(T a, T b, T c, const_parent_ptr prnt):
                    parent(const_cast<parent_ptr>(prnt)),
                    triple{a,b,c},
                    children{nullptr,nullptr,nullptr}{
            
            }
            void makechild(std::size_t child) const{
                T new_triple[] = {0,0,0};
                for(unsigned char i = 0; i < TRIPLE_SIZE; ++i){
                    for(unsigned char j = 0; j < TRIPLE_SIZE; ++j){
                        new_triple[i] += BRANCH_MATRICES[child][i][j]*triple[j]; 
                    }
                }
                children[child] = child_ptr(new PythagoreanTripleTree<T>(
                                     new_triple[FIRST_SIDE],
                                     new_triple[SECOND_SIDE],
                                     new_triple[HYPOTENUSE],
                                     const_cast<parent_ptr>(this)));
            }


            
    };
   template<typename T>
   constexpr std::array<std::array<std::array<T,PythagoreanTripleTree<T>::TRIPLE_SIZE>,PythagoreanTripleTree<T>::TRIPLE_SIZE>,PythagoreanTripleTree<T>::TREE_BRANCHES> 
       PythagoreanTripleTree<T>::BRANCH_MATRICES;
}

namespace pythagorean_triple_internal {

    // given a comparison operator between nodes of a PythagoreanTripleTree
    // with the properties that
    //      1) any 2 nodes can be compared
    //      2) any node is strictly less than its immediate children
    // this class will iterate through the entire tree in the order defined
    // by the comparison
    template<typename T>
    class PythagoreanTripleTree_IncreasingIterator: 
            public std::iterator<std::forward_iterator_tag,project_euler::PythagoreanTripleTree<T>> {
        public:
            typedef project_euler::PythagoreanTripleTree<T> tree;
            typedef tree* tree_ptr;
            explicit PythagoreanTripleTree_IncreasingIterator(tree& start)
                :current_value(&start),
                 upcoming_values{}{}
            bool operator==(const PythagoreanTripleTree_IncreasingIterator& other_it){
                return this->current_value == other_it.current_value;
            }
            bool operator!=(const PythagoreanTripleTree_IncreasingIterator& it){
                return !this->operator==(it);
            }
            tree_ptr operator->(){
                return current_value;
            }

            tree& operator*(){
                return *current_value;
            }
        private:
            constexpr static short unsigned TREE_BRANCHES = 3;
            tree_ptr current_value;
            std::list<tree_ptr> upcoming_values;
            virtual bool less_than(const tree_ptr,const tree_ptr) = 0;
        protected:
            void increment(){
                std::array<tree_ptr,3> current_children;
                for(short unsigned i = 0; i < TREE_BRANCHES; ++i){
                    current_children[i] = current_value->get_child(i).get();
                }
                std::sort(current_children.begin(),current_children.end(),
                        [this](const tree_ptr first, const tree_ptr second)
                        {return this->less_than(first,second);});

                auto upcoming_value = upcoming_values.begin();
                for(auto &child: current_children){
                    for(; upcoming_value != upcoming_values.end(); ++upcoming_value){
                        if(less_than(child,*upcoming_value)){
                            break;
                        }
                    }
                    upcoming_values.insert(upcoming_value,child);
                }
                current_value = upcoming_values.front();
                upcoming_values.pop_front();
            }
    };

    template<typename T>
    class PythagoreanTripleTree_HypotenuseIterator:public PythagoreanTripleTree_IncreasingIterator<T>{
         public:
             explicit PythagoreanTripleTree_HypotenuseIterator<T>(project_euler::PythagoreanTripleTree<T>& start):
                PythagoreanTripleTree_IncreasingIterator<T>(start){}
             PythagoreanTripleTree_HypotenuseIterator operator++(){
                this->increment();
                return *this;
             }
             PythagoreanTripleTree_HypotenuseIterator& operator++(int){
                PythagoreanTripleTree_HypotenuseIterator temp(*this);
                this->increment();
                return temp;
             }
         private:
             typedef typename PythagoreanTripleTree_IncreasingIterator<T>::tree_ptr tree_ptr;
             bool less_than(const tree_ptr triple1,const tree_ptr triple2){
                 return triple1->get_hypotenuse() < triple2->get_hypotenuse();
             }
    };

    template<typename T>
    class PythagoreanTripleTree_PerimeterIterator: public PythagoreanTripleTree_IncreasingIterator<T>{
        public:
             PythagoreanTripleTree_PerimeterIterator& operator++(){
                this->increment();
                return *this;
             }
             PythagoreanTripleTree_PerimeterIterator operator++(int){
                PythagoreanTripleTree_PerimeterIterator temp(*this);
                this->increment();
                return temp;
             }
         private:
             typedef typename PythagoreanTripleTree_IncreasingIterator<T>::tree_ptr tree_ptr;
             bool less_than(tree_ptr triple1, tree_ptr triple2){
                 return triple1->get_first_side()
                      + triple1->get_second_side()
                      + triple1->get_hypotenuse()
                      < triple2->get_first_side()
                      + triple2->get_second_side()
                      + triple2->get_hypotenuse();
             }
    };
}
#endif
