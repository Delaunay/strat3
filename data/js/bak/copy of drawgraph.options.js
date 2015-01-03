
var option = {
    margin : {
        top : 20,
        bot : 40,
        right : 40,
        left : 80
    },
    width: 1,
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
        textcolor : "rgba(200,200,200,1)",
        font : "14px Courier New",
        date : false,
        datedata : 0,
        scaleX : function(x)    { return x; },
        sacleY : function(y)    { return y; },
        multiplicatorX : 1,
        multiplicatorY : 100
    }
};

