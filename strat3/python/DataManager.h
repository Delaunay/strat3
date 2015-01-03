// This file containts helper function to translate C++ function into python
#ifndef STRAT3_DATAMANAGER_PYTHON_HEADER
#define STRAT3_DATAMANAGER_PYTHON_HEADER
#include <DataManager.h>

namespace strat3{
namespace python{
namespace datamanager{

    Matrix get_matrix(MatrixManager & self, Key k)
    {
        return *self.matrix(k);
    }

    void set_matrix(MatrixManager & self, Key k, Matrix mat)
    {
        *self.matrix(k) = mat;
    }

    void add_matrix(MatrixManager& self, Key k, Matrix& x)
    {
        // false because python manage the memory
        self.addMatrix(k, &x, false);
    }


    MatrixManager get_matrix_manager(DataManager & self, Key k)
    {
        return *self.matrixManager(k);
    }

    void set_matrix_manager(DataManager & self, Key k, MatrixManager mat)
    {
        *self.matrixManager(k) = mat;
    }

    void add_matrix_manager(DataManager& self, Key k, MatrixManager& x)
    {
        // false because python manage the memory
        self.addMatrixManager(k, &x, false);
    }

}
}
}

#endif
