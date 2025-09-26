#include "ArbolAVL.h"
#include <queue>
#include <iostream>
using namespace std;

template <class T>
ArbolAVL<T>::ArbolAVL()
{
    this->raiz = NULL;
}

template <class T>
ArbolAVL<T>::~ArbolAVL()
{
    if (this->raiz != NULL)
    {
        delete this->raiz;
        this->raiz = NULL;
    }
}

template <class T>
bool ArbolAVL<T>::esVacio()
{
    return this->raiz == NULL;
}

template <class T>
T ArbolAVL<T>::datoRaiz()
{
    return (this->raiz)->obtenerDato();
}

// recurrente y se implementa acá y NO desde el nodo
template <class T>
int ArbolAVL<T>::altura()
{
    if (this->esVacio())
        return -1;
    else
        return this->altura(this->raiz);
}

template <class T>
int ArbolAVL<T>::altura(NodoAVL<T> *nodo)
{
    int valt;
    if (nodo->esHoja())
    {
        valt = 0;
    }
    else
    {
        int valt_izq = -1;
        int valt_der = -1;
        if (nodo->obtenerHijoIzq() != NULL)
            valt_izq = this->altura(nodo->obtenerHijoIzq());
        if (nodo->obtenerHijoDer() != NULL)
            valt_der = this->altura(nodo->obtenerHijoDer());
        if (valt_izq > valt_der)
            valt = valt_izq + 1;
        else
            valt = valt_der + 1;
    }
    return valt;
}

// recurrente
template <class T>
int ArbolAVL<T>::tamano()
{
    if (this->esVacio())
        return 0;
    else
        return this->tamano(this->raiz);
}

template <class T>
int ArbolAVL<T>::tamano(NodoAVL<T> *nodo)
{
    if (nodo == NULL)
        return 0;
    else
        return 1 + this->tamano(nodo->obtenerHijoIzq()) + this->tamano(nodo->obtenerHijoDer());
}

// iterativa
template <class T>
bool ArbolAVL<T>::insertar(T val)
{
    if (this->raiz == NULL)
    {
        this->raiz = new NodoAVL<T>(val);
        return true;
    }

    const int MAXH = 256;
    NodoAVL<T> *path[MAXH];
    int top = -1;

    NodoAVL<T> *padre = NULL;
    NodoAVL<T> *cur = this->raiz;

    while (cur != NULL)
    {
        if (top + 1 < MAXH)
        {
            path[++top] = cur;
        }
        if (val < cur->obtenerDato())
        {
            padre = cur;
            cur = cur->obtenerHijoIzq();
        }
        else if (val > cur->obtenerDato())
        {
            padre = cur;
            cur = cur->obtenerHijoDer();
        }
        else
        {
            while (top >= 0)
            {
                this->balancear(path[top]);
                --top;
            }
            return false;
        }
    }

    NodoAVL<T> *nuevo = new NodoAVL<T>(val);
    if (val < padre->obtenerDato())
        padre->fijarHijoIzq(nuevo);
    else
        padre->fijarHijoDer(nuevo);

    if (top + 1 < MAXH)
    {
        path[++top] = nuevo;
    }

    while (top >= 0)
    {
        this->balancear(path[top]);
        --top;
    }

    return true;
}

