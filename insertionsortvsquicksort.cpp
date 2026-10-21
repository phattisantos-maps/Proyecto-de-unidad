#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void insertionSort(int A[],int n){
    for(int i=1;i<n;i++){
        int key=A[i];
        int j=i-1;
        while(j>=0 && A[j]>key){
            A[j+1]=A[j];
            j--;
        }
        A[j+1]=key;
    }
}

void Reduce(int A[],int inicio,int final){
    int izq=inicio;
    int der=final;
    int pos=izq;
    int cen=1;
    while(cen==1){
        cen=0;
        while(A[pos]<=A[der] && pos!=der){
            der=der-1;
        }
        if(pos!=der){
            int aux=A[pos];
            A[pos]=A[der];
            A[der]=aux;
            pos=der;
            while(A[pos]>=A[izq] && pos!=izq){
                izq=izq+1;
            }
            if(pos!=izq){
                aux=A[pos];
                A[pos]=A[izq];
                A[izq]=aux;
                pos=izq;
                cen=1;
            }
        }
        if(pos-1>inicio){
            Reduce(A,inicio,pos-1);
        }
        if(pos+1<final){
            Reduce(A,pos+1,final);
        }
    }
}

void QuickSort(int A[],int n){
    Reduce(A,0,n-1);
}

int main(){
    int n=5000;
    int A1[5000];
    int A2[5000];
    srand(time(0));
    for(int i=0;i<n;i++){
        int val=rand()%10000;
        A1[i]=val;
        A2[i]=val;
    }
    clock_t t1=clock();
    insertionSort(A1,n);
    clock_t t2=clock();
    cout<<"Insertion Sort tiempo: "<<double(t2-t1)/CLOCKS_PER_SEC<<"s"<<endl;
    clock_t t3=clock();
    QuickSort(A2,n);
    clock_t t4=clock();
    cout<<"QuickSort tiempo: "<<double(t4-t3)/CLOCKS_PER_SEC<<"s"<<endl;
    return 0;
}