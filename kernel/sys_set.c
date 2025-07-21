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
sys_set(void)
{
    int pid, priority;
    argint(0, &pid);
    argint(1, &priority);
    // if (argint(0, &pid) < 0 || argint(1, &priority) < 0)
    //     return -1;
    
    if(priority < MIN_PRIORITY || priority > MAX_PRIORITY)
        return;
    printf("Test");
    printf("%d", pid);
    printf("End Test");
    struct proc *p;
    int found = 0;

    // Find the process with the given pid
    for(p = proc; p < &proc[NPROC]; p++) {      
        if(p->pid == pid) {
            printf("Test");
            printf("pid: %d, state: %d, name: %s\n", p->pid, p->state, p->name);
            acquire(&p->lock);
            p->priority = priority; // Set the new priority
            release(&p->lock);
            found = 1;
            break;
        }
    }

    if(!found) {
        printf("Process with pid %d not found.\n", pid);
    } else {
        printf("Set priority of process %d to %d.\n", pid, priority);
    }
    // struct proc *p;
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
            printf("pid: %d, state: %s, name: %s, parent: %s\n", p->pid, state_var, p->name, p->parent ? p->parent->name : "(init)");
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
