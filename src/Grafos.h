//
// Created by cland on 29/05/2025.
//

#ifndef GRAFOS_H
#define GRAFOS_H
#include <string>
#include <vector>

struct Arista;
using namespace std;
struct Vertice {
    string nombre;
    Vertice * siguiente;
    Arista * arista;


    explicit Vertice(string n): nombre(n),siguiente(nullptr),arista(nullptr){};
};

struct Arista {
    Arista * siguiente; // apuntador
    Vertice * destino;
    int distancia;
    int tiempo;

    Arista(Vertice *  d, int dist, int tiemp) : destino(d), distancia(dist), tiempo(tiemp), siguiente(nullptr) {};
};

class Grafos {
private:
    Vertice * principio;
    Vertice * obtenerVertice(string n);
public:
    Grafos();
    ~Grafos();
    void insertarVertice(string n);
    void insertarArista(string origen, string destino);
    void listaAdyacencia();
    void eliminarArista(string origen, string destino);
    void ordenarCarreteras(string nombreCiudad, string criterio); // "distancia" o "tiempo"
    void quickSort(vector<Arista *> &a, int inicio, int fin, const string &criterio);
    void mostrarCiudades();

    void ejecutar();
};

#endif //GRAFOS_H
