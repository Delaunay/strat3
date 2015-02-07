#ifndef STRAT3_DATAMANAGER_MATRIXQUERY_HEADER
#define STRAT3_DATAMANAGER_MATRIXQUERY_HEADER

#include "../enum.h"

class MatrixManager;

/*! @brief
 */
class MatrixQuery
{
    public:
        MatrixQuery(MatrixManager* dm, int rowMin, int rowMax);

        Matrix middleRows(Key k, int startRow, int nb);

        int cols(Key k);
        int size();
        int min();
        int max();

    protected:
        MatrixManager* _DataManager;

        int _RowMax;
        int _RowMin;
};


#endif
