#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include <QtWidgets/QMainWindow>
#include "maparea.h"
#include <QtWidgets/QGridLayout>
#include <thread>
#include <QtWidgets/QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    static MainWindow& getInstance();

    ~MainWindow();

public slots:
    void setCar(int id, int x, int y);
    void setPpl(int id, int x, int y);

private:
    explicit MainWindow(QWidget *parent = 0);
    MainWindow(const MainWindow &) = delete;
    MainWindow& operator=(const MainWindow &) = delete;

    QMenu* initMenu();

    Ui::MainWindow *ui;
    MapArea *mapArea;
    QLabel *statusLabel;
};

#endif // MAINWINDOW_H
