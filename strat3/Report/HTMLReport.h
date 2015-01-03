#ifndef STRAT3_REPORT_HTMLREPORT_HEADER
#define STRAT3_REPORT_HTMLREPORT_HEADER

#include "Report.h"


// we use single quote in HTML double quote in C++ (so we do not have to put \" )
class HTMLReport
{
public:

    HTMLReport(Key rep_filename, DataAnalyser* data):
        _Data(data)
    {
        _file.open(Key(Key("../gen/") + rep_filename).c_str(), std::ios::out);
    }

    void tableOfContents();

    // Report components
    void overview();
    void risk();
    void strategies();

    void data()
    {
        Key title("Data");
        Key graph_1("_holding_evol.svg");
        Key graph_2("_weight_target.svg");

        _file <<"<h2 id='"<< title << "'>"<< title <<"</h2>"

                    "<p class='pull-right'><button type='button' class='btn btn-default btn-sm'>Load Porfolio Values</button></p>"
                    "<h3 id='dpv'>Portfolio Values</h3>";

                // Asset = Liabilities + Equity || Graphic
                    for (int i = 0; i < _Data->size(); i++)
                    _file << "<h5>"<< _Data->strategyName(i) <<"</h5>"
                             "<div class='center-block'><embed src='graph/"<< _Data->strategyName(i)  <<"_values.svg' type='image/svg+xml'></embed></div><br>";

           _file << "<p class='pull-right'><button type='button' class='btn btn-default btn-sm'>Load Holding Log</button></p>"
                    "<h3 id='dh'>Holdings</h3>"
                        "<h4 id='dhe'>Holdings Evolution</h5>"
                        "<p class='text-justify'>Holdings percentage change</p>";

                    for (int i = 0; i < _Data->size(); i++)
                        _file << "<h5>"<< _Data->strategyName(i) <<"</h5>"
                                 "<div class='center-block'><embed src='graph/"<< _Data->strategyName(i) + graph_1 <<"' type='image/svg+xml'></embed></div><br>";

               _file << // "<h4 id='dhv'>Holdings Variation</h4>"

                    "<p class='pull-right'><button type='button' class='btn btn-default btn-sm'>Load Order Log</button></p>"
                    "<h3 id='dto'>Transaction Order</h3>"
                    "<p class='text-justify'>Units of assets bought/sold</p>";

                        for (int k = 0; k < _Data->size(); k++)
                        {
                        _file << "<h4>"<< _Data->strategyName(k) <<"</h4>"

                        "<table class='table table-bordered table-condensed table-hover table-responsive'>"
                                "<thead>"
                                    "<tr>"
                                        "<th></th>";
                                        for(int i = 0; i < _Data->security_size(); i++)
                                            _file << "<th>Sec" << std::to_string(i) << "</th>";

                           _file << "</tr>"
                                "</thead>"
                                    "<tr>"
                                        "<td>Mean</td>";
                                    for(int i = 0; i < _Data->security_size(); i++)
                                        _file << "<td>" << _Data->_HoldStat[k](DataAnalyser::Mean, i) << "</td>";

                           _file << "</tr>"
                                    "<tr>"
                                    "<td>St. Dev.</td>";
                                    for(int i = 0; i < _Data->security_size(); i++)
                                        _file << "<td>" << _Data->_HoldStat[k](DataAnalyser::SD, i) << "</td>";
                           _file << "</tr>"
                                "<tbody>"

                                "</tbody>"
                            "</table>";
                        }

                    _file <<
                    "<p class='pull-right'><button type='button' class='btn btn-default btn-sm'>Load Target Weight Log</button></p>"
                    "<h3 id='dtw'>Target Weights</h3>";

             for (int i = 0; i < _Data->size(); i++)
                 _file << "<h5>"<< _Data->strategyName(i) <<"</h5>"
                          "<div class='center-block'><embed src='graph/"<< _Data->strategyName(i) + graph_2 <<"' type='image/svg+xml'></embed></div><br>";
    }

    void performance()
    {
         _file <<"<h2 id='performance'>Performance</h2>"
                    "<h3  id='psd'>Stochastic Dominance</h3>";
    }

    // Structure
    void head(Key title = Key("Strat3_report"));
    void header();
    void foot();

    // Report Body
    void body()
    {
        tableOfContents();
        overview();
        risk();
        performance();
        transactions();
        assets();
        strategies();
        data();
        definitions();
    }

    // generate the whole thing
    void generate()
    {
        head();
        header();
        body();
        foot();

        _file.close();
    }

    void transactions()
    {
        _file <<"<h2 id='Transactions'>Transactions</h2>"
                "<div class='bs-callout bs-callout-warning'>"
                    "<h4>Section Skipped</h4>"
                    "No Market Engine was specified."
                "</div>";
    }

    void assets()
    {
        _file << "<h2 id='Assets'>Assets</h2>"
                 "<div class='bs-callout bs-callout-warning'>"
                     "<h4>Section Skipped</h4>"
                     "No Asset descriptions provided."
                 "</div>";
    }

    void definitions();

private:

    DataAnalyser* _Data;
    std::fstream _file;

};
#endif
