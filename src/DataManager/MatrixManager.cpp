#include "MatrixManager.h"
#include "MatrixQuery.h"

//#include "../Error/FileError.h"

//#include <iostream>

#include <fstream>

MatrixManager::MatrixManager()
{}

MatrixManager::~MatrixManager()
{
//    std::unordered_map<Key, Matrix>::iterator i = _matrix.begin();

//    while(i != _matrix.end())
//    {
//        if ( (*i).second.ownership == true )
//            delete (*i).second.m;

//        i++;
//    }
}

void MatrixManager::add_matrix(Key k, Matrix m)
{
    _matrix[k] = m;
}

Matrix* MatrixManager::matrix(Key k)    {   return &_matrix[k];   }


void MatrixManager::save_all(FileName n, FileType t, SaveOptions o)
{
    switch(t)
    {
        case Binary:
            write_binary_all(n, o);
            return;
        case CSV:
            write_csv_all(n, o);
            return;
        default:
            return;
    }
}

void MatrixManager::save(Key k, FileName n, FileType t, SaveOptions o)
{
    switch(t)
    {
        case Binary:
            write_binary(k, n, o);
            return;
        case CSV:
            write_csv(k, n, o);
            return;
        default:
            return;
    }
}

void MatrixManager::load(FileName n, FileType t)
{
    switch(t)
    {
        case Binary:
            read_binary(n);
            return;
        case CSV:
//            readCSV(n);
            return;
        default:
            return;
    }
}

void MatrixManager::write_binary_all(FileName n, SaveOptions o)
{}

void MatrixManager::write_binary(Key k, FileName n, SaveOptions o)
{
    // I have a problem with append
    // I need to open the file twice fseek is repporting an Error rewind() fail il I use only one file
    int  mn  [1] = { 1 };
    long size[2] = { matrix(k)->rows(), matrix(k)->cols() };
    char t   [255];
    k.copy(t, 255);
    t[k.size()] = '\0';

    // std::cout << matrix(k)->rows() << ' ' << matrix(k)->cols() << std::endl;

    // if append open the existing file
    // if openning the file fail the file doesnot exist and is created
    if (o == Append)
    {
        FILE* file2 = fopen(n.c_str(), "rb+");
        FILE* file = fopen(n.c_str(), "ab+");

        if ((file != NULL) && (file2 != NULL)) // if file2 == NULL then the file does not exist
        {
            // add Matrix' data at the end of the file
            fwrite  (t,     sizeof(char), 255,  file);  // Write Matrix' Title
            fwrite  (size,  sizeof(long),  2,    file);  // Write Matrix' Size
            fwrite  (&(*matrix(k))(0, 0), sizeof(double), size[0] * size[1], file);   // Write Matrix' data

            // increase the number of matrix by one
            int a = fread(mn, sizeof(int), 1, file2);

            if (a != 1)
                fprintf(stderr, "WriteBinary : error reading Matrix Size\n");

            mn[0]++;
            rewind(file2);
            fwrite(mn, sizeof(int), 1, file2);

            fclose(file2);
            fclose(file);
            return;
        }
    }

    // open the file or create it
    FILE* file = fopen(n.c_str(), "wb+");
    if (file == NULL)
        throw "FileError";

    fwrite  (mn,    sizeof(int),  1,    file);  // Write the number of Matrix
    fwrite  (t,     sizeof(char), 255,  file);  // Write Matrix' Title
    fwrite  (size,  sizeof(long),  2,   file);  // Write Matrix' Size
    fwrite  (&(*matrix(k))(0, 0), sizeof(double), size[0] * size[1], file);   // Write Matrix' data

    fclose(file);
}

void MatrixManager::read_binary(FileName n)
{
    FILE* file = fopen(n.c_str(), "rb");

    if (file == NULL)
        throw "FileError";

    int  mn  [1] = { 0 };
    long size[2] = { 0, 0 };

    // read the number of matrix saved inside the file
    size_t r = fread(mn, sizeof(int), 1, file);
    if (r != 1)
    {
        fclose(file);
        throw "Fucking Error";
    }

    // load each matrix
    for (int i = 0; i < mn[0]; i++)
    {
        char title[255];

        // read title and matrix size
        r = fread(title, sizeof(char), 255, file);

        if (r != 255)
        {
            fclose(file);
            throw "Fucking Error";
        }

        r = fread(size, sizeof(long), 2, file);
        if (r != 2)
        {
            fclose(file);
            throw "Fucking Error";
        }

        // BUG SOMEWHERE
        size[0] = std::max(size[0], long(1));
        size[1] = std::max(size[1], long(1));

        // allocate memory
        Matrix m = Matrix(Matrix::Zero(size[0], size[1]));
        _matrix[Key(title)] = std::move(m);

        // read data
        r = fread(&(m)(0, 0), sizeof(double), size[0] * size[1], file);

        if (r != size[0] * size[1])
        {
            fclose(file);
            throw "Fucking Error";
        }
    }

    fclose(file);
}

void MatrixManager::write_csv(Key k, FileName n, SaveOptions o)
{}

void MatrixManager::write_csv_all(FileName n, SaveOptions o)
{}

uint MatrixManager::size() { return _matrix.size(); }

MatrixQuery MatrixManager::make_query(int min, int max)
{
    return MatrixQuery(this, min, max);
}


void MatrixManager::read_csv        (FileName n, Key key, bool header, const char* colsep)
{
    std::ifstream file(n.c_str(), std::ios::in);

    if (!file)
            throw "File does not exist";

    std::pair<int, int> size = read_size(&file, header, colsep);

    Matrix A = Matrix(Matrix::Zero(size.first, size.second));
    add_matrix(key, std::move(A));

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
                ss >> (A)(j, i) >> c;
            else
                ss >> (A)(j, i);
        }
    }

    file.close();
}

std::pair<int, int> MatrixManager::read_size(std::ifstream* file, bool header, const char* colsep)
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
