/**
 * @file      peer_to_peer.h 
 * @author    Kemal UZGOREN
 *
 * @version   v1.0.0
 * @date      25.05.2025
 *
 * @details   
 */
#ifndef PEER_TO_PEER_H_
#define PEER_TO_PEER_H_

#include "server.h"
#include "../../DataStructures/Lists/linked_list.h"

struct peer_to_peer_t {

    struct server_t server; 
    struct linked_list_t known_hosts; 

    int domain; 
    int service; 
    int protocol; 
    int port; 
    u_long interface; 

    void (*user_portal)(struct peer_to_peer_t *peer_to_peer);
    void *(*server_function)(void *arg); 
    void *(*client_function)(void *arg);
};

struct peer_to_peer_t peer_to_peer_constructor(int domain, int service,
                                 int protocol, int port, 
                                 u_long interface,
                                 void *(*server_function)(void *arg), 
                                 void *(*client_function)(void *arg)); 


#endif  /*  PEER_TO_PEER_H_ */