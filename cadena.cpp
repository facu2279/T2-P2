/* 5198750 */

#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"
#include "../include/usoTads.h"

#include <stdio.h>
#include <stdlib.h>


struct nodo
{
    TInfo dato;
    TLocalizador anterior;
    TLocalizador siguiente;
};

struct repCadena
{
    TLocalizador inicio;
    TLocalizador final;
};


/*
  Devuelve 'true' si y solo si 'loc' es un 'TLocalizador' válido.
  En cadenas enlazadas un 'TLocalizador' es válido si y solo si no es 'NULL'.
*/
bool esLocalizador(TLocalizador loc) { return loc != NULL; }

/*
  Devuelve la 'TCadena' vacía (sin elementos).
*/
TCadena crearCadena(){
    TCadena res = new repCadena;
    res->inicio = res->final = NULL;
    return res;
}

/*
  Libera la memoria asignada a 'cad' y la de todos sus elementos.
*/
void liberarCadena(TCadena cad){
    TLocalizador ABorrar;
    while (cad->inicio != NULL){
        ABorrar = cad->inicio;
        cad->inicio = cad->inicio->siguiente;
        liberarInfo(ABorrar->dato);
        delete ABorrar;
    }
    delete cad;
}

/*
  Devuelve 'true' si y solo si 'cad' es vacía (no tiene elementos).
*/
bool esVaciaCadena(TCadena cad){ return (cad->inicio==NULL); }

/*
  Devuelve el 'TLocalizador' con el que se accede al inicio de 'cad'.
  Si esVaciaCadena(cad) devuelve un 'TLocalizador' no válido.
*/
TLocalizador inicioCadena(TCadena cad){
    TLocalizador res;
    return res=cad->inicio;
}

/*
  Devuelve el 'TLocalizador' con el que se accede al final de 'cad'.
  Si esVaciaCadena(cad) devuelve un 'TLocalizador' no válido.
*/
TLocalizador finalCadena(TCadena cad){
    TLocalizador res;
    return res= cad->final;
}

/*
  Devuelve el elemento de 'cad' al que se accede con 'loc'.
  Precondición: localizadorEnCadena(loc, cad).
*/
TInfo infoCadena(TLocalizador loc, TCadena cad){
    TInfo res;
    return res = loc->dato;
}

/*
  Devuelve el 'TLocalizador' con el que se accede al elemento de 'cad'
  inmediatamente siguiente a 'loc'.
  Si esFinalCadena(loc, cad) devuelve un 'TLocalizador' no válido.
  Precondición: localizadorEnCadena(loc, cad).
*/
TLocalizador siguiente(TLocalizador loc, TCadena cad){
    return loc->siguiente;
}

/*
  Devuelve el 'TLocalizador' con el que se accede al elemento de 'cad'
  inmediatamente anterior a 'loc'.
  Si esInicioCadena(loc, cad) devuelve un 'TLocalizador' no válido.
  Precondición: localizadorEnCadena(loc, cad).
*/
TLocalizador anterior(TLocalizador loc, TCadena cad){
    return loc->anterior;    
}

/*
  Devuelve 'true' si y solo si con 'loc' se accede al último elemento de 'cad'.
  Si esVaciaCadena (cad) devuelve 'false'.
*/
bool esFinalCadena(TLocalizador loc, TCadena cad){
    if (esVaciaCadena(cad) or !localizadorEnCadena(loc, cad))
    {
        return false;
    }
    else
    {
        return (loc->siguiente == NULL);
    }    
}

/*
  Devuelve 'true' si y solo si con 'loc' se accede al primer elemento de 'cad'.
  Si esVaciaCadena (cad) devuelve 'false'.
*/
bool esInicioCadena(TLocalizador loc, TCadena cad){    
    if (esVaciaCadena(cad) or !localizadorEnCadena(loc, cad))
    {
        return false;
    }
    else
    {
        return loc->anterior == NULL;
    }
}

/*
  Se inserta 'i' como último elemento de 'cad'.
  Devuelve 'cad'.
  Si esVaciaVadena (cad) 'i' se inserta como único elemento de 'cad'.
*/
TCadena insertarAlFinal(TInfo i, TCadena cad){
    TLocalizador res = new nodo;
    res->dato = i;

    if (esVaciaCadena(cad))
    {
        res->anterior = res->siguiente = NULL;
        cad->inicio = cad->final = res;
    }
    else
    {
        res->anterior = cad->final;
        cad->final->siguiente = res;
        res->siguiente = NULL;
        cad->final=res;
    }
    return cad;
}

/*
  Se inserta 'i' como un nuevo elemento inmediatamente antes de 'loc'.
  Devuelve 'cad'.
  Precondición: localizadorEnCadena(loc, cad).
*/
TCadena insertarAntes(TInfo i, TLocalizador loc, TCadena cad){
    TLocalizador res = new nodo;
    res->dato = i;
    
        if (esInicioCadena(loc, cad)){
            res->anterior = NULL;
            res->siguiente = loc;
            loc->anterior = res;
            cad->inicio = res;
        }
        else
        {
            loc->anterior->siguiente = res;
            res->anterior = loc->anterior;
            res->siguiente = loc;
            loc->anterior = res;
        }    
    return cad;
}

