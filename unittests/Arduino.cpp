/*--------------------------------------------------------------------
 * This file is part of the RcCarSwitches arduino library.
 *
 * RcCarSwitches is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * RcCarSwitches is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with RcCarSwitches.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright: Jochen Schales 2015
 *
 * --------------------------------------------------------------------*/


#include "Arduino.h"

#include <cstdlib>
#include <sys/time.h>
#include <cstdio>

long millis()
{
    static struct timeval sInitialTimeVal;
    static bool sIsInitialized = false;

    if (!sIsInitialized)
    {
        sIsInitialized = true;
        gettimeofday(&sInitialTimeVal,NULL);
    }

    struct timeval lTimeVal;

    gettimeofday(&lTimeVal,NULL);

    return (lTimeVal.tv_sec - sInitialTimeVal.tv_sec) * 1000 + (lTimeVal.tv_usec - sInitialTimeVal.tv_usec) / 1000;
}


#include <windows.h>

void millisleep(long usec)
{
    HANDLE timer;
    LARGE_INTEGER ft;

    ft.QuadPart = -(10*usec*1000); // Convert to 100 nanosecond interval, negative value indicates relative time

    timer = CreateWaitableTimer(NULL, TRUE, NULL);
    SetWaitableTimer(timer, &ft, 0, NULL, NULL, 0);
    WaitForSingleObject(timer, INFINITE);
    CloseHandle(timer);
}



