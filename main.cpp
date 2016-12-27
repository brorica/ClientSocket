#include <netinet/in.h>
#include "senddata.h"
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    /*
    argc=3;
    argv[1] = "127.0.0.1";
    argv[2] = "12345";
    */
    if(argc != 3)
    {
        printf("usage : netclient <ip> <port>\n");
        exit(0);
    }
    int sd = socket(AF_INET,SOCK_STREAM, 0);      // socket description
    if(sd==-1)
    {
        cout << strerror(errno) << endl;
        exit(0);
    }

    sockaddr_in addr;                     // socket address
    addr.sin_family = AF_INET;      // use version 4
  //  addr.sin_addr.s_addr = htonl(0x7F000001) ;   // local IP address
    addr.sin_port = htons(atoi(argv[2]));     // port number
    inet_pton(AF_INET, argv[1], &addr.sin_addr.s_addr);

    // if connect start, syn
    if( connect(sd, (sockaddr*)&addr,sizeof(addr)) == -1 )
    {
        cout << strerror(errno) << endl;
        exit(0);
    }
    senddata(sd);


    close(sd);


    return 0;
}
