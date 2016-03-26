
#include <QApplication>

#include "DataManager/Buffer.h"
#include "MainWindow.h"


int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

//    MatrixView w;

//    CSVReader csv_dat("../../data/data.csv");
//    Matrix m = csv_dat.get_eigen3<MatrixRowMajor>();

//    // w.add_matrix("price", "../../data/data.csv");

//    matrix_manager_instance().add_matrix("price1", &m, false);
//    matrix_manager_instance().add_matrix("price2", &m, false);
//    matrix_manager_instance().add_matrix("price3", &m, false);
//    matrix_manager_instance().add_matrix("price4", &m, false);

//    w.update();

    MainWindow w;

//    QPushButton w;

//    w.setIcon(QIcon(QPixmap("../../img/bsplash.png")));
//    w.setIconSize(QSize(464, 544));

//    w.resize(100, 100);

    w.show();

    return app.exec();
}
