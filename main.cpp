#include "src/GUI/mainwindow.h"
#include <TrafficControl.h>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow& w = MainWindow::getInstance();

    TrafficControl trafficControl;
    trafficControl.setMovableAllowedToMove(true);
    std::thread trafficThread(&TrafficControl::run, &trafficControl);

    w.setTrafficControl(std::shared_ptr<TrafficControl>(&trafficControl));
    w.show();

    trafficThread.join();

    return a.exec();
}
