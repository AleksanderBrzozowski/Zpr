#include "src/GUI/mainwindow.h"
#include <TrafficControl.h>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow& w = MainWindow::getInstance();

    TrafficControl trafficControl(w);
    std::thread trafficThread(&TrafficControl::run, &trafficControl);

    w.show();

    trafficControl.setMovableAllowedToMove(false);
    trafficThread.join();

    return a.exec();
}
