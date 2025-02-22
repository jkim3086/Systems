/*
 * process.c
 * Multithreaded OS Simulation for CS 2200, Project 6 - Fall 2015
 *
 * This file contains process data for the simulator.
 */

#include "os-sim.h"
#include "process.h"


/*
 * Note: The operations must alternate: OP_CPU, OP_IO, OP_CPU, ...
 * In addition, the first and last operations must be OP_CPU.  Otherwise,
 * the simulator will not work.
 */

static op_t pid0_ops[] = {
    { OP_CPU, 2 },
    { OP_IO, 2 },
    { OP_CPU, 3 },
    { OP_IO, 5 },
    { OP_CPU, 1 },
    { OP_IO, 4 },
    { OP_CPU, 2 },
    { OP_IO, 2 },
    { OP_CPU, 3 },
    { OP_IO, 5 },
    { OP_CPU, 1 },
    { OP_IO, 4 },
    { OP_CPU, 2 },
    { OP_IO, 2 },
    { OP_CPU, 3 },
    { OP_IO, 5 },
    { OP_CPU, 1 },
    { OP_IO, 4 },
    { OP_CPU, 2 },
    { OP_IO, 5 },
    { OP_CPU, 1 },
    { OP_IO, 4 },
    { OP_CPU, 2 },
    { OP_IO, 2 },
    { OP_CPU, 3 },
    { OP_IO, 5 },
    { OP_CPU, 1 },
    { OP_IO, 4 },
    { OP_CPU, 2 },
    { OP_TERMINATE, 0 }
};

static op_t pid1_ops[] = {
    { OP_CPU, 3 },
    { OP_IO, 4 },
    { OP_CPU, 2 },
    { OP_IO, 6 },
    { OP_CPU, 1 },
    { OP_IO, 3 },
    { OP_CPU, 4 },
    { OP_IO, 4 },
    { OP_CPU, 2 },
    { OP_IO, 6 },
    { OP_CPU, 1 },
    { OP_IO, 3 },
    { OP_CPU, 4 },
    { OP_IO, 4 },
    { OP_CPU, 2 },
    { OP_IO, 6 },
    { OP_CPU, 1 },
    { OP_IO, 3 },
    { OP_CPU, 4 },
    { OP_IO, 3 },
    { OP_CPU, 4 },
    { OP_IO, 4 },
    { OP_CPU, 2 },
    { OP_IO, 6 },
    { OP_CPU, 1 },
    { OP_IO, 3 },
    { OP_CPU, 4 },
    { OP_TERMINATE, 0 }
};

static op_t pid2_ops[] = {
    { OP_CPU, 1 },
    { OP_IO, 4 },
    { OP_CPU, 2 },
    { OP_IO, 5 },
    { OP_CPU, 1 },
    { OP_IO, 3 },
    { OP_CPU, 3 },
    { OP_IO, 4 },
    { OP_CPU, 2 },
    { OP_IO, 5 },
    { OP_CPU, 1 },
    { OP_IO, 3 },
    { OP_CPU, 3 },
    { OP_IO, 4 },
    { OP_CPU, 2 },
    { OP_IO, 5 },
    { OP_CPU, 1 },
    { OP_IO, 3 },
    { OP_CPU, 3 },
    { OP_IO, 4 },
    { OP_CPU, 2 },
    { OP_IO, 5 },
    { OP_CPU, 1 },
    { OP_IO, 3 },
    { OP_CPU, 3 },
    { OP_TERMINATE, 0 }
};

static op_t pid3_ops[] = {
    { OP_CPU, 9 },
    { OP_IO, 1 },
    { OP_CPU, 6 },
    { OP_IO, 1 },
    { OP_CPU, 8 },
    { OP_IO, 1 },
    { OP_CPU, 7 },
    { OP_IO, 1 },
    { OP_CPU, 6 },
    { OP_IO, 1 },
    { OP_CPU, 8 },
    { OP_IO, 1 },
    { OP_CPU, 7 },
    { OP_IO, 1 },
    { OP_CPU, 6 },
    { OP_IO, 1 },
    { OP_CPU, 8 },
    { OP_IO, 1 },
    { OP_CPU, 8 },
    { OP_TERMINATE, 0 }
};

