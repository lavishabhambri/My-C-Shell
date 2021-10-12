#ifndef __INTERRUPT_H
#define __INTERRUPT_H

// These functions are used to implement the command - baywatch -n 5 interrupt
void interrupt(long long totalArgsInEachCommand, char *c[]);
int endingCondition(ll time, char *c[]);

#endif