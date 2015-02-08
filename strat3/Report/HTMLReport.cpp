#include "HTMLReport.h"

void HTMLReport::tableOfContents()
{
    _file <<
    "<div id='table_of_contents' class='well'>"
    "<h1>EW.V0R1F2</h1>"
        "<h2>Table of Contents</h2>"
            "<ol>"
                "<li><a href='#Overview'>Overview</a></li>"
                    "<ol>"
                        "<li><a href='#Holding Period Return'>Holding Period Return</a></li>"
                        "<li><a href='#Statistics'>Statistics</a></li>"
                    "</ol>"

                "<li><a href='#Risk'>Risk</a></li>"
                    "<ol>"
                        "<li><a href='#prd'>Periodict Return</a></li>"
                        "<li><a href='#pve'>Volatility Evolution</a></li>"
                        "<li><a href='#pdd'>Drawdown</a></li>"
                        "<li><a href='#density'>Density</a></li>"
                        "<li><a href='#pld'>Loss Distribution</a></li>"
                        "<li><a href='#pgd'>Gain Distribution</a></li>"
                    "</ol>"

                "<li><a href='#Performance'>Performance</a></li>"
                     "<ol>"
                        "<li><a href='#psd'>Stochastic Dominance</a></li>"
                     "</ol>"

                "<li><a href='#Transactions'>Transactions</a></li>"
                "<li><a href='#Assets'>Assets</a></li>"
                "<li><a href='#Strategies'>Strategies</a></li>"
                    //"<ol>"
                    //    "<li><a href='#Descriptions'>Descriptions</a></li>"
                    //"</ol>"
                "<li><a href='#Data'>Data</a></li>"
                    "<ol>"
                        "<li><a href='#dpv'>Portfolio Values</a></li>"
                        "<li><a href='#dh'>Holdings</a></li>"
                             //"<ol>"
                                //"<li><a href='#dhe'>Holdings Evolution</a></li>"
                                //"<li><a href='#dhv'>Holdings Variation</a></li>"
                             //"</ol>"
                        "<li><a href='#dto'>Transaction Order</a></li>"
                        "<li><a href='#dtw'>Target Weight</a></li>"
                    "</ol>"

                "<li><a href='#Definitions'>Definitions</a></li>"
                "<li><a href='#Disclaimer'>Disclaimer</a></li>"
            "</ol>"
    "</div>";
}

void HTMLReport::head(Key title)
{
    _file <<
"<html lang='en'>"
"<head>"
    "<meta charset='utf-8'>"
        "<link href='../gen/css/bootstrap.min.css' rel='stylesheet' type='text/css'>"
        "<link href='../data/css/style.css' rel='stylesheet' type='text/css'>"
        "<script type='text/javascript' src='MathJax/MathJax.js?config=TeX-AMS-MML_HTMLorMML-full'></script>"
        "<title>"<< title <<"</title>"
"</head>"
"<body>";
}

void HTMLReport::header()
{
    time_t t = time(0);
    _file <<  "<p id='time' class='pull-right'> Generated on : "<< ctime(&t) << "</p>"
              "<br>";
}

void HTMLReport::foot()
{
    time_t t = time(0);
    _file <<
    "<h2 id='Disclaimer'>Disclaimer</h2>"
        "<p class='text-justify'>"
        "THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS \"AS IS\" "
        "AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE "
        "IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE "
        "ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE "
        "LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR "
        "CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF "
        "SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS "
        "INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN "
        "CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) "
        "ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE "
        "POSSIBILITY OF SUCH DAMAGE."
        "</p>"

    "<footer>"
        "<p id='bottom' class='pull-right'> Generated on : "<< ctime(&t) <<"</p>"
        "<p>&copy; Pierre Delaunay</p>"
    "</footer>"
    "</body>"
"</html>";
}


void HTMLReport::overview()
{
    Key title("Overview");
    Key graph("holding_ret.svg");
    int m = _Data->size();

    _file <<
    "<h2 id='"<< title << "'>"<< title << "</h2>"
        "<h3 id='Holding Period Return'>Holding Period Return</h3>"
        "<div class='center-block'><embed src='graph/"<< graph <<"' type='image/svg+xml'></embed></div><br>"

        "<h3 id='Statistics'>Statistics</h3>"

        "<table class='table table-bordered table-condensed table-hover table-responsive'>"
            "<thead>"
                "<th> Strategies </th>"
                "<th>Mean</th>"
                "<th>St. Dev.</th>"
                "<th>Sharp</th>"
                "<th>Skew</th>"
                "<th>Kurtosis</th>"
                "<th>Positive</th>"
                "<th>Negative</th>"
            "</thead>"
            "<tbody>";


        for (int i = 0; i < m; i++)
        {
            _file <<"<tr>"
                        "<td>" << _Data->strategyName(i)                                                                    << "</td>"
                        "<td>" << format_double(_Data->_StatisticPoint(DataAnalyser::Mean,     i) * 250.0 * 100.0, 2)       << "</td>"
                        "<td>" << format_double(_Data->_StatisticPoint(DataAnalyser::SD,       i) * sqrt(250.0) * 100.0, 2) << "</td>"
                        "<td>" << format_double(_Data->_StatisticPoint(DataAnalyser::Mean,     i) * 250.0 /
                                               (_Data->_StatisticPoint(DataAnalyser::SD,       i) * sqrt(250.0)), 4)        << "</td>"
                        "<td>" << format_double(_Data->_StatisticPoint(DataAnalyser::Skew,     i), 4)                       << "</td>"
                        "<td>" << format_double(_Data->_StatisticPoint(DataAnalyser::Kurtosis, i), 2)                       << "</td>"
                        "<td>" <<               _Data->_StatisticPoint(DataAnalyser::Positive, i)                           << "</td>"
                        "<td>" <<               _Data->_StatisticPoint(DataAnalyser::Negative, i)                           << "</td>"
                    "</tr>";
        }

   _file << "</tbody>"
        "</table>"
        "* p * 100.0 * 250.0 <br>"
        "** p * 100.0 * sqrt(250.0)"
        ;
}