static op_t pid4_ops[] = {
    { OP_CPU, 10 }, 
    { OP_IO, 1 },
    { OP_CPU, 14 },
    { OP_IO, 1 },
    { OP_CPU, 7 },
    { OP_IO, 2 },
    { OP_CPU, 11 },
    { OP_IO, 1 },
    { OP_CPU, 14 },
    { OP_IO, 1 },
    { OP_CPU, 7 },
    { OP_IO, 2 },
    { OP_CPU, 11 },
    { OP_IO, 1 },
    { OP_CPU, 14 },
    { OP_IO, 1 },
    { OP_CPU, 7 },
    { OP_IO, 2 },
    { OP_CPU, 11 },
    { OP_TERMINATE, 0 }
};

static op_t pid5_ops[] = {
    { OP_CPU, 9 }, 
    { OP_IO, 1 },
    { OP_CPU, 10 },
    { OP_IO, 2 },
    { OP_CPU, 15 },
    { OP_IO, 1 },
    { OP_CPU, 8 },
    { OP_IO, 1 },
    { OP_CPU, 10 },
    { OP_IO, 2 },
    { OP_CPU, 15 },
    { OP_IO, 1 },
    { OP_CPU, 8 },
    { OP_IO, 1 },
    { OP_CPU, 10 },
    { OP_IO, 2 },
    { OP_CPU, 15 },
    { OP_IO, 1 },
    { OP_CPU, 8 },
    { OP_TERMINATE, 0 }
};

static op_t pid6_ops[] = {
    { OP_CPU, 6 }, 
    { OP_IO, 3 },
    { OP_CPU, 9 },
    { OP_IO, 1 },
    { OP_CPU, 14 },
    { OP_IO, 1 },
    { OP_CPU, 11 },
    { OP_IO, 3 },
    { OP_CPU, 9 },
    { OP_IO, 1 },
    { OP_CPU, 14 },
    { OP_IO, 1 },
    { OP_CPU, 11 },
    { OP_IO, 3 },
    { OP_CPU, 9 },
    { OP_IO, 1 },
    { OP_CPU, 14 },
    { OP_IO, 1 },
    { OP_CPU, 11 },
    { OP_TERMINATE, 0 }
};

static op_t pid7_ops[] = {
    { OP_CPU, 6 }, 
    { OP_IO, 3 },
    { OP_CPU, 12 },
    { OP_IO, 3 },
    { OP_CPU, 7 },
    { OP_IO, 1 },
    { OP_CPU, 9 },
    { OP_IO, 3 },
    { OP_CPU, 12 },
    { OP_IO, 3 },
    { OP_CPU, 7 },
    { OP_IO, 1 },
    { OP_CPU, 9 },
    { OP_IO, 3 },
    { OP_CPU, 12 },
    { OP_IO, 3 },
    { OP_CPU, 7 },
    { OP_IO, 1 },
    { OP_CPU, 9 },
    { OP_TERMINATE, 0 }
};

pcb_t processes[PROCESS_COUNT] = {
    { 0, "Iapache", 8, PROCESS_NEW, pid0_ops },
    { 1, "Ibash", 7, PROCESS_NEW, pid1_ops },
    { 2, "Imozilla", 7, PROCESS_NEW, pid2_ops },
    { 3, "Ccpu", 5, PROCESS_NEW, pid3_ops },
    { 4, "Cgcc", 1, PROCESS_NEW, pid4_ops },
    { 5, "Cspice", 2, PROCESS_NEW, pid5_ops },
    { 6, "Cmysql", 4, PROCESS_NEW, pid6_ops },
    { 7, "Csim", 3, PROCESS_NEW, pid7_ops }
};


