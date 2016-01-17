/**
 * L0 System commands \todo put the enum CMD_L to as_teocli.cpp module 
 */
enum CMD_L {
    
    CMD_L_ECHO = 65,         ///< #65 Echo command
    CMD_L_ECHO_ANSWER,       ///< #66 Answer to echo command
    CMD_L_PEERS = 72,        ///< #72 Get peers command
    CMD_L_PEERS_ANSWER,      ///< #73 Answer to get peers command
    CMD_L_AUTH = 77,         ///< #77 Auth command
    CMD_L_AUTH_ANSWER,       ///< #78 Auth answer command
    CMD_L_L0_CLIENTS,        ///< #79 Get clients list command
    CMD_L_L0_CLIENTS_ANSWER, ///< #80 Clients list answer command
    
    CMD_L_END = 127
};

// Teonet client test
void teocli_test() {

    // Teonet L0 server parameters
    const string host_name = "teocli-as"; // This client name
    const string peer_name = "teo-web"; // Peer to send messages to
    const string TCP_SERVER = "127.0.0.1"; // Server to connect to
    const int TCP_PORT = 9000; // Server port

    // Initialize L0 Client library
    teoLNullInit();

    // Connect to L0 server
    teoLNullConnectData con = teoLNullConnect(TCP_SERVER, TCP_PORT);
    Print("Connection fd: " + con.fd + "\n");
    if(con.fd > 0) {

        // Send (1) Initialization packet to L0 server
        int snd = teoLNullLogin(con, host_name);
        //if(snd == -1) perror(strerror(errno));
        Print("Send " + snd + " bytes packet to L0 server, Initialization packet\n");

        // Send (2) peer list request to peer, command CMD_L_PEERS
        snd = teoLNullSend(con, CMD_L_PEERS, peer_name, "", 1);        
        Print("Send " + snd + " bytes packet to L0 server to peer " + peer_name + ", " +
              "cmd = " + CMD_L_PEERS + " (CMD_L_PEERS)\n");

        // Receive (1) answer from server, CMD_L_PEERS_ANSWER      
//        while((rc = teoLNullRecv(con)) == -1) teoLNullSleep(50);  

        // Process received data
//        if(rc > 0) {
            
//            teoLNullCPacket *cp = (teoLNullCPacket*) con->read_buffer;            
//            printf("Receive %d bytes: %d bytes data from L0 server, "
//                    "from peer %s, cmd = %d\n", 
//                    (int)rc, cp->data_length, cp->peer_name, cp->cmd);
            
            // Process CMD_L_PEERS_ANSWER
//            if(cp->cmd == CMD_L_PEERS_ANSWER && cp->data_length > 1) {
//            }
//        }

        // Close connection
//        teoLNullDisconnect(con);
    }

    // Cleanup L0 Client library
    teoLNullCleanup();
}
