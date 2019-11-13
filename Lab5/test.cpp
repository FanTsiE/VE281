#include <iostream>
#include <getopt.h>
#include <ctime>
#include "unsorted_heap.h"
#include "binary_heap.h"
#include "fib_heap.h"
using namespace std;

struct pt{
    int x;
    int y;
};
struct path{
    int path_cost=-1;
    pt point;
    int weight=0;
    bool reached=false;
    path *pred=nullptr;

    struct comp{
        bool operator()(path p1, path p2)const{
            if(p1.path_cost!=p2.path_cost)return p1.path_cost<p2.path_cost;
            else if(p1.point.x!=p2.point.x)return p1.point.x<p2.point.x;
            else return p1.point.y<p2.point.y;
        }
    };
};

void trace_back_path(path *N){
    if(N->pred!=nullptr)trace_back_path(N->pred);
   /* cout << "(" <<N->point.x<< ", " << N->point.y << ")" << endl;*/
}
int main(int argc, char* argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int opt;
    bool verbose = false;
    string imp;
    string string1="vi:";
    const char *str= string1.c_str();
    static struct option long_options[] = {
            {"implementation", required_argument, NULL, 'i'},
            {"verbose",        no_argument,       NULL, 'v'},
            {NULL,             0,                 NULL, 0},
    };
    while ((opt = getopt_long(argc, argv, str, long_options, NULL)) != -1) {
        if (opt == 'v')verbose = true;
        else if (opt == 'i')imp = optarg;
    }
    clock_t start, end;
    int length, width;
    cin >> length;
    cin >> width;
    int start_x, start_y, end_x, end_y;
    cin >> start_x >> start_y;
    path S;
    S.point.x = start_x;
    S.point.y = start_y;
    cin >> end_x >> end_y;
    start=clock();
    auto **p = new path *[width];
    for (int i = 0; i < width; i++) {
        p[i] = new path[length];
    }
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < length; j++) {
            cin >> p[i][j].weight;
            p[i][j].point.y = i;
            p[i][j].point.x = j;
        }
    }

    priority_queue<path , path::comp> *PQ;
    if (imp == "UNSORTED") PQ = new unsorted_heap<path, path::comp>;
    else if (imp == "BINARY") PQ = new binary_heap<path, path::comp>;
    else if (imp == "FIBONACCI") PQ = new fib_heap<path, path::comp>;

    int step = 0;
    p[start_y][start_x].path_cost = p[start_y][start_x].weight;
    p[start_y][start_x].reached = true;
    PQ->enqueue(p[start_y][start_x]);
    while (!PQ->empty()) {
        path C = PQ->dequeue_min();
        /*if (verbose) {
            cout << "Step " << step << endl;
            cout << "Choose cell (" << C.point.x << ", " << C.point.y << ") with accumulated length "
                 << C.path_cost << "." << endl;
        }*/
        step++;
        if (C.point.x < length - 1 && !p[C.point.y][C.point.x + 1].reached) {
            auto *N = new path();
            N = &p[C.point.y][C.point.x + 1];
            N->path_cost = C.path_cost + N->weight;
            N->reached = true;
            N->pred = &p[C.point.y][C.point.x];
            if (N->point.x == end_x && N->point.y == end_y) {
                /*if(verbose) {
                    cout << "Cell (" << N->point.x << ", " << N->point.y << ") with accumulated length " << N->path_cost
                         << " is the ending point." << endl;
                }
                cout << "The shortest path from (" << S.point.x << ", " << S.point.y << ") to (" << N->point.x << ", "
                     << N->point.y << ") is " << N->path_cost << "." << endl;
                cout << "Path:" << endl;*/
                trace_back_path(N);
                end=clock();
                cout<<(double)(end-start)/CLOCKS_PER_SEC<<endl;
                return 0;
            } else {
                PQ->enqueue(*N);
                /*if (verbose) {
                    cout << "Cell (" << N->point.x << ", " << N->point.y << ") with accumulated length "
                         << N->path_cost << " is added into the queue." << endl;
                }*/
            }
        }
        if (C.point.y < width - 1 && !p[C.point.y + 1][C.point.x].reached) {
            auto *N = new path();
            N = &p[C.point.y + 1][C.point.x];
            N->path_cost = C.path_cost + N->weight;
            N->reached = true;
            N->pred =&p[C.point.y][C.point.x];
            if (N->point.x == end_x && N->point.y == end_y) {
                /*if(verbose) {
                    cout << "Cell (" << N->point.x << ", " << N->point.y << ") with accumulated length " << N->path_cost
                         << " is the ending point." << endl;
                }
                cout << "The shortest path from (" << S.point.x << ", " << S.point.y << ") to (" << N->point.x << ", "
                     << N->point.y << ") is " << N->path_cost << "." << endl;
                cout << "Path:" << endl;*/
                trace_back_path(N);
                end=clock();
                cout<<(double)(end-start)/CLOCKS_PER_SEC<<endl;
                return 0;
            } else {
                PQ->enqueue(*N);
               /* if (verbose) {
                    cout << "Cell (" << N->point.x << ", " << N->point.y << ") with accumulated length "
                         << N->path_cost << " is added into the queue." << endl;
                }*/
            }
        }
        if (C.point.x > 0 && !p[C.point.y][C.point.x - 1].reached) {
            auto *N = new path();
            N = &p[C.point.y][C.point.x - 1];
            N->path_cost = C.path_cost + N->weight;
            N->reached = true;
            N->pred = &p[C.point.y][C.point.x];
            if (N->point.x == end_x && N->point.y == end_y) {
                /*if(verbose) {
                    cout << "Cell (" << N->point.x << ", " << N->point.y << ") with accumulated length " << N->path_cost
                         << " is the ending point." << endl;
                }
                cout << "The shortest path from (" << S.point.x << ", " << S.point.y << ") to (" << N->point.x << ", "
                     << N->point.y << ") is " << N->path_cost << "." << endl;
                cout << "Path:" << endl;*/
                trace_back_path(N);
                end=clock();
                cout<<(double)(end-start)/CLOCKS_PER_SEC<<endl;
                return 0;
            } else {
                PQ->enqueue(*N);
                /*if (verbose) {
                    cout << "Cell (" << N->point.x << ", " << N->point.y << ") with accumulated length "
                         << N->path_cost << " is added into the queue." << endl;
                }*/
            }
        }

        if (C.point.y > 0 && !p[C.point.y - 1][C.point.x].reached) {
            auto *N = new path();
            N = &p[C.point.y - 1][C.point.x];
            N->path_cost = C.path_cost + N->weight;
            N->reached = true;
            N->pred =&p[C.point.y][C.point.x];
            if (N->point.x == end_x && N->point.y == end_y) {
                //if(verbose) {
                   // cout << "Cell (" << N->point.x << ", " << N->point.y << ") with accumulated length " << N->path_cost
                    //     << " is the ending point." << endl;
                //}
                //cout << "The shortest path from (" << S.point.x << ", " << S.point.y << ") to (" << N->point.x << ", "
                //     << N->point.y << ") is " << N->path_cost << "." << endl;
               // cout << "Path:" << endl;
                trace_back_path(N);
                end=clock();
                cout<<(double)(end-start)/CLOCKS_PER_SEC<<endl;
                return 0;
            } else {
                PQ->enqueue(*N);
                if (verbose) {
                    //cout << "Cell (" << N->point.x<< ", " << N->point.y << ") with accumulated length "
                        // << N->path_cost << " is added into the queue." << endl;
                }
            }
        }

    }
    return 0;
}
