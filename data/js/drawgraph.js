var color = 
[
    "rgba(100  ,100    , 200, 0.7)",
    "rgba(100  ,200    , 200, 0.7)",
    "rgba(200  ,200    , 100, 0.7)",
    "rgba(100  ,200    , 200, 0.7)",
    "rgba(5    , 5     , 5, 0.7)",
    "rgba(155  , 5     , 5, 0.7)",
    "rgba(5    , 155   , 5, 0.7)",
    "rgba(5    , 5     , 155, 0.7)",
    "rgba(5    , 155   , 155, 0.7)",
    "rgba(155  , 5     , 155, 0.7)"
];

var color_hist = 
[
    "rgba(100  ,100    , 200, 0.3)",
    "rgba(100  ,200    , 200, 0.3)",
    "rgba(200  ,200    , 100, 0.3)",
    "rgba(100  ,200    , 200, 0.3)",
    "rgba(5    , 5     , 5, 0.3)",
    "rgba(155  , 5     , 5, 0.3)",
    "rgba(5    , 155   , 5, 0.3)",
    "rgba(5    , 5     , 155, 0.3)",
    "rgba(5    , 155   , 155, 0.3)",
    "rgba(155  , 5     , 155, 0.3)"
];

function dataRangeMatrix(data)
{
    var maxx = data[0][0][0];
    var maxy = data[0][0][1];
    
    var minx = data[0][0][0];
    var miny = data[0][0][1];
    
    for (var k = 0; k < data.length;k++)
    {
        for (var i = 0; i < data[k].length;i++) 
        {
            if (maxx < data[k][i][0])   maxx = data[k][i][0];
            if (maxy < data[k][i][1])   maxy = data[k][i][1];
            
            if (minx > data[k][i][0])   minx = data[k][i][0];
            if (miny > data[k][i][1])   miny = data[k][i][1];
        }
    }
    
    var rr =    [  [   maxx,   minx    ],
                   [   maxy,   miny    ]
                ];
    return rr;
}

function scale(data, w, h, margin, sx = function(x){ return x;   }, sy = function(y){ return y;   }  )
{
    this.sx = sx;
    this.sy = sy;
    var r = dataRangeMatrix(data);
    this.maxX = r[0][0];
    this.maxY = r[1][0];
    this.minX = r[0][1];
    this.minY = r[1][1];
    this.width = w;
    this.height = h;
    this.margin = margin;
    this.gwidth = w - (this.margin.right + this.margin.left);
    this.gheight = h  - (this.margin.top + this.margin.bot);
    
    this.rangeX = Math.abs(this.maxX - this.minX);
    this.rangeY = Math.abs(this.maxY - this.minY);
    
    this.X = function(x)  {   return ( this.sx(x - this.minX)) * ( this.gwidth / this.sx(this.rangeX) ) + this.margin.left;     }
    this.Y = function(y)  {   return this.gheight * ( 1 - ( this.sy(y - this.minY) ) / this.sy(this.rangeY) ) + this.margin.top;   }
    
    this.wsX = function(x)  {   return ( (x - this.minX)) * ( this.gwidth / (this.rangeX) ) + this.margin.left;     }
    this.wsY = function(y)  {   return this.gheight * ( 1 - ((y - this.minY) ) /(this.rangeY) ) + this.margin.top;   }
}

var gridoption = {
    stepX : 10,
    stepY : 10,
    color : "rgba(0, 0, 0, 0.5)",
    textcolor : "rgba(20,20,20,1)",
    width : 1,
    label : true,
    ylabel : null,
    xlabel : null,
    ypos : "left",
    xpos : "bot",
    font : "14px Courier New",
    date : false,
    datedata : null,
    scaleX : function(x)    { return x; },
    sacleY : function(x)    { return x; },
    multiplicatorX : 1,
    multiplicatorY : 1,
};

