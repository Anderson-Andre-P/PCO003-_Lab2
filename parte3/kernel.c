#include "kernel.h"

#define POOL_SIZE 10

process * pool[POOL_SIZE];
int start, end;

char kernelInit(void){
    start = 0;
    end = 0;
    return SUCCESS;
}

char kernelAddProc(process * newProc){
    //checking for free space
    if ( ((end+1)%POOL_SIZE) != start){
        pool[end] = newProc;
        end = (end+1)%POOL_SIZE;
        return SUCCESS;
    }
    return FAIL;
}

void kernelLoop(void){
    int i, best;
    process * tmp;

    for(;;){
        //Do we have any process to execute?
        if (start != end){

            //procura o processo de maior prioridade na fila circular
            best = start;
            for (i = (start+1)%POOL_SIZE; i != end; i = (i+1)%POOL_SIZE){
                if (pool[i]->priority > pool[best]->priority){
                    best = i;
                }
            }

            //troca o de maior prioridade com o primeiro da fila
            tmp = pool[start];
            pool[start] = pool[best];
            pool[best] = tmp;

            //executa; se pedir REPEAT, volta para o fim da fila
            if (pool[start]->func() == REPEAT){
                kernelAddProc(pool[start]);
            }
            //prepare to get the next process;
            start = (start+1)%POOL_SIZE;
        }
    }
}