// iterativa
template <class T>
bool ArbolAVL<T>::eliminar(T val)
{
    if (this->raiz == NULL)
        return false;

    const int MAXH = 256;
    NodoAVL<T> *path[MAXH];
    int top = -1;

    NodoAVL<T> *padre = NULL;
    NodoAVL<T> *cur = this->raiz;

    while (cur != NULL)
    {
        if (top + 1 < MAXH)
        {
            path[++top] = cur;
        }
        if (val < cur->obtenerDato())
        {
            padre = cur;
            cur = cur->obtenerHijoIzq();
        }
        else if (val > cur->obtenerDato())
        {
            padre = cur;
            cur = cur->obtenerHijoDer();
        }
        else
            break;
    }

    if (cur == NULL)
    {
        while (top >= 0)
        {
            this->balancear(path[top]);
            --top;
        }
        return false;
    }

    if (cur->obtenerHijoIzq() == NULL || cur->obtenerHijoDer() == NULL)
    {
        NodoAVL<T> *hijo;
        if (cur->obtenerHijoIzq() != NULL)
            hijo = cur->obtenerHijoIzq();
        else
            hijo = cur->obtenerHijoDer();

        if (padre == NULL)
        {
            delete this->raiz;
            this->raiz = hijo;
        }
        else
        {
            if (padre->obtenerHijoIzq() == cur)
                padre->fijarHijoIzq(hijo);
            else
                padre->fijarHijoDer(hijo);
            delete cur;
        }
    }
    else
    {
        NodoAVL<T> *padreSuc = cur;
        NodoAVL<T> *suc = cur->obtenerHijoDer();

        if (top + 1 < MAXH)
        {
            path[++top] = suc;
        }

        while (suc->obtenerHijoIzq() != NULL)
        {
            padreSuc = suc;
            suc = suc->obtenerHijoIzq();
            if (top + 1 < MAXH)
            {
                path[++top] = suc;
            }
        }

        cur->fijarDato(suc->obtenerDato());

        NodoAVL<T> *hijoSuc;
        if (suc->obtenerHijoDer() != NULL)
            hijoSuc = suc->obtenerHijoDer();
        else
            hijoSuc = NULL;

        if (padreSuc->obtenerHijoIzq() == suc)
            padreSuc->fijarHijoIzq(hijoSuc);
        else
            padreSuc->fijarHijoDer(hijoSuc);

        delete suc;
    }

    while (top >= 0)
    {
        this->balancear(path[top]);
        --top;
    }

    return true;
}

// iterativa
template <class T>
bool ArbolAVL<T>::buscar(T val)
{
    NodoAVL<T> *nodo = this->raiz;
    bool encontrado = false;

    while (nodo != NULL && !encontrado)
    {
        if (val < nodo->obtenerDato())
        {
            nodo = nodo->obtenerHijoIzq();
        }
        else if (val > nodo->obtenerDato())
        {
            nodo = nodo->obtenerHijoDer();
        }
        else
        {
            encontrado = true;
        }
    }
    return encontrado;
}

// recurrente
template <class T>
void ArbolAVL<T>::PreOrden()
{
    if (!this->esVacio())
        this->PreOrden(this->raiz);
}

template <class T>
void ArbolAVL<T>::PreOrden(NodoAVL<T> *nodo)
{
    if (nodo != NULL)
    {
        cout << nodo->obtenerDato() << " ";
        this->PreOrden(nodo->obtenerHijoIzq());
        this->PreOrden(nodo->obtenerHijoDer());
    }
}

// recurrente
template <class T>
void ArbolAVL<T>::InOrden()
{
    if (!this->esVacio())
        this->InOrden(this->raiz);
}

template <class T>
void ArbolAVL<T>::InOrden(NodoAVL<T> *nodo)
{
    if (nodo != NULL)
    {
        this->InOrden(nodo->obtenerHijoIzq());
        cout << nodo->obtenerDato() << " ";
        this->InOrden(nodo->obtenerHijoDer());
    }
}

// recurrente
template <class T>
void ArbolAVL<T>::PosOrden()
{
    if (!this->esVacio())
        this->PosOrden(this->raiz);
}

template <class T>
void ArbolAVL<T>::PosOrden(NodoAVL<T> *nodo)
{
    if (nodo != NULL)
    {
        this->PosOrden(nodo->obtenerHijoIzq());
        this->PosOrden(nodo->obtenerHijoDer());
        cout << nodo->obtenerDato() << " ";
    }
}

