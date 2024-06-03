#ifndef SCHEDPROC_H
#define SCHEDPROC_H

typedef struct Process {
    int id;   // ����� ��������
    int arrival_time;  // ����� ��������
	int completion_time;  // ����� ����������
    int burst_time;  // ����� ��������
	int priority;  // ���������
    int waiting_time;  // ����� ��������
} Process;

#endif 