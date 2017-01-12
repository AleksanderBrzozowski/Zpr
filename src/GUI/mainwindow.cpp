#include "mainwindow.h"

MainWindow& MainWindow::getInstance() {
    static MainWindow instance;
    return instance;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setMaximumHeight(1080);
    setMaximumWidth(1920);
    mapArea = new MapArea(this);
    setCentralWidget(mapArea);

    statusLabel = new QLabel("Current option: Create road", this);
    ui->menuBar->addMenu(initMenu());
    ui->statusBar->addWidget(statusLabel);

    resetLabel();
}

QMenu* MainWindow::initMenu() {
    QMenu *toolsMenu = new QMenu("Tools", this);

    QAction *toggleGrid = new QAction("Toggle grid", toolsMenu);
    connect(toggleGrid, &QAction::triggered, mapArea, &MapArea::toggleGrid);
    toolsMenu->addAction(toggleGrid);

    QAction *createRoad = new QAction("Create road", toolsMenu);
    connect(createRoad,
            &QAction::triggered, [=]() {mapArea->setCurrentOption(EventInterpreter::Option::setRoad);
                                        statusLabel->setText("Current option: Create road");}
            );
    toolsMenu->addAction(createRoad);

    QAction *spawnCar = new QAction("Spawn car", toolsMenu);
    connect(spawnCar,
            &QAction::triggered, [=]() {mapArea->setCurrentOption(EventInterpreter::Option::setCar);
                                        statusLabel->setText("Current option: Spawn Car");}
            );
    toolsMenu->addAction(spawnCar);
    QAction *spawnFastCar = new QAction("Spawn fast car", toolsMenu);
    connect(spawnFastCar,
            &QAction::triggered, [=]() {mapArea->setCurrentOption(EventInterpreter::Option::setFastCar);
                                        statusLabel->setText("Current option: Spawn fast Car");}
            );
    toolsMenu->addAction(spawnFastCar);
    QAction *setBuilding = new QAction("Set building", toolsMenu);
    connect(setBuilding, &QAction::triggered, [=]() {mapArea->setCurrentOption(EventInterpreter::Option::setBuilding);
                                                     statusLabel->setText("Current option: Set building");}
            );
    toolsMenu->addAction(setBuilding);
    QAction *setCamera = new QAction("Set camera", toolsMenu);
    connect(setCamera, &QAction::triggered, [=]() {mapArea->setCurrentOption(EventInterpreter::Option::setCamera);
                                                   statusLabel->setText("Current option: Set camera");}
            );
    toolsMenu->addAction(setCamera);

    return toolsMenu;
}

void MainWindow::resetLabel() {
    statusLabel->setText("Current option: None. Select tool from menu.");
}

MainWindow::~MainWindow() {

}

void MainWindow::setTrafficControl(std::shared_ptr<TrafficControl> tc) {
    mapArea->setTrafficControl(tc);
}


void MainWindow::setCar(const unsigned int id, const unsigned int x, const unsigned int y,
                        const bool fast) {
    mapArea->setCar(id, x, y, fast);
}

void MainWindow::setPpl(const unsigned int id, const unsigned int x, const unsigned int y) {
    mapArea->setPpl(id, x, y);
}

void MainWindow::removeObject(const unsigned int id) {
    mapArea->removeObject(id);
}

void MainWindow::refresh() {
    mapArea->update();
}
