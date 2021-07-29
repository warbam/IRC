#ifndef SERVER_HPP
# define SERVER_HPP
# include <map>
# include <vector>
# include <list>
# include <string>
# include <cstring>
# include <iostream>
# include <iomanip>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <cerrno>
# include <fcntl.h>
# include <sys/ioctl.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <sys/select.h>
# include <sys/time.h>
# include <netinet/in.h>
# include "User.hpp"
# include "Channel.hpp"

# define TRUE 1
# define FALSE 0
# define PASS_OPE 1234
# define SERVER_NAME "ft_irc.com"


class Channel;

typedef struct s_data
{
    struct sockaddr_in              addr;
    int                             master_socket;
    int                             new_sd;
    int                             ret_select;
    int                             ret_read;
    char                            buffer[512];
    fd_set                          m_set;
    fd_set                          w_set;
    int                             opt;
    struct timeval                  timeout;
    int                             addrlen;
    int                             max_sd;
    std::map<int, User>::iterator   it;

    s_data(){opt = TRUE;};

}               t_data;

class Server
{
    public:
        // Class
        Server();
        ~Server();

        // Setter
        void setPort(int port);
        void setPassword(std::string password);

        // Getter
        int         getPort(void);
        std::string getPassword(void);

        // Method
        void addUser(int fd);
        void init(void);
        void loop(void);
        std::string response(std::string num, std::string resp);

        // Command
        std::vector<std::string> cutMsg(std::string cmd);
        void parseMsg(void);
        void pass(std::vector<std::string> &args);
        void nick(std::vector<std::string> &args);
        void createOrJoinWithPass(std::string chan_name, std::string password);
        void user(std::vector<std::string> &args);
        void join(std::vector<std::string> &args);

        // Close
        void disconnect( void );
        void close_con(void);

    private:
        std::map<int, User>                     _user;
        std::map<std::string, Channel>          _chan;
        int                                     _port;
        std::string                             _password;
        t_data                                  _data;

        void clearBuffer(void);
        void new_connection(void);
        void receive(void);
        void select_fun(void);
};

#endif