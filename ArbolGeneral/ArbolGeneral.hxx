#include "ArbolGeneral.h"

template <class T>
ArbolGeneral<T>::ArbolGeneral() {
    this->raiz = NULL;
}

template <class T>
ArbolGeneral<T>::ArbolGeneral(T val) {
    NodoGeneral<T>* nodo = new NodoGeneral<T>;
    nodo->fijarDato(val);
    this->raiz = nodo;
}

template <class T>
ArbolGeneral<T>::~ArbolGeneral() {
    delete this->raiz;
    this->raiz = NULL;
}

template <class T>
bool ArbolGeneral<T>::esVacio() {
    return this->raiz == NULL;
}

template <class T>
NodoGeneral<T>* ArbolGeneral<T>::obtenerRaiz() {
    return this->raiz;
}
template <class T>
void ArbolGeneral<T>::fijarRaiz(NodoGeneral<T>* nraiz) {
    this->raiz = nraiz;
}

template <class T>
bool ArbolGeneral<T>::insertarNodo(T padre, T n) {
    // si el arbol es vacio:
    // - crear nuevo nodo, asignar dato, poner ese nodo como raiz
    if (this->esVacio()) {
        NodoGeneral<T>* nuevo = new NodoGeneral<T>;
        nuevo->fijarDato(n);
        this->fijarRaiz(nuevo);
        return true;
    }

    // si hay al menos un nodo en el arbol:
    // - revisar el nodo donde estoy para ver si coincide con padre
    // - si es el padre, insertar ahi el nuevo hijo
    if (this->raiz->obtenerDato() == padre) {
        this->raiz->adicionarDesc(n);
        return true;
    }

    // - si no es el padre, revisar cada nodo hijo y llamar a insertar alli
    std::list< NodoGeneral<T>* >::iterator it;
    NodoGeneral<T>* aux;
    bool insertado = false;
    for (it = this->raiz->desc.begin(); it != this->raiz->desc.end(); it++) {
        aux = *it;
        ArbolGeneral<T> subarbol(aux);
        if (subarbol.insertarNodo(padre, n)) {
            insertado = true;
            break;
        }
    }
    return insertado;
}

template <class T>
bool ArbolGeneral<T>::eliminarNodo(T n) {
    // si el arbol es vacio:
    // - retornar
    if (this->esVacio()) {
        return false;
    }
    // si es la raiz la que quiero eliminar:
    // - hacer delete a raiz
    // - poner raiz en nulo
    if (this->raiz->obtenerDato() == n) {
        delete this->raiz;
        this->raiz = NULL;
        return true;
    }
    // si hay al menos un nodo en el arbol:
    // - si alguno de los hijos es el que quiero eliminar
    // - si ninguno de los hijos es el que quiero eliminar:
    // - revisar cada nodo hijo y llamar a eliminar alli
    std::list< NodoGeneral<T>* >::iterator it;
    NodoGeneral<T>* aux;
    bool eliminado = false;
    for (it = this->raiz->desc.begin(); it != this->raiz->desc.end(); it++) {
        aux = *it;
        if (aux->obtenerDato() == n) {
            eliminado = this->raiz->eliminarDesc(n);
            break;
        } else {
            ArbolGeneral<T> subarbol(aux);
            eliminado = subarbol.eliminarNodo(n);
            if (eliminado) {
                break;
            }
        }
    }
    return eliminado;
}
template <class T>
bool ArbolGeneral<T>::buscar(T n) {
    // si el arbol no esta vacio:
    // - comparo dato en el nodo actual con dato parametro
    // - si es ese, retorno que lo encontre
    // - si no, para cada nodo hijo hacer el llamado a buscar 
    if (this->esVacio()) {
        return false;
    }
    if (this->raiz->obtenerDato() == n) {
        return true;
    }
    // si no es la raiz, buscar en los hijos
    std::list< NodoGeneral<T>* >::iterator it;
    NodoGeneral<T>* aux;
    for (it = this->raiz->desc.begin(); it != this->raiz->desc.end(); it++) {
        aux = *it;
        ArbolGeneral<T> subarbol(aux);
        if (subarbol.buscar(n)) {
            return true;
        }
    }
    return false;
}
//altura del arbol
template <class T>
int ArbolGeneral<T>::altura() {
    if (this->esVacio()) {
        return -1;
    } else {
        return this->raiz.altura();
    }
}
//preorden implementando con recursividad en nodo
template <class T>
void ArbolGeneral<T>::preOrden() {
    if (!this->esVacio()) {
        this->raiz->preOrden();
    }
}


