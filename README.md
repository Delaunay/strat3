
Dependencies
------------

* Eigen3    - Matrix, linear Solver - License :
* Gnuplot   -
* Bootstrap - base CSS/JavaScript   - License
* Python    -




TODO
----

* Implement a Monte Carlo Benchmark 
in order to do so we need
    * Portfolio managing n strategies at the same time
    * strategy making n different strategies at the same time
    to fully use vectorized operation and win execution time
    we also need Datalog et DataAnalyzer to be able to handle those
    finaly the benchmark should be compute on different basis
        * best Return   5% quantile | mean of 5% best 
        * best Std      5% quantile |
        * best Sharp    5% quantile |
        * best skew etc ...
        
this is made to rule out the possibility that the portfolio performance is a product
of luck and truly represent an economic reality
