/* 
 * File:   as_connect.h
 * Author: Kirill Scherba <kirill@scherba.ru>
 *
 * Created on January 12, 2016, 12:04 PM
 */

#ifndef ASCONNECT_H
#define	ASCONNECT_H

#include <angelscript.h>

#if !(defined(_WIN32) || defined(_WIN64))

typedef unsigned int DWORD;

DWORD timeGetTime();
int getch();

#endif

typedef void (*registerGlobalFuntions)(asIScriptEngine *engine) ;

/**
 * AngelScript module data
 */
typedef struct asData {
    
    asIScriptEngine *engine;
    asIScriptContext *ctx;
    DWORD timeOut;
    
} asData;

asData *asEngineInit(const char *script, registerGlobalFuntions rgf = NULL);
void asEngineDestroy(asData *data);

int asCheckFuncError(asData *data, asIScriptFunction *func, int r);

#endif	/* ANGELSCRIPT_H */