/*
  Se remueve el elemento al que se accede desde 'loc' y se libera la memoria
  asignada al mismo y al nodo apuntado por el localizador.
  Devuelve 'cad'.
  El valor de 'loc' queda indeterminado.
  Precondición: localizadorEnCadena(loc, cad).
*/
TCadena removerDeCadena(TLocalizador loc, TCadena cad){
    if (esFinalCadena(cad->inicio,cad))
    {
        cad->inicio = NULL;
        cad->final = NULL;
        liberarInfo(loc->dato);
        loc->anterior = NULL;
        loc->siguiente = NULL;
        delete loc;
    }
    else if (esFinalCadena(loc, cad))
    {
        cad->final = loc->anterior;
        loc->anterior->siguiente = NULL;
        loc->anterior = NULL;
        liberarInfo(loc->dato);
        delete loc;
    }
    else if (esInicioCadena(loc, cad))
    {
        cad->inicio = loc->siguiente;
        loc->siguiente->anterior = NULL;
        loc->siguiente = NULL;
        liberarInfo(loc->dato);
        delete loc;
    }
    else
    {
        loc->anterior->siguiente = loc->siguiente;
        loc->siguiente->anterior = loc->anterior;
        loc->siguiente = NULL;
        loc->anterior = NULL;
        liberarInfo(loc->dato);
        delete loc;
    }
    return cad;
}

/*
  Imprime los elementos de 'cad' de la siguiente forma:
  (n de pos1,r de pos1)(n de pos2,r de pos2) ...
  donde 'n` es el componente natural y 'r' es el componente real.
  Antes de terminar, se debe imprimir un fin de linea.
  Si esVaciaCadena(cad) sólo se imprime el fin de línea.
*/
void imprimirCadena(TCadena cad){
    if (esVaciaCadena(cad))
    {
        printf("\n");
    }
    else
    { 
        TLocalizador ptr = cad->inicio;
        while (ptr != NULL)
        {
            printf("(%d,%4.2lf)",natInfo(ptr->dato),realInfo(ptr->dato));
            ptr = ptr->siguiente;
        }
        printf("\n");
    }    
}

/*
  Devuelve el 'TLocalizador' con el que se accede al k-esimo elemento de 'cad'.
  Si 'k' es 0 o mayor a la cantidad de elementos de 'cad' devuelve un
  localizdor  no válido.
*/
TLocalizador kesimo(nat k, TCadena cad){
    TLocalizador res;
    nat i = 1;
    if (k == 0 or k > longitud(cad))
    {
        res = NULL;
    }
    else
    {
        res= cad->inicio;

        for (i=1; i<k; i++){
            res = res->siguiente;
        }
    }
    return res;
}

/*
  Devuelve 'true' si y solo si con 'loc' se accede a un elemento de 'cad',
  (o sea, si apunta a un nodo de 'cad').
  Si esVaciaCadena (cad) devuelve 'false'.
*/
bool localizadorEnCadena(TLocalizador loc, TCadena cad){
    TLocalizador cursor = inicioCadena(cad);
    while (esLocalizador(cursor) && (cursor != loc))
    {
        cursor = siguiente(cursor, cad);
    }
    return esLocalizador(cursor);
}

/*
  Devuelve 'true' si y solo si 'loc1' es igual o precede a 'loc2' en 'cad'.
  Si esVaciaCadena (cad) devuelve 'false'.
*/
bool precedeEnCadena(TLocalizador loc1, TLocalizador loc2, TCadena cad){
    bool res;
    res = localizadorEnCadena(loc1, cad);
    if (res)
    {
        TLocalizador cursor = loc1;
        while (esLocalizador(cursor) && (cursor != loc2))
        {
            cursor = siguiente(cursor, cad);
        }
        res = esLocalizador(cursor);
    }
    return res;
}

/*
  Se inserta en 'cad' la 'TCadena' 'sgm' inmediatamente después de 'loc',
  manteniendo los elementos originales y el orden relativo entre ellos.
  Devuelve 'cad'.
  No se debe obtener memoria (los nodos de 'sgm' pasan a ser parte de 'cad').
  Se libera la memoria asignada al resto de las estructuras de 'sgm'.
  El valor de 'sgm' queda indeterminado.
  Si esVaciaCadena(cad) 'loc' es ignorado y el segmento queda insertado.
  Precondición: esVaciaCadena(cad) o localizadorEnCadena(loc, cad).
*/
TCadena insertarSegmentoDespues(TCadena sgm, TLocalizador loc, TCadena cad){
    if (esVaciaCadena(cad) && !esVaciaCadena(sgm))
    {
        cad->inicio = sgm->inicio;
        cad->final = sgm->final;
    }
    else if (esFinalCadena(loc, cad) && !esVaciaCadena(sgm))
    {
        loc->siguiente = sgm->inicio;
        sgm->inicio->anterior = loc;
        cad->final = sgm->final;
    }
    else if (!esVaciaCadena(sgm))
    {
        sgm->final->siguiente = loc->siguiente;
        loc->siguiente->anterior = sgm->final;
        loc->siguiente = sgm->inicio;
        sgm->inicio->anterior = loc;
    }

    sgm->inicio = NULL;
    sgm->final = NULL;    
    delete sgm;

    return cad;
}

