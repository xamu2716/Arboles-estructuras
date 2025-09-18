#ifndef __ARBOLGENERAL_H__
#define __ARBOLGENERAL_H__

#include "NodoGeneral.h"

template <class T>
class ArbolGeneral {
protected:
    NodoGeneral<T>* raiz;
public:
    ArbolGeneral();
    ArbolGeneral(T val);
    ~ArbolGeneral();
    bool esVacio();
    NodoGeneral<T>* obtenerRaiz();
    void fijarRaiz(NodoGeneral<T>* nraiz);
    bool insertarNodo(T padre, T n);
    bool eliminarNodo(T n);
    bool buscar(T n);
    int altura();
    unsigned int tamano();
    void preOrden();
    void posOrden();
    void nivelOrden();
};
#include "ArbolGeneral.hxx"
#endif
