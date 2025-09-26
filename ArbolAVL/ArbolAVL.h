#ifndef __ARBOLAVL_H__
#define __ARBOLAVL_H__

#include "NodoAVL.h"

template <class T>
class ArbolAVL
{
protected:
    NodoAVL<T> *raiz;

public:
    ArbolAVL();
    ~ArbolAVL();
    bool esVacio();
    T datoRaiz();
    int altura();
    int altura(NodoAVL<T> *nodo);
    int tamano();
    int tamano(NodoAVL<T> *nodo);
    bool insertar(T val); // se hace llamado a balanceo
    bool eliminar(T val); // se hace llamado a balanceo
    bool buscar(T val);
    void PreOrden();
    void PreOrden(NodoAVL<T> *nodo);
    void InOrden();
    void InOrden(NodoAVL<T> *nodo);
    void PosOrden();
    void PosOrden(NodoAVL<T> *nodo);
    void NivelOrden();
    void rotarDerecha(NodoAVL<T> *padre, NodoAVL<T> *n2);
    void rotarIzquierda(NodoAVL<T> *padre, NodoAVL<T> *n1);
    void rotarIzqDer(NodoAVL<T> *padre, NodoAVL<T> *n1);
    void rotarDerIzq(NodoAVL<T> *padre, NodoAVL<T> *n1);
    bool balancear(NodoAVL<T> *nodo); // Dependiendo del resultado se hace llamado a la rotacion correspondiente
};

#include "ArbolAVL.hxx"

#endif
