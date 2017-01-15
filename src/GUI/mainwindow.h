#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include <QtWidgets/QMainWindow>
#include "maparea.h"
#include <QtWidgets/QGridLayout>
#include <thread>
#include <QtWidgets/QLabel>
#include "../Map.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    static MainWindow& getInstance();

    void setMap(std::shared_ptr<Map> map);

    ~MainWindow();

    void setCar(const unsigned int id, const unsigned int x, const unsigned int y,
                const bool fast = false);
    void setPpl(const unsigned int id, const unsigned int x, const unsigned int y);
    void removeObject(const unsigned int id);
    void refresh();
    void resetLabel();

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
