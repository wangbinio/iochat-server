//
// Created by summer on 2024/9/4.
//

#ifndef SERVER_H
#define SERVER_H

#include "inc.h"

class Server : public std::enable_shared_from_this<Server> {
public:
  Server(net::io_service& io_service, unsigned short port);
  void Start();

private:
  net::io_service& io_service_;
  tcp::acceptor acceptor_;
};


#endif //SERVER_H
