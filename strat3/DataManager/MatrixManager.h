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

        MatrixManager();

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
        void                readCSV (FileName n, Key key, bool header = false, const char* colsep = ",");
        std::pair<int, int> readSize(std::ifstream* file, bool header = false, const char* colsep = ",");

        int         size();
        MatrixQuery makeQuery(int min, int max);

    protected:

        std::unordered_map<Key, Element> _Matrix;
};

#endif
