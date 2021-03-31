/* 5083180 */

#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"
#include "../include/usoTads.h"

#include <stdio.h>
#include <stdlib.h>

struct nodoCadena{
    TInfo data;
    TLocalizador prev;
    TLocalizador next;
};

struct _rep_cadena{
    TLocalizador start;
    TLocalizador end;
};

bool esLocalizador(TLocalizador loc){
    return loc != NULL;
}

TCadena crearCadena(){
    TCadena new_cadena = new _rep_cadena;
    new_cadena->start = new_cadena->end = NULL;
    return new_cadena;
}

void liberarCadena(TCadena cad){
    TLocalizador to_delete;
    while (cad->start != NULL) {
        to_delete = cad->start;
        cad->start = cad->start->next;
        liberarInfo(to_delete->data);
        delete to_delete;
    }
    delete cad;    
}

bool esVaciaCadena(TCadena cad){
    return cad->start == NULL;
}

TLocalizador inicioCadena(TCadena cad){
    TLocalizador ini;
    return ini = cad->start;
}

TLocalizador finalCadena(TCadena cad){
    TLocalizador end_cad;
    return end_cad = cad->end;
}

TInfo infoCadena(TLocalizador loc, TCadena cad){
    TInfo info;
    return info = loc->data;
}

TLocalizador siguiente(TLocalizador loc, TCadena cad){
    return loc->next;
}

TLocalizador anterior(TLocalizador loc, TCadena cad){
    return loc->prev;
}

bool esFinalCadena(TLocalizador loc, TCadena cad){
    if (esVaciaCadena(cad) || !localizadorEnCadena(loc,cad)) {
        return false;
    }
    return (loc->next == NULL);
}

bool esInicioCadena(TLocalizador loc, TCadena cad){
    if (esVaciaCadena(cad) || !localizadorEnCadena(loc,cad)) {
        return false;
    }
    return (loc->prev == NULL);
}

TCadena insertarAlFinal(TInfo i, TCadena cad){
    TLocalizador nodin = new nodoCadena;
    nodin->data = i;

    if (esVaciaCadena(cad)) {
        nodin->prev = nodin->next = NULL;
        cad->start = cad->end = nodin;
    } else {
        cad->end->next = nodin;
        nodin->prev = cad->end;
        nodin->next = NULL;
        cad->end = nodin;
    }
    return cad;    
}

TCadena insertarAntes(TInfo i, TLocalizador loc, TCadena cad){
    TLocalizador nodin = new nodoCadena;
    nodin->data = i;

    if (esInicioCadena(loc,cad)) {
        nodin->prev = NULL;
        nodin->next = loc;
        loc->prev = nodin;
        cad->start = nodin;
    } else {
        nodin->prev = loc->prev;
        loc->prev->next = nodin;
        nodin->next = loc;
        loc->prev = nodin;
    }
    return cad;
}

TCadena removerDeCadena(TLocalizador loc, TCadena cad){
    if (esFinalCadena(cad->start,cad))
    {
        cad->start = NULL;
        cad->end = NULL;
        liberarInfo(loc->data);
        loc->prev = NULL;
        loc->next = NULL;
        delete loc;
    } else if (esFinalCadena(loc, cad)) {
        cad->end = loc->prev;
        loc->prev->next = NULL;
        loc->prev = NULL;
        liberarInfo(loc->data);
        delete loc;
    } else if (esInicioCadena(loc, cad)) {
        cad->start = loc->next;
        loc->next->prev = NULL;
        loc->next = NULL;
        liberarInfo(loc->data);
        delete loc;
    } else {
        loc->prev->next = loc->next;
        loc->next->prev = loc->prev;
        loc->next = NULL;
        loc->prev = NULL;
        liberarInfo(loc->data);
        delete loc;
    }
    return cad;
}

