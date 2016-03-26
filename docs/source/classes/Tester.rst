Tester
*********

Overview
--------
Tester manage interaction between classes and data access. This is the main class to create to run a backtest
  
.. code-block:: c++

    Tester mybacktest();
    
    mybacktest.addData(&myData);
    
    mybacktest.addStrategy(&myStrategy1);
    mybacktest.addStrategy(&myStrategy2);
    
    mybacktest.run();