#include "src/GUI/mainwindow.h"
#include <TrafficControl.h>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow& w = MainWindow::getInstance();

    CrossFactory* crossFactory = new CrossFactory();
    TrafficControl trafficControl(crossFactory, crossFactory->getCrosses());
    w.setTrafficControl(std::shared_ptr<TrafficControl>(&trafficControl));
    trafficControl.setMovableAllowedToMove(true);
    w.show();

    int returningCode = a.exec();
    trafficControl.setMovableAllowedToMove(false);
    delete crossFactory;
    return returningCode;
}
