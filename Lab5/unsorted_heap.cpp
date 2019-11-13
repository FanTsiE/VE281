#include "unsorted_heap.h"
using namespace std;

template<typename TYPE, typename COMP = std::less<TYPE> >
unsorted_heap::unsorted_heap(COMP comp = COMP()){
    this->data=comp;
}

template<typename TYPE, typename COMP = std::less<TYPE> >
virtual void unsorted_heap::enqueue(const TYPE &val){
    this->data=val;
}

template<typename TYPE, typename COMP = std::less<TYPE> >
virtual TYPE unsorted_heap::dequeue_min(){

}