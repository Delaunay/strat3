var option = {
    margin : {
        top : 20,
        bot : 40,
        right : 40,
        left : 80
    },
    width: 2,
    axes : true,
    axesoption :  {
        width: 1,
        color: "rgba(0,0,0, 1)"
    },
    grid : true,
    gridoption: {
        stepX : 10,
        stepY : 10,
        color : "rgba(5, 5, 5, 0.5)",
        width : 1,
        label : true,
        ylabel : null,
        xlabel : null,
        ypos : "left",
        xpos : "bot",
        textcolor : "rgba(20,20,20,1)",
        font : "14px Courier New",
        date : false,
        datedata : 0,
        scaleX : function(x)    { return x; },
        sacleY : function(y)    { return y; },
        multiplicatorX : 1,
        multiplicatorY : 100
    }
};

var color = 
[
    "rgba(128  ,0    , 0, 0.7)",
    "rgba(0  ,128    , 64, 0.7)",
    "rgba(0    , 0     , 255, 0.7)",
    "rgba(0  ,128    , 0, 0.7)",
    "rgba(155  , 5     , 5, 0.7)",
    "rgba(5    , 155   , 5, 0.7)",
    "rgba(255  ,128    , 0, 0.7)",
    "rgba(5    , 5     , 155, 0.7)",
    "rgba(5    , 155   , 155, 0.7)",
    "rgba(155  , 5     , 155, 0.7)"
];

var option_hist = {
    margin : {
        top : 40,
        bot : 40,
        right : 40,
        left : 80
    },
    width: 2,
    axes : true,
    axesoption :  {
        width: 2,
        color: "rgba(0,0,0, 1)"
    },
    fillRect : true,
    grid : true,
    gridoption: {
        stepX : 10,
        stepY : 10,
        color : "rgba(5, 5, 5, 0.5)",
        width : 1,
        label : true,
        ylabel : null,
        xlabel : null,
        ypos : "left",
        xpos : "bot",
        textcolor : "rgba(20,20,20,1)",
        font : "14px Courier New",
        date : false,
        datedata : 0,
        scaleX : function(x)    { return x; },
        sacleY : function(y)    { return y; },
        multiplicatorX : 1,
        multiplicatorY : 100
    }
};

var option_x100 = {
    margin : {
        top : 15,
        bot : 40,
        right : 15,
        left : 55
    },
    width: 2,
    axes : true,
    axesoption :  {
        width: 1,
        color: "rgba(0,0,0, 1)"
    },
    grid : true,
    gridoption: {
        stepX : 5,
        stepY : 5,
        color : "rgba(5, 5, 5, 0.5)",
        width : 1,
        label : true,
        ylabel : null,
        xlabel : null,
        ypos : "left",
        xpos : "bot",
        textcolor : "rgba(20,20,20,1)",
        font : "14px Courier New",
        date : false,
        datedata : 0,
        scaleX : function(x)    { return x; },
        sacleY : function(y)    { return y; },
        multiplicatorX : 100,
        multiplicatorY : 100
    }
};
