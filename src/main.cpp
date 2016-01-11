/* 
 * File:   main.cpp
 * Author: Kirill Scherba <kirill@scherba.ru>
 *
 * Created on January 11, 2016, 5:37 PM
 */

#include <iostream>  // cout
#include <assert.h>  // assert()
#include <string.h>  // strstr()
//#ifdef _LINUX_
	#include <sys/time.h>
	#include <stdio.h>
	#include <termios.h>
	#include <unistd.h>
//#else
//	#include <conio.h>   // kbhit(), getch()
//	#include <windows.h> // timeGetTime()
//#endif
#include <angelscript.h>
//#include "../../../add_on/scriptstdstring/scriptstdstring.h"

using namespace std;

#define TAS_VERSION "0.0.1"

/*
 * 
 */
int main(int argc, char** argv) {

    cout << "Teocli AngelScript ver " << TAS_VERSION << endl;

    return 0;
}
