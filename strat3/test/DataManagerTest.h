#include "../DataManager/all.h"
#include <unordered_map>

#include <gtest/gtest.h>
TEST(DataManager, Operator)
{
    MatrixManager A;
    MatrixManager C;

    Matrix B = Matrix::Random(100, 10);
    Matrix D = Matrix::Random(10, 100);

    A.addMatrix("bar", &B, false);
    A.addMatrix("foo", &D, false);

    A.save("bar", "pasta.file", Binary, Erase);
    A.save("foo", "pasta.file", Binary, Append);

    C.load("pasta.file", Binary);

    EXPECT_LT((*A.matrix("bar") - *C.matrix("bar")).sum(), 1e-10);
}

TEST(DataQuery, Operator)
{
    MatrixManager A;
    MatrixManager C;

    Matrix B = Matrix::Random(100, 10);
    Matrix D = Matrix::Random(100, 100);

    DataManager DM;
    DM.addMatrixManager("first", &A, false);
    DM.addMatrixManager("second", &C, false);

    A.addMatrix("bar", &B, false);
    A.addMatrix("foo", &D, false);

    C.addMatrix("bar", &B, false);
    C.addMatrix("foo", &D, false);

    DataQuery DQ = DM.dataQuery(0, 50);

    Matrix blockB = DQ.middleRows("first", "bar", 0, 50);
    Matrix blockD = DQ.middleRows("first", "foo", 0, 50);

    EXPECT_EQ(blockB.rows(), 50);
    EXPECT_EQ(blockD.rows(), 50);

    EXPECT_EQ(blockB.cols(), 10);
    EXPECT_EQ(blockD.cols(), 100);

    // check lower limit is working
    blockB = DQ.middleRows("first", "bar", 0, 25);
    blockD = DQ.middleRows("first", "foo", 0, 25);

    EXPECT_EQ(blockB.rows(), 25);
    EXPECT_EQ(blockD.rows(), 25);

    EXPECT_EQ(blockB.cols(), 10);
    EXPECT_EQ(blockD.cols(), 100);

    // check upper limit is working
    blockB = DQ.middleRows("first", "bar", 0, 125);
    blockD = DQ.middleRows("first", "foo", 0, 125);

    EXPECT_EQ(blockB.rows(), 50);
    EXPECT_EQ(blockD.rows(), 50);

    EXPECT_EQ(blockB.cols(), 10);
    EXPECT_EQ(blockD.cols(), 100);
}

TEST(MatrixManager, LoadCSV)
{
    MatrixManager mm;

    mm.readCSV("../data/test.csv", "price");

//    std::cout << *mm.matrix("price") << std::endl;
}

TEST(MatrixManager, LoadBIN)
{
    MatrixManager mm;

    mm.readBinary("../data/test.bin");

//    std::cout << *mm.matrix("price") << std::endl;
}




