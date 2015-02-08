#include "Predictor.h"

#include "../smath.h"
#include "../Strategy/DataStruct.h"
#include "../DataManager/DataQuery.h"

HistoricalCovariance::HistoricalCovariance(Key managerKey, Key matrixkey, unsigned int ws):
    _FeatureManagerKey(managerKey), _FeatureMatrixKey(matrixkey), window_size(ws)
{
    _Version = 1.0;
    _Description = "Computes historical covariance with a moving window (window = " +
                   std::to_string(ws) +"). if window < 0 every available observation are used";

    _Title = "Historical Covariance";
}

void HistoricalCovariance::predict(DataStruct* dq)
{
    // get data
    if (window_size < 0)
        data = dq->dataManager->getAll(_FeatureManagerKey, _FeatureMatrixKey);
    else
        data = dq->dataManager->reverseMiddleRows(_FeatureManagerKey,
                                                  _FeatureMatrixKey,
                                                   window_size + 1);
    // returns
    returns    = compute_returns(data);
    covariance = compute_covariance(returns);
}
