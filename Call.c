#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include "call.h"

void init_queue(CallQueue* q) {
    q->head = q->tail = NULL;
    q->size = 0;
}

void enqueue(CallQueue* q, int id, int arrivalTime, double duration) {
    Call* call = (Call*)malloc(sizeof(Call));
    call->id = id;
    call->arrivalTime = arrivalTime;
    call->duration = duration > 0 ? duration : 0;
    call->next = NULL;

    if (q->tail) {
        q->tail->next = call;
    }
    else {
        q->head = call;
    }
    q->tail = call;
    q->size++;
}

void clear_queue(CallQueue* q) {
    Call* current = q->head;
    while (current) {
        Call* tmp = current;
        current = current->next;
        free(tmp);
    }
    q->head = q->tail = NULL;
    q->size = 0;
}

int generate_poisson(double lambda) {
    double L = exp(-lambda);
    int k = 0;
    double p = 1.0;
    do {
        k++;
        p *= (double)rand() / RAND_MAX;
    } while (p > L);
    return k - 1;
}

double generate_normal(double mean, double stddev) {
    double u1 = (double)rand() / RAND_MAX;
    double u2 = (double)rand() / RAND_MAX;
    double z = sqrt(-2.0 * log(u1)) * cos(2.0 * M_PI * u2);
    return mean + stddev * z;
}