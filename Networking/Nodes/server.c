/**
 * @file      server.c 
 * @author    Kemal UZGOREN
 *
 * @version   v1.0.0
 * @date      25.05.2025
 *
 * @details   
 */
#include "server.h"
#include "dictionary.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void register_routes_server(struct server_t *server, 
                            char *(*route_function)(void *arg), 
                            char *path); 

struct server_t server_constructor(int domain, int service, int protocol, u_long interface, int port, int backlog) {
    struct server_t server; 

    server.domain = domain;
    server.service = service;
    server.protocol = protocol;
    server.interface = interface;
    server.port = port;
    server.backlog = backlog;

    server.address.sin_family = domain; 
    server.address.sin_port = htons(port); 
    server.address.sin_addr.s_addr = htonl(interface); 

    server.socket = socket(domain, service, protocol); 

    server.router = dictionary_constructor(compare_string_keys); 

    server.register_routes = register_routes_server; 

    if(server.socket == 0) {
        perror("Failed to connect socket...\n");
        exit(1); 
    }

    if ((bind(server.socket, (struct sockaddr *)&server.address, sizeof(server.address))) < 0) {
        perror("Failed to bind socket...\n"); 
        exit(1); 
    }

    if((listen(server.socket, server.backlog)) < 0) {
        perror("Failed to start listening...\n"); 
        exit(1); 
    }
    
    return server; 
}


static void register_routes_server(struct server_t *server, 
                                    char *(*route_function)(void *arg), 
                                    char *path){

    struct server_route_t route; 
    route.router_function = route_function; 
    server->router.insert(&server->router, path, sizeof(char[strlen(path)]), &route, sizeof(route)); 

}