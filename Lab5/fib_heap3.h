#ifndef FIB_HEAP_H
#define FIB_HEAP_H

#include <algorithm>
#include <cmath>
#include "priority_queue.h"
#include <list>
#include <vector>
// OVERVIEW: A specialized version of the 'heap' ADT implemented as a 
//           Fibonacci heap.
template<typename TYPE, typename COMP = std::less<TYPE> >
class fib_heap: public priority_queue<TYPE, COMP> {
public:
    typedef unsigned size_type;

    // EFFECTS: Construct an empty heap with an optional comparison functor.
    //          See test_heap.cpp for more details on functor.
    // MODIFIES: this
    // RUNTIME: O(1)
    fib_heap(COMP comp = COMP());

    // EFFECTS: Deconstruct the heap with no memory leak.
    // MODIFIES: this
    // RUNTIME: O(n)
    ~fib_heap();

    // EFFECTS: Add a new element to the heap.
    // MODIFIES: this
    // RUNTIME: O(1)
    virtual void enqueue(const TYPE &val);

    // EFFECTS: Remove and return the smallest element from the heap.
    // REQUIRES: The heap is not empty.
    // MODIFIES: this
    // RUNTIME: Amortized O(log(n))
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
    // Note: compare is a functor object
    COMP compare;


private:
    // Add any additional member functions or data you require here.
    // You may want to define a struct/class to represent nodes in the heap and a
    // pointer to the min node in the heap.



    void meld();

    struct node{
        TYPE key;
        vector<node*> children;
        node *parent= nullptr;
        int degree=0;
        int marked=0;
    };
    vector<vector<node*> > roots (64);
    node * min_node;
    unsigned int node_num;
};


template<typename TYPE, typename COMP>
fib_heap<TYPE, COMP>::fib_heap(COMP comp) {
    compare = comp;
    // Fill in the remaining lines if you need.
    min_node=nullptr;
    node_num=0;
}

template<typename TYPE, typename COMP>
fib_heap<TYPE, COMP>::~fib_heap(){}

template<typename TYPE, typename COMP>
void fib_heap<TYPE, COMP> :: enqueue(const TYPE &val) {
    auto *new_node=new node;
    new_node->key=val;
    new_node->parent=new_node;
    if(this->size()==1)min_node=new_node;
    else if (compare(val,min_node->key))min_node=new_node;
    new_node->degree=0;
    roots.push_back(temp);
    node_num++;
}

template<typename TYPE, typename COMP>
TYPE fib_heap<TYPE, COMP> :: dequeue_min() {
    TYPE temp=min_node->key;
    for(int i=0;i<min_node->children.size();i++){
        roots[min_node->children[i]->degree].push_back(min_node->children[i]);
    }
    /*for(int i=0;i<=roots[min_node->degree].size()-1;i++){
        if(roots[min_node->degree][i]->parent==min_node)break;
        roots[min_node->degree].erase(roots[min_node->degree][i]);
        node_num--;
    }*/
    typename vector<node*> ::iterator it=roots[min_node->degree].begin();
    for(;it!=roots[min_node->degree].end();it++){
        if(*it==min_node)break;
        if(it!=roots[min_node->degree].end()){
            roots[min_node->degree].erase(it--);
            node_num--;
        }
    }
    meld();
    return temp;
}

template<typename TYPE, typename COMP>
const TYPE &fib_heap<TYPE, COMP> :: get_min() const {
    return min_node->key;
}

template<typename TYPE, typename COMP>
bool fib_heap<TYPE, COMP> :: empty() const {
    return this->size()==0;
}

template<typename TYPE, typename COMP>
unsigned fib_heap<TYPE, COMP> :: size() const {
    return node_num;
}

template<typename TYPE, typename COMP>
void fib_heap<TYPE, COMP>::meld(){
    min_node=nullptr;
    for(auto it=roots.begin();it!=roots.end();it++){
        int deg=1;
        while(true){
            if(roots[deg].size()>1){
                node* node1=roots[deg][roots[deg].size()-1];
                roots[deg].pop_back();
                node* node2=roots[deg][roots[deg].size()-1];
                roots[deg].pop_back();

                if(compare(node1->key,node2->key)){
                    node1->children.push_back(node2);
                    node1->degree++;
                    node2->parent=node1;
                }
                else{
                    swap(node1,node2);
                    node1->children.push_back(node2);
                    node1->degree++;
                    node2->parent=node1;
                }
                roots[node1->degree].push_back(node1);
                if(min_node== nullptr||compare(min_node->key,node1->key))min_node=node1;
            }
            else if(roots[deg].size()==1){
                if(min_node== nullptr||compare(min_node->key,roots[deg][0]->key))min_node=roots[deg][0];
            }
            break;
        }
        deg++;
    }
}


// Add the definitions of the member functions here. Please refer to
// binary_heap.h for the syntax.

#endif //FIB_HEAP_H
