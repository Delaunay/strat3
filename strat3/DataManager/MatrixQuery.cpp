
#include "MatrixQuery.h"
#include "MatrixManager.h"

MatrixQuery::MatrixQuery(MatrixManager* dm, int rowMin, int rowMax):
    _DataManager(dm), _RowMax(rowMax), _RowMin(rowMin)
{}

/*!
 * \brief middleRows return a block of nb rows coming from the matrix k
 * \param k         Matrix Key
 * \param startRow
 * \param nb        Number of Row returned
 * \return          Matrix Block
 */
Matrix MatrixQuery::middleRows(Key k, int startRow, int nb)
{
    startRow = std::max(startRow, _RowMin);
    nb = std::min(_RowMax - startRow, nb);

    return _DataManager->matrix(k)->middleRows(startRow, nb);
}

int MatrixQuery::cols(Key k) {   return _DataManager->matrix(k)->cols(); }
int MatrixQuery::size()      {   return _DataManager->size();    }
int MatrixQuery::min()       {   return _RowMin; }
int MatrixQuery::max()       {   return _RowMax; }
