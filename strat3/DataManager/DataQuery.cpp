#include "DataQuery.h"
#include "DataManager.h"
#include "MatrixManager.h"

DataQuery::DataQuery(DataManager* dm, int rowMin, int rowMax):
    _DataManager(dm), _RowMax(rowMax), _RowMin(rowMin)
{}

/*!
 * \brief middleRows return a block of nb rows coming from the matrix k
 * \param k         Matrix Key
 * \param startRow
 * \param nb        Number of Row returned
 * \return          Matrix Block
 */
Matrix DataQuery::middleRows(Key manager, Key matrix, int startRow, int nb)
{
    startRow = std::max(startRow, _RowMin);
    nb = std::min(_RowMax - startRow, nb);

    return _DataManager->matrixManager(manager)
                       ->matrix(matrix)
                       ->middleRows(startRow, nb);
}

/*!
 * \brief reverseMiddleRows return nb rows from today
 * \param manager
 * \param matrix
 * \param nb
 * \return
 */
Matrix DataQuery::reverseMiddleRows(Key manager, Key matrix, int nb)
{
    int startRow = std::max(_RowMax - nb - 1, _RowMin);
    return _DataManager->matrixManager(manager)
                       ->matrix(matrix)
                       ->middleRows(startRow, nb);
}

int DataQuery::size() {    return _DataManager->size();    }
int DataQuery::cols(Key k, Key k2) {    return _DataManager->matrixManager(k)->matrix(k2)->cols(); }
int DataQuery::min()   {   return _RowMin; }
int DataQuery::max()   {   return _RowMax; }
