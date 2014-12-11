#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "../../src/test/add_functions.cpp"
#include "../../src/map/Map.cpp"
#include "painter.h"
#include "animate.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setMouseTracking(true);
    str = QString("Hi");

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
    if (event->button() == Qt::LeftButton)
    {
        str = QString("Click");
        curPos.setX(event->pos().x());
        curPos.setY(event->pos().y());

        if (drag_state == 0)
        {
            if ((drag_obj = map.get_build_object(Point(curPos.x()/POINT_WIDTH, curPos.y()/POINT_HEIGHT))) != 0)
            {
                drag_state = 1;
            }
        }
    }
    else
    {
       QMainWindow::mousePressEvent(event);
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent*)
{
    str = QString("Release");
    drag_state = 0;
}

void MainWindow::mouseMoveEvent(QMouseEvent *ev) {

    QPoint pos = ev->pos();
    str = QString("%1, %2").arg(pos.x()/POINT_WIDTH).arg(pos.y()/POINT_HEIGHT);

    if (drag_state == 1)
    {
       map.moveBuildObj(drag_obj, Point(pos.x()/POINT_WIDTH, pos.y()/POINT_HEIGHT));
    }
}


void MainWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    paint_map_on_display(&painter, &map);

    animate_one_state(&map);

    painter.drawText(QRect(20, 20, 200, 50), Qt::AlignCenter, str);
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

