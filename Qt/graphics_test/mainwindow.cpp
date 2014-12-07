#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "../../src/test/add_functions.cpp"
#include "painter.h"
#include "animate.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(100);

    //set contex menu
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this,	       SIGNAL(customContextMenuRequested(const QPoint)),this,
          SLOT(contextMenuRequested(QPoint)));

    m_pBuild = new QMenu();
    m_pAddBuild = m_pBuild->addAction("add Build");
    connect(m_pAddBuild, SIGNAL(triggered()), this, SLOT(m_add_build()));

    setWindowTitle("LandscapeTycoon");
    setFixedSize(800,500);

    addTestRoad(&map);
    addTestObject(&map);
    addTestDynObject(&map);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    int numBuild;

    if (event->button() == Qt::LeftButton)
    {

    }
    else
    {
       QMainWindow::mousePressEvent(event);
    }
}



void MainWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    paint_map_on_display(&painter, &map);

    animate_one_state(&map);
}

void MainWindow::contextMenuRequested(QPoint point)
{
    QPoint globalPoint = mapToGlobal(point);
    int objId = getObjectInMap(point);

    curPos.setX(point.x());
    curPos.setY(point.y());

    switch (objId)
    {
        case 0: m_pBuild->popup(globalPoint);
            break;
//        case 1: m_pUnit->popup(globalPoint);
//          break;
//        case 2: m_pBuild->popup(globalPoint);
//          break;
    }
}

int MainWindow::getObjectInMap(QPoint point)
{
    return 0;
}



//SLOTS

 void MainWindow::m_add_build()
 {
    t_coordinate x_point = curPos.x() / POINT_WIDTH;
    t_coordinate y_point = curPos.y() / POINT_HEIGHT;
    addBuildObj(&map, x_point, y_point, 1);
 }