void imprimirCadena(TCadena cad){
    if (esVaciaCadena(cad)) {
        printf("\n");
    }
    else { 
        TLocalizador ptr = cad->start;
        while (ptr != NULL) {
            printf("(%d,%4.2lf)",natInfo(ptr->data),realInfo(ptr->data));
            ptr = ptr->next;
        }
        printf("\n");
    }    
}

TLocalizador kesimo(nat k, TCadena cad){
    TLocalizador res;
    nat i = 1;
    if (k == 0 or k > longitud(cad)) {
        res = NULL;
    }
    else {
        res= cad->start;

        for (i=1; i<k; i++){
            res = res->next;
        }
    }
    return res;
}

bool localizadorEnCadena(TLocalizador loc, TCadena cad){
    TLocalizador cursor = inicioCadena(cad);
    while (esLocalizador(cursor) && (cursor != loc))
    {
        cursor = siguiente(cursor, cad);
    }
    return esLocalizador(cursor);
}

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

TCadena insertarSegmentoDespues(TCadena sgm, TLocalizador loc, TCadena cad){
        if (esVaciaCadena(cad) && !esVaciaCadena(sgm))
    {
        cad->start = sgm->start;
        cad->end = sgm->end;
    }
    else if (esFinalCadena(loc, cad) && !esVaciaCadena(sgm))
    {
        loc->next = sgm->start;
        sgm->start->prev = loc;
        cad->end = sgm->end;
    }
    else if (!esVaciaCadena(sgm))
    {
        sgm->end->next = loc->next;
        loc->next->prev = sgm->end;
        loc->next = sgm->start;
        sgm->start->prev = loc;
    }

    sgm->start = NULL;
    sgm->end = NULL;    
    delete sgm;

    return cad;
}

TCadena copiarSegmento(TLocalizador desde, TLocalizador hasta, TCadena cad){
    TCadena res = crearCadena();
    if (esVaciaCadena(cad)) {
        return res;
    } else {
        TLocalizador p = desde;
        TLocalizador fin = hasta->next;
        while (p != fin) {
            insertarAlFinal(copiaInfo(p->data),res);
            p = p->next;
        }
        p = NULL;
        delete p;
    }
    return res;
}

TCadena borrarSegmento(TLocalizador desde, TLocalizador hasta, TCadena cad){
    if (esVaciaCadena(cad)) {
        return cad;
    }
    else {
        TLocalizador p = desde;
        TLocalizador fin = hasta->next;
        while (p != fin) {
            p = p->next;
            removerDeCadena(desde,cad);
            desde = p;
        }
        fin = NULL;
        delete fin;
    }
    return cad;    
}

TCadena cambiarEnCadena(TInfo i, TLocalizador loc, TCadena cad){
    loc->data = i;
    return cad;
}

TCadena intercambiar(TLocalizador loc1, TLocalizador loc2, TCadena cad){
    TInfo temp = loc1->data;
    loc1->data = loc2->data;
    loc2->data = temp;

    temp = NULL;
    liberarInfo(temp);

    return cad;
}

TLocalizador siguienteClave(nat clave, TLocalizador loc, TCadena cad){
    TLocalizador res;
    if (esVaciaCadena(cad)) {
        res = NULL;
    }
    else {
        res = loc;
        while (res != NULL && natInfo(res->data) != clave) {
            res = res->next;
        }
    }
    return res;
}

TLocalizador anteriorClave(nat clave, TLocalizador loc, TCadena cad){
    TLocalizador res;
    if(esVaciaCadena(cad)) {
        res = NULL;
    } else {
        res = loc;
        while (res != NULL && natInfo(res->data) != clave) {
            res = res->prev;
        }
    }
    return res;
}

TLocalizador menorEnCadena(TLocalizador loc, TCadena cad){
    TLocalizador min = loc;
    while (loc != NULL) {
        if (natInfo(loc->data) < natInfo(min->data)) {
            min = loc;
        }
        loc = loc->next;
    }
    return min;
}