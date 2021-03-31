/* 5083180 */
#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"
#include "../include/usoTads.h"

#include <stdio.h>
#include <stdlib.h>

bool pertenece(nat elem, TCadena cad){
    if (!esVaciaCadena(cad)) {
        TLocalizador ptr = inicioCadena(cad);
        while (siguiente(ptr,cad) != NULL && natInfo(infoCadena(ptr,cad)) != elem)
        {
            ptr = siguiente(ptr,cad);
        }

        nat res = natInfo(infoCadena(ptr,cad));

        ptr = NULL;
        //delete ptr;

        return  (res == elem);
    } else {
        return false;
    }    
}

/*
  Devuelve la cantidad de elementos de 'cad'.
*/
nat longitud(TCadena cad){

    nat i = 0;

    if (!esVaciaCadena(cad))
    {
        TLocalizador ptr = inicioCadena(cad);
        while (ptr != NULL)
        {
            ptr = siguiente(ptr,cad);
            i++;
        }
    }
    return i;
}

/*
  Devuelve 'true' si y solo si 'cad' está ordenada de forma no dereciente
  (creciente de manera no estricta) según las campos naturales de sus elementos.
  Si esVaciaVadena(cad) devuelve 'true'.
*/
bool estaOrdenadaPorNaturales(TCadena cad){
    if (esVaciaCadena(cad))
    {
        return true;
    }
    else
    {
        TLocalizador ptr = inicioCadena(cad);
        while ((siguiente(ptr,cad) != NULL) && (natInfo(infoCadena(ptr,cad)) <= natInfo(infoCadena(siguiente(ptr,cad),cad))))
        {
            ptr = siguiente(ptr,cad);
        }
        return siguiente(ptr,cad) == NULL;
    }
}

/*  
  Devuelve 'true' si y solo si los componentes naturales de algún par de 
  elementos de 'cad' son iguales.  
*/
bool hayNatsRepetidos(TCadena cad){
    TLocalizador a,b;
    bool flag = false;

    if (longitud(cad) >= 2)
    {
        a = inicioCadena(cad);
        b = siguiente(a,cad);

        while ((siguiente(a,cad) != NULL) && (!flag)){
            b = siguiente(a,cad);

            while ((b!=NULL) && (!flag)){
                if (natInfo(infoCadena(a,cad)) == natInfo(infoCadena(b,cad)))
                {
                    flag = true;
                }
                b = siguiente(b,cad);
            }
            a = siguiente(a,cad);
        }
    }
    return flag;
}

/*
  Devuelve 'true' si y solo si 'c1' y 'c2' son iguales (es decir, si los
  elementos son iguales y en el mismo orden).
  Si esVaciaCadena(c1) y esVaciaCadena(c2) devuelve 'true'.
*/
bool sonIgualesCadena(TCadena c1, TCadena c2){
    TLocalizador t1, t2;
    t1 = inicioCadena(c1);
    t2 = inicioCadena(c2);
    
    if (longitud(c1) == longitud(c2))
    {
        while ((t1 != NULL) && sonIgualesInfo(infoCadena(t1,c1),infoCadena(t2,c2)))
        {
            t1 = siguiente(t1,c1);
            t2 = siguiente(t2,c2);
        }
    }
    return (t1 == NULL && t2 == NULL);
}

/*
  Devuelve el resultado de concatenar 'c2' después de 'c1'.
  La 'TCadena' resultado no comparte memoria ni con 'c1' ni con 'c2'.
*/
TCadena concatenar(TCadena c1, TCadena c2){
    TCadena res = copiarSegmento(inicioCadena(c1),finalCadena(c1),c1);
    TCadena aux2 = copiarSegmento(inicioCadena(c2),finalCadena(c2),c2);
    res = insertarSegmentoDespues(aux2,finalCadena(res),res);
    return res;
}

/*
  Se ordena 'cad' de manera creciente según los componentes naturales de sus
  elementos.
  Devuelve 'cad'
  Precondición: ! hayNatsRepetidos(cad)
  No se debe obtener ni devolver memoria de manera dinámica.
  Se debe mantener las relaciones de precedencia entre localizadores.
  Si esVaciaCadena(cad) no hace nada.
  Algoritmo usado: SelectionSort.
*/
TCadena ordenar(TCadena cad){
nat n = longitud(cad);
    for (nat i = 1; i < n; i++)
    {
        for (nat j = i+1; j <= n ; j++)
        {
            if (natInfo(infoCadena(kesimo(j,cad),cad)) < natInfo(infoCadena(kesimo(i,cad),cad)))
            {
                intercambiar(kesimo(j,cad),kesimo(i,cad),cad);
            }
        }
    }
    return cad;
}

/*
  Cambia todas las ocurrencias de 'original' por 'nuevo' en los elementos
  de 'cad'.
  Devuelve 'cad'
  No debe quedar memoria inaccesible.
*/
TCadena cambiarTodos(nat original, nat nuevo, TCadena cad){
    TLocalizador p = siguienteClave(original,inicioCadena(cad),cad);
    TInfo aux;
    TInfo data;
    while (p != NULL)
    {
        data = crearInfo(nuevo,realInfo(infoCadena(p,cad)));
        aux = infoCadena(p,cad);
        cambiarEnCadena(data,p,cad);
        p = siguienteClave(original,siguiente(p,cad),cad);
        liberarInfo(aux);
    }

    return cad;
}

/*
  Devuelve la 'TCadena' de elementos de 'cad' que cumplen
  "menor <= natInfo (elemento) <= mayor".
  El orden relativo de los elementos en la 'TCadena' resultado debe ser el mismo
  que en 'cad'.
  Precondición: estaOrdenadaPorNaturales (cad), 'menor' <= 'mayor',
  pertenece (menor, cad), pertenece (mayor, cad).
  La 'TCadena' resultado no comparte memoria con 'cad'.
*/
TCadena subCadena(nat menor, nat mayor, TCadena cad){
    TLocalizador a,b;
    TCadena res;

    a = siguienteClave(menor,inicioCadena(cad),cad);
    b = finalCadena(cad);

    while (b!=NULL && natInfo(infoCadena(b,cad)) != mayor)
    {
        b = anterior(b,cad);
    }

    res = copiarSegmento(a,b,cad);
    return res;
}