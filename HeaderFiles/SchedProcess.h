#ifndef SCHEDPROC_H
#define SCHEDPROC_H

typedef struct Process {
    int id;   // номер процесса
    int arrival_time;  // время прибытия
	int completion_time;  // время завершения
    int burst_time;  // время действия
	int priority;  // приоритет
    int waiting_time;  // время ожидания
} Process;

#endif 