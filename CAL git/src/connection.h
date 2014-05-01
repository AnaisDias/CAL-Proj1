/*
 * connection.h
 *
 *  Created on: 27 de Abr de 2014
 *      Author: Anaís
 */

#ifndef CONNECTION_H_
#define CONNECTION_H_


#include <cstdio>
#include <cstdlib>
#include <cstring>

#ifdef linux
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#else
#include <winsock2.h>
#endif

#include <string>
#include <iostream>

using namespace std;

class Connection {
 public:
  Connection(short port);

  bool sendMsg(string msg);
  string readLine();
 private:
#ifdef linux
  int sock;
#else
  SOCKET sock;
#endif
};



#endif /* CONNECTION_H_ */
