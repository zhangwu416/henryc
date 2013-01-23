#include "socks_ops.h"

#include <iostream>
using namespace std;

namespace henrylib
{
    namespace mynetwork
    {
        namespace socks_ops
        {
            int get_sock_error(int sockfd_)
            {
                int optval = 0;
                socklen_t optlen = sizeof(int);

                if (::getsockopt(sockfd_, SOL_SOCKET, SO_ERROR, &optval, &optlen) < 0)
                {
                    return errno;
                }

                return optval;
            }

            int set_sock_nonblock(int sockfd_)
            {
                int flag = ::fcntl(sockfd_, F_GETFL, 0);
                if (flag < 0)
                {
                    return flag;
                }

                flag |= O_NONBLOCK;
                if (::fcntl(sockfd_, F_SETFL, flag) < 0)
                {
                    return -1;
                }

                return 0;

            }

            int set_sock_close_on_exec(int sockfd_)
            {
                int flag = ::fcntl(sockfd_, F_GETFD, 0);
                if (flag < 0)
                {
                    return flag;
                }

                flag |= FD_CLOEXEC;
                if (::fcntl(sockfd_, F_SETFD, flag) < 0)
                {
                    return -1;
                }

                return 0;
            }

            void to_ip_port_by_addr(char* buffer_, size_t size_, const struct sockaddr_in& addr_)
            {
                if (buffer_ != NULL && size_ != 0)
                {
                    uint16_t port = ntohs(addr_.sin_port);
                    char host[INET_ADDRSTRLEN + 1] = {0};
                    to_ip_by_addr(host, INET_ADDRSTRLEN, addr_);
                    snprintf(buffer_, size_, "%s:%u", host, port);
                }
            }

            void to_ip_by_addr(char* buffer_, size_t size_, const struct sockaddr_in& addr_)
            {
                if (buffer_ != NULL && size_ != 0)
                {
                    ::inet_ntop(AF_INET, &addr_.sin_addr, buffer_, size_);
                }
            }

            
            uint32_t ipv4_string_to_int(const string& ipv4_str_)
            {
                in_addr_t netaddr = ::inet_addr(ipv4_str_.c_str());
                if (netaddr == INADDR_NONE)
                {
                    return 0;
                }

                return ntohl(netaddr);
            }

            string  ipv4_int_to_string(uint32_t ipv4_int_)
            {
                struct in_addr addr;
                bzero(&addr, sizeof(addr));
                addr.s_addr = htonl(ipv4_int_);
                return string(::inet_ntoa(addr));
            }

            void  ipv4_int_to_string(uint32_t ipv4_int_, string& ipv4_str_out_)
            {
                struct in_addr addr;
                bzero(&addr, sizeof(addr));
                addr.s_addr = htonl(ipv4_int_);
                ipv4_str_out_ = string(::inet_ntoa(addr));
            }

            void from_ip_port_to_addr(const char* ip_, uint16_t port_, struct sockaddr_in* addr_)
            {
                if (ip_ != NULL && addr_ != NULL)
                {
                    addr_->sin_family = AF_INET;
                    addr_->sin_port = htons(port_);
                    addr_->sin_addr.s_addr = ::inet_addr(ip_);
                    //! ::inet_pton(AF_INET, IP, &addr_->sin_addr);
                }
            }

            struct sockaddr_in get_local_addr(int sockfd_)
            {
                struct sockaddr_in addr;
                socklen_t len = sizeof(struct sockaddr_in);
                bzero(&addr, len);

                ::getsockname(sockfd_, (struct sockaddr*)&addr, &len);

                return addr;
            }

            struct sockaddr_in get_peer_addr(int sockfd_)
            {
                struct sockaddr_in addr;
                socklen_t len = sizeof(struct sockaddr_in);
                bzero(&addr, len);

                ::getpeername(sockfd_, (struct sockaddr*)&addr, &len);

                return addr;
            }

            bool is_self_connect(int sockfd_)
            {
                struct sockaddr_in localaddr = get_local_addr(sockfd_);
                struct sockaddr_in peeraddr = get_peer_addr(sockfd_);
                return localaddr.sin_port == peeraddr.sin_port && localaddr.sin_addr.s_addr == peeraddr.sin_addr.s_addr;
            }

            int set_addr_resuse(int sockfd_, bool on_)
            {
                int optval = on_ ? 1 : 0;
                if (::setsockopt(sockfd_, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0)
                {
                    return errno;
                }

                return 0;
            }
        }
    }
}
