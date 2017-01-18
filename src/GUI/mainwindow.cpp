#include "mainwindow.h"

///\brief MainWindow::REFRESH_TIME. Time between cars movement.
const std::chrono::milliseconds MainWindow::REFRESH_TIME = std::chrono::milliseconds(50);
///\brief MainWindow::CAMERA_SCAN_FREQ. Time between camera scans
const std::chrono::seconds MainWindow::CAMERA_SCAN_FREQ = std::chrono::seconds(1);

/*!
 * \brief MainWindow::getInstance.
 * \return Returns instance of MainWindow object. Only way
 * to create that object.
 */
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
    QAction *setHuman = new QAction("Set human", toolsMenu);
    connect(setHuman, &QAction::triggered, [=]() {mapArea->setCurrentOption(EventInterpreter::Option::setHuman);
                                                  statusLabel->setText("Current option: Set camera");}
            );
    toolsMenu->addAction(setHuman);

    return toolsMenu;
}

/*!
 * \brief MainWindow::resetLabel.
 * \details Sets status label to say that no option is chosen and
 * advise to choose one.
 */
void MainWindow::resetLabel() {
    statusLabel->setText("Current option: None. Select tool from menu.");
}

MainWindow::~MainWindow() {

}

/*!
 * \brief MainWindow::setCar.
 * \param id - car ID.
 * \param x - position X.
 * \param y - position Y.
 * \param fast - flag says if car is fast car or not. false by default.
 * \details Sets car to appropriate position, and specify type of car being set.
 */
void MainWindow::setCar(const unsigned int id, const unsigned int x, const unsigned int y,
                        const bool fast) {
    mapArea->setCar(id, x, y, fast);
}

/*!
 * \brief MainWindow::setPpl.
 * \param id - person ID.
 * \param x - position X.
 * \param y - position Y.
 * \details Sets person to appropriate position, so it can be repainted where it actually is.
 */
void MainWindow::setPpl(const unsigned int id, const unsigned int x, const unsigned int y) {
    mapArea->setPpl(id, x, y);
}

/*!
 * \brief MainWindow::removeObject.
 * \param id - object ID.
 * \details Removes object from list of object that are being redrawn. Supposed to be called
 * when object doesn't exist anymore.
 */
void MainWindow::removeObject(const unsigned int id) {
    mapArea->removeObject(id);
}

/*!
 * \brief MainWindow::refresh.
 * \details Refreshes rendered area. Render area doesn't refresh itself, so
 * it can be done only when needed.
 */
void MainWindow::refresh() {
    mapArea->update();
}

/*!
 * \brief MainWindow::setMap.
 * \param map
 * \details Sets map object to allow pass user-generated events
 * to model. Without map any user input won't take any affect.
 * \sa EventInterpreter::setMap.
 */
void MainWindow::setMap(std::shared_ptr<Map> map) {
    mapArea->setMap(map);
}
