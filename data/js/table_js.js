
function table_js(file_name, colname, html_id, format_func)
{

if (arguments.length == 3)
{
    format_func = function(x) { return x; };
}

    
d3.csv(file_name, function(data) {

    // the columns you'd like to display
    // var columns = ["time", "invested", "cash", "asset",	"liabilities", "equity"];
    // var colname = ["Time", "Invested", "Cash", "Asset",	"Liabilities", "Equity"];

    var table = d3.select(html_id)
        .append("table")
        .attr("id", html_id + "_table")
        .attr("class", "table table-bordered table-condensed table-hover table-responsive"),
        
        thead = table.append("thead"),
        tbody = table.append("tbody");

    // append the header row
    thead.append("tr")
        .selectAll("th")
        .data(colname) // display colname
        .enter()
        .append("th")
            .text(function(column) { return column; });

    // create a row for each object in the data
    var rows = tbody.selectAll("tr")
        .data(data)
        .enter()
        .append("tr");

    // create a cell in each row for each column
    var cells = rows.selectAll("td")
        .data(function(row) {
            return colname.map(function(column) {
                return {column: column, value: format_func(row[column])};
            });
        })
        .enter()
        .append("td")
            .text(function(d) { return d.value; });
            
    // $(html_id).DataTable();
});
}