function drawGrid(scale, ctx, option = gridoption)
{
    if (option.date == true)
        if (option.datedata == null)
            option.date = false;
            
    function drawHLine(y)   
    {   
        ctx.moveTo(scale.wsX(scale.minX),scale.Y(y));  
        ctx.lineTo(scale.wsX(scale.maxX),scale.Y(y));
    }
    
    function drawVLine(x)   
    {   
        ctx.moveTo(scale.X(x),scale.wsY(scale.minY));  
        ctx.lineTo(scale.X(x),scale.wsY(scale.maxY));
    }
    
    ctx.fillStyle = option.textcolor;
    
    function li(x, d1, d2, x1, x2)
    {
        if (x1 == x2)
            return d1.valueOf();
            
        return (d1.valueOf() - d2.valueOf())/(x1 - x2) * (x - x1) + d1.valueOf();
    }
    
    function drawHText(x, text)
    {
        if (option.date == true)
        {
            x1 = Math.floor(text);
            x2 = Math.ceil(text);
            
            a = new Date(li(text, option.datedata[x1], option.datedata[x2], x1, x2));
            var m = a.getMonth() + 1;
            text = a.getFullYear() + "." + m + "." + a.getDate();

            x = x - 125;
        }
        else
            text = Math.floor(scale.sx(text)* 100 * option.multiplicatorX)/100;
       
        if (option.xpos == "top")
            ctx.fillText(text, scale.X(x), scale.margin.top/2);
        else
            ctx.fillText(text, scale.X(x), scale.height - scale.margin.bot/2);
    }
    
    function drawVText(y, text)
    { 
        if (option.ypos == "left")
            ctx.fillText(Math.floor(text * option.multiplicatorY * 100)/100, 10, scale.Y(y));
        else
            ctx.fillText(Math.floor(text * option.multiplicatorY * 100)/100, scale.X(scale.maxX) + 10, scale.Y(y));
    }
   
    ctx.lineWidth = option.width;
    ctx.strokeStyle = option.color;
    ctx.font = option.font;
    
    ctx.beginPath();
    var b = 0;
    
    for (var j = 0; j <= option.stepX; j++)
    {
        b = scale.minX + scale.rangeX * j / option.stepX;
        drawVLine(b);
        if (option.label == true)
            drawHText(b, b);
    }

    for (var j = 0; j <= option.stepY; j++)
    {
        b = scale.minY + scale.rangeY * j / option.stepY; 
        drawHLine(b);
        if (option.label == true)
            drawVText(b, b);
    }
    ctx.stroke();
}

var axesoption = {
    width: 1,
    color: "rgba(0,0,0, 1)"
}

function drawAxes(scale, ctx, option = axesoption)
{
    ctx.beginPath();
    
    ctx.lineWidth = option.width;
    ctx.strokeStyle = option.color; 
        
    if (scale.minX < 0)
    {
        ctx.moveTo( scale.X(0),scale.Y(scale.minY));  
        ctx.lineTo( scale.X(0),scale.Y(scale.maxY));
    }
    else
    {
        ctx.moveTo( scale.X(scale.minX),scale.Y(scale.minY));  
        ctx.lineTo( scale.X(scale.minX),scale.Y(scale.maxY));
    }
    
    if (scale.minY < 0)
    {
        ctx.moveTo( scale.X(scale.minX),  scale.Y(0));  
        ctx.lineTo( scale.X(scale.maxX),  scale.Y(0))
    }
    else
    {
        ctx.moveTo( scale.X(scale.minX),scale.Y(scale.minY));  
        ctx.lineTo( scale.X(scale.maxX),scale.Y(scale.minY));
    }
    ctx.stroke();
}

var linesoption = {
    margin : {
        top : 40,
        bot : 40,
        right : 40,
        left : 80
    },
    width: 1,
    axes : true,
    axesoption :  axesoption,
    grid : true,
    gridoption: gridoption
};

function drawLines(data, id, color, option = linesoption) 
{
    var canvas = document.getElementById(id);
    
    if (null == canvas || !canvas.getContext) 
        return;
        
    var ctx = canvas.getContext("2d");
    
    var s = new scale(data, canvas.width, canvas.height, option.margin, option.gridoption.scaleX,option.gridoption.scaleY);
    
    if (option.grid == true)
        drawGrid(s, ctx, option.gridoption);
   
    if (option.axes == true)
        drawAxes(s, ctx, option.axesoption);
    
    for (var k = 0; k < data.length;k++)
    {
        ctx.beginPath();
        
        ctx.lineWidth = option.width;
        
        ctx.strokeStyle = color[k % color.length];
     
        ctx.moveTo(s.X(data[k][0][0])  , s.Y(data[k][0][1]));
        
        for (var i = 1; i < data[k].length;i++) 
        {
            ctx.lineTo(s.X(data[k][i][0]), s.Y(data[k][i][1]));
        }
        
        ctx.stroke();
    }
}

var histogramsoption = {
    margin : {
        top : 40,
        bot : 40,
        right : 40,
        left : 80
    },
    width: 1,
    axes : true,
    axesoption :  axesoption,
    fillRect : true,
    grid : true,
    gridoption: gridoption
};

function drawHistograms(data, id, color = color, option = histogramsoption) 
{
    var canvas = document.getElementById(id);
    if (null==canvas || !canvas.getContext) 
        return;
        
    var ctx=canvas.getContext("2d");
    var s = new scale(data, canvas.width, canvas.height, option.margin);

    if (option.grid == true)
        drawGrid(s, ctx, option.gridoption);
        
    var cumul = 0;
    
    for (var k = 0; k < data.length;k++)
    {
        var width = ( data[k][0][0] - data[k][1][0]) * ( s.gwidth / s.rangeX );
        
        ctx.beginPath();
        
        ctx.lineWidth = option.width;
        
        if (option.fillRect)
            ctx.fillStyle = color[(k) % color.length];
        else
            ctx.fillStyle = "rgba(255, 255, 255, .3)";
            
        ctx.strokeStyle = color[(k) % color.length];
        
        // we move the first column so the others column will be centered
        // since the first column had been move the last column should be cut too
        for (var i = 0, n = data[k].length; i < n;i++) 
        {
            var y = s.Y(Math.max(0, s.minY));
            var h = s.Y(data[k][i][1]) - s.Y(0);
            if (i == 0)
                ctx.rect(s.X(data[k][i][0]) - width/2, y, width/2, h);
            else if (i == n - 1)
                ctx.rect(s.X(data[k][i][0]), y, width/2, h);
            else
                ctx.rect(s.X(data[k][i][0]) - width/2, y, width , h);
        }
        
        ctx.fill();
        ctx.stroke();
    }
    
    if (option.axes == true)
        drawAxes(s, ctx, option.axesoption);
}

