#ifndef STRAT3_DATAMANAGER_MATRIXMANAGER_HEADER
#define STRAT3_DATAMANAGER_MATRIXMANAGER_HEADER

#include <unordered_map>

#include "../enum.h"
#include "enum.h"

class MatrixQuery;

/*! @brief MatrixManager manage multiples instance of Eigen Matrix.
 * Each Matrix have a given unique identifier of type Key
 * Each Matrix are loaded in memory
*/
class BT_EXPORT MatrixManager
{
    public:
//        struct Element
//        {
//            public:
//                Element(Matrix* m = 0, bool o = true):
//                    m(m), ownership(o)
//                {}

//                Matrix* m;

//                Matrix& matrix()    {   return (*m);    }

//                //! true if the matrix will be deleted by its parent.
//                bool    ownership;
//        };

        MatrixManager();

        ~MatrixManager();

        void add_matrix(Key k, Matrix m);
        Matrix* matrix(Key k);


        /*! @brief save a matrix into a file.
         *  @param k which matrix should be saved
         *  @param n name of the file
         *  @param t file type (binary or CSV), the extension is not added
         *  @param o either Erase or Append
        */
        void save(Key k, FileName n, FileType t, SaveOptions o);
        void save_all(FileName n, FileType t, SaveOptions o);

        /*!
         * \brief load a matrix-like file in memory
         * \param n FileName
         * \param t FileType
         */
        void load            (FileName n, FileType t);
        void write_binary_all(FileName n, SaveOptions o);
        void write_binary    (Key k, FileName n, SaveOptions o);
        void read_binary     (FileName n);
        void write_csv       (Key k, FileName n, SaveOptions o);
        void write_csv_all   (FileName n, SaveOptions o);

        /*!
         * \brief readCSV
         * \param n
         * \param key
         * \param header
         * \param colsep
         */
        void                read_csv (FileName n, Key key, bool header = false, const char* colsep = ",");
        std::pair<int, int> read_size(std::ifstream* file, bool header = false, const char* colsep = ",");

        uint         size();
        MatrixQuery make_query(int min, int max);

        std::unordered_map<Key, Matrix> _matrix;
};

#include <iostream>

/*! @brief
 */
class BT_EXPORT MatrixQuery
{
    public:
        MatrixQuery(MatrixManager* dm, const int& row_min, const int& row_max):
            _manager(dm), _row_max(row_max), _row_min(row_min)
        {
            if (row_min > row_max)
            {
                _row_max = row_min;
                _row_min = row_max;
            }
        }

        Matrix middle_rows(const Key& k, uint startRow, uint nb){
            startRow = std::min(std::max(startRow, _row_min), _row_max);

            int end = startRow + nb;

            if (end > _row_max)
                nb = _row_max - startRow;

//            std::cout << "mr:" << startRow << "x" << nb << std::endl;

            return _manager->matrix(k)->middleRows(startRow, nb);
        }

        Matrix bottom_rows(const Key& k, uint nb){

            int startRow = std::max(_row_max - nb, (uint) 0);

//            std::cout << "bt:" << startRow << "x" << nb << std::endl;

            return _manager->matrix(k)->middleRows(startRow, nb);
        }

        const uint cols(const Key& k) {   return _manager->matrix(k)->cols(); }
        const uint size()             {   return _manager->size();    }

        inline const uint& min()       {   return _row_min; }
        inline const uint& max()       {   return _row_max; }

        inline const int min_int()       {   return _row_min; }
        inline const int max_int()       {   return _row_max; }

    protected:
        MatrixManager* _manager;

        uint _row_max;
        uint _row_min;
};

#endif
