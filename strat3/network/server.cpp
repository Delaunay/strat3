#include <SFML/Network.hpp>
#include <list>

#include "types.h"

namespace strat3{

/*

enum OPCODE
{
    TWEIGHT,
    TANSWER,
    MATRIX,   // Key => (n x m) => data
};


class BacktestServer
{
public:
    typedef std::list<sf::TcpSocket*> ClientList;

    BacktestServer():
        client(new sf::TcpSocket)
    {}

    void accept_client()
    {
        static sf::Socket::Status s;

        s = listener.accept(*client);

        if (s == sf::Socket::Done){
            clients.insert(clients.begin(), client);
            selector.add(*client);

            client = new sf::TcpSocket;
            client->setBlocking(false);
        }
    }

    void process_clients()
    {
        static sf::Socket::Status s;
        //sf::

        for(auto& skt:clients)
        {
            if(selector.isReady(*skt))
            {
                 client_action(*skt);
            }
        }
    }

    void client_action(sf::TcpSocket& connection)
    {
        s = skt->receive(&buffer[0], buffer.size(), received);

        if (s == sf::Socket::Disconnected){
            selector.remove(*skt);
            clients.remove(skt);
            break;      // need to break because
                        // the list is not good anymore
        }
        else{
            std::cout << "I received:\n";
            std::cout << buffer.substr(0, received) << "\n";

            std::size_t sent = 0;
            while(sent != message.size())
                s = skt->send(&message[0], message.size());

            if (s != sf::Socket::Done)
                std::cout << "WTF: " << s << std::endl;
        }
    }

    ~BacktestServer()
    {
        delete client;

        for(auto& skt:clients)
            delete skt;
    }


protected:
    sf::TcpSocket*      client{nullptr};

    ClientList          clients;
    sf::SocketSelector  selector;
    sf::TcpListener     listener;
    const uint16        port{STRAT3_PORT};
};
*/
}
int main()
{
    return 0;
}