// Depreciated
function dataRange(data)
{
    var maxx = data[0][0];
    var maxy = data[0][1];
    
    var minx = data[0][0];
    var miny = data[0][1];
    
    for (var k = 0; k < data.length ;k++)
    {
        if (maxx < data[k][0])   maxx = data[k][0];
        if (maxy < data[k][1])   maxy = data[k][1];
        
        if (minx > data[k][0])   minx = data[k][0];
        if (miny > data[k][1])   miny = data[k][1];
    }
    
    var rr =    [  [   maxx,   minx    ],
                   [   maxy,   miny    ]
                ];
    return rr;
}

function drawLine(data, id, color, option) 
{
    var canvas = document.getElementById(id);
    
    if (null == canvas || !canvas.getContext) 
        return;
        
    var ctx = canvas.getContext("2d");
    
    var r = dataRange(data);
    
    var maxX = r[0][0];
    var maxY = r[1][0];
    
    var minX = r[0][1];
    var minY = r[1][1];
   
    var rangeX = maxX - minX;
    var rangeY = maxY - minY;
    
    function XX(x)  {   return ( x - minX) * ( ctx.canvas.width / rangeX );     }
    function YY(y)  {   return canvas.height * ( 1 - ( y - minY ) / rangeY );   }
    
    ctx.beginPath();
    
    ctx.lineWidth = 1;
    ctx.strokeStyle = "rgb(128,128,128)"; 
    
    
    if (minX < 0)
    {
        ctx.moveTo( XX(0),YY(minY));  
        ctx.lineTo( XX(0),YY(maxY));
    }
    else
    {
        ctx.moveTo( XX(minX),YY(minY));  
        ctx.lineTo( XX(minX),YY(maxY));
    }
    
    if (minY < 0)
    {
        ctx.moveTo( XX(minX),   YY(0));  
        ctx.lineTo( XX(maxX),   YY(0))
    }
    else
    {
        ctx.moveTo( XX(minX),YY(minY));  
        ctx.lineTo( XX(maxX),YY(minY));
    }
    
    ctx.stroke();
    
    ctx.beginPath();
        
    ctx.lineWidth = 2;
    
    ctx.strokeStyle = color;
 
    ctx.moveTo(XX(data[0][0])  , YY(data[0][1]));
    
    for (var i = 1; i < data.length;i++) 
    {
        ctx.lineTo(XX(data[i][0]), YY(data[i][1]));
    }
    
    ctx.stroke();
}

function drawHistogram(data, id, color, option) 
{
    var canvas = document.getElementById(id);
    if (null==canvas || !canvas.getContext) 
        return;
        
    var ctx=canvas.getContext("2d");

    var r = dataRange(data);

    var maxX = r[0][0];
    var maxY = r[1][0];

    var minX = r[0][1];
    var minY = r[1][1];

    if (minY == 1)
        minY = 0;

    var rangeX = maxX - minX;
    var rangeY = maxY - minY;

    function XX(x)  {   return ( x - minX) * ( ctx.canvas.width / rangeX );           }
    function YY(y)  {   return canvas.height * ( 1 - ( y - minY ) / rangeY );   }

    var width = ( data[0][0] - data[1][0]) * ( ctx.canvas.width / rangeX );

    ctx.strokeStyle = color;
    
    ctx.lineWidth = 2;
    ctx.fillStyle = "rgb(34, 34, 34)";
    ctx.strokeStyle = "rgb(0, 0, 0)";

    for (var i = 0; i < data.length;i++) 
    {
        ctx.rect(XX(data[i][0]), YY(data[i][1]), width , canvas.height + 10);
    }
    
    ctx.fill();
    ctx.stroke();
    
    ctx.beginPath();

    ctx.lineWidth = 1;
    ctx.strokeStyle = "rgb(128,128,128)"; 

    if (minX < 0)
    {
        ctx.moveTo( XX(0),YY(minY));  
        ctx.lineTo( XX(0),YY(maxY));
    }
    else
    {
        ctx.moveTo( XX(minX),YY(minY));  
        ctx.lineTo( XX(minX),YY(maxY));
    }
    
    if (minY < 0)
    {
        ctx.moveTo( XX(minX),   YY(0));  
        ctx.lineTo( XX(maxX),   YY(0))
    }
    else
    {
        ctx.moveTo( XX(minX),YY(minY));  
        ctx.lineTo( XX(maxX),YY(minY));
    }

    ctx.stroke();
    
    ctx.beginPath();
}


