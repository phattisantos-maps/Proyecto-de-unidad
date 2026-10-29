#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;
using namespace chrono;

void insertionSort(int A[],int n,long long &comparaciones,long long &movimientos){
    for(int i=1;i<n;i++){
        int key=A[i];
        int j=i-1;
        while(j>=0){
            comparaciones++;
            if(A[j]>key){
                A[j+1]=A[j];
                movimientos++;
                j--;
            }else{
                break;
            }
        }
        A[j+1]=key;
        movimientos++;
    }
}

int Reduce(int A[],int inicio,int final,long long &comparaciones,long long &intercambios){
    int pivote=A[inicio+(final-inicio)/2];
    int izq=inicio;
    int der=final;

    while(izq<=der){
        while(izq<=final&&A[izq]<pivote){
            comparaciones++;
            izq++;
        }
        while(der>=inicio&&A[der]>pivote){
            comparaciones++;
            der--;
        }
        if(izq<=der){
            if(izq!=der){
                int aux=A[izq];
                A[izq]=A[der];
                A[der]=aux;
                intercambios++;
            }
            izq++;
            der--;
        }
    }
    return izq;
}

void QuickSort(int A[],int inicio,int final,long long &comparaciones,long long &intercambios){
    if(inicio<final){
        int pos=Reduce(A,inicio,final,comparaciones,intercambios);
        QuickSort(A,inicio,pos-1,comparaciones,intercambios);
        QuickSort(A,pos,final,comparaciones,intercambios);
    }
}

int main(){
    const int n=5000;
    int A1[n];
    int A2[n];

    srand(time(0));

    for(int i=0;i<n;i++){
        int val=rand()%10000;
        A1[i]=val;
        A2[i]=val;
    }

    long long compIns=0,movIns=0;
    auto t1=steady_clock::now();
    insertionSort(A1,n,compIns,movIns);
    auto t2=steady_clock::now();

    long long compQS=0,intQS=0;
    auto t3=steady_clock::now();
    QuickSort(A2,0,n-1,compQS,intQS);
    auto t4=steady_clock::now();

    double tiempoIns=duration<double,milli>(t2-t1).count();
    double tiempoQS=duration<double,milli>(t4-t3).count();

    cout<<"===== RESULTADOS ====="<<endl;
    cout<<"Cantidad de elementos: "<<n<<endl;
    cout<<"Insertion Sort tiempo: "<<tiempoIns<<" ms"<<endl;
    cout<<"Comparaciones: "<<compIns<<endl;
    cout<<"Movimientos: "<<movIns<<endl;
    cout<<"----------------------"<<endl;
    cout<<"QuickSort tiempo: "<<tiempoQS<<" ms"<<endl;
    cout<<"Comparaciones: "<<compQS<<endl;
    cout<<"Intercambios: "<<intQS<<endl;

    return 0;
}




