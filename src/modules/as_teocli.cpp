/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <assert.h> // assert
#include <string.h> // strstr
#include <unistd.h> // close

#include <iostream>  // cout
 
#include "as_teocli.h"
#include "teonet_l0_client.h"

using namespace std;

static teoLNullConnectData* _teoLNullConnect(string &server, int port) {
    
    return teoLNullConnect(server.c_str(), port);
}

static void _teoLNullDisconnect(teoLNullConnectData &con) {
    
    #if defined(HAVE_MINGW) || defined(_WIN32) || defined(_WIN64) 
        #define close_socket(fd) closesocket(fd)
    #else
        #define close_socket(fd) close(fd)
    #endif
    
    cout << "Disconnect fd: " << con.fd << endl;
    if(con.fd > 0) close_socket(con.fd);
    if(con.read_buffer != NULL) free(con.read_buffer);
    // \todo How to free con 
    //teoLNullDisconnect(&con);
}

static int _teoLNullLogin(teoLNullConnectData &con, string &host_name) {
    
    return teoLNullLogin(&con, host_name.c_str());
}

static int _teoLNullSend(teoLNullConnectData &con, int cmd, string &peer_name, 
        void *data, int data_length) {
    
    return teoLNullSend(&con, cmd, peer_name.c_str(), data, data_length);
}

/**
 * Register Teocli functions for executing in AngelScripts
 * 
 * Register the functions that the scripts will be allowed to use.
 * Note how the return code is validated with an assert(). This helps
 * us discover where a problem occurs, and doesn't pollute the code
 * with a lot of if's. If an error occurs in release mode it will
 * be caught when a script is being built, so it is not necessary
 * to do the verification here as well.    
 * 
 * @param engine
 */
void RegisterTeocliFuntions(asIScriptEngine *engine) {
    
    int r;
    
    // L0 client connect data type
    r = engine->RegisterObjectType(
        "teoLNullConnectData", sizeof(teoLNullConnectData), 
        asOBJ_VALUE | asOBJ_POD
    ); assert( r >= 0 );
    
    // L0 client connect data property              
    r = engine->RegisterObjectProperty(
        "teoLNullConnectData", "int fd", 
        asOFFSET(teoLNullConnectData,fd)
    ); assert( r >= 0 );

    // L0 client global functions
    
    // Initialize L0 Client library
    // void teoLNullInit();
    r = engine->RegisterGlobalFunction(
        "void teoLNullInit()", 
        asFUNCTION(teoLNullInit), asCALL_CDECL
    ); assert( r >= 0 );
    
    // Connect to L0 server
    // teoLNullConnectData* teoLNullConnect(const char *server, int port);
    r = engine->RegisterGlobalFunction(
        "teoLNullConnectData& teoLNullConnect(string &in server, int port)", 
        asFUNCTION(_teoLNullConnect), asCALL_CDECL
    ); assert( r >= 0 );
    
    // Close connection
    // void teoLNullDisconnect(teoLNullConnectData *con);
    r = engine->RegisterGlobalFunction(
        "void teoLNullDisconnect(teoLNullConnectData &in con)", 
        asFUNCTION(_teoLNullDisconnect), asCALL_CDECL
    ); assert( r >= 0 );
    
    // Cleanup L0 Client library
    // void teoLNullCleanup();
    r = engine->RegisterGlobalFunction(
        "void teoLNullCleanup()", 
        asFUNCTION(teoLNullCleanup), asCALL_CDECL
    ); assert( r >= 0 );
    
    // Send Initialization packet to L0 server
    // ssize_t teoLNullLogin(teoLNullConnectData *con, const char* host_name);
    r = engine->RegisterGlobalFunction(
        "int teoLNullLogin(teoLNullConnectData &in con, string &in host_name)", 
        asFUNCTION(_teoLNullLogin), asCALL_CDECL
    ); assert( r >= 0 );
    
    // Create L0 clients packet and send it to L0 server
    // ssize_t teoLNullSend(teoLNullConnectData *con, int cmd, const char *peer_name, 
    //    void *data, size_t data_length)
    r = engine->RegisterGlobalFunction(
        "int teoLNullSend(teoLNullConnectData &in con, int cmd, string &in peer_name, string &in data, int data_length)", 
        asFUNCTION(_teoLNullSend), asCALL_CDECL
    ); assert( r >= 0 );
}
