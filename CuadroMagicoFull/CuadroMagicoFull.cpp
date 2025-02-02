// CuadroMagicoFull.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include <stdio.h>
#include <tchar.h>
#include <conio.h>
#include <algorithm>
#include <vector>
#include <stack>
#include <iostream>
#include <ctime>        
#include <cstdlib>

using namespace std;
stack<vector<int>> pila;
vector<int> nodoMeta;
vector<int> nodoInicial;
int profundidadMaxima = 0;

bool izquierda(vector<int> arreglo, int posicionCero, int orden) {
	return !(posicionCero % orden == 0) && (posicionCero - 1 >= 0);
}

vector<int> moverIzquierda(vector<int> arreglo, int posicionCero, int orden) {	
	arreglo[posicionCero] = arreglo[posicionCero - 1];
	arreglo[posicionCero - 1] = 0;
	return arreglo;
}

bool derecha(vector<int> arreglo, int posicionCero, int orden) {
	return !((posicionCero + 1) % orden == 0) && ((posicionCero + 1) < orden*orden);
}

vector<int> moverDerecha(vector<int> arreglo, int posicionCero, int orden) {
	arreglo[posicionCero] = arreglo[posicionCero + 1];
	arreglo[posicionCero + 1] = 0;
	return arreglo;
}

bool arriba(vector<int> arreglo, int posicionCero, int orden) {
	return posicionCero - orden >= 0;
}

vector<int> moverArriba(vector<int> arreglo, int posicionCero, int orden) {
	arreglo[posicionCero] = arreglo[posicionCero - orden];
	arreglo[posicionCero - orden] = 0;
	return arreglo;
}

bool abajo(vector<int> arreglo, int posicionCero, int orden) {
	return posicionCero + orden < orden*orden;
}

vector<int> moverAbajo(vector<int> arreglo, int posicionCero, int orden) {
	arreglo[posicionCero] = arreglo[posicionCero + orden];
	arreglo[posicionCero + orden] = 0;
	return arreglo;
}

bool sonIguales(vector<int> tableroMeta, vector<int> tableroActual) {

	for (size_t i = 0; i < tableroMeta.size(); i++)
	{
		if (tableroMeta[i] != tableroActual[i]) {
			return false;
		}
	}
	return true;
}

int encontrarEspacio(vector<int> arreglo) {
	for (size_t i = 0; i < arreglo.size(); i++) {
		if (arreglo[i] == 0) {
			return i;
		}
	}
	return -1;
}

void imprimirTablero(vector<int> arreglo) {
	for (size_t i = 0; i < arreglo.size(); i++)
	{
		if (i % ((int)sqrt(arreglo.size())) == 0) {
			cout << "\n" << endl;
		}
		cout << arreglo[i] << " ";
	}
	cout << endl;
}

void imprimirPila(stack<vector<int>> pila) {
	while (!pila.empty())
	{
		imprimirTablero(pila.top());
		pila.pop();
		cout << "---------------------------" << endl;
	}
}

bool busqueda(vector<int> nodo,int profundidad) {
	int espacio = encontrarEspacio(nodo);
	int orden = (int)sqrt(nodo.size());
	pila.push(nodo);
	if (sonIguales(nodo,nodoMeta)) {
		return true;
	}
	else  if (profundidad < profundidadMaxima) {
		profundidad++;
		if (izquierda(nodo, espacio, orden)) {
			vector<int> nodito = moverIzquierda(nodo, espacio, orden);
			if (busqueda(nodito, profundidad)) {
				return true;
			}
		}
		if (arriba(nodo, espacio, orden)) {
			vector<int> nodito = moverArriba(nodo, espacio, orden);
			if (busqueda(nodito, profundidad)) {
				return true;
			}
		}
		if (derecha(nodo, espacio, orden)) {
			vector<int> nodito = moverDerecha(nodo, espacio, orden);
			if (busqueda(nodito, profundidad)) {
				return true;
			}
		}
		if (abajo(nodo, espacio, orden)) {
			vector<int> nodito = moverAbajo(nodo, espacio, orden);
			if (busqueda(nodito, profundidad)) {
				return true;
			}
		}
	}
	pila.pop();
	return false;
}

void llenarArreglos(vector<int>& tableroInicial,vector<int>& tableroMeta,int orden) {
	int donde = orden * orden;
	for (size_t i = 0 ; i < donde ; i++) {
		tableroInicial.push_back(i);
	}
	
	for (size_t i = 1 ; i < tableroInicial.size() ; i++) {
		tableroMeta.push_back(i);
	}
	tableroMeta.push_back(0);
	srand(unsigned(time(0)));
	random_shuffle(tableroInicial.begin(), tableroInicial.end());
}

int main()
{
	int orden = 0;
	profundidadMaxima = 0;

	cout << "Ingrese el orden(N x N) del tablero: "; cin >> orden; cout << endl;
	cout << "Ingrese la profundidad maxima: "; cin >> profundidadMaxima; cout << endl;

	llenarArreglos(nodoInicial,nodoMeta,orden);
	cout << "Tablero Inicial:"<<endl;
	imprimirTablero(nodoInicial);
	cout << "---------------------------" << endl;
	cout << "Procesado sea paciente ..." << endl;
	if(busqueda(nodoInicial,0)){
		cout << "Encontrado "<<pila.size()<<endl;
		imprimirPila(pila);
	}
	else {
		cout << "No Encontrado" << endl;
	}
	
	cout << endl;
	system("pause");
    return 0;
}

