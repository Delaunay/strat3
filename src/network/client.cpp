#include <vector>
#include <SFML/Network.hpp>
#include "Abstract/Strategy.h"
#include "Backtester/DynamicObject.h"

#include "types.h"

using DynamicLoading::DynamicObject;

namespace strat3{

typedef DynamicObject<Strategy> MStrategy;

class Client
{
public:
    Client()
    {}

    ~Client()   {   socket.disconnect();    }

    // Connect to server
    void connect(sf::IpAddress& add, uint16& port)
    {
        socket.setBlocking(false);
        status = socket.connect(add, port);

        for(auto& el:_strategies)
        {
            register_strategy(el);
        }
    }

    void initialize()
    {
        // Strategy
    }

    void receive_matrix()
    {
    }

    void register_strategy(std::pair<unsigned int, MStrategy>&)
    {

    }

    void send_transaction_weight() {}

    void send_data_request() {}


    MStrategy& add_strategy(std::string s)
    {
        _strategies.push_back(std::make_pair(_strategies.size(), MStrategy(s)));

        return _strategies[_strategies.size() - 1].second;
    }

protected:
    sf::TcpSocket socket;
    sf::Socket::Status status;
    std::vector<std::pair<unsigned int, MStrategy> > _strategies;

};
}

int main()
{
    return 0;
}
