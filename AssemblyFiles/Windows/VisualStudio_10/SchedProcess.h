#ifndef SCHEDPROC_H
#define SCHEDPROC_H

typedef struct Process {
    int id;
    int time_arrival;
    int time_burst;
	int priority;
    int time_warning;
    int time_completion;
} Process;

#endif 