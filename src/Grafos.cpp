#include <functional>
#include <iostream>
#include <vector>
using namespace std;
#include "Grafos.h"
Grafos::Grafos():principio(nullptr){}

Vertice * Grafos::obtenerVertice(string n) {
    Vertice * temp = principio;
    while (temp != nullptr) {
        if (temp ->nombre == n) {
            return temp;
        }
        temp = temp -> siguiente;
    }
    return nullptr;
}

void Grafos::insertarVertice(string n) {
    if (obtenerVertice(n) != nullptr) {
        cout << "ya existe esta ciudad"<<endl;
        return;
    }

    Vertice * nuevo = new Vertice(n);
    if (principio == nullptr) {
        principio = nuevo;
    } else {
        Vertice * temp = principio;
        while (temp -> siguiente != nullptr) {
            temp = temp ->siguiente;
        }
        temp -> siguiente = nuevo;
        cout << "se inserto la ciudad:  " << n << endl;
    }
}

void Grafos::insertarArista(string origen, string destino) {
    Vertice * vorigen = obtenerVertice(origen);
    Vertice * vdestino = obtenerVertice(destino);

    if (vorigen == nullptr || vdestino == nullptr) {
        cout << "Una o ambas ciudades no existen" << endl;
        return;
    }

    int distancia, tiempo;
    cout << "Ingrese la distancia en kilometros entre " << origen << " y " << destino << ": "<<endl;
    cin >> distancia;
    cout << " Ingrese el tiempo en horas entre " << origen << " y " << destino << ": "<<endl;
    cin >> tiempo;

    Arista * nuevaOrigen = new Arista(vdestino, distancia, tiempo);
    nuevaOrigen -> siguiente = vorigen -> arista;
    vorigen -> arista = nuevaOrigen;

    Arista * nuevaDestino = new Arista(vorigen, distancia, tiempo);
    nuevaDestino -> siguiente = vdestino -> arista;
    vdestino -> arista = nuevaDestino;

    cout << "Se inserto la carretera entre " << origen << " y " << destino << endl;
}


void Grafos::listaAdyacencia() {
    Vertice * v = principio;
    while (v != nullptr) {
        cout << "|"<<v->nombre <<"|"<< " -> "<<"|";
        Arista * a = v->arista;
        while (a != nullptr) {
            cout << a->destino->nombre << " (D: " << a->distancia << " km, T: " << a->tiempo << " hrs) "<<"|";
            a = a->siguiente;
        }
        cout <<"|"<< endl;
        v = v->siguiente;
    }
}



void Grafos::eliminarArista(string origen, string destino){
    Vertice* vorigen = obtenerVertice(origen);
    Vertice * vdestino = obtenerVertice(destino);
    if(vorigen == nullptr || vdestino==nullptr){
        cout << "no existe una o las dos ciudades" << endl;
        return;
    }
    //arista origen->destino
    Arista* actual = vorigen->arista;
    Arista* anterior = nullptr;
    while(actual != nullptr && actual->destino != vdestino){
        anterior = actual;
        actual=actual->siguiente;
    }
    if(actual == nullptr){
        cout << "no se encontro la carretera" << endl;
        return;
    }else{
        if(anterior==nullptr) vorigen->arista = actual->siguiente;
        else anterior->siguiente = actual->siguiente;
        delete actual;
    }
    Arista* actual2 = vdestino->arista;
    Arista* anterior2 = nullptr;
    while(actual2 != nullptr && actual2->destino != vorigen){
        anterior2 = actual2;
        actual2=actual2->siguiente;
    }
    if(actual2 == nullptr){
        cout << "no se encontro la carretera" << endl;
        return;
    }else{
        if(anterior2==nullptr) vdestino->arista = actual2->siguiente;
        else anterior2->siguiente = actual2->siguiente;
        delete actual2;
    }
    cout << "se elimino la carretera entre " << origen << " y " << destino << endl;
}

void Grafos::mostrarCiudades() {
    if (principio == nullptr) {
        cout << "No hay ciudades registradas." << endl;
        return;
    }

    cout << "Ciudades en la red de transporte:" << endl;
    Vertice* actual = principio;
    while (actual != nullptr) {
        cout << "- " << actual->nombre << endl;
        actual = actual->siguiente;
    }
}


void Grafos::quickSort(vector<Arista*>& a, int inicio, int fin, const string& criterio) {
    if (inicio >= fin) return;

    int i = inicio;
    int d = fin;
    int pivote = (criterio == "distancia") ? a[(inicio + fin) / 2]->distancia : a[(inicio + fin) / 2]->tiempo;

    while (i <= d) {
        while ((criterio == "distancia" && a[i]->distancia < pivote) ||
               (criterio == "tiempo" && a[i]->tiempo < pivote)) ++i;

        while ((criterio == "distancia" && a[d]->distancia > pivote) ||
               (criterio == "tiempo" && a[d]->tiempo > pivote)) --d;

        if (i <= d) {
            swap(a[i], a[d]);
            ++i;
            --d;
        }
    }

    quickSort(a, inicio, d, criterio);
    quickSort(a, i, fin, criterio);
}

void Grafos::ordenarCarreteras(string nombreCiudad, string criterio) {
    Vertice* ciudad = obtenerVertice(nombreCiudad);
    if (!ciudad) {
        cout << "La ciudad no existe" << endl;
        return;
    }

    vector<Arista*> aristas;
    Arista* actual = ciudad->arista;
    while (actual != nullptr) {
        aristas.push_back(actual);
        actual = actual->siguiente;
    }

    quickSort(aristas, 0, aristas.size() - 1, criterio);

    size_t i = 0;
    while (i < aristas.size() - 1) {
        aristas[i]->siguiente = aristas[i + 1];
        ++i;
    }
    aristas[i]->siguiente = nullptr;
    ciudad->arista = aristas[0];

    cout << "Carreteras de " << nombreCiudad << " ordenadas por " << criterio << "." << endl;
}


void Grafos::mostrarVerticeConAristas(const string& nombreCiudad) {
    Vertice* v = obtenerVertice(nombreCiudad);

    cout << v->nombre << " -> ";
    Arista* a = v->arista;
    while (a != nullptr) {
        cout << a->destino->nombre << " (D: " << a->distancia << " km, T: " << a->tiempo << " hrs) ";
        a = a->siguiente;
    }
    cout << endl;
}
bool Grafos::vacio() {
    if (principio==nullptr) return 0;
}

Grafos::~Grafos() {
    Vertice * v = principio;
    while (v != nullptr) {
        Arista * a = v -> arista;
        while (a != nullptr) {
            Arista * tempA = a;
            a = a -> siguiente;
            delete tempA;
        }
        Vertice * tempV = v;
        v =v-> siguiente;
        delete tempV;
    }
    cout<<"\n\nSe libero la memoria"<< endl;
}

