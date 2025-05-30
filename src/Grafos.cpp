#include <iostream>
//
// Created by cland on 29/05/2025.
//
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
        cout << "ya existe ese vertice"<<endl;
        return;
    }

    Vertice * nuevo = new Vertice(n);
    if (principio == nullptr) {
        principio = nuevo;
    } else {
        Vertice * temp = principio;
        while (temp -> siguiente != nullptr) { // me coloca en el ultimo valor
            temp = temp ->siguiente;
        }
        temp -> siguiente = nuevo;
        cout << "se inserto el vertice:  " << n << endl;
    }
}

void Grafos::insertarArista(string origen, string destino) {
    Vertice * vorigen = obtenerVertice(origen);
    Vertice * vdestino = obtenerVertice(destino);

    if (vorigen == nullptr || vdestino == nullptr) {
        cout << "Uno o ambos vertices no existen" << endl;
        return;
    }

    int distancia, tiempo;
    cout << "Ingrese la distancia entre " << origen << " y " << destino << ": ";
    cin >> distancia;
    cout << "Ingrese el tiempo entre " << origen << " y " << destino << ": ";
    cin >> tiempo;

    Arista * nuevaOrigen = new Arista(vdestino, distancia, tiempo);
    nuevaOrigen -> siguiente = vorigen -> arista;
    vorigen -> arista = nuevaOrigen;

    Arista * nuevaDestino = new Arista(vorigen, distancia, tiempo);
    nuevaDestino -> siguiente = vdestino -> arista;
    vdestino -> arista = nuevaDestino;

    cout << "Se inserto la arista de " << origen << " y " << destino << endl;
}


void Grafos::listaAdyacencia() {
    Vertice * v = principio;
    while (v != nullptr) {
        cout << v->nombre << " -> ";
        Arista * a = v->arista;
        while (a != nullptr) {
            cout << a->destino->nombre << " (D: " << a->distancia << ", T: " << a->tiempo << ") ";
            a = a->siguiente;
        }
        cout << endl;
        v = v->siguiente;
    }
}



void Grafos::eliminarArista(string origen, string destino){
    Vertice* vorigen = obtenerVertice(origen);
    Vertice * vdestino = obtenerVertice(destino);
    if(vorigen == nullptr || vdestino==nullptr){
        cout << "no existe uno o los dos vertices" << endl;
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
        cout << "no se encontro la arista" << endl;
        return;
    }else{
        if(anterior==nullptr) vorigen->arista = actual->siguiente;
        else anterior->siguiente = actual->siguiente;
        delete actual;
    }
    //arista destino->origen
    Arista* actual2 = vdestino->arista;
    Arista* anterior2 = nullptr;
    while(actual2 != nullptr && actual2->destino != vorigen){
        anterior2 = actual2;
        actual2=actual2->siguiente;
    }
    if(actual2 == nullptr){
        cout << "no se encontro la arista" << endl;
        return;
    }else{
        if(anterior2==nullptr) vdestino->arista = actual2->siguiente;
        else anterior2->siguiente = actual2->siguiente;
        delete actual2;
    }
    cout << "se elimino la arista entre " << origen << " y " << destino << endl;
};

// tengo que eliminar toda la lista de aristas que tiene y ya puedo eliminar el vertice
Grafos::~Grafos() {
    Vertice * v = principio;
    while (v != nullptr) {
        Arista * a = v -> arista; // aqui entro a la lista de aristas de este vertice
        while (a != nullptr) {
            Arista * tempA = a;
            a = a -> siguiente;
            delete tempA;
        }
        Vertice * tempV = v;
        v =v-> siguiente;
        delete tempV;
    }
    cout<<"Se libero la memoria"<< endl;
}

void Grafos::ejecutar() {
    insertarVertice("A");
    insertarVertice("B");
    insertarVertice("C");
    insertarArista("A","B");
    insertarArista("A","C");
    listaAdyacencia();
    eliminarArista("A","B");
    listaAdyacencia();

}