/** 
 * \file   main.cpp
 * \author Kirill Scherba <kirill@scherba.ru>
 * 
 * Teocli AngelScript sample application
 *
 * Created on January 11, 2016, 5:37 PM
 */

#include <iostream>  // cout
#include "modules/as_connect.h"

using namespace std;

#define TAS_VERSION "0.0.1"

int RunScriptFunction(asData *data);

/**
 * Main application function
 * 
 * @param argc
 * @param argv
 * @return 
 */
int main(int argc, char** argv) {

    cout << "Teocli AngelScript ver " << TAS_VERSION << endl;
    
    // Initialize AngelScript Engine and execute main function of the script
    asData *data = asEngineInit("main.as");
        
    if(data != NULL) {
        
        // Run scripts test function float calc(float, float)
        RunScriptFunction(data);

        // Destroy AngelScript Engine
        asEngineDestroy(data);    
    }

    // Wait until the user presses a key
    cout << endl << "Press any key to quit." << endl;
    while(!getch());
    
    return 0;
}

/**
 * Run script function example 
 * 
 * @param data
 * @return 
 */
int RunScriptFunction(asData *data) {

    int r;
    const char *decl = "float calc(float, float)";

    // 1) Find the function for the function we want to execute.
    asIScriptFunction *func = data->engine->GetModule(0)->GetFunctionByDecl(decl);
    if( func == 0 ) {

        cout << "The function '" << decl << "' was not found." << endl;
        return -1;
    }

    // 2) Prepare the script context with the function we wish to execute. Prepare()
    // must be called on the context before each new script function that will be
    // executed. Note, that if you intend to execute the same function several 
    // times, it might be a good idea to store the function returned by 
    // GetFunctionByDecl(), so that this relatively slow call can be skipped.
    r = data->ctx->Prepare(func);
    if( r < 0 ) {

        cout << "Failed to prepare the context." << endl;
        return -1;
    }

    // 3) Now we need to pass the parameters to the script function. 
    data->ctx->SetArgFloat(0, 3.14159265359f);
    data->ctx->SetArgFloat(1, 2.71828182846f);

    // 4) Set the timeout before executing the function. Give the function 1 sec
    // to return before we'll abort it.
    data->timeOut = timeGetTime() + 1000;

    // 5) Execute the function
    cout << endl << "===========" << endl 
            << "Executing function '" << decl << "' of the script." << endl;
    cout << "---" << endl;
    r = data->ctx->Execute();
    cout << "---" << endl;

    // 6) Check execution result and get return value
    if(!asCheckFuncError(data, func, r)) {

        // Retrieve the return value from the context
        float returnValue = data->ctx->GetReturnFloat();
        cout << "The script function returned: " << returnValue << endl;
    }

    return 0;
}
