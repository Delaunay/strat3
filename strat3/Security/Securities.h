#ifndef STRAT3_STRAT3_SECURITIES_HEADER
#define STRAT3_STRAT3_SECURITIES_HEADER


/*
 * Define Securities property.
 *
 * Strategy can make queries requesting special
 * properties. (require boost)
 */


#if USING_BOOST_MULTI_INDEX

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>

using boost::multi_index_container;
using namespace boost::multi_index;

namespace SecurityDatabaseInternal{
    struct AssetTicker
    {
        unsigned int    id;
        std::string     ticker;
        std::string     asset_type;
        std::string     market;
        std::string     other1;
        std::string     other2;
        std::string     other3;

        AssetTicker(unsigned int i, std::string t, std::string a, std::string m,
                    std::string o1, std::string o2, std::string o3):
            id(i), ticker(t), asset_type(a), market(m), other1(o1), other2(o2), other3(o3)
        {}

        friend std::ostream& operator<<(std::ostream& os,const AssetTicker& e)
        {
            os << e.id << " " << e.ticker << " " << e.asset_type << std::endl;

            return os;
        }
    };

    struct id{};
    struct ticker{};
    struct asset_type{};
    struct market{};
    struct other1{};
    struct other2{};
    struct other3{};

    typedef multi_index_container<
      AssetTicker,
      indexed_by<
        ordered_unique<     boost::multi_index::tag<id>,            BOOST_MULTI_INDEX_MEMBER(AssetTicker,unsigned int,id)>,
        ordered_unique<     boost::multi_index::tag<ticker>,        BOOST_MULTI_INDEX_MEMBER(AssetTicker,std::string,ticker)>,
        ordered_non_unique< boost::multi_index::tag<asset_type>,    BOOST_MULTI_INDEX_MEMBER(AssetTicker,std::string,asset_type)>,
        ordered_non_unique< boost::multi_index::tag<market>,        BOOST_MULTI_INDEX_MEMBER(AssetTicker,std::string,market)>,
        ordered_non_unique< boost::multi_index::tag<other1>,        BOOST_MULTI_INDEX_MEMBER(AssetTicker,std::string,other1)>,
        ordered_non_unique< boost::multi_index::tag<other2>,        BOOST_MULTI_INDEX_MEMBER(AssetTicker,std::string,other2)>,
        ordered_non_unique< boost::multi_index::tag<other3>,        BOOST_MULTI_INDEX_MEMBER(AssetTicker,std::string,other3)>
        >
    > SecSet;
}

class SecurityDatabase
{
    public:
        enum Field{
            ID,
            Ticker,
            Asset_Type,
            Market,
            Other1,
            Other2,
            Other3,
        };
        typedef SecurityDatabaseInternal::AssetTicker Element;
        typedef SecurityDatabaseInternal::SecSet      Container;

        typedef Container::nth_index<0>::type SecIDSet;
        typedef Container::nth_index<1>::type SecTickerSet;
        typedef Container::nth_index<2>::type SecAssetTypeSet;
        typedef Container::nth_index<3>::type SecMarketSet;

        typedef SecIDSet::iterator SecIDIterator;
        typedef SecTickerSet::iterator SecTickerIterator;
        typedef SecAssetTypeSet::iterator SecAssetTypeIterator;
        typedef SecMarketSet::iterator SecMarketIterator;

        SecurityDatabase():
            _Size(0)
        {}

        void addSec(std::string t,
                    std::string a   = std::string("EQU"),
                    std::string m   = std::string("EQU"),
                    std::string so1 = std::string(""),
                    std::string so2 = std::string(""),
                    std::string so3 = std::string("")
                    );

        std::string     getTicker       (unsigned int ID);
        unsigned int    getid           (std::string s);
        SecTickerSet&   getTickers      ();
        Container       getSet          ()          {   return _Data;  }
        unsigned int    size            ()          {   return _Size;  }

        void print_out_by_id()
        {
            // get a view to index #0 (id)
            const SecIDSet& id_index =  _Data.get<0>();

            // use id_index as a regular std::set
             std::copy(id_index.begin(), id_index.end(),
                       std::ostream_iterator<Element>(std::cout));
        }


    protected:

        unsigned int _Size;
        Container    _Data;
};

#else
#include <string>
#include "../enum.h"

class Security
{
public:

    Security(Index id, std::string ticker,      std::string type     = "Equity",
               std::string market   = "Equity", std::string location = "USD",
               std::string currency = "USD");

    Index       ID;
    std::string ticker;     // XBB      SPY
    std::string type;       // ETF      ETF
    std::string market;     // BONDS    EQUITY
    std::string location;   // CAD      USD
    std::string currency;   // CAD      CAD
};


class SecurityDatabase
{
public:
    SecurityDatabase();

    void add_security(Index id, std::string ticker, std::string type,
                      std::string market = "", std::string location = "",
                      std::string currency = "");



    Index size();

    const Security& operator[] (Index id);

    const std::string ticker  (Index id);
    const std::string type    (Index id);
    const std::string market  (Index id);
    const std::string location(Index id);
    const std::string currency(Index id);

protected:
    std::vector<Security> securities;
};

#endif

#endif
