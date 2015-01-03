#ifndef STRAT3_DATAMANAGER_HEADER
#define STRAT3_DATAMANAGER_HEADER

#include <string>

#if __linux
#include <eigen3/Eigen/Dense>
#else
#include <Eigen/dense>
#endif

#include <unordered_map>
#include <stdio.h>

#include <fstream>

#include "../enum.h"


using namespace std;

enum SaveFileOptions
{
    OneFile = 0,
    MultipleFile = 1
};
enum SaveOptions
{
    Erase = 0,
    Append = 1
};

enum FileType
{
    Binary = 0,
    CSV = 1
};

std::vector<std::string> load_date(std::string n, bool header = false);

Matrix load_date_matrix(std::string n, bool header = false);
//typedef std::string         Key;
//typedef std::string         FileName;
//typedef Eigen::MatrixXd     Matrix;
//typedef Eigen::VectorXd     Column;
//typedef Eigen::RowVectorXd  Row;
//typedef unsigned int        Index;

/*! @brief DataManagerDisk offer similar functionality than DataManager.
 *  The only difference is that no matrix is loaded in memory until the user
 * ask for it. Only parts of the matrix can be loaded if specified. This can be useful for huge dataset
 * or if RAM space is limited
*/
class DataManagerDisk
{
    public:

    protected:
};


class MatrixQuery;

/*! @brief MatrixManager manage multiples instance of Eigen Matrix.
 * Each Matrix have a given unique identifier of type Key
 * Each Matrix are loaded in memory
*/
class MatrixManager
{
    public:
        struct Element
        {
            public:
                Element(Matrix* m = 0, bool o = true):
                    m(m), ownership(o)
                {}

                Matrix* m;

                //! true if the matrix will be deleted by its parent.
                bool    ownership;
        };

        MatrixManager()
        {}

        ~MatrixManager();

        void addMatrix(Key k, Matrix* m, bool owned = true);

        Matrix* matrix(Key k);


        /*! @brief save a matrix into a file.
         *  @param k which matrix should be saved
         *  @param n name of the file
         *  @param t file type (binary or CSV), the extension is not added
         *  @param o either Erase or Append
        */
        void save(Key k, FileName n, FileType t, SaveOptions o);
        void saveAll(FileName n, FileType t, SaveOptions o);

        /*!
         * \brief load a matrix-like file in memory
         * \param n FileName
         * \param t FileType
         */
        void load           (FileName n, FileType t);
        void writeBinaryAll (FileName n, SaveOptions o);
        void writeBinary    (Key k, FileName n, SaveOptions o);
        void readBinary     (FileName n);
        void writeCSV       (Key k, FileName n, SaveOptions o);
        void writeCSVAll    (FileName n, SaveOptions o);

        /*!
         * \brief readCSV
         * \param n
         * \param key
         * \param header
         * \param colsep
         */
        void readCSV        (FileName n, Key key, bool header = false, const char* colsep = ",")
        {
            std::ifstream file(n.c_str(), std::ios::in);

            if (!file)
                    throw "File does not exist";

            std::pair<int, int> size = readSize(&file, header, colsep);

            Matrix* A = new Matrix(Matrix::Zero(size.first, size.second));
            addMatrix(key, A, true);

            std::string line;

            // suboptimal
            file.close();
            file.open(n.c_str(), std::ios::in);

//            file = file.seekg(0);

            char c;

            if (header)
                std::getline(file, line);

            for(int j = 0; j < size.first; j++)
            {
                std::getline(file, line);
                std::istringstream ss(line);

                for (int i = 0; i < size.second; i++)
                {
                    if (i < size.second - 1)
                        ss >> (*A)(j, i) >> c;
                    else
                        ss >> (*A)(j, i);
                }
            }

            file.close();
        }

        std::pair<int, int> readSize(std::ifstream* file, bool header = false, const char* colsep = ",")
        {
            std::string line;
            std::getline(*file, line);

            int col = 1;
            int row = 1  - header;

            for (auto i = 0; i < line.size(); i++)
                if (line[i] == colsep[0])
                    col++;

            while (std::getline(*file, line))
            {
                if (line.find(colsep) != 0)
                    row++;
            }

            return std::pair<int, int>(row, col);
        }

        int  size           ();
        MatrixQuery makeQuery(int min, int max);

    protected:

        std::unordered_map<Key, Element> _Matrix;
};


/*! @brief
 */
class MatrixQuery
{
    public:
        MatrixQuery(MatrixManager* dm, int rowMin, int rowMax):
            _DataManager(dm), _RowMax(rowMax), _RowMin(rowMin)
        {}

        /*!
         * \brief middleRows return a block of nb rows coming from the matrix k
         * \param k         Matrix Key
         * \param startRow
         * \param nb        Number of Row returned
         * \return          Matrix Block
         */
        Matrix middleRows(Key k, int startRow, int nb)
        {
            startRow = std::max(startRow, _RowMin);
            nb = std::min(_RowMax - startRow, nb);

            return _DataManager->matrix(k)->middleRows(startRow, nb);
        }

        int cols(Key k) {    return _DataManager->matrix(k)->cols(); }
        int size() {    return _DataManager->size();    }
        int min()   {   return _RowMin; }
        int max()   {   return _RowMax; }

    protected:
        MatrixManager* _DataManager;

        int _RowMax;
        int _RowMin;
};

class DataQuery;

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

                //! true if the matrix will be deleted by its parent.
                bool    ownership;
        };

        MatrixManager* matrixManager(Key k) {   return _MatrixManager[k].m;   }

        void addMatrixManager(Key k, MatrixManager* mm, bool own)
        {
            _MatrixManager[k] = Element(mm, own);
        }

        void readBinary(Key k, FileName n)
        {
            MatrixManager* m = new MatrixManager();
            m->readBinary(n);

            _MatrixManager[k] = Element(m, true);
        }

//        Key date(int index)
//        {
//            return _Date[index];
//        }

        //Matrix date_matrix() {  return _Date;   }
        //std::vector<std::string>& date_vector()  {  return _Date;  }

        DataQuery dataQuery(int rowMin, int rowMax);

        int size()  {   return _MatrixManager.size();   }

    protected:

        //std::vector<std::string> _Date;
        //Matrix _Date;
        std::unordered_map<Key, Element> _MatrixManager;
};

/*! @brief
 */
class DataQuery
{
    public:
        DataQuery(DataManager* dm, int rowMin, int rowMax):
            _DataManager(dm), _RowMax(rowMax), _RowMin(rowMin)
        {}

        /*!
         * \brief middleRows return a block of nb rows coming from the matrix k
         * \param k         Matrix Key
         * \param startRow
         * \param nb        Number of Row returned
         * \return          Matrix Block
         */
        Matrix middleRows(Key manager, Key matrix, int startRow, int nb)
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
        Matrix reverseMiddleRows(Key manager, Key matrix, int nb)
        {
            int startRow = std::max(_RowMax - nb - 1, _RowMin);
            return _DataManager->matrixManager(manager)
                               ->matrix(matrix)
                               ->middleRows(startRow, nb);
        }

        int size() {    return _DataManager->size();    }
        int cols(Key k, Key k2) {    return _DataManager->matrixManager(k)->matrix(k2)->cols(); }
        int min()   {   return _RowMin; }
        int max()   {   return _RowMax; }


    protected:
        DataManager* _DataManager;

        // give back date


        int _RowMax;
        int _RowMin;
};

#endif
