#ifndef STRAT3_GUI_MAINWINDOW_HEADER
#define STRAT3_GUI_MAINWINDOW_HEADER

#include <QMainWindow>
#include <QSplashScreen>
#include <QMenuBar>
#include <QPushButton>

#include <QTableView>
#include <QListView>
#include <QTreeView>
#include <QStandardItemModel>

#include <iostream>

#include "DataManager/MatrixManager.h"
#include "Backtester/Backtester.h"
#include "DataManager/Buffer.h"

#define QNEW(type, var) type* var = new type
#define ANEW(var, type) var = new type

typedef unsigned int uint;
using strat3::Backtester;

#define WIDTHF 0.5

constexpr int screen_width()  { return 1200 * WIDTHF; }
constexpr int screen_height() { return screen_width() * 9.0 / 16.0; }

Backtester& backtest_instance();
MatrixManager& matrix_manager_instance();


class MatrixView: public QTreeView
{
public:
    MatrixView():
        size(0)
    {
        //model.setHorizontalHeaderItem(0, new QStandardItem("Matrix"));
        //model.setHorizontalHeaderLabels({"Matrix", "Matrix"});
        model.setColumnCount(2);

        setModel(&model);
        update();
    }

    void update()
    {
        if (size != matrix_manager_instance().size())
        {
            model.clear();

            QStandardItem *mname = 0,
                          *msize = 0;

            uint j = 0;

            // parent->appendRow(item);
            for(auto& i:matrix_manager_instance()._matrix)
            {
                mname = new QStandardItem(i.first.c_str());
                Matrix& m = i.second.matrix();
                msize = new QStandardItem(QString("(") + QString::fromStdString(std::to_string(m.rows())) +
                                          QString("x") + QString::fromStdString(std::to_string(m.cols())) +
                                          QString(")"));
                msize->setTextAlignment(Qt::AlignCenter);

                model.setItem(j, 0, mname);
                model.setItem(j, 1, msize);

                ++j;
            }
        }
    }

    std::vector<Matrix> matrices;
    uint size;
    QStandardItemModel model;
};

#include <QDialog>
#include <QDockWidget>


class MainWindow : public QMainWindow
{
public:
    MainWindow()
    {
        setWindowTitle("Strat3");

        QNEW(QMenuBar, menubar);

        QNEW(QMenu, file);  file->setTitle("File");
        menubar->addMenu(file);

        QAction* a = new QAction("Add Matrix", this);
        connect(a, SIGNAL(triggered()), this, SLOT(add_matrix_wizard()));

        menubar->addMenu(file);
        file->addAction(a);

//        menubar->addAction("Files");
//        menubar->addAction("Strategy");
//        menubar->addAction("");

        setMenuBar(menubar);

        QNEW(QDockWidget, dock);
        this->addDockWidget(Qt::LeftDockWidgetArea, dock);

        dock->setWidget(new MatrixView);

        setMinimumSize(minimumSizeHint());
    }

    void add_matrix_wizard()
    {
        QDialog diag(this);

        diag.show();
    }


    QSize sizeHint() const override
    {
        return QSize(screen_width(), screen_height());
    }

    QSize minimumSizeHint() const override
    {
        return QSize(screen_width()/2, screen_height()/2);
    }

    void show()
    {
        QSplashScreen splash(QPixmap("../../img/bsplash.png"));
        splash.show();

        // loading stuff
        splash.showMessage("[  0%] [                  ]", Qt::AlignCenter, Qt::white);

        splash.showMessage("[ 50%] [                  ]", Qt::AlignCenter, Qt::white);

        splash.showMessage("[100%] [                  ]", Qt::AlignCenter, Qt::white);
        // loading done
        splash.finish(this);
        return QMainWindow::show();
    }

protected:
};



#endif