// iterativa
template <class T>
void ArbolAVL<T>::NivelOrden()
{
    if (!this->esVacio())
    {
        queue<NodoAVL<T> *> cola;
        cola.push(this->raiz);
        NodoAVL<T> *nodo;

        while (!cola.empty())
        {
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

// Rotación DERECHA:
// n_padre = n2->hijoIzq
// n2->hijoIzq = n1->hijoDer
// n1->hijoDer = n2
template <class T>
void ArbolAVL<T>::rotarDerecha(NodoAVL<T> *padre, NodoAVL<T> *n2)
{
    if (!n2 || !n2->obtenerHijoIzq())
        return;

    NodoAVL<T> *n1 = n2->obtenerHijoIzq();
    NodoAVL<T> *n_padre = n1; // nueva sub-raíz

    n2->fijarHijoIzq(n1->obtenerHijoDer());
    n1->fijarHijoDer(n2);

    if (padre == NULL)
        this->raiz = n_padre;
    else if (padre->obtenerHijoIzq() == n2)
        padre->fijarHijoIzq(n_padre);
    else
        padre->fijarHijoDer(n_padre);
}

// Rotación IZQUIERDA:
// n_padre = n1->hijoDer
// n1->hijoDer = n2->hijoIzq
// n2->hijoIzq = n1
template <class T>
void ArbolAVL<T>::rotarIzquierda(NodoAVL<T> *padre, NodoAVL<T> *n1)
{
    if (!n1 || !n1->obtenerHijoDer())
        return;

    NodoAVL<T> *n2 = n1->obtenerHijoDer();
    NodoAVL<T> *n_padre = n2; // nueva sub-raíz

    n1->fijarHijoDer(n2->obtenerHijoIzq());
    n2->fijarHijoIzq(n1);

    if (padre == NULL)
        this->raiz = n_padre;
    else if (padre->obtenerHijoIzq() == n1)
        padre->fijarHijoIzq(n_padre);
    else
        padre->fijarHijoDer(n_padre);
}

// Rotación IZQ-DER (LR):
// aux = rotIzquierda(n1->hijoIzq)
// n1->hijoIzq = aux
// n_padre = rotDerecha(n1)
template <class T>
void ArbolAVL<T>::rotarIzqDer(NodoAVL<T> *padre, NodoAVL<T> *n1)
{
    if (!n1 || !n1->obtenerHijoIzq())
        return;

    // rotIzquierda sobre el hijo izquierdo, con padre = n1
    this->rotarIzquierda(n1, n1->obtenerHijoIzq());
    // luego rotDerecha sobre n1, con el padre original
    this->rotarDerecha(padre, n1);
}

// Rotación DER-IZQ (RL):
// aux = rotDerecha(n1->hijoDer)
// n1->hijoDer = aux
// n_padre = rotIzquierda(n1)
template <class T>
void ArbolAVL<T>::rotarDerIzq(NodoAVL<T> *padre, NodoAVL<T> *n1)
{
    if (!n1 || !n1->obtenerHijoDer())
        return;

    // rotDerecha sobre el hijo derecho, con padre = n1
    this->rotarDerecha(n1, n1->obtenerHijoDer());
    // luego rotIzquierda sobre n1, con el padre original
    this->rotarIzquierda(padre, n1);
}

template <class T>
bool ArbolAVL<T>::balancear(NodoAVL<T> *nodo)
{
    if (nodo == NULL)
        return true;

    int hi, hd, bf;

    // Altura hijo izquierdo
    if (nodo->obtenerHijoIzq() != NULL)
        hi = this->altura(nodo->obtenerHijoIzq());
    else
        hi = -1;

    // Altura hijo derecho
    if (nodo->obtenerHijoDer() != NULL)
        hd = this->altura(nodo->obtenerHijoDer());
    else
        hd = -1;

    // Factor de balance
    bf = hi - hd;

    // Caso balanceado
    if (bf >= -1 && bf <= 1)
        return true;

    // Desbalance a la izquierda (LL o LR)
    if (bf > 1)
    {
        NodoAVL<T> *izq = nodo->obtenerHijoIzq();
        int hLL, hLR;

        if (izq->obtenerHijoIzq() != NULL)
            hLL = this->altura(izq->obtenerHijoIzq());
        else
            hLL = -1;

        if (izq->obtenerHijoDer() != NULL)
            hLR = this->altura(izq->obtenerHijoDer());
        else
            hLR = -1;

        if (hLL >= hLR)
        {
            // Caso LL: rotación simple derecha
            this->rotarDerecha(nodo);
        }
        else
        {
            // Caso LR: rotación doble izquierda-derecha
            this->rotarIzqDer(nodo);
        }
        return true;
    }

    // Desbalance a la derecha (RR o RL)
    if (bf < -1)
    {
        NodoAVL<T> *der = nodo->obtenerHijoDer();
        int hRR, hRL;

        if (der->obtenerHijoDer() != NULL)
            hRR = this->altura(der->obtenerHijoDer());
        else
            hRR = -1;

        if (der->obtenerHijoIzq() != NULL)
            hRL = this->altura(der->obtenerHijoIzq());
        else
            hRL = -1;

        if (hRR >= hRL)
        {
            // Caso RR: rotación simple izquierda
            this->rotarIzquierda(nodo);
        }
        else
        {
            // Caso RL: rotación doble derecha-izquierda
            this->rotarDerIzq(nodo);
        }
        return true;
    }

    return true;
}