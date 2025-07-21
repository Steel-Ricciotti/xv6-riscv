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
sys_ps(void)
{
    struct proc *p;
    int totalCounter = 0;
    for(p = proc; p < &proc[NPROC]; p++) {
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
            printf("pid: %d, name: %s, state: %s, priority: %d\n",p->pid, p->name,state_var,p->priority);
            totalCounter++;
        }
    }
    printf("Process State Summary:\n");
    printf("Total: %d\n", totalCounter);

    
    for(int i = 0; i < NCPU; i++) {
        struct cpu *c = &cpus[i];
        printf("CPU %d ", i);
        if(c->proc) {
            printf("CPU %d: running process %d\n", i, c->proc->pid);
        } else {
            printf("CPU %d: idle\n", i);
        }
    }
}
