/*
  Http.h - Library for calling Http Server.
  Created by Bureau 401.
*/
#ifndef Http_h
#define Http_h

#include "Arduino.h"
#include "Ethernet.h"

class Http
{
  public:
    Http();
    Http(boolean synchronous);
    String request(IPAddress ip, int port, String url);
    
  private:
    EthernetClient _client;
    boolean _pendingRequest;
    boolean _synchronous;
    String _response;
    
    void _connectAndSend(IPAddress ip, int port, String url);
    String _requestSync(IPAddress ip, int port, String url);
    String _requestAsync(IPAddress ip, int port, String url);
    String _parseResponse();
};

#endif