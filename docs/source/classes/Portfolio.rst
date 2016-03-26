Portfolio
*********

Overview
--------
A Portfolio is a set of multiple securities. Its goal is to manage Strategy's holding by reconciliating the target holding send by :doc:`Strategy` and the actual holding. It is the portfolio that workout the number of share to order if any. 

Feature
-------
  - Logging :
      
    - Targets holding
    - Actual holding
    - Portfolio Value
        
  - Send transactions and process results
  
Target Setting
--------------

The portfolio currently support 4 types of target setting : 
  - Total Percentage
  - Differential Percentage
  - Total Share
  - Differential Share

Actual Holdings :
  - SPY : 0.20
  - XBB : 0.80

Total Percentage
................

Targets :
  - SPY : 0.25
  - XBB : 0.75

.. code-block:: python

  spy_buy  = (0.25 - 0.20) * portfolio_value / spy_price
  xbb_sell = (0.75 - 0.80) * portfolio_value / xbb_price

Differential Percentage
.......................

Targets :
  - SPY : 0.02
  - XBB : -0.02

.. code-block:: python

  spy_buy  = 0.02 * portfolio_value / spy_price
  xbb_sell = - 0.02 * portfolio_value / xbb_price

Total Share
...........

Targets :
  - SPY : 100
  - XBB : 500

.. code-block:: python

  spy_buy  = 100 - 0.20 * portfolio_value / spy_price
  xbb_sell = 500 - 0.75 * portfolio_value / xbb_price

Differential Share
..................

Targets :
    - SPY : 5
    - XBB : -5

.. code-block:: python

  spy_buy  = 5
  xbb_sell = -5

.. seealso:: the mean of communication between :doc:`Strategy` and :doc:`Portfolio`:: :doc:`TransactionMatrix`
.. seealso:: the mean of communication between :doc:`Portfolio` and :doc:`MarketEngine`:: :doc:`Transaction`
