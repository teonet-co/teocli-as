#include <iostream>  // cout

#include <assert.h>  // assert()
#include <string.h>  // strstr()
#include <stdlib.h>  // malloc(), free()

#if !(defined(_WIN32) || defined(_WIN64))
    #include <sys/time.h>
    #include <stdio.h>
    #include <termios.h>
    #include <unistd.h>
#else
    #include <conio.h>   // kbhit(), getch()
    #include <windows.h> // timeGetTime()
#endif

#include "as_connect.h"

// Add Ons
#include "../../../angelscript/sdk/add_on/scriptstdstring/scriptstdstring.h"
#include "../../../angelscript/sdk/add_on/scriptbuilder/scriptbuilder.h"

using namespace std;

#if !(defined(_WIN32) || defined(_WIN64))

#define UINT unsigned int 

// Linux doesn't have timeGetTime(), this essentially does the same
// thing, except this is milliseconds since Epoch (Jan 1st 1970) instead
// of system start. It will work the same though...
DWORD timeGetTime() {

    timeval time;
    gettimeofday(&time, NULL);
    return time.tv_sec*1000 + time.tv_usec/1000;
}

// Linux does have a getch() function in the curses library, but it doesn't
// work like it does on DOS. So this does the same thing, with out the need
// of the curses library.
int getch() {

	struct termios oldt, newt;
	int ch;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~( ICANON | ECHO );
	tcsetattr( STDIN_FILENO, TCSANOW, &newt );

	ch = getchar();

	tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
	return ch;
}

#endif

// Function prototypes
static void ConfigureEngine(asIScriptEngine *engine, registerGlobalFuntions rgf);
static int  CompileScript(asIScriptEngine *engine, const char *script);
void PrintString(string &str);
void PrintString_Generic(asIScriptGeneric *gen);
void timeGetTime_Generic(asIScriptGeneric *gen);
void LineCallback(asIScriptContext *ctx, DWORD *timeOut);
void MessageCallback(const asSMessageInfo *msg, void *param);
int ExecuteMain(asData *data, const char *decl);

/**
 * Initialize AngelScript Engine
 * 
 * @return 
 */
asData *asEngineInit(const char *script, registerGlobalFuntions rgf) {
    
    int r;    
    asData *data = (asData *)malloc(sizeof(asData));
    
    // Create the script engine
    data->engine = asCreateScriptEngine();
    if( data->engine == 0 ) {
    
            cout << "Failed to create script engine." << endl;
            free(data);
            return NULL;
    }

    // The script compiler will write any compiler messages to the callback.
    data->engine->SetMessageCallback(asFUNCTION(MessageCallback), 0, asCALL_CDECL);

    // Configure the script engine with all the functions, 
    // and variables that the script should be able to use.
    ConfigureEngine(data->engine, rgf);

    // Compile the script code
    r = CompileScript(data->engine, script);
    if( r < 0 ) {
    
            data->engine->Release();
            free(data);
            return NULL;
    }

    // Create a context that will execute the script.
    data->ctx = data->engine->CreateContext();
    if( data->ctx == 0 ) {
    
            cout << "Failed to create the context." << endl;
            data->engine->Release();
            free(data);
            return NULL;
    }

    // We don't want to allow the script to hang the application, e.g. with an
    // infinite loop, so we'll use the line callback function to set a timeout
    // that will abort the script after a certain time. Before executing the 
    // script the timeOut variable will be set to the time when the script must 
    // stop executing. 
    r = data->ctx->SetLineCallback(asFUNCTION(LineCallback), &data->timeOut, 
            asCALL_CDECL);
    if( r < 0 ) {
    
            cout << "Failed to set the line callback function." << endl;
            data->ctx->Release();
            data->engine->Release();
            free(data);
            return NULL;
    }
    
    // Execute main function
    ExecuteMain(data, "void main()");

    return data;
}

/**
 * Destroy AngelScript Engine
 * 
 * @param data Pointer to asData
 */
void asEngineDestroy(asData *data) {
    
    if(data != NULL) {
        
        data->ctx->Release();
        data->engine->Release();
        free(data);
    }
}

/**
 * Check execution errors
 * 
 * @param data pointer to asData
 * @param func pointer to asIScriptFunction
 * @param r Value returned by ctx->Execute function
 * 
 * @return 0 - there is not execution errors; 1 - error was found
 */
int asCheckFuncError(asData *data, asIScriptFunction *func, int r) {
    
    // Check execution result and get return value
    if( r != asEXECUTION_FINISHED ) {
        
        // The execution didn't finish as we had planned. Determine why.
        if( r == asEXECUTION_ABORTED ) {
            cout << "The script was aborted before it could finish. "
                    "Probably it timed out." << endl;
        }
        else if( r == asEXECUTION_EXCEPTION )
        {
            cout << "The script ended with an exception." << endl;

            // Write some information about the script exception
            asIScriptFunction *func = data->ctx->GetExceptionFunction();
            cout << "func: " << func->GetDeclaration() << endl;
            cout << "modl: " << func->GetModuleName() << endl;
            cout << "sect: " << func->GetScriptSectionName() << endl;
            cout << "line: " << data->ctx->GetExceptionLineNumber() << endl;
            cout << "desc: " << data->ctx->GetExceptionString() << endl;
        }
        else {
            
            cout << "The script ended for some unforeseen reason (" << r << ")." 
                    << endl;
        }
        
        return 1;
    }
    return 0;
}

/**
 * Compiler messages callback
 * 
 * @param msg
 * @param param
 */
void MessageCallback(const asSMessageInfo *msg, void *param) {

    const char *type = "ERR ";
    if( msg->type == asMSGTYPE_WARNING ) 
            type = "WARN";
    else if( msg->type == asMSGTYPE_INFORMATION ) 
            type = "INFO";

    printf("%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, 
            type, msg->message);
}

