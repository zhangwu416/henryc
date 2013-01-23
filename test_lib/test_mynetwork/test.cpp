#include <iostream>
using namespace std;

#include "socks_ops.h"

using namespace henrylib::mynetwork;

int main()
{
    cout << "len:" << INET_ADDRSTRLEN << endl;
    
    uint32_t naddr = socks_ops::ipv4_string_to_int("127.0.0.1");
    cout << naddr << endl;

    string haddr;
    socks_ops::ipv4_int_to_string(naddr, haddr);
    cout << haddr << endl;
    
    uint16_t port = 80;
    struct sockaddr_in addr;
    bzero(&addr, sizeof(struct sockaddr_in));
    socks_ops::from_ip_port_to_addr(haddr.c_str(), port,  &addr);

    char buffer[1024] = {0};
    socks_ops::to_ip_port_by_addr(buffer, 1024, addr);
    cout << buffer << endl;

    return 0;
}
