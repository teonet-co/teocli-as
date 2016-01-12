#include "script.as"

void main(void) 
{    

    Print("Hello world!\n");


    // Print the current system time
    Print("main: System has been running for " + GetSystemTime()/1000.0 + "." + 
        GetSystemTime()%1000.0 + " seconds\n");

    //for(;;);
}
