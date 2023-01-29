#ifndef PRASING_REQUEST_HPP
#define PRASING_REQUEST_HPP

//    define variables //

// -------  cpp -----//
#include <iostream>

// ------    c   ----//
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>  /* See NOTES */
#include <netinet/in.h> // for type (struct sockaddr_in)
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <map>

class  Prasing_Request {
    private :
     std ::string methode;
     std ::string url;
     std ::string budy_url;
     int status;
      std ::map <std::string, std::string> mymap;
     public :
     int check_first_line(std::string first_line);
     void prasing_headr(std ::string headrs);
};
#endif