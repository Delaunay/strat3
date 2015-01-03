//#include "../Strategy/Strategy.h"
//#include <boost/python.hpp>

//using namespace boost::python;

//class StrategyWrap : public Strategy, wrapper<Strategy>
//{
//public:
//    StrategyWrap(Key managerKey, Key matrixkey, int securitySize,
//                 bool rebalanced = true, Index frequency = 1):
//        Strategy(managerKey, matrixkey, securitySize, rebalanced,
//                 frequency)
//    {}
////    virtual TransactionWeight* operator() (DataQuery*);
////    virtual TransactionWeight* operator() (DataStruct*);

////    // new
////    virtual TransactionWeight* compute_weight(DataStruct*);
////    virtual TransactionWeight* compute_weight(DataQuery*);

////    TransactionWeight compute_weight(DataStruct* q)
////    {
////        if (override f = this->get_override("compute_weight"))
////            return f(q);
////        return *Strategy::compute_weight(q);
////    }

//////    TransactionWeight* compute_weight (DataQuery* q)
//////    {
//////        if (override f = this->get_override("compute_weight"))
//////            return f(q);
//////        return Strategy::compute_weight(q);
//////    }

////    TransactionWeight operator() (DataStruct* q)
////    {
////        if (override f = this->get_override("__call__"))
////            return f(q);
////        return *Strategy::operator() (q);
////    }

////    TransactionWeight* operator() (DataQuery* q)
////    {
////        if (override f = this->get_override("__call__"))
////            return f(q);
////        return Strategy::operator() (q);
////    }

//    std::string title()
//    {
//        if (override f = this->get_override("title"))
//            return f();
//        return Strategy::title();
//    }

//    std::string description()
//    {
//        if (override f = this->get_override("description"))
//            return f();
//        return Strategy::description();
//    }

////    TransactionWeight* def_call_op_q(DataQuery* q)  { return this->Strategy::operator ()(q); }
////    TransactionWeight* def_call_op_s(DataStruct* q) { return this->Strategy::operator ()(q); }
////    TransactionWeight* def_call_cw_q (DataQuery* q) { return this->Strategy::compute_weight(q); }
////    TransactionWeight* def_call_cw_s (DataStruct* q){ return this->Strategy::compute_weight(q); }

//    std::string def_title()            { return this->Strategy::title(); }
//    std::string def_description()      { return this->Strategy::description(); }
//};
