#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include <algorithm>
#include "priority_queue.h"
using namespace std;
// OVERVIEW: A specialized version of the 'heap' ADT implemented as a binary
//           heap.
template<typename TYPE, typename COMP = std::less<TYPE> >
class binary_heap: public priority_queue<TYPE, COMP> {
public:
  typedef unsigned size_type;

  // EFFECTS: Construct an empty heap with an optional comparison functor.
  //          See test_heap.cpp for more details on functor.
  // MODIFIES: this
  // RUNTIME: O(1)
  binary_heap(COMP comp = COMP());

  // EFFECTS: Add a new element to the heap.
  // MODIFIES: this
  // RUNTIME: O(log(n))
  virtual void enqueue(const TYPE &val);

  // EFFECTS: Remove and return the smallest element from the heap.
  // REQUIRES: The heap is not empty.
  // MODIFIES: this
  // RUNTIME: O(log(n))
  virtual TYPE dequeue_min();

  // EFFECTS: Return the smallest element of the heap.
  // REQUIRES: The heap is not empty.
  // RUNTIME: O(1)
  virtual const TYPE &get_min() const;

  // EFFECTS: Get the number of elements in the heap.
  // RUNTIME: O(1)
  virtual size_type size() const;

  // EFFECTS: Return true if the heap is empty.
  // RUNTIME: O(1)
  virtual bool empty() const;

private:
  // Note: This vector *must* be used in your heap implementation.
  std::vector<TYPE> data;
  // Note: compare is a functor object
  COMP compare;
  void percolate_up() ;
  void percolate_down();

private:
  // Add any additional member functions or data you require here.
};

template<typename TYPE, typename COMP>
binary_heap<TYPE, COMP> :: binary_heap(COMP comp) {
    compare = comp;
    data.push_back(TYPE());
    // Fill in the remaining lines if you need.
}

template<typename TYPE, typename COMP>
void binary_heap<TYPE, COMP> :: enqueue(const TYPE &val) {
   data.push_back(val);
   percolate_up();
}

template<typename TYPE, typename COMP>
TYPE binary_heap<TYPE, COMP> :: dequeue_min() {
    swap(data[1],data[data.size()-1]);
    auto min=data[data.size()-1];
    data.pop_back();
    percolate_down();
    return min;
}

template<typename TYPE, typename COMP>
const TYPE &binary_heap<TYPE, COMP> :: get_min() const {
    if (empty())return data[0];
    else return data[1];
}

template<typename TYPE, typename COMP>
bool binary_heap<TYPE, COMP> :: empty() const {
    return this->size()==0;
}

template<typename TYPE, typename COMP>
unsigned binary_heap<TYPE, COMP> :: size() const {
    auto size=data.size()-1;
    return static_cast<unsigned int>(size);
}

template<typename TYPE, typename COMP>
void binary_heap<TYPE, COMP> ::percolate_up()  {
    auto id=size();
    while(id > 1 ){
        if(compare(data[id], data[id/2])){
            swap(data[id],data[id/2]);
            id = id / 2;
        }
        else break;
    }
}

template<typename TYPE, typename COMP>
void binary_heap<TYPE, COMP> ::percolate_down() {
    auto size=this->size();
    unsigned id=1;
    while(id*2<=size){
        if(2*id+1>size){
            if(!compare(data[id],data[id*2])){
                swap(data[id],data[2*id]);
                id=2*id;
            }
            else break;
        }
        else {
            if(!compare(data[id],data[id*2])&&compare(data[id*2],data[2*id+1])){
                swap(data[id],data[2*id]);
                id=2*id;
            }
            else if(!compare(data[id],data[id*2+1])&&compare(data[2*id+1],data[2*id])){
                swap(data[id],data[2*id+1]);
                id=2*id+1;
            }
            else break;
        }

    }
}
#endif //BINARY_HEAP_H
