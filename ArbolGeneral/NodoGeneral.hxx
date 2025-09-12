#include "NodoGeneral.h"

template< class T >
NodoGeneral<T>::NodoGeneral() {
    this->desc.clear();
}

template< class T >
NodoGeneral<T>::~NodoGeneral() {
    std::list< NodoGeneral<T>* >::iterator it;
    for (it = this->desc.begin(); it != this->desc.end(); it++) {
        delete *it;
    }
    this->desc.clear();
}

template< class T >
T& NodoGeneral<T>::obtenerDato() {
    return this->dato;
}

template< class T >
void NodoGeneral<T>::fijarDato(T& val) {
    this->dato = val;
}
template< class T >
void NodoGeneral<T>::limpiarLista() {
    desc.clear();   
}
template< class T >
void NodoGeneral<T>::adicionarDesc(T& nval) {
    NodoGeneral<T>* nuevo = new NodoGeneral<T>();
    nuevo->fijarDato(nval);
    this->desc.push_back(nuevo);
}
template< class T >
bool NodoGeneral<T>::eliminarDesc(T& val) {
    // buscar el nodo con el valor dado
    std::list< NodoGeneral<T>* >::iterator it;
    NodoGeneral<T> *aux;
    bool eliminado = false;

    for (it = this->desc.begin(); it != this->desc.end(); it++) {
        aux = *it;
        if (aux->obtenerDato() == val)
            break;
    }
    // si lo encontramos, eliminarlo
    if (it != this->desc.end()) {
        delete *it;
        this->desc.erase(it);
        eliminado = true;
    }
    return eliminado;
}