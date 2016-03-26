template<typename T>
struct Points
{
public:
    
    Points(T x, T y):
        x(x), y(y)
    {}

    T x;
    T y;
};


//! read the size (number of row and number of column) of a CSV file 
Points<int> read_csv_size(std::ifstream* file, bool header = false, const char* colsep = ",")
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

    return Points<int>(row, col);
}

//! import a CSV file containning numbers into a Eigen::Matrix
template<typename T>
Eigen<Matrix, T, -1, -1> read_csv(FileName n, bool header = false, const char* colsep = ",")
{
    std::ifstream file(n.c_str(), std::ios::in);

    if (!file)
        return Eigen<Matrix, T, -1, -1> ()

    Points<int> size = readSize(&file, header, colsep);

    Eigen<Matrix, T, -1, -1>  A = Eigen<Matrix, T, -1, -1::Zero(size.x, size.y);

    std::string line;

    // suboptimal
    file.close();
    file.open(n.c_str(), std::ios::in);
    // file = file.seekg(0);

    char c;

    if (header)
        std::getline(file, line);

    for(int j = 0; j < size.x; j++)
    {
        std::getline(file, line);
        std::istringstream ss(line);

        for (int i = 0; i < size.y; i++)
        {
            if (i < size.y - 1)
                ss >> A(j, i) >> c;
            else
                ss >> A(j, i);
        }
    }

    file.close();
    return A;
}
