#include "ArbolBinarioOrd.h"
#include <queue>
#include <iostream>
using namespace std; 

template< class T >
ArbolBinarioOrd<T>::ArbolBinarioOrd(){
    this->raiz = NULL;
}

template< class T >
ArbolBinarioOrd<T>::~ArbolBinarioOrd(){
    if(this->raiz != NULL){
        delete this->raiz;
        this->raiz = NULL;
    }
}

template< class T >
bool ArbolBinarioOrd<T>::esVacio(){
    return this->raiz == NULL;
}

template< class T >
T ArbolBinarioOrd<T>::datoRaiz(){
    return (this->raiz)->obtenerDato();
}

//recurrente y se implementa acá y NO desde el nodo
template< class T >
int ArbolBinarioOrd<T>::altura(){
    if (this->esVacio())
        return -1;
    else
        return this->altura(this->raiz);    
}

template< class T >
int ArbolBinarioOrd<T>::altura(NodoBinario<T>* nodo){
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
int ArbolBinarioOrd<T>::tamano(){
    if (this->esVacio())
        return 0;
    else
        return this->tamano(this->raiz);
}

template< class T >
int ArbolBinarioOrd<T>::tamano(NodoBinario<T>* nodo){
    if (nodo == NULL)
        return 0;
    else
        return 1 + this->tamano(nodo->obtenerHijoIzq()) + this->tamano(nodo->obtenerHijoDer());
}

//iterativa
template< class T >
bool ArbolBinarioOrd<T>::insertar(T val){
    NodoBinario<T>* nodo = this->raiz;
    NodoBinario<T>* padre = this->raiz;
    bool insertado = false;
    bool duplicado = false;

    while (nodo != NULL) {
        padre = nodo;
        if (val < nodo->obtenerDato()) {
            nodo = nodo->obtenerHijoIzq();
        } else if (val > nodo->obtenerDato()) {
            nodo = nodo->obtenerHijoDer();
        } else {
            duplicado = true;
            break;
        }
    }
    
    if(!duplicado){
        NodoBinario<T>* nuevo= new NodoBinario<T>(val);
        if(nuevo != NULL){
            if(val > padre->obtenerDato())
            padre->fijarHijoIzq(nuevo);
            else
            padre->fijarHijoDer(nuevo);
        }
        insertado = true;
    }
    return insertado;
}

//iterativa
template< class T >
bool ArbolBinarioOrd<T>::eliminar(T val){
    if (this->esVacio()) return false;
    
    NodoBinario<T>* actual = this->raiz;
    NodoBinario<T>* padre = NULL;
    bool esHijoIzq = false;
    
    // Buscar el nodo a eliminar
    while (actual != NULL && actual->obtenerDato() != val) {
        padre = actual;
        if (val < actual->obtenerDato()) {
            actual = actual->obtenerHijoIzq();
            esHijoIzq = true;
        } else {
            actual = actual->obtenerHijoDer();
            esHijoIzq = false;
        }
    }
    
    if (actual == NULL) return false; // No encontrado
    
    // Caso 1: Nodo hoja
    if (actual->esHoja()) {
        if (padre == NULL) {
            this->raiz = NULL;
        } else if (esHijoIzq) {
            padre->fijarHijoIzq(NULL);
        } else {
            padre->fijarHijoDer(NULL);
        }
        delete actual;
    }
    // Caso 2: Nodo con un hijo
    else if (actual->obtenerHijoIzq() == NULL) {
        if (padre == NULL) {
            this->raiz = actual->obtenerHijoDer();
        } else if (esHijoIzq) {
            padre->fijarHijoIzq(actual->obtenerHijoDer());
        } else {
            padre->fijarHijoDer(actual->obtenerHijoDer());
        }
        actual->fijarHijoDer(NULL);
        delete actual;
    }
    else if (actual->obtenerHijoDer() == NULL) {
        if (padre == NULL) {
            this->raiz = actual->obtenerHijoIzq();
        } else if (esHijoIzq) {
            padre->fijarHijoIzq(actual->obtenerHijoIzq());
        } else {
            padre->fijarHijoDer(actual->obtenerHijoIzq());
        }
        actual->fijarHijoIzq(NULL);
        delete actual;
    }
    // Caso 3: Nodo con dos hijos
    else {
        NodoBinario<T>* sucesor = actual->obtenerHijoDer();
        NodoBinario<T>* padreSucesor = actual;
        
        while (sucesor->obtenerHijoIzq() != NULL) {
            padreSucesor = sucesor;
            sucesor = sucesor->obtenerHijoIzq();
        }
        
        actual->fijarDato(sucesor->obtenerDato());
        
        if (padreSucesor == actual) {
            padreSucesor->fijarHijoDer(sucesor->obtenerHijoDer());
        } else {
            padreSucesor->fijarHijoIzq(sucesor->obtenerHijoDer());
        }
        
        sucesor->fijarHijoDer(NULL);
        delete sucesor;
    }
    
    return true;
}

// iterativa
template< class T >
bool ArbolBinarioOrd<T>::buscar(T val) {
    NodoBinario<T>* nodo = this->raiz;
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
void ArbolBinarioOrd<T>::preOrden(){
    if (!this->esVacio())
        this->preOrden(this->raiz);
}

template< class T >
void ArbolBinarioOrd<T>::preOrden(NodoBinario<T>* nodo){
    if (nodo != NULL) {
        cout << nodo->obtenerDato() << " ";
        this->preOrden(nodo->obtenerHijoIzq());
        this->preOrden(nodo->obtenerHijoDer());
    }
}

// recurrente
template< class T >
void ArbolBinarioOrd<T>::inOrden() {
    if (!this->esVacio())
        this->inOrden(this->raiz);
}

template< class T >
void ArbolBinarioOrd<T>::inOrden(NodoBinario<T>* nodo) {
    if (nodo != NULL) {
        this->inOrden(nodo->obtenerHijoIzq());
        cout << nodo->obtenerDato() << " ";
        this->inOrden(nodo->obtenerHijoDer());
    }
}

//recurrente
template< class T >
void ArbolBinarioOrd<T>::posOrden(){
    if (!this->esVacio())
        this->posOrden(this->raiz);
}

template< class T >
void ArbolBinarioOrd<T>::posOrden(NodoBinario<T>* nodo){
    if (nodo != NULL) {
        this->posOrden(nodo->obtenerHijoIzq());
        this->posOrden(nodo->obtenerHijoDer());
        cout << nodo->obtenerDato() << " ";
    }
}

// iterativa
template< class T >
void ArbolBinarioOrd<T>::nivelOrden() {
    if (!this->esVacio()) {
        queue< NodoBinario<T>* > cola;
        cola.push(this->raiz);
        NodoBinario<T>* nodo;
        
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