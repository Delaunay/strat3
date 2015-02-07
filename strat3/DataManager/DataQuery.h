#ifndef STRAT3_DATAMANAGER_DATAQUERY_HEADER
#define STRAT3_DATAMANAGER_DATAQUERY_HEADER

#include "../enum.h"

class DataManager;

/*! @brief
 */
class DataQuery
{
    public:
        DataQuery(DataManager* dm, int rowMin, int rowMax);

        Matrix middleRows(Key manager, Key matrix, int startRow, int nb);

        Matrix reverseMiddleRows(Key manager, Key matrix, int nb);
        int size();
        int cols(Key k, Key k2);
        int min();
        int max();


    protected:
        DataManager* _DataManager;

        int _RowMax;
        int _RowMin;
};

#endif
