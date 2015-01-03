var sec_name      = ["Sec0", "Sec1"]
// var strat_name    = ["strat0", "strat1"];
var strat_name    = ["EqualWeighted", "EqualWeighted2"];
var value_header  = ["time", "invested", "cash", "asset", "liabilities", "equity"];
var state_header  = ["time", "Sec0", "Sec1"]
var weight_header = ["time", "type", "Sec0", "Sec1"]
var order_header  = state_header; // if no Market Engine
var point_header  = ["stat", "strat0" , "strat1"];

var weight= [];
var state = [];  
var value = [];  
var order = [];  
var path  = [];  
var point; 

var nb_strat = strat_name.length;
var nb_sec   = sec_name.length;


var type_weight = function(d)
{
    d["time"] = +d["time"];
    d["type"] = +d["type"];
    
    for(i = 0; i < nb_sec; i++)
        d[sec_name[i]] = +d[sec_name[i]];

    return d;
};

var type_state = function(d)
{
    d["time"] = +d["time"];
    
    for(i = 0; i < nb_sec; i++)
        d[sec_name[i]] = +d[sec_name[i]];

    return d;
};

var type_value = function(d)
{
    d["time"]        = +d["time"];
    d["invested"]    = +d["invested"];
    d["cash"]        = +d["cash"];
    d["asset"]       = +d["asset"];
    d["liabilities"] = +d["liabilities"];
    d["equity"]      = +d["equity"];
    
    return d;
};

var type_path = function(d)
{
    d["time"]         = +d["time"];
    d["invested"]     = +d["invested"];
    d["cumulative"]   = +d["cumulative"];
    d["periodically"] = +d["periodically"];
    d["drawdown"]     = +d["drawdown"];
    
    return d;
};

var type_order = function(d)
{
    d["time"] = +d["time"];
    
    for(i = 0; i < nb_sec; i++)
        d[sec_name[i]] = +d[sec_name[i]];

    return d;
};

// load all the generated data into memory
for(i = 0; i < nb_strat; i++)
{
    d3.csv("../gen/" + strat_name[i] + ".MatrixWeight.csv", type_weight, function(error, data) {
        weight.append(data);
    });
    d3.csv("../gen/" + strat_name[i] + ".PortfolioState.csv", type_state, function(error, data) {
        state.append(data);
    });
    d3.csv("../gen/" + strat_name[i] + ".PortfolioValues.csv", type_value, function(error, data) {
        value.append(data);
    });
    d3.csv("../gen/" + strat_name[i] + ".TransactionOrder.csv", type_order, function(error, data) {
        order.append(data);
    });
    d3.csv("../gen/" + strat_name[i] + ".PathStatistic.csv", type_path, function(error, data) {
        path.append(data);
    });
}

var type_point = function(d)
{
    d["stat"] = d["stat"];
    
    for(i = 0; i < nb_strat; i++)
        d[strat_name[i]] = +d[strat_name[i]];

    return d;
};
        
d3.csv("../gen/Strat3.StatisticPoint.csv", type_point, function(error, data) {
    point = data;
});

