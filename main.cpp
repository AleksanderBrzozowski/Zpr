#include "src/GUI/mainwindow.h"
#include <TrafficControl.h>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow& w = MainWindow::getInstance();

    TrafficControl trafficControl;
    w.setTrafficControl(std::shared_ptr<TrafficControl>(&trafficControl));
    trafficControl.setMovableAllowedToMove(true);
    w.show();

    int returningCode = a.exec();
    trafficControl.setMovableAllowedToMove(false);
    return returningCode;
}
