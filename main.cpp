#include "src/GUI/mainwindow.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow& w = MainWindow::getInstance();

    std::shared_ptr<Map> map(new Map);
    w.setMap(map);
    map->setRunningMovablePermission(true);
    w.show();

    int returningCode = a.exec();
    return returningCode;
}