void HTMLReport::risk()
{
    Key title("Risk");
    Key graph_1("daily_ret.svg");
    Key graph_2("volatility_ret.svg");
    Key graph_3("drawdown_ret.svg");
    Key graph_4("distri_ret.svg");
    Key graph_5("loss_distri_ret.svg");
    Key graph_6("gain_distri_ret.svg");

    // lack Value at risk

    double n = _Data->obs();
    _file <<
    "<h2 id='"<< title << "'>"<< title << "</h2>"

        "<h3 id='prd'>Periodic Return</h3>"
        "<div class='center-block'><embed src='graph/"<< graph_1 <<"' type='image/svg+xml'></embed></div><br>"

        "<h3 id='pve'>Volatility</h3>"
        "<div class='center-block'><embed src='graph/"<< graph_2 <<"' type='image/svg+xml'></embed></div><br>"
             "<table class='table table-bordered table-condensed table-hover table-responsive'>"
             "<thead>"
                 "<tr>"
                     "<th></th>"
                     "<th>Mean</th>"
                     "<th>St Dev.</th>"
                     "<th>Count</th>"
                 "</tr>"
             "</thead>"
                 "<tbody>";
                     for(int i = 0; i < _Data->size(); i++)
                         _file << "<tr>"
                                      "<td>" << _Data->strategyName(i) << "</td>"
                                      "<td>" << trunc(_Data->_MovingSDStat(DataAnalyser::Mean, i) * 100.0 * sqrt(250.0), 2)<< "</td>"
                                      "<td>" << trunc(_Data->_MovingSDStat(DataAnalyser::SD, i) * 100.0 * sqrt(250.0), 2)  << "</td>"
                                      "<td>" << _Data->_MovingSDStat(DataAnalyser::Positive, i)<< "</td>"
                                  "</tr>";
            _file << "<tr>"
                 "</tbody>"
             "</table>"

        "<h3 id='pdd'>Drawdown</h3>"
        "<div class='center-block'><embed src='graph/"<< graph_3 <<"' type='image/svg+xml'></embed></div><br>"

        "<h3 id='density'>Density</h3>"
        "<div class='center-block'><embed src='graph/"<< graph_4 <<"' type='image/svg+xml'></embed></div><br>"

        // break down loss / gain
        "<div class='row'>"
             "<div class='col-md-6'>"
                "<div class='center-block'><embed src='graph/"<< graph_5 <<"' type='image/svg+xml'></embed></div><br>"

                "<table class='table table-bordered table-condensed table-hover table-responsive'>"
                "<thead>"
                    "<tr>"
                        "<th></th>"
                        "<th>Mean</th>"
                        "<th>St Dev.</th>"
                        "<th>Count (%)</th>"
                    "</tr>"
                "</thead>"
                    "<tbody>";
                        for(int i = 0; i < _Data->size(); i++)
                            _file << "<tr>"
                                         "<td>" << _Data->strategyName(i) << "</td>"
                                         "<td>" << trunc(_Data->_StatisticPoint(DataAnalyser::MeanNegative, i) * 100.0 * 250.0, 2)<< "</td>"
                                         "<td>" << trunc(_Data->_StatisticPoint(DataAnalyser::SDNegative, i) * 100.0 * sqrt(250.0), 2) << "</td>"
                                         "<td>" << trunc(double(_Data->_StatisticPoint(DataAnalyser::Negative, i) * 100.0) / n, 2)<< "</td>"
                                     "</tr>";
               _file << "<tr>"
                    "</tbody>"
                "</table>"

             "</div>"
             "<div class='col-md-6'>"
                "<div class='center-block'><embed src='graph/"<< graph_6 <<"' type='image/svg+xml'></embed></div><br>"
                    "<table class='table table-bordered table-condensed table-hover table-responsive'>"
                        "<thead>"
                            "<tr>"
                                "<th></th>"
                                "<th>Mean</th>"
                                "<th>St Dev.</th>"
                                "<th>Count (%)</th>"
                            "</tr>"
                        "</thead>"
                        "<tbody>";
                            for(int i = 0; i < _Data->size(); i++)
                                _file << "<tr>"
                                             "<td>" << _Data->strategyName(i) << "</td>"
                                             "<td>" << trunc(_Data->_StatisticPoint(DataAnalyser::MeanPositive, i) * 100.0 * 250.0, 2)<< "</td>"
                                             "<td>" << trunc(_Data->_StatisticPoint(DataAnalyser::SDPositive, i) * 100.0 * sqrt(250.0), 2)<< "</td>"
                                             "<td>" << trunc(double(_Data->_StatisticPoint(DataAnalyser::Positive, i) * 100.0) / n, 2)<< "</td>"
                                         "</tr>";
                   _file << "<tr>"
                        "</tbody>"
                    "</table>"

             "</div>"
        "</div>"
        "<p>* 0 excluded</p>";
}

