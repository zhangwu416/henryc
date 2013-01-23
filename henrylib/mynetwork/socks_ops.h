#ifndef _SOCKS_OPS_H_
#define _SOCKS_OPS_H_

/*!***************************************
 * struct sockaddr
 * {
 *  sa_family_t sin_family;  //! 2
 *  char        sa_data[14]; //! 14   
 * }//! 16
 *
 * struct sockaddr_in
 * {
 *  sa_family_t     sin_family; //! 2 uint16_t
 *  in_port_t       sin_port;   //! 2 uint16_t
 *  struct in_addr  sin_addr;   //! 4 uint32_t
 *  char            sin_zero[8]; //! 8
 * } //!16
 *
 * struct in_addr
 * {
 *  in_addr_t s_addr; //! uint32_t
 * }
 *
 *
 ****************************************/
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> //for struct sockaddr_in
#include <arpa/inet.h> // for inet_xx

#include <fcntl.h>
#include <unistd.h> // for fcntl

#include <errno.h> // for errno
#include <string>
using namespace std;

namespace henrylib
{
    namespace mynetwork
    {
        namespace socks_ops
        {
            int get_sock_error(int sockfd_);
            int set_sock_nonblock(int sockfd_);
            int set_sock_close_on_exec(int sockfd_);
            void to_ip_port_by_addr(char* buffer_, size_t size_, const struct sockaddr_in& addr_);
            void to_ip_by_addr(char* buffer_, size_t size_, const struct sockaddr_in& addr_);

            uint32_t ipv4_string_to_int(const string& ipv4_str_);
            string  ipv4_int_to_string(uint32_t ipv4_int_);
            void  ipv4_int_to_string(uint32_t ipv4_int_, string& ipv4_str_out_);
            void from_ip_port_to_addr(const char* ip_, uint16_t port_, struct sockaddr_in* addr_);
    
            struct sockaddr_in get_local_addr(int sockfd_);
            struct sockaddr_in get_peer_addr(int sockfd_);
            bool is_self_connect(int sockfd_);


            int set_addr_resuse(int sockfd_, bool on_);
        }
    }
}

#endif
