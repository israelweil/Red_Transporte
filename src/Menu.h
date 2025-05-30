// Menu.h
#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include "Grafos.h"

using namespace std;

class Menu {
private:
    Grafos grafo;

    void agregarCiudad() {
        string nombre;
        cout << "Ingrese el nombre de la ciudad: ";
        cin >> nombre;
        grafo.insertarVertice(nombre);
    }

    void agregarCarretera() {
        string c1, c2;
        cout << "Ciudad origen: ";
        cin >> c1;
        cout << "Ciudad destino: ";
        cin >> c2;
        grafo.insertarArista(c1, c2);
    }

    void ordenarCarreteras() {
        grafo.mostrarCiudades();
        int opcion;
        string ciudad, criterio;
        cout << "Ingrese el nombre de la ciudad para ordenar sus carreteras: ";
        cin >> ciudad;
        cout << "Ingrese criterio de orden:\n";
        cout << "1. Distancia\n2. Tiempo\nSeleccione una opcion: "<<endl;
        cin >> opcion;
        if (opcion == 1) {
            criterio = "distancia";
        } else if (opcion == 2) {
            criterio = "tiempo";
        } else {
            cout << "Opcion no valida. Usando 'distancia' por defecto." << endl;
            criterio = "distancia";
        }
        grafo.ordenarCarreteras(ciudad, criterio);
        grafo.listaAdyacencia();
    }

    void mostrarCarreteras() {
        cout << "\nLista de adyacencia:\n";
        grafo.listaAdyacencia();
    }
    void mostrarCiudades() {
        grafo.mostrarCiudades();
    }

public:
    void ejecutar() {
        int opcion;
        do {
            cout << "\n--- Menu del Sistema de Rutas ---\n";
            cout << "1. Agregar ciudad\n";
            cout << "2. Agregar carretera\n";
            cout << "3. Ordenar carreteras por distancia o tiempo (Quick Sort)\n";
            cout << "4. Mostrar carreteras\n";
            cout << "5. Mostrar ciudades\n";
            cout << "6. Salir\n";
            cout << "Seleccione una opcion: ";
            cin >> opcion;

            switch (opcion) {
                case 1:
                    agregarCiudad();
                    break;
                case 2:
                    agregarCarretera();
                    break;
                case 3:
                    ordenarCarreteras();
                    break;
                case 4:
                    mostrarCarreteras();
                    break;
                case 5:
                    mostrarCiudades();
                    break;
                case 6:
                    cout << "Saliendo del programa...\n";
                    break;
                default:
                    cout << "Opción no válida. Intente de nuevo.\n";
                    return;
            }
        } while (opcion != 6);
    }
};

#endif
