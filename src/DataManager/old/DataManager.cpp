#include"DataManager.h"
#include"DataQuery.h"

#include"MatrixManager.h"

/*******************************************************************************
 *
 ******************************************************************************/

MatrixManager* DataManager::matrixManager(Key k) {   return _MatrixManager[k].m;   }

void DataManager::addMatrixManager(Key k, MatrixManager* mm, bool own)
{
    _MatrixManager[k] = Element(mm, own);
}

void DataManager::readBinary(Key k, FileName n)
{
    MatrixManager* m = new MatrixManager();
    m->readBinary(n);

    _MatrixManager[k] = Element(m, true);
}

int DataManager::size()  {   return _MatrixManager.size();   }

DataQuery DataManager::dataQuery(int rowMin, int rowMax)
{
    return DataQuery(this, rowMin, rowMax);
}

/*******************************************************************************
 *
 ******************************************************************************/

std::vector<std::string> load_date(std::string n, bool header)
{
    std::ifstream file(n.c_str(), std::ios::in);
    std::vector<std::string> date;
    std::string line;

    if (header)
        std::getline(file, line);

    int i = 0;

    while (std::getline(file, line))
    {
        line.resize(10);
        date.push_back(line);
        i++;
    }

    file.close();
    return date;
}

Matrix load_date_matrix(std::string n, bool header)
{
    std::ifstream file(n.c_str(), std::ios::in);
    std::vector<double> date;
    std::string line;

    if (header)
        std::getline(file, line);

    char c = ' ';
    int i = 0;

    while (std::getline(file, line))
    {
        line.resize(10);
        std::istringstream ss(line);

        date.push_back(0);date.push_back(0);date.push_back(0);

        ss >> date[i] >> c >> date[i + 1] >> c >> date[i + 2];
        i += 3;
    }

    //Matrix m =;
    return Eigen::Map<Eigen::Matrix<double, -1, -1, Eigen::RowMajor> >(&date[0], i/3, 3);
}
