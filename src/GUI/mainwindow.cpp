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
    mapArea = new MapArea(this);
    setCentralWidget(mapArea);

    statusLabel = new QLabel("Current option: Create road", this);
    ui->menuBar->addMenu(initMenu());
    ui->statusBar->addWidget(statusLabel);

}

QMenu* MainWindow::initMenu() {
    QMenu *toolsMenu = new QMenu("Tools", this);

    QAction *toggleGrid = new QAction("Toggle grid", toolsMenu);
    connect(toggleGrid, &QAction::triggered, mapArea, &MapArea::toggleGrid);
    toolsMenu->addAction(toggleGrid);

    QAction *createRoad = new QAction("Create road", toolsMenu);
    connect(createRoad, &QAction::triggered, [=]() {mapArea->setCurOption(MapArea::optionSetRoad);
                                                         statusLabel->setText("Current option: Create road");});
    toolsMenu->addAction(createRoad);

    QAction *spawnCar = new QAction("Spawn car", toolsMenu);
    connect(spawnCar, &QAction::triggered, [=]() {mapArea->setCurOption(MapArea::optionSetCar);
                                                        statusLabel->setText("Current option: Spawn Car");});
    toolsMenu->addAction(spawnCar);

    return toolsMenu;
}

MainWindow::~MainWindow() {

}


void MainWindow::setCar(int id, int x, int y) {
    mapArea->setCar(id, x, y);
}

void MainWindow::setPpl(int id, int x, int y) {
    mapArea->setPpl(id, x, y);
}


