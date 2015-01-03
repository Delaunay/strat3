
var w = window,
    d = document,
    e = d.documentElement,
    g = d.getElementsByTagName('body')[0],
    wi = w.innerWidth || e.clientWidth || g.clientWidth,
    he = w.innerHeight|| e.clientHeight|| g.clientHeight;

var internal_option = {
    xlabel: "",
    ylabel: "",
    margin: {
        top: 20,
        right: 20,
        bottom: 30,
        left: 50
    },
    width: wi - 255,
    height: he/3,
};

function Chart(id, option)
{
    if (arguments.length == 1)
    {
        this.option = internal_option;
    }
    else
    {
        this.option = option;
    }
    
    //this.x = d3.scale.linear()
    //   .range([0, this.option.width]);
        
    //this.y = d3.scale.linear()
    //    .range([this.option.height, 0]);
        
    x = d3.scale.linear()
        .range([0, this.option.width]);
        
    y = d3.scale.linear()
        .range([this.option.height, 0]);
        
    this.setDomainX = function(a)
    {
        x.domain(a);
        this.drawAxis();
        return this;
    }
    
    this.setDomainY = function(a)
    {
        y.domain(a);
        this.drawAxis();
        return this;
    }

    this.xAxis = d3.svg.axis()
        .scale(/*this.*/x)
        .orient("bottom");
        
    this.yAxis = d3.svg.axis()
        .scale(/*this.*/y)
        .orient("left");

    this.container = d3.select(id);
    this.svg = this.container.append("svg")
        .attr("width", this.option.width + this.option.margin.left + this.option.margin.right)
        .attr("height", this.option.height + this.option.margin.top + this.option.margin.bottom)
        .append("g")
        .attr("transform", "translate(" + this.option.margin.left + "," + this.option.margin.top + ")");

    getX = function(d) 
    { 
        return d[0]; 
    };
    getY = function(d) 
    { 
        return d[1]; 
    };
    
    this.setDomain = function(data)
    {
        x.domain(d3.extent(data, getX));
        y.domain(d3.extent(data, getY));
        this.drawAxis();
    }
    
    this.setXGetFunctor = function(a)
    {
        getX = a;
        return this;
    }
    
    this.setYGetFunctor = function(a)
    {
        getY = a;
        return this;
    }
    
    this.cordX = function(d) 
    { 
        return x(getX(d)); 
    };
    this.cordY = function(d) 
    { 
        return y(getY(d)); 
    };
 
    this.draw = function(data, name, style){
        line = d3.svg.line()
            .x(this.cordX)
            .y(this.cordY);

        this.svg.append("path")
            .datum(data)
            .attr("class", name)
            .attr("d", line);

        return this;
    };
    
    this.drawAxis = function ()
    {
       this.svg.selectAll("g").remove();
       
       this.svg.append("g")
        .attr("class", "x axis")
        .attr("transform", "translate(0," + this.option.height + ")")
        .call(this.xAxis)
      .append("text")
        .attr("x", this.option.width)
        .attr("y", - 10)
        .attr("dx", ".71em")
        .style("text-anchor", "end")
        .text(this.option.xlabel);

        this.svg.append("g")
            .attr("class", "y axis")
            .call(this.yAxis)
          .append("text")
            .attr("transform", "rotate(-90)")
            .attr("y", 6)
            .attr("dy", ".71em")
            .style("text-anchor", "end")
            .text(this.option.ylabel);
            
        return this;
    };
    //this.drawAxis();
    
    this.bindDraw =  function(name, style){
        return function(data) {
            return this.draw(data, name, style);
        }
    };
    

    
    return this;
}