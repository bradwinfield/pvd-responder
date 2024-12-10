// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h> 
#include <string.h> 
#define PORT 8080 
int main(int argc, char const *argv[]) 
{ 
    int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    //int opt = 1; 
    int hitcount = 0;
    int addrlen = sizeof(address); 
    char buffer[1024] = {0}; 
    char response[1024];
    struct hostent *host_entry;
    char hostbuffer[256]; 
    char hitcount_s[80];
    char *IPbuffer; 
    int hostname; 
    char guid[80];

    hostname = gethostname(hostbuffer, sizeof(hostbuffer)); 
    host_entry = gethostbyname(hostbuffer); 
    IPbuffer = inet_ntoa(*((struct in_addr*) host_entry->h_addr_list[0]));

    strcpy (guid,"No CF_INSTANCE_GUID found");
    char *g = getenv("CF_INSTANCE_GUID");
    if ( g != NULL ) sprintf(guid,"%s",g);
       
    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
    while (1) {
    	if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
                       (socklen_t*)&addrlen))<0) 
    	{ 
        	perror("accept"); 
        	exit(EXIT_FAILURE); 
    	} 
    	valread = read( new_socket , buffer, 1024); 
        strcpy(response,"HTTP/1.1 200 OK\n\n{\"HIT_COUNT\":");
        hitcount++;
        sprintf(hitcount_s,"%d",hitcount);
        strcat(response,hitcount_s);
        strcat(response,",\"CF_INSTANCE_IP\":\"");
        strcat(response, IPbuffer);
        strcat(response,"\",\"CF_INSTANCE_GUID\":\"");
        strcat(response,guid);
        strcat(response,"\",\"RESPONSE\":\"\"}");
    	send(new_socket , response , strlen(response) , 0 ); 
	    close(new_socket);
    }
    return 0; 
}
