#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <climits>
#include<ctime>
#include<cassert>
using namespace std;


void BubbleSort(int n, int a[]){
    for(int i=0;i<n-1;i++){
        for (int j=i+1;j<n;j++){
            if(a[i]>a[j]){
            int temp=a[j];
            a[j]=a[i];
            a[i]=temp;
            }
        }
    }
}
void InsertionSort(int n, int a[]){
    for (int i=1;i<n;i++){
        int tmp= a[i], j = i-1;
        while (j>=0 && tmp<a[j]){
            a[j+1] = a[j];
            --j;
        }
        a[j+1] = tmp;
    }
}
void SelectionSort(int n,int a[]){
    int min=0;
    for(int i=0;i<n-1;i++){
       min=i;
       for(int j=i+1;j<n;j++){
           if(a[j]<a[min])min=j;
           int temp=a[i];
           a[i]=a[min];
           a[min]=temp;
        }
    }
}
void Merge(int a[],int left, int mid ,int right){
    int i, j, k;
    int n1 = mid-left + 1;
    int n2 =  right - mid;
    int sub1[n1], sub2[n2];
    for (i = 0; i < n1; i++)sub1[i] = a[left + i];
    for (j = 0; j < n2; j++)sub2[j] = a[mid+1+j];
    i = 0;j = 0;k =left;
    while (i < n1 && j < n2){
        if (sub1[i] <= sub2[j]) {
            a[k] = sub1[i];
            i++;
        }
        else {
            a[k] = sub2[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        a[k] = sub1[i];
        i++;
        k++;
    }
    while (j < n2) {
        a[k] = sub2[j];
        j++;
        k++;
    }
}
void MergeSort(int a[], int left, int right) {
    int len=right-left+1;
    if (left >= right) return;
    int mid = (left+right)/2;
    MergeSort(a, left, mid);
    MergeSort(a, mid+1, right);
    Merge(a, left, mid, right);
}

int Partition(int a[],int left,int right){
    int pivot = a[left];
    int i = left - 1, j = right + 1;
    while(true) {
        while(a[i]<pivot)i++;
        while(a[j]>pivot)j--;
        if(i>=j)return j;
       int temp=a[i];
       a[i]=a[j];
       a[j]=temp;
    }
}
int Partition_Helper(int a[], int left, int right) {
    srand(time(nullptr));
    int pivotat = left + rand() % (right - left);
    int temp=a[pivotat];
    a[pivotat]=a[left];
    a[left]=temp;
    return Partition(a, left, right);
}

void QuickSort(int a[], int left, int right){
    if(left>=right)return;
    int pivotat=Partition_Helper(a,left,right);
    QuickSort(a, left, pivotat);
    QuickSort(a, pivotat+1, right);
}

int RanSelection(int a[],int i,int left,int right){
    int r=0;
    if(left==right)return a[right];
    int pivotat = Partition_Helper(a, left, right);
    if (pivotat -left +1== i){
        r=a[pivotat];
        return r;
    }
    else if (pivotat -left+ 1 > i){
        r=RanSelection(a, i, left, pivotat - 1);
        return r;
    }
    r=RanSelection(a, i - (pivotat + 1) + left, pivotat + 1, right);
    return r;
}

int DetPartion(int a[],int p,int left, int right){
    int i=left;
    for (int j = left; j <= right- 1; j++) {
        if (a[j] <= p) {
            int temp=a[i];
            a[i]=a[j];
            a[j]=temp;
            i++;
        }
    }
    int tmp=p;
    p=a[i];
    a[i]=tmp;
    return i;
}

int DetSelection(int a[],int i,int left,int right){
    int len=right-left+1;
    int res=0;
    int pivot=0;
    int n=len/5;
    if(len==1)return a[right];
    if(len<10){
        InsertionSort(len,a);
        return a[i-1];
    }
    int b[5];
    int c[n];
    for(int k=0;k<n;k++){
        for(int j=0;j<5;j++){
            b[j]=a[j+5*k];
            InsertionSort(5,b);
            c[k]=b[2];
        }
    }
    pivot=DetSelection(c,n/2,0,n-1);
    int pivotat = DetPartion(a, pivot, left, right);
    if (pivotat -left +1== i){
        res=a[pivotat];
        return res;
    }
    else if (pivotat -left+ 1 > i){
        res=DetSelection(a, i, left, pivotat - 1);
        return res;
    }
    res=DetSelection(a, i - (pivotat + 1) + left, pivotat + 1, right);
    return res;
}


int main() {
    int n,p,q=0,res=0;
    cin>>p;
    cin>>n;
    int *a=new int[n]();
    if(p<5) {
        for (int i = 0; i < n; i++)cin >> a[i];
    }
    else{
        cin>>q;
        for (int i = 0; i < n; i++)cin >> a[i];
    }
    if(p==0) BubbleSort(n,a);
    if(p==1)InsertionSort(n,a);
    if(p==2)SelectionSort(n,a);
    if(p==3)MergeSort(a,0,n-1);
    if(p==4)QuickSort(a,0,n-1);
    if(p==5)res=RanSelection(a,q,0,n-1);
    if(p==6)res=DetSelection(a,q,0,n-1);
    if(p<5){
        for(int i=0;i<n;i++)cout<<a[i]<<endl;
    }
    else cout<<"The order-"<<q<<" item is "<<res;
    return 0;
}