#ifndef LAB5_FIB_TEST_H
#define LAB5_FIB_TEST_H
#include <algorithm>
#include <cmath>
#include "priority_queue.h"
#include <list>
#include <vector>
using namespace std;
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
    struct node{
        TYPE key;
        list<node> children;
        int degree=0;
        node(TYPE val,int deg){key=val;degree=deg;}
    };

    list<node>roots;
    typename std::list<node>::iterator min_node;
    unsigned int node_num;


    struct comp {
        COMP compare;
        bool operator()(const node &n1, const node &n2) const {
            return compare(n1.key,n2.key);
        }
    };


    //void consolidate();
    //void Fibonacci_Heap_Link(node *y,node *x);
};

template<typename TYPE, typename COMP>
fib_heap<TYPE, COMP>::fib_heap(COMP comp) {
    node_num=0;
    min_node= roots.begin();
}

template<typename TYPE, typename COMP>
fib_heap<TYPE, COMP>::~fib_heap(){
    roots.clear();
}

template<typename TYPE, typename COMP>
const TYPE &fib_heap<TYPE, COMP> :: get_min() const {
    return min_node->key;
}

template<typename TYPE, typename COMP>
void fib_heap<TYPE, COMP> :: enqueue(const TYPE &val) {
    if (roots.empty()) {
        roots.push_front(node(val,0));
        min_node=roots.begin();
    }
    else if (compare(val,(*min_node).key)) min_node=roots.insert(min_node,node(val,0));
    else roots.insert(min_node,node(val,0));
    node_num++;
}

template<typename TYPE, typename COMP>
TYPE fib_heap<TYPE, COMP> :: dequeue_min() {
    roots.splice(min_node,(*min_node).children);
    TYPE val=min_node->key;
    roots.erase(min_node);
    node_num--;
    if (min_node==roots.end()) min_node=roots.begin();
    unsigned int max_degree=(unsigned)(log(node_num)/log(1.618))+1;
    std::vector<typename std::list<node>::iterator> arr(max_degree);
    for (int i=0;i<max_degree;i++)arr[i]=roots.end();
    typename std::list<node>::iterator it=roots.begin();
    auto size=roots.size();
    it=roots.begin();
    for (int i=0;i<size;i++) {
        int flag=0;
        typename std::list<node>::iterator x=it;
        auto deg=(*x).degree;
        while (arr[deg]!=roots.end()) {
            typename std::list<node >::iterator y=arr[deg];
            if (compare((*y).key,(*x).key)) swap(x,y);
            (*x).children.push_back(move(*y));
            if (y==it) {
                it = roots.erase(y);
                flag = 1;
            }
            else roots.erase(y);
            (*x).degree++;
            arr[deg]=roots.end();
            deg++;
        }
        arr[deg]=x;
        if (flag==0) ++it;
    }
    min_node = min_element(roots.begin(), roots.end(), comp{compare});
    return val;
}


template<typename TYPE, typename COMP>
bool fib_heap<TYPE, COMP> :: empty() const {
    return node_num==0;
}

template<typename TYPE, typename COMP>
unsigned fib_heap<TYPE, COMP> :: size() const {
    return node_num;
}

/*template<typename TYPE, typename COMP>
void fib_heap<TYPE,COMP>:: consolidate() {
    int max_degree = static_cast<int>(floor(log(static_cast<double>(node_num)) / log(static_cast<double>(1 + sqrt(static_cast<double>(5))) / 2)));
    auto arr=new node*[max_degree+2];
    for(int i = 0;i<max_degree+2;i++) arr[i]=nullptr;
    //node *x=new node;
    //node *y=new node;
    node *x,*y,*temp;
    //typename vector<node*>::iterator it;
    for(auto it=roots.begin();it!=roots.end();++it) {
        x = *it;
        auto deg= (*it)->degree;

        while(arr[deg]!= nullptr) {
            y = arr[deg];
            if(!compare(x->key, y->key)) { temp=x;x=y;y=temp;}
            Fibonacci_Heap_Link(y,x);
            arr[deg] = NULL;
            deg++;
        }
        arr[deg] = x;
    }
    min_node = nullptr;
    for(int i = 0;i<max_degree+2;i++) {
        if(arr[i] != nullptr) {
            if(*min_node == NULL) {
               roots.clear();
               min_node = arr[i];
               roots.push_back(min_node);
            }
            else {
               roots.push_back(arr[i]);
                if(compare(arr[i]->key,min_node->key))
                    min_node=arr[i];
            }
        }
    }
    delete[] arr;
}*/

/*template<typename TYPE, typename COMP>
 void fib_heap<TYPE,COMP>::Fibonacci_Heap_Link(node *y, node *x) {
     typename list<node*>::iterator it=roots.begin();
     for(;it!=roots.end();){
         if(*it==y)roots.erase(it++);
         else it++;
     }
     x->children.push_back(y);
     y->parent=x;
     x->degree++;
}*/

#endif //LAB5_FIB_TEST_H
