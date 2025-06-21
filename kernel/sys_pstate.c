#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "riscv.h"
#include "spinlock.h"
#include "proc.h"
#include "defs.h"
extern struct proc proc[NPROC];
extern struct cpu cpus[NCPU];

void
sys_pstate(void)
{
    //Prints out the pricess id, process name, process state, nad parent name.
    struct proc *p;
    int runCounter = 0;
    int sleepCounter = 0;
    int runnableCounter = 0;
    int totalCounter = 0;
    for(p = proc; p < &proc[NPROC]; p++) {
        if(p->state == RUNNABLE) {
            runnableCounter++;
        } else if(p->state == RUNNING) {
            runCounter++;
        } else if(p->state == SLEEPING) {
            sleepCounter++;
        }        
        if(p->state == RUNNABLE || p->state == RUNNING || p->state == SLEEPING)
        {
            const char *state_var;
            switch (p->state) {
                    case SLEEPING:
                        state_var = "SLEEPING";
                        break;
                    case RUNNABLE:
                        state_var = "RUNNABLE";
                        break;
                    case RUNNING:
                        state_var = "RUNNING";
                        break;
                    default:
                        state_var = "UNKNOWN";
                        break;                        
                }            
            printf("pid: %d, state: %s, name: %s, parent: %s\n", p->pid, state_var, p->name, p->parent ? p->parent->name : "(init)");
            totalCounter++;
        }
    }
    printf("Process State Summary:\n");
    printf("Total: %d\n", totalCounter);
    // printf("RUNNING: %d\n", runCounter);
    // printf("SLEEPING: %d\n", sleepCounter);
    
    for(int i = 0; i < NCPU; i++) {
        struct cpu *c = &cpus[i];
        //Print all details about the CPU state

        printf("CPU %d ", i);

        if(c->proc) {
            printf("CPU %d: running process %d\n", i, c->proc->pid);
        } else {
            printf("CPU %d: idle\n", i);
        }
    }
}
