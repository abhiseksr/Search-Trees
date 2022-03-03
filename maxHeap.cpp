/* Priority Queue (Max Heap) implementation C/C++
Author - Abhishek Kumar*/

#include<iostream>
using namespace std;

class PriorityQueue{
    private:
        int size, capacity;
        void allocate(int newsize){
            int *temp = arr;
            arr = new int[newsize];
            for (int i=1;i<size;i++){
                arr[i] = temp[i];
            }
            capacity = newsize-1;
            delete[] temp;
        }
        void heapSort(){
            int n = size-1;
            while (n>1){
                if (arr[n]>arr[n/2]){
                    swap(arr[n],arr[n/2]);
                }
                else{
                    break;
                }
                n /= 2;
            }
            top = arr[1];
        }
        
        int heapify(){
            int temp = arr[1], n = 1;
            arr[1] = arr[--size];
            while (n<size){
                if (2*n<size && 2*n+1<size){
                    if (arr[2*n]>arr[2*n+1]){
                        if (arr[2*n]>arr[n]){
                            swap(arr[2*n],arr[n]);
                            n  = 2*n;
                        }
                        else{
                            break;
                        }
                    }
                    else{
                        if (arr[2*n+1]>arr[n]){
                            swap(arr[2*n+1],arr[n]);
                            n = 2*n+1;
                        }
                        else{
                            break;
                        }
                    }
                }
                else if (2*n<size){
                    if (arr[2*n]>arr[n]){
                        swap(arr[2*n],arr[n]);
                        n = 2*n;
                    }
                    else{
                        break;
                    }
                }
                else{
                    break;
                }
            }
            top = arr[1];
            return temp;
        }
    public:
        int top;
        int *arr = 0;
        PriorityQueue(){
            size = 1;
            capacity = 4;
            arr = new int[5];
        }
        void push (int data){
            if (size>capacity){
                allocate(capacity*2);
            }
            arr[size++] = data;
            heapSort();
        }

        int pop(){
            if (size==2) {
                size--;
                return arr[1];
            }
            return heapify();
        }

        int getSize(){
            return size;
        }

        int empty(){
            if (size<2) return 1;
            return 0;
        }

};

int main(){

    PriorityQueue p;
    p.push(3);
    p.push(4);
    p.push(5);
    p.push(1);
    p.push(18);
    p.push(10);
    p.push(19);
    p.push(5);
    p.push(3);
    p.push(6);
    p.push(22);
    p.push(5);
    p.push(16);
    p.push(99);
    while (!p.empty()){
        cout<<p.top<<' ';
        p.pop();
    }
    cout<<endl;
    p.push(9);
    p.push(10);
    p.push(11);
    for (int i=1;i<20;i++) p.push(i);
    while (!p.empty()){
        cout<<p.top<<' ';
        p.pop();
    }
    cout<<endl;
    return 0;
}