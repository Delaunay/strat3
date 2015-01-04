#include <gtest/gtest.h>

#include "StrategyTest.h"
#include "../Tester.h"

#include "../Strategy/VarianceMin.h"
#include "../Report/Report.h"
#include "../Report/HTMLReport.h"
#include "../Report/TEXReport.h"

class SingleSec : public Strategy
{
    public:
        SingleSec(Key managerKey, Key matrixkey, int securitySize):
            Strategy(managerKey, matrixkey, securitySize),
            _Set(false)
        {
            _Title = "Equity";
            _Description = "Equity Portfolio";
            _Version = 1;
        }

        TransactionWeight* operator() (DataQuery* m)
        {
            if (!_Set)
            {
                _Weight.weight = Column::Zero(_Weight.weight.rows(), 1);
                _Set = true;
                _Weight.weight(0, 0) = 1;
            }

            return &(_Weight);
        }

    protected:

        bool _Set;
};


class SingleSec2 : public Strategy
{
    public:
        SingleSec2(Key managerKey, Key matrixkey, int securitySize):
            Strategy(managerKey, matrixkey, securitySize),
            _Set(false)
        {
            _Title = "Debt";
            _Description = "Debt Portfolio";
            _Version = 1;
        }

        TransactionWeight* operator() (DataQuery* m)
        {
            if (!_Set)
            {
                _Weight.weight = Column::Zero(_Weight.weight.rows(), 1);
                _Set = true;
                _Weight.weight(1, 0) = 1;
            }

            return &(_Weight);
        }

    protected:

        bool _Set;
};

// initialization
Tester        test;
DataManager   data;
MatrixManager price;

EqualWeight strat("price", "price", 2);
Portfolio   portfolio(2, 10000.0, "../gen/EqualWeighted", 0);
SingleSec   strat2("price", "price", 2);
Portfolio   portfolio2(2, 10000.0, "../gen/Equity", 0);
SingleSec2  strat3("price", "price", 2);
Portfolio   portfolio3(2, 10000.0, "../gen/Debt", 0);
VarianceMin vm("price", "price", 2);
Portfolio   vmp(2, 10000.0, "../gen/Debt", 0);

NodeTuple myStrat;
NodeTuple myStrat2;
NodeTuple myStrat3;
NodeTuple vm_nt;

TEST(Tester, setup)
{
    test.setStratWindow(21);
    price.readCSV("../data/test.csv", "price", true);
    data.addMatrixManager("price", &price, false);
    test.setDataManager(&data, "price", "price");

    myStrat.strat       = &strat;
    myStrat.portfolio   = &portfolio;
    myStrat.log         = 0;
    myStrat.market      = 0;

    myStrat2.strat       = &strat2;
    myStrat2.portfolio   = &portfolio2;
    myStrat2.log         = 0;
    myStrat2.market      = 0;

    myStrat3.strat       = &strat3;
    myStrat3.portfolio   = &portfolio3;
    myStrat3.log         = 0;
    myStrat3.market      = 0;

    vm_nt.strat       = &vm;
    vm_nt.portfolio   = &vmp;
    vm_nt.log         = 0;
    vm_nt.market      = 0;

    test.addStrategy(&myStrat2);
    test.addStrategy(&myStrat);
    test.addStrategy(&myStrat3);
    test.addStrategy(&vm_nt);
}

TEST(Tester, run)
{
    for (int i = 0, n = test.periodRunning(); i < n; i++)
    {
        test.runOneStep();
    }
}

DataAnalyser mt(&test);

TEST(Tester, GenerateData)
{
    // compute all the data
    mt.create_matrix();
}
TEST(Tester, Gnuplot_data)
{
    Matrix date = load_date_matrix("../data/date_test.csv", true);
    test.setDates(date);

    // export the data into gnuplot friendly format
    mt.gpTimeStratData();
    mt.gpDistributionData();
    mt.gpTimeSecData();
}

TEST(Tester, Gnuplot_svg_graph)
{
    // run gnuplot to generate svg graph
    mt.generate_gp(false);
}

TEST(Tester, HTMLReport)
{
    // generate the html
    HTMLReport rep("strat3_report.html", &mt);
    rep.generate();
}

TEST(Tester, Gnuplot_eps_graph)
{
    // run gnuplot to generate eps graph
    mt.generate_gp(true);
}

TEST(Tester, TEXReport)
{
    // generate the tex
    TEXReport rept("strat3_report.tex", &mt);
    rept.generate();
}

