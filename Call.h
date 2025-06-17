#ifndef CALL_H
#define CALL_H

typedef struct Call {
    int id;
    int arrivalTime;
    double duration;
    struct Call* next;
} Call;

typedef struct {
    Call* head;
    Call* tail;
    int size;
} CallQueue;

void init_queue(CallQueue* q);
void enqueue(CallQueue* q, int id, int arrivalTime, double duration);
void clear_queue(CallQueue* q);
int generate_poisson(double lambda);
double generate_normal(double mean, double stddev);

#endif
#pragma once
