#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "AdptArray.h"

typedef struct AdptArray_
{
    int size;
    PElement *pel;
    DEL_FUNC Dell_func;
    COPY_FUNC Copy_func;
    PRINT_FUNC Print_func;
    } AdptArray_;


PAdptArray CreateAdptArray(COPY_FUNC c, DEL_FUNC d,PRINT_FUNC p){
    PAdptArray paa = NULL;
    if((paa = malloc(sizeof( AdptArray_))) == NULL){
        return NULL;
    }
    paa->pel = NULL;
    paa->size = 0;
    paa->Copy_func = c;
    paa->Dell_func = d;
    paa->Print_func = p;

    return paa;
}

void DeleteAdptArray(PAdptArray paa){
    if(paa == NULL)
        return;

    if(paa->pel != NULL){    
        for(int i = 0;i < paa->size;i++){
            if(paa->pel[i] != NULL)
                paa->Dell_func(paa->pel[i]);
        }
        free(paa->pel);
    }
    free(paa);
}
Result SetAdptArrayAt(PAdptArray paa, int i, PElement element){
    if (paa == NULL)
        return FAIL;

    if(i < 0)
        return FAIL;    

    if (i >= paa->size){
        PElement *new_pel = calloc((i+1),sizeof(PElement));
        if(new_pel == NULL)
            return FAIL;

        if (paa->pel != NULL){
            for (int j = 0; j < paa->size; j++){
                if (paa->pel[j] != NULL){
                    new_pel[j] = paa->Copy_func(paa->pel[j]);
                    paa->Dell_func(paa->pel[j]);
                }
            }
        }
        free(paa->pel);
        paa->pel = new_pel;
        paa->size = i + 1;
    }
    if(paa->pel[i] != NULL)
        paa->Dell_func(paa->pel[i]);

    paa->pel[i] = paa->Copy_func(element);

    return SUCCESS;
}
PElement GetAdptArrayAt(PAdptArray paa, int i){
    if (paa == NULL)
        return NULL;

    if (i < 0 || i >= paa->size || paa->pel[i] == NULL)
        return NULL;

    return paa->Copy_func(paa->pel[i]);
}

int GetAdptArraySize(PAdptArray paa){
    if(paa == NULL)
        return 0;
    return paa->size;
}
void PrintDB(PAdptArray paa){
    if(paa == NULL)
        return;

    for(int i = 0; i < paa->size;i++){
        if (paa->pel[i] != NULL){
            paa->Print_func(paa->pel[i]);
        }
    }
}
