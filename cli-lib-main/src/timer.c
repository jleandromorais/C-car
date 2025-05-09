/**
 * timer.c
 * Created on Aug, 23th 2023
 * Author: Tiago Barros
 * Based on "From C to C++ course - 2002"
*/

#include "timer.h"
#include <sys/time.h>
#include <stdio.h>

static struct timeval timer, now;
static int delay = -1;

void timerInit(int valueMilliSec)
{
    delay = valueMilliSec;
    gettimeofday(&timer, NULL);
}

void timerDestroy()
{
    delay = -1;
}

void timerUpdateTimer(int valueMilliSec)
{
    delay = valueMilliSec;
    gettimeofday(&timer, NULL);
}
// Em timer.c
long long getTimeDiff() {
    gettimeofday(&now, NULL);
    long long now_ms = now.tv_sec * 1000LL + now.tv_usec / 1000;
    long long timer_ms = timer.tv_sec * 1000LL + timer.tv_usec / 1000;
    return now_ms - timer_ms; // Diferença absoluta em milissegundos
}

int timerTimeOver()
{
    int ret = 0;

    if (getTimeDiff() > delay)
    {
        ret = 1;
       // gettimeofday(&timer, NULL);
    }

    return ret;
}

void timerPrint()
{
    printf("Timer: %lld", getTimeDiff());

}