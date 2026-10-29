#include<iostream>
#include<vector>
#include<algorithm>
#include<random>
#include<chrono>
#include<string>
#include<iomanip>
#include<cstdlib>
using namespace std;
using namespace chrono;

struct Estadisticas{
    long long comparaciones=0;
    long long movimientos=0;
    long long intercambios=0;
    double tiempoMs=0.0;
};

void insertionSort(vector<int>&A,Estadisticas&e){
    int n=static_cast<int>(A.size());
    for(int i=1;i<n;i++){
        int key=A[i];
        int j=i-1;
        while(j>=0){
            e.comparaciones++;
            if(A[j]>key){
                A[j+1]=A[j];
                e.movimientos++;
                j--;
            }else{
                break;
            }
        }
        A[j+1]=key;
        e.movimientos++;
    }
}

int reducir(vector<int>&A,int inicio,int final,Estadisticas&e){
    int pivote=A[inicio+(final-inicio)/2];
    int izq=inicio;
    int der=final;
    while(izq<=der){
        while(izq<=final){
            e.comparaciones++;
            if(A[izq]<pivote){
                izq++;
            }else{
                break;
            }
        }
        while(der>=inicio){
            e.comparaciones++;
            if(A[der]>pivote){
                der--;
            }else{
                break;
            }
        }
        if(izq<=der){
            if(izq!=der){
                swap(A[izq],A[der]);
                e.intercambios++;
            }
            izq++;
            der--;
        }
    }
    return izq;
}

void quickSort(vector<int>&A,int inicio,int final,Estadisticas&e){
    if(inicio<final){
        int pos=reducir(A,inicio,final,e);
        quickSort(A,inicio,pos-1,e);
        quickSort(A,pos,final,e);
    }
}

double mediana(vector<double>tiempos){
    sort(tiempos.begin(),tiempos.end());
    int n=static_cast<int>(tiempos.size());
    if(n%2==1)return tiempos[n/2];
    return (tiempos[n/2-1]+tiempos[n/2])/2.0;
}

Estadisticas probarInsertion(const vector<int>&original,int repeticiones){
    Estadisticas resultado;
    vector<double>tiempos;
    for(int r=0;r<repeticiones;r++){
        vector<int>A=original;
        Estadisticas e;
        auto inicio=steady_clock::now();
        insertionSort(A,e);
        auto fin=steady_clock::now();
        e.tiempoMs=duration<double,milli>(fin-inicio).count();
        if(!is_sorted(A.begin(),A.end())){
            cerr<<"Error en Insertion Sort"<<endl;
            exit(EXIT_FAILURE);
        }
        tiempos.push_back(e.tiempoMs);
        if(r==0){
            resultado.comparaciones=e.comparaciones;
            resultado.movimientos=e.movimientos;
        }
    }
    resultado.tiempoMs=mediana(tiempos);
    return resultado;
}

Estadisticas probarQuickSort(const vector<int>&original,int repeticiones){
    Estadisticas resultado;
    vector<double>tiempos;
    for(int r=0;r<repeticiones;r++){
        vector<int>A=original;
        Estadisticas e;
        auto inicio=steady_clock::now();
        quickSort(A,0,static_cast<int>(A.size())-1,e);
        auto fin=steady_clock::now();
        e.tiempoMs=duration<double,milli>(fin-inicio).count();
        if(!is_sorted(A.begin(),A.end())){
            cerr<<"Error en QuickSort"<<endl;
            exit(EXIT_FAILURE);
        }
        tiempos.push_back(e.tiempoMs);
        if(r==0){
            resultado.comparaciones=e.comparaciones;
            resultado.intercambios=e.intercambios;
        }
    }
    resultado.tiempoMs=mediana(tiempos);
    return resultado;
}

void ejecutarPrueba(const string&nombre,const vector<int>&datos,int repeticiones){
    Estadisticas ins=probarInsertion(datos,repeticiones);
    Estadisticas qs=probarQuickSort(datos,repeticiones);
    cout<<"\n===== "<<nombre<<" =====\n";
    cout<<"Insertion Sort\n";
    cout<<"Tiempo mediano: "<<ins.tiempoMs<<" ms\n";
    cout<<"Comparaciones: "<<ins.comparaciones<<'\n';
    cout<<"Movimientos: "<<ins.movimientos<<'\n';
    cout<<"\nQuickSort\n";
    cout<<"Tiempo mediano: "<<qs.tiempoMs<<" ms\n";
    cout<<"Comparaciones: "<<qs.comparaciones<<'\n';
    cout<<"Intercambios: "<<qs.intercambios<<'\n';
}

int main(){
    const int n=5000;
    const int repeticiones=7;
    mt19937 generador(static_cast<unsigned int>(system_clock::now().time_since_epoch().count()));
    uniform_int_distribution<int>distribucion(0,9999);
    uniform_int_distribution<int>distribucionDuplicados(0,9);
    vector<int>aleatorios(n);
    vector<int>duplicados(n);
    for(int i=0;i<n;i++){
        aleatorios[i]=distribucion(generador);
        duplicados[i]=distribucionDuplicados(generador);
    }
    vector<int>ordenados=aleatorios;
    sort(ordenados.begin(),ordenados.end());
    vector<int>inversos=ordenados;
    reverse(inversos.begin(),inversos.end());
    cout<<fixed<<setprecision(6);
    cout<<"COMPARACION DE ALGORITMOS DE ORDENAMIENTO\n";
    cout<<"Codigo: 2026-119011\n";
    cout<<"Cantidad de elementos: "<<n<<'\n';
    cout<<"Repeticiones por algoritmo: "<<repeticiones<<'\n';
    cout<<"Tiempo expresado en milisegundos (ms)\n";
    ejecutarPrueba("ARREGLO ALEATORIO",aleatorios,repeticiones);
    ejecutarPrueba("ARREGLO ORDENADO",ordenados,repeticiones);
    ejecutarPrueba("ARREGLO INVERSO",inversos,repeticiones);
    ejecutarPrueba("ARREGLO CON DUPLICADOS",duplicados,repeticiones);
    cout<<"\nTodas las pruebas finalizaron correctamente.\n";
    return 0;
}  