void HTMLReport::definitions()
{
    _file <<
     "<h2 id='Definitions'>Definitions</h2>"
         "<table class='table table-bordered table-condensed table-hover table-responsive'>"
             "<thead>"
                 "<tr>"
                     "<th>Name</th><th>Formula</th><th>Description</th>"
                 "</tr>"
             "</thead>"
             "<tbody>"
                 "<tr>"
                     "<td>Mean</td>"
                     "<td>\\( \\bar{x} = \\frac{1}{n} \\sum_{i = 0}^{n}  x_i \\)</td>"
                     "<td>"
                         "Average"
                     "</td>"
                 "</tr>"
                 "<tr>"
                     "<td>Standard Deviation</td>"
                     "<td>\\( \\sigma = \\sqrt{\\frac{1}{n} \\sum_{i = 0}^{n}  (x_i - \\bar{x})^2} \\)</td>"
                     "<td>"
                         "Average deviation from the mean (Volatility)."
                     "</td>"
                 "</tr>"
                 "<tr>"
                     "<td>Skew</td>"
                     "<td>\\( S = \\frac{1}{n\\sigma^3} \\sum_{i = 0}^{n} ( x_i - \\bar{x})^3 \\)</td>"
                     "<td>"
                         "Symmetry <br>"
                         "S < 0: Average < Median < Mode <br>"
                         "S = 0: Average = Median = Mode <br>"
                         "S > 0: Average > Median > Mode <br>"
                     "</td>"
                 "</tr>"
                 "<tr>"
                     "<td>Kurtosis</td>"
                     "<td>\\( K = \\frac{1}{n\\sigma^4} \\sum_{i = 0}^{n} ( x_i - \\bar{x})^4 \\)</td>"
                     "<td>"
                         "Fat tail. The normal distribution has a Kurtosis of 3"
                     "</td>"
                 "</tr>"
                 "<tr>"
                     "<td>Drawdown</td>"
                     "<td>\\( Max\\Bigg(\\ln\\bigg(\\frac{V_0}{V_0}\\bigg), ..., \\ln\\bigg(\\frac{V_{t - 1}}{V_0}\\bigg)\\Bigg) - \\ln\\bigg(\\frac{V_t}{V_0}\\bigg) \\)</td>"
                     "<td>"
                         "Show something interesting I am sure"
                     "</td>"
                 "</tr>"
             "</tbody>"
         "</table>";
}

void HTMLReport::strategies()
{
    _file << "<h2 id='Strategies'>Strategies</h2>"
                "<table class='table table-bordered table-condensed table-hover table-responsive'>"
                    "<thead>"
                        "<tr>"
                            "<th></th>";
                            for(int i = 0; i < _Data->size(); i++)
                                _file << "<th>" << _Data->strategyName(i) << "</th>";
               _file << "</tr>"
                    "</thead>"
                    "<tbody>"
                        "<tr>"
                            "<td>Description</td>";
                        for(int i = 0; i < _Data->size(); i++)
                            _file << "<td>" << _Data->_Data->getStrategy(i)->description() << "</td>";

               _file << "</tr>"
                        "<tr>"
                            "<td>frequency</td>";
                        for(int i = 0; i < _Data->size(); i++)
                            _file << "<td>" << _Data->_Data->getStrategy(i)->frequency() << "p</td>";

               _file << "</tr>"
                        "<tr>"
                            "<td>Version</td>";
                        for(int i = 0; i < _Data->size(); i++)
                            _file << "<td>" << _Data->_Data->getStrategy(i)->version() << "v</td>";

               _file << "</tr>"
                        "<tr>"
                            "<td>Rebalanced</td>";
                        for(int i = 0; i < _Data->size(); i++)
                            _file << "<td>" << get_bool_as_string(_Data->_Data->getStrategy(i)->rebalanced()) << "</td>";

               _file << "</tr>"

                    "</tbody>"
                "</table>";
}

