#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "../../src/saves/saves.h"

#include "../../src/test/add_functions.cpp"
#include "../../src/map/Map.cpp"
#include "../../src/algorithms/find_path.cpp"

#include <deque>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setMouseTracking(true);
    str = QString("Hi");
    menu_label = QString("Menu label");
    menu_is_active = false;
    enable_to_move = false;

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(100);

    //set contex menu
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint)),this,
                  SLOT(contextMenuRequested(QPoint)));

    ////////////////////////////////////////
    ///   configure context Menu
    ///
    m_pBuild        = new QMenu();
    m_pAddBuild     = m_pBuild->addAction("add Build");
    m_pAddRoad      = m_pBuild->addAction("add Road");
    m_pFindPath     = m_pBuild->addAction("find Path");
    m_pAddDynObj    = m_pBuild->addAction("add dyn obj");
    m_pEnableMove   = m_pBuild->addAction("enable/disable move");

    m_pDynObj   = new QMenu();
    m_pSetPath  = m_pDynObj->addAction("Set path");


    connect(m_pAddBuild  , SIGNAL(triggered()), this, SLOT(m_add_build       ()));
    connect(m_pAddRoad   , SIGNAL(triggered()), this, SLOT(m_add_road        ()));
    connect(m_pFindPath  , SIGNAL(triggered()), this, SLOT(m_find_path       ()));
    connect(m_pAddDynObj , SIGNAL(triggered()), this, SLOT(m_add_dyn_object  ()));
    connect(m_pEnableMove, SIGNAL(triggered()), this, SLOT(m_ena_dis_move_obj()));

    connect(m_pSetPath , SIGNAL(triggered()), this, SLOT(m_set_path ()));
    ///
    /////////////////////////////////////////

    setWindowTitle("LandscapeTycoon");
    setFixedSize(800,500);

    /////////////////////////////////////////
    ///   add initial tests objects
    ///
    addTestRoad(&map);
    addTestObject(&map);
    addTestDynObject(&map);
    ///
    /////////////////////////////////////////

    /////////////////////////////////////////
    ///         UNIT TEST
    ///
    qDebug() << "UNIT TEST START";

    std::deque<Point> path;

    find_path.find_road_path(&map, Point(11,11), Point(12,14), &path);

    std::deque<Point>::iterator it  = path.begin();
    std::deque<Point>::iterator ite = path.end();
    for (; it != ite; ++it)
    {
        qDebug() << QString("Path X=") << (*it).X << QString("Path Y=") << (*it).Y;
    }

    qDebug() << "UNIT TEST STOP";

    ///
    ///////////////////////////////////////////
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

        if (menu_is_active == SET_PATH_FOR_DYN_OBJ)
        {
            TMainObject *obj;
            Point cur_point = Point(curPos.x()/POINT_WIDTH, curPos.y()/POINT_HEIGHT);
            if ((obj = map.get_build_object(cur_point)) != 0)
            {
                std::deque<Point> path;

                if (stations.size() == 0)
                {
                    find_path.find_road_path(&map, dynObj->cur_pos, cur_point, &path);
                }
                else
                {
                    find_path.find_road_path(&map, stations.back().point, cur_point, &path);
                }
                if (path.size() != 0)
                {
                    menu_label += QString("\nSt X=%1 Y=%2 ").arg(cur_point.X).arg(cur_point.Y);
                    checkPoint station;

                    station.point.X = cur_point.X;
                    station.point.Y = cur_point.Y;
                    station.get_all = false;
                    station.put_all = false;
                    stations.push_back(station);
                }
            }
        }
        if (drag_state == 0 && enable_to_move)
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

void MainWindow::mouseReleaseEvent(QMouseEvent* ev)
{
    //QPoint pos = ev->pos();

    str = QString("Release");
    drag_state = 0;

    if (menu_is_active)
    {
        switch (isButtonPress(Point(ev->pos().x(),ev->pos().y())))
        {
        case BUT_OK:
                set_doList( dynObj, stations, 0);
                menu_is_active = 0;
            break;

        case BUT_LOAD:
                menu_label += QString("L ");
                stations.back().get_all = true;
            break;

        case BUT_UNLOAD:
                menu_label += QString("U ");
                stations.back().put_all = true;
            break;
        }
    }
    else
    {
        switch (isButtonPress(Point(ev->pos().x(),ev->pos().y())))
        {
        case BUT_SAVE:
                menu_label = QString("SAVE");
                saves(&map);
            break;
        case BUT_LOADXML:
                menu_label = QString("LOAD");
                load(&map);
            break;
        }
    }
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

//    paint_map_on_display(&painter, &map);
    paint_objects_on_dsplay(&painter, &map);
//  paint_map_on_display(&painter, &show_map);

    animate_one_state(&map);

    paint_debug_label(&painter, menu_label);
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
        case 1: m_pDynObj->popup(globalPoint);
            break;
//        case 2: m_pBuild->popup(globalPoint);
//          break;
    }
}

int MainWindow::getObjectInMap(QPoint point)
{
    std::list<TMainDynObject*>::iterator it  = map.dynObjects.begin();
    std::list<TMainDynObject*>::iterator ite = map.dynObjects.end();
    for (; it != ite; ++it)
    {
        if ((*it)->cur_pos.X == point.x()/POINT_WIDTH && (*it)->cur_pos.Y == point.y()/POINT_HEIGHT)
        {
            dynObj = (*it);
            return 1;
        }
    }
    return 0;
}



//SLOTS

 void MainWindow::m_add_build()
 {
    t_coordinate x_point = curPos.x() / POINT_WIDTH;
    t_coordinate y_point = curPos.y() / POINT_HEIGHT;
    addBuildObj(&map, x_point, y_point, 1);
 }

 void MainWindow::m_add_road()
 {
    t_coordinate x_point = curPos.x() / POINT_WIDTH;
    t_coordinate y_point = curPos.y() / POINT_HEIGHT;
    addRoad(&map, x_point, y_point);
 }

 void MainWindow::m_find_path()
 {
     t_coordinate x_point = curPos.x() / POINT_WIDTH;
     t_coordinate y_point = curPos.y() / POINT_HEIGHT;


     if (map.field[x_point][y_point].road.size() != 0 || map.field[x_point][y_point].object.size() != 0)
     {
        std::deque<Point> path;
        find_path.find_road_path(&map, Point((*map.dynObjects.begin())->cur_pos.X,(*map.dynObjects.begin())->cur_pos.Y), Point(x_point,y_point), &path);

        if (path.size() != 0)
        {
            str = QString("Path find");
            (*map.dynObjects.begin())->change_path(path);
        }

     }
 }

void MainWindow::m_set_path()
{
    menu_is_active = SET_PATH_FOR_DYN_OBJ;
    stations.clear();

    menu_label = QString("Set do List = ");
}

void MainWindow::m_add_dyn_object()
{
    Point point = Point(curPos.x() / POINT_WIDTH, curPos.y() / POINT_HEIGHT);

    if (map.field[point.X][point.Y].road.size() != 0 && map.field[point.X][point.Y].object.size() == 0)
    {
        createDynObject(&map, point, 4);
    }
}

void MainWindow::m_ena_dis_move_obj()
{
    enable_to_move = enable_to_move ? false:true;
}
