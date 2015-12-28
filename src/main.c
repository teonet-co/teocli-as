/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * lr-tmp application
 *
 * main.cpp
 * Copyright (C) Kirill Scherba 2011-2014 <kirill@scherba.ru>
 *
 * yodge-node is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * yodge-node is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "ev_mgr.h"

#define TTMP_VERSION "0.0.0"

#ifdef TEO_THREAD
volatile int teonet_run = 1;
#endif

/**
 * Teonet event handler
 *
 * @param ke
 * @param event
 * @param data
 * @param data_len
 * @param user_data
 */
void event_cb(ksnetEvMgrClass *ke, ksnetEvMgrEvents event, void *data,
              size_t data_len, void *user_data) {

    switch(event) {

        // Calls after event manager stopped
        case EV_K_STOPPED:
            #ifdef TEO_THREAD
            teonet_run = 0;
            #endif
            break;

        default:
            break;
    }
}

/*
 *
 */
int main(int argc, char** argv) {

    printf("Teovpn ver " TTMP_VERSION "\n");

    // Initialize teonet event manager and Read configuration
    ksnetEvMgrClass *ke = ksnetEvMgrInit(argc, argv, event_cb /*NULL*/, READ_ALL);

    // To run teonet as thread change AM_CONDITIONAL(TEO_THREAD, false) in configure.ac to true
    #ifdef TEO_THREAD
    ksnetEvMgrRunThread(ke);
    for(; teonet_run;) {
        sleep(1);
    }
    #else
    // Start teonet
    ksnetEvMgrRun(ke);
    #endif

    return (EXIT_SUCCESS);
}