/**
 * ConfigureEngine
 * 
 * @param engine
 */
static void ConfigureEngine(asIScriptEngine *engine, registerGlobalFuntions rgf) {

    int r;

    // Register the script string type
    // Look at the implementation for this function for more information  
    // on how to register a custom string type, and other object types.
    RegisterStdString(engine);

    if( !strstr(asGetLibraryOptions(), "AS_MAX_PORTABILITY") )
    {
            // Register the functions that the scripts will be allowed to use.
            // Note how the return code is validated with an assert(). This helps
            // us discover where a problem occurs, and doesn't pollute the code
            // with a lot of if's. If an error occurs in release mode it will
            // be caught when a script is being built, so it is not necessary
            // to do the verification here as well.
            r = engine->RegisterGlobalFunction("void Print(string &in)", 
                    asFUNCTION(PrintString), asCALL_CDECL); assert( r >= 0 );
            r = engine->RegisterGlobalFunction("uint GetSystemTime()", 
                    asFUNCTION(timeGetTime), asCALL_STDCALL); assert( r >= 0 );             
    }
    else
    {
            // Notice how the registration is almost identical to the above. 
            r = engine->RegisterGlobalFunction("void Print(string &in)", 
                    asFUNCTION(PrintString_Generic), asCALL_GENERIC); 
                    assert( r >= 0 );
            r = engine->RegisterGlobalFunction("uint GetSystemTime()", 
                    asFUNCTION(timeGetTime_Generic), asCALL_GENERIC); 
                    assert( r >= 0 );
    }
    // Register custom global functions
    if(rgf != NULL) rgf(engine);


    // It is possible to register the functions, properties, and types in 
    // configuration groups as well. When compiling the scripts it then
    // be defined which configuration groups should be available for that
    // script. If necessary a configuration group can also be removed from
    // the engine, so that the engine configuration could be changed 
    // without having to recompile all the scripts.
}

/**
 * Execute main function
 * 
 * @param data
 * @return 
 */
int ExecuteMain(asData *data, const char* decl) {
    
    int r;
    
    // Find the function for the function we want to execute.
    asIScriptFunction *func = data->engine->GetModule(0)->GetFunctionByDecl(decl);
    if( func == 0 ) {
    
        cout << "The function " << decl << " was not found." << endl;
        return -1;
    }

    // Prepare the script context with the function we wish to execute. Prepare()
    // must be called on the context before each new script function that will be
    // executed. Note, that if you intend to execute the same function several 
    // times, it might be a good idea to store the function returned by 
    // GetFunctionByDecl(), so that this relatively slow call can be skipped.
    r = data->ctx->Prepare(func);
    if( r < 0 ) {
    
        cout << "Failed to prepare the context." << endl;
        return -1;
    }

    // Set the timeout before executing the function. Give the function 1 sec
    // to return before we'll abort it.
    data->timeOut = timeGetTime() + 1000;

    // Execute the function
    cout << endl << "===========" << endl 
            << "Executing function '" << decl << "' of the script." << endl;
    cout << "---" << endl;
    r = data->ctx->Execute();
    cout << "---" << endl;
    if(!asCheckFuncError(data, func, r)) {
    
        cout << "The script finished successfully." << endl;
    }
    
    return 0;
}

/**
 * CompileScript
 * 
 * @param engine
 * @return 
 */
static int CompileScript(asIScriptEngine *engine, const char* script) {

    int r;

    // The builder is a helper class that will load the script file, 
    // search for #include directives, and load any included files as 
    // well.
    CScriptBuilder builder;

    // Build the script. If there are any compiler messages they will
    // be written to the message stream that we set right after creating the 
    // script engine. If there are no errors, and no warnings, nothing will
    // be written to the stream.
    r = builder.StartNewModule(engine, 0);
    if( r < 0 )
    {
            cout << "Failed to start new module" << endl;
            return r;
    }
    r = builder.AddSectionFromFile(script);
    if( r < 0 )
    {
            cout << "Failed to add script file" << endl;
            return r;
    }
    r = builder.BuildModule();
    if( r < 0 )
    {
            cout << "Failed to build the module" << endl;
            return r;
    }

    // The engine doesn't keep a copy of the script sections after Build() has
    // returned. So if the script needs to be recompiled, then all the script
    // sections must be added again.

    // If we want to have several scripts executing at different times but 
    // that have no direct relation with each other, then we can compile them
    // into separate script modules. Each module use their own namespace and 
    // scope, so function names, and global variables will not conflict with
    // each other.       

    return 0;
}

/**
 * line callback function
 * 
 * @param ctx
 * @param timeOut
 */
void LineCallback(asIScriptContext *ctx, DWORD *timeOut) {

    // If the time out is reached we abort the script
    if( *timeOut < timeGetTime() )
            ctx->Abort();

    // It would also be possible to only suspend the script,
    // instead of aborting it. That would allow the application
    // to resume the execution where it left of at a later 
    // time, by simply calling Execute() again.
}

/**
 * Function implementation with native calling convention
 * 
 * @param str
 */
void PrintString(string &str) {

    cout << str;
}

/**
 * Function implementation with generic script interface
 * 
 * @param gen
 */
void PrintString_Generic(asIScriptGeneric *gen) {

    string *str = (string*)gen->GetArgAddress(0);
    cout << *str;
}

/**
 * Function wrapper is needed when native calling conventions are not supported
 * 
 * @param gen
 */
void timeGetTime_Generic(asIScriptGeneric *gen) {

    gen->SetReturnDWord(timeGetTime());
}
