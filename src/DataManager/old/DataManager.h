#ifndef STRAT3_DATAMANAGER_HEADER
#define STRAT3_DATAMANAGER_HEADER

#if __linux
    #include <eigen3/Eigen/Dense>
#else
    #include <Eigen/dense>
#endif

#include <string>
#include <stdio.h>
#include <fstream>
#include <unordered_map>

#include "../enum.h"

using namespace std;


//typedef std::string         Key;
//typedef std::string         FileName;
//typedef Eigen::MatrixXd     Matrix;
//typedef Eigen::VectorXd     Column;
//typedef Eigen::RowVectorXd  Row;
//typedef unsigned int        Index;

class DataQuery;
class MatrixManager;


class DataManager
{
    public:
        struct Element
        {
            public:
                Element(MatrixManager* m = 0, bool o = true):
                    m(m), ownership(o)
                {}

                MatrixManager* m;

                //! true if the matrix will be deleted by its parent.s
                bool    ownership;
        };

        MatrixManager* matrixManager(Key k);

        void addMatrixManager(Key k, MatrixManager* mm, bool own);
        void readBinary(Key k, FileName n);
        DataQuery dataQuery(int rowMin, int rowMax);

        int size();

    protected:

        std::unordered_map<Key, Element> _MatrixManager;
};

std::vector<std::string> load_date(std::string n, bool header = false);
Matrix load_date_matrix(std::string n, bool header = false);

#endif
