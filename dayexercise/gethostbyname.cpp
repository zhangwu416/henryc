
#include <iostream>
using namespace std;

#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char** argv)
{
    struct hostent* host = NULL;
    char* ptr = *(++argv);

    //!if ((host = gethostbyname(ptr)) == NULL)
    //! ./xxx www.163.com
    //! ./xxx www.google.com
    struct in_addr addr;
    if (inet_aton(ptr, &addr) == 0)
    {
        cout << "error addr" << endl;
        return -1;
    }

    if ((host = gethostbyaddr((const char*)&addr, 4, AF_INET)) == NULL)
    //! ./xxx 127.0.0.1
    {
        cout << "error:" << hstrerror(h_errno) << endl;
    }
    else
    {
        cout << "official hostname:" << host->h_name << endl;
        char** pptr = host->h_aliases;
        for (; *pptr != NULL; ++pptr)
        {
            cout << "alias name:" << *pptr << endl;
        }

        cout << "length:" << host->h_length << endl;
        cout << "inet addrstrlen:" << INET_ADDRSTRLEN << endl;
        cout << "AF_INET:" << AF_INET << endl;
        char str[INET_ADDRSTRLEN];
        bzero(str, INET_ADDRSTRLEN);
        for (pptr = host->h_addr_list; *pptr != NULL; pptr++)
        {
            cout << "addr:" << inet_ntop(host->h_addrtype, *pptr, str, INET_ADDRSTRLEN) << endl;
        }
    }
    return 0;
}