/*
  Devuelve una 'TCadena' con los elementos de 'cad' que se encuentran entre
  'desde' y 'hasta', incluidos.
  La 'TCadena' resultado no comparte memoria con 'cad'.
  Si esVaciaCadena(cad) devuelve la 'TCadena' vacia.
  Precondición: esVaciaCadena(cad) o precedeEnCadena(desde, hasta, cad).
*/
TCadena copiarSegmento(TLocalizador desde, TLocalizador hasta, TCadena cad){
    TCadena res = crearCadena();
    if (esVaciaCadena(cad))
    {
        return res;
    }
    else
    {
        TLocalizador p = desde;
        TLocalizador fin = hasta->siguiente;
        while (p != fin)
        {
            insertarAlFinal(copiaInfo(p->dato),res);
            p = p->siguiente;
        }
        p = NULL;
        delete p;
    }
    return res;
}

/*
  Remueve de 'cad' los elementos que se encuentran  entre 'desde' y 'hasta',
  incluidos y libera la memoria que tenían asignada y la de sus nodos.
  Devuelve 'cad'.
  Si esVaciaCadena(cad) devuelve la 'TCadena' vacía.
  Precondición: esVaciaCadena(cad) o precedeEnCadena(desde, hasta, cad).
*/
TCadena borrarSegmento(TLocalizador desde, TLocalizador hasta, TCadena cad){
    if (esVaciaCadena(cad))
    {
        return cad;
    }
    else
    {
        TLocalizador p = desde;
        TLocalizador fin = hasta->siguiente;
        while (p != fin)
        {
            p = p->siguiente;
            removerDeCadena(desde,cad);
            desde = p;
        }
        fin = NULL;
        delete fin;
    }
    return cad;    
}

/*
  Sustituye con 'i' el elemento de 'cad' al que se accede con 'loc'.
  Devuelve 'cad'.
  No destruye el elemento al que antes se accedía con 'loc'.
  Precondición: localizadorEnCadena(loc, cad).
*/
TCadena cambiarEnCadena(TInfo i, TLocalizador loc, TCadena cad){
    loc->dato = i;
    return cad;
}

/*
  Intercambia los elementos a los que se accede con 'loc1' y 'loc2'.
  'loc1' y 'loc2' mantienen su relación de precedencia.
  Devuelve 'cad'.
  Precondición:
  localizadorEnCadena (loc1, cad)
  y localizadorEnCadena (loc2, cad).
*/
TCadena intercambiar(TLocalizador loc1, TLocalizador loc2, TCadena cad){
    TInfo temp = loc1->dato;
    loc1->dato = loc2->dato;
    loc2->dato = temp;

    temp = NULL;
    liberarInfo(temp);

    return cad;
}

/*
  Devuelve el primer 'TLocalizador' con el que se accede a un elemento cuyo
  componente natural es igual a 'clave', buscando desde 'loc' (inclusive) hacia
  el final de 'cad'. Si no se encuentra o 'cad' es vacía devuelve un
  'TLocalizador' no válido.
  Precondición: esVaciaCadena(cad) o localizadorEnCadena(loc, cad).
*/
TLocalizador siguienteClave(nat clave, TLocalizador loc, TCadena cad){
    TLocalizador res;
    if (esVaciaCadena(cad))
    {
        res = NULL;
    }
    else
    {
        res = loc;
        while (res != NULL && natInfo(res->dato) != clave)
        {
            res = res->siguiente;
        }
    }
    return res;
}

/*
  Devuelve el primer 'TLocalizador' con el que se accede a un elemento cuyo
  componente natural es igual a 'clave', buscando desde 'loc' (inclusive) hacia
  el inicio de 'cad'. Si no se encuentra o 'cad' es vacía devuelve un
  'TLocalizador' no válido.
  Precondición: esVaciaCadena(cad) o localizadorEnCadena(loc, cad).
*/
TLocalizador anteriorClave(nat clave, TLocalizador loc, TCadena cad){
    TLocalizador res;
    if(esVaciaCadena(cad))
    {
        res = NULL;
    }
    else
    {
        res = loc;
        while (res != NULL && natInfo(res->dato) != clave)
        {
            res = res->anterior;
        }
    }
    return res;
}

/*
  Devuelve el 'TLocalizador' con el que se accede al elemento cuyo componente
  natural es el menor en el segmento que va desde 'loc' hasta finalCadena(cad).
  Si hay más de un elemento cuyo valor es el menor el resultado accede al que
  precede a los otros.
  Precondición: localizadorEnCadena(loc, cad).
*/
TLocalizador menorEnCadena(TLocalizador loc, TCadena cad){
    TLocalizador min = loc;
    while (loc != NULL)
    {
        if (natInfo(loc->dato) < natInfo(min->dato))
        {
            min = loc;
        }
        loc = loc->siguiente;
    }
    return min;
}