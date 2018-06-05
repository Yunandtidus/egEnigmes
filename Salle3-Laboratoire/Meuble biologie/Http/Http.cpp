/*
  Http.cpp - Library for calling Http Server.
  Created by Bureau 401.
*/

#include "Arduino.h"
#include "Http.h"
#include <SPI.h>

/** Default constructor, synchronous mode */
Http::Http() : Http(true){}

/** Constructor
 * @param synchronous : if this HttpClient should be synchronous 
 */
Http::Http(boolean synchronous)
{
  _synchronous = synchronous;
}

String Http::request(IPAddress ip, int port, String url)
{
  if (_synchronous){
    return _requestSync(ip, port, url);
  } else {
    return _requestAsync(ip, port, url);
  }
}

String Http::_requestSync(IPAddress ip, int port, String url)
{
  _client.stop();
  _connectAndSend(ip, port, url);
  while (_client.connected()){
    while (_client.available()){
      _response += (char)(_client.read());
    }
  }
  _client.stop();
  return _parseResponse();
}

String Http::_requestAsync(IPAddress ip, int port, String url)
{
  if(!_pendingRequest) {
    _connectAndSend(ip, port, url);
  } else {
    while (_client.available()){
      _response += (char)(_client.read());
    }
  }
  
  if (!_client.connected()) {
    Serial.println("[DEBUG] disconnecting");
    _pendingRequest = false;
    _client.stop();
    return _parseResponse();
  }
  
  return "";
}

void Http::_connectAndSend(IPAddress ip, int port, String url){
  if (_client.connect(ip, port)){
      Serial.println("[DEBUG] connected");
      _client.println("GET "+url+" HTTP/1.1");
      _client.println("Host: arduino-http");
      _client.println("Connection: close");
      _client.println();
      
      Serial.println("[DEBUG] Sending request to : " + url);
      _pendingRequest = true;
    } else {
      Serial.println("[DEBUG] can't connect to server");
    }
}

String Http::_parseResponse(){
  // ignore http headers, get only the message
  String ret = _response.substring(_response.indexOf("\r\n\r\n"), _response.length());
  _response = "";
  ret.trim();
  return ret;
}
