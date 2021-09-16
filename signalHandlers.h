#ifndef __SIGNALHANDLERS_H
#define __SIGNALHANDLERS_H


void sigchildHandler();
void ctrlCHandler(int sig);
void ctrlZHandler(int sig);

#endif