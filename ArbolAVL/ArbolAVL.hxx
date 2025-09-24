#include "ArbolAVL.h"
#include <queue>
#include <iostream>
using namespace std; 

template< class T >
ArbolAVL<T>::ArbolAVL(){
    this->raiz = NULL;
}

template< class T >
ArbolAVL<T>::~ArbolAVL(){
    if(this->raiz != NULL){
        delete this->raiz;
        this->raiz = NULL;
    }
}

template< class T >
bool ArbolAVL<T>::esVacio(){
    return this->raiz == NULL;
}

template< class T >
T ArbolAVL<T>::datoRaiz(){
    return (this->raiz)->obtenerDato();
}

//recurrente y se implementa acá y NO desde el nodo
template< class T >
int ArbolAVL<T>::altura(){
    if (this->esVacio())
        return -1;
    else
        return this->altura(this->raiz);    
}

template< class T >
int ArbolAVL<T>::altura(NodoAVL<T>* nodo){
    int valt;
    if (nodo->esHoja()){
        valt = 0;
    } else{
        int valt_izq = -1;
        int valt_der = -1;
        if(nodo->obtenerHijoIzq() != NULL)
            valt_izq = this->altura(nodo->obtenerHijoIzq());
        if(nodo->obtenerHijoDer() != NULL)
            valt_der = this->altura(nodo->obtenerHijoDer());
        if(valt_izq > valt_der)
            valt = valt_izq + 1;
        else
            valt = valt_der + 1;  
    }
    return valt;
}

//recurrente
template< class T >
int ArbolAVL<T>::tamano(){
    if (this->esVacio())
        return 0;
    else
        return this->tamano(this->raiz);
}

template< class T >
int ArbolAVL<T>::tamano(NodoAVL<T>* nodo){
    if (nodo == NULL)
        return 0;
    else
        return 1 + this->tamano(nodo->obtenerHijoIzq()) + this->tamano(nodo->obtenerHijoDer());
}

//iterativa
template< class T >
bool ArbolAVL<T>::insertar(T val){
    
}

//iterativa
template< class T >
bool ArbolAVL<T>::eliminar(T val){
    
}

// iterativa
template< class T >
bool ArbolAVL<T>::buscar(T val) {
    NodoAVL<T>* nodo = this->raiz;
    bool encontrado = false;

    while (nodo != NULL && !encontrado) {
        if (val < nodo->obtenerDato()) {
            nodo = nodo->obtenerHijoIzq();
        } else if (val > nodo->obtenerDato()) {
            nodo = nodo->obtenerHijoDer();
        } else {
            encontrado = true;
        }
    }
    return encontrado;
}

//recurrente
template< class T >
void ArbolAVL<T>::PreOrden(){
    if (!this->esVacio())
        this->PreOrden(this->raiz);
}

template< class T >
void ArbolAVL<T>::PreOrden(NodoAVL<T>* nodo){
    if (nodo != NULL) {
        cout << nodo->obtenerDato() << " ";
        this->PreOrden(nodo->obtenerHijoIzq());
        this->PreOrden(nodo->obtenerHijoDer());
    }
}

// recurrente
template< class T >
void ArbolAVL<T>::InOrden() {
    if (!this->esVacio())
        this->InOrden(this->raiz);
}

template< class T >
void ArbolAVL<T>::InOrden(NodoAVL<T>* nodo) {
    if (nodo != NULL) {
        this->InOrden(nodo->obtenerHijoIzq());
        cout << nodo->obtenerDato() << " ";
        this->InOrden(nodo->obtenerHijoDer());
    }
}

//recurrente
template< class T >
void ArbolAVL<T>::PosOrden(){
    if (!this->esVacio())
        this->PosOrden(this->raiz);
}

template< class T >
void ArbolAVL<T>::PosOrden(NodoAVL<T>* nodo){
    if (nodo != NULL) {
        this->PosOrden(nodo->obtenerHijoIzq());
        this->PosOrden(nodo->obtenerHijoDer());
        cout << nodo->obtenerDato() << " ";
    }
}

// iterativa
template< class T >
void ArbolAVL<T>::NivelOrden() {
    if (!this->esVacio()) {
        queue< NodoAVL<T>* > cola;
        cola.push(this->raiz);
        NodoAVL<T>* nodo;
        
        while (!cola.empty()) {
            nodo = cola.front();
            cola.pop();
            cout << nodo->obtenerDato() << " ";
            
            if (nodo->obtenerHijoIzq() != NULL)
                cola.push(nodo->obtenerHijoIzq());
            if (nodo->obtenerHijoDer() != NULL)
                cola.push(nodo->obtenerHijoDer());
        }
    }
}

template<class T>
void ArbolAVL<T>::rotarDerecha(NodoAVL<T>* nodo){

}

template<class T>
void ArbolAVL<T>::rotarIzquierda(NodoAVL<T>* nodo){

}

template<class T>
void ArbolAVL<T>::rotarIzqDer(NodoAVL<T>* nodo){

}

template<class T>
void ArbolAVL<T>::rotarDerIzq(NodoAVL<T>* nodo){

}

template<class T>
bool ArbolAVL<T>::balancear(NodoAVL<T>* nodo){

}