#include "mainwindow.h"
#include "paint_map.h"
#include "add_functions.h"
//#include "ui_mainwindow.h"
//#include <QtGui>
//#include <cmath>

enum{
    CHOOSE_BUILD = 1,
    CHOOSE_NEXT_TRAIN_BUILD = 2,

    MAX_BUILD = 100,
    MAX_LINK = 100,
    MAX_TRAIN = 100,


    //Train
    TRAIN_FORWARD = 1,
    TRAIN_BACK = 2,
    TRAIN_SPEED_1 = 4
};

unsigned int builds[MAX_BUILD][2];
unsigned int links[MAX_LINK][2];

struct s_train
{
    QPoint          p1, p2;
    float           left_path[2];
    unsigned int    state;
    float           speed_x, speed_y;
};

s_train trains[MAX_TRAIN];

unsigned int rect_hight = 20;
unsigned int rect_width = 20;
unsigned int line_width = 3;

unsigned int count_rect = 3;
unsigned int count_link = 3;
unsigned int count_train = 0;

unsigned int coord_rect[3][2] = {
    {100, 250},
    {600, 100},
    {300, 350}
};

unsigned int link_road[3][2] = {
    {0, 1},
    {1, 2},
    {2, 0}
};

QString str;

void addTrainToStruct (unsigned int p1, unsigned int p2, float speed)
{
    trains[count_train].left_path[0] = 0;
    trains[count_train].left_path[1] = 0;


    trains[count_train].p1.setX(builds[p1][0]);
    trains[count_train].p1.setY(builds[p1][1]);
    trains[count_train].p2.setX(builds[p2][0]);
    trains[count_train].p2.setY(builds[p2][1]);

    int a_b = std::abs(trains[count_train].p2.y() - trains[count_train].p1.y()) + std::abs(trains[count_train].p2.x() - trains[count_train].p1.x());

    trains[count_train].speed_x = (trains[count_train].p2.x() - trains[count_train].p1.x()) / (float)a_b * speed;
    trains[count_train].speed_y = (trains[count_train].p2.y() - trains[count_train].p1.y()) / (float)a_b * speed;
    trains[count_train].state = TRAIN_FORWARD;

    ++count_train;
}


void next_step(TMainDynObject* obj)
{
    switch (obj->orientation)
    {
        case STEP_TOP:
                --obj->cur_pos.Y;
            break;

        case STEP_BOT:
                ++obj->cur_pos.Y;
            break;

        case STEP_LEFT:
                --obj->cur_pos.X;
            break;

        case STEP_RIGHT:
                ++obj->cur_pos.X;
            break;
    }

    obj->orientation = *obj->steps.begin();
    obj->steps.erase(obj->steps.begin());
    obj->left_path = 0;
}

void stepToDynObject(TMainDynObject* obj)
{
    if (obj->steps.size() != 0)
    {
        obj->left_path += obj->speed;
        if (obj->orientation == STEP_BOT || obj->orientation == STEP_TOP )
        {
            if (obj->left_path > POINT_HEIGHT)
            {
                next_step(obj);
            }
        }
        else
        {
            if (obj->left_path > POINT_WIDTH)
            {
                next_step(obj);
            }
        }
    }

}

void tainStep(Map* map)
{
    for (std::list<TMainDynObject*>::iterator i = map->dynObjects.begin(); i != map->dynObjects.end(); ++i)
    {
        stepToDynObject(*i);
    }

//    for (unsigned int i = 0; i < count_train; ++i)
//    {
//        if (trains[i].state == TRAIN_FORWARD)
//        {
//            if (    std::abs(trains[i].p2.x() - trains[i].p1.x()) <= std::abs(trains[i].left_path[0])
//                 && std::abs(trains[i].p2.y() - trains[i].p1.y()) <= std::abs(trains[i].left_path[1]))
//            {
//                trains[i].state = TRAIN_BACK;
//                trains[i].left_path[0] = 0;
//                trains[i].left_path[1] = 0;
//                int x = trains[i].p1.x(), y = trains[i].p1.y();
//                trains[i].p1.setX(trains[i].p2.x());
//                trains[i].p1.setY(trains[i].p2.y());
//                trains[i].p2.setX(x);
//                trains[i].p2.setY(y);
//            }
//            else
//            {
//                trains[i].left_path[0] += trains[i].speed_x;
//                trains[i].left_path[1] += trains[i].speed_y;
//            }
//        }
//        else if (trains[i].state == TRAIN_BACK)
//        {
//            if (   std::abs(trains[i].p2.x() - trains[i].p1.x()) <= std::abs(trains[i].left_path[0])
//                && std::abs(trains[i].p2.y() - trains[i].p1.y()) <= std::abs(trains[i].left_path[1]))
//            {
//                trains[i].state = TRAIN_FORWARD;
//                trains[i].left_path[0] = 0;
//                trains[i].left_path[1] = 0;
//                int x = trains[i].p1.x(), y = trains[i].p1.y();
//                trains[i].p1.setX(trains[i].p2.x());
//                trains[i].p1.setY(trains[i].p2.y());
//                trains[i].p2.setX(x);
//                trains[i].p2.setY(y);
//            }
//            else
//            {
//                trains[i].left_path[0] -= trains[i].speed_x;
//                trains[i].left_path[1] -= trains[i].speed_y;
//            }
//        }
//    }
}

void initBuildAndLink()
{
    for (unsigned int i = 0; i < count_rect; ++i)
    {
       builds[i][0] = coord_rect[i][0];
       builds[i][1] = coord_rect[i][1];
    }
    for (unsigned int i = 0; i < count_link; ++i)
    {
       links[i][0] = link_road[i][0];
       links[i][1] = link_road[i][1];
    }

    addTrainToStruct(0,1,TRAIN_SPEED_1);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    int numBuild;

    if (event->button() == Qt::LeftButton) {
         if(state == CHOOSE_BUILD)
         {
            curPos.setX(event->pos().x());
            curPos.setY(event->pos().y());
            if ((numBuild = isBuild()) != -1)
            {
                links[count_link][0] = fromBuild;
                links[count_link][1] = numBuild;
                ++count_link;
                state = 0;
            }
         }else if (state == CHOOSE_NEXT_TRAIN_BUILD)
         {
             curPos.setX(event->pos().x());
             curPos.setY(event->pos().y());
             if ((numBuild = isBuild()) != -1)
             {
                 addTrainToStruct(fromBuild, numBuild, TRAIN_SPEED_1);
                 state = 0;
             }
         }
     } else {
         // pass on other buttons to base class
         QMainWindow::mousePressEvent(event);
     }
}

void MainWindow::addBuild()
{
    str = QString::number(curPos.x()) + QString(" + ") + QString::number(curPos.y());
    builds[count_rect][0] = curPos.x();
    builds[count_rect][1] = curPos.y();
    ++count_rect;
}

int MainWindow::isBuild()
{
    for (unsigned int i = 0; i < count_rect; ++i)
    {
        if(builds[i][0] < curPos.x() && builds[i][0] + rect_width > curPos.x()
           && builds[i][1] < curPos.y() && builds[i][1] + rect_hight > curPos.y())
        {
            return i;
        }
    }
    return -1;
}

void MainWindow::addLink()
{
    unsigned int num_obj =  isBuild();
    fromBuild = num_obj;
    state = CHOOSE_BUILD;
}

void MainWindow::addTrain()
{
    unsigned int num_obj =  isBuild();
    fromBuild = num_obj;
    state = CHOOSE_NEXT_TRAIN_BUILD;
}



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    state = 0;
    init_coord[0] = 100;
    init_coord[1] = 250;
    coord[0] = 100;
    coord[1] = 250;
    left_path[0] = 0;
    left_path[1] = 0;
    stopUnitMove = false;

    initBuildAndLink();

    str = QString("Hi my programm");

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(100);
    stop = false;

    m_pContextMenu = new QMenu();
    m_pUnit        = new QMenu();
    m_pBuild       = new QMenu();

    setWindowTitle("Show Menu on Right Click and Trigger Actions");
    setFixedSize(800,500);
    setContextMenuPolicy(Qt::CustomContextMenu);

    m_pAddBuild      = m_pContextMenu->addAction("add Build");

    m_pActionStop    = m_pUnit->addAction("StopUnit");
    m_pActionStart   = m_pUnit->addAction("StartUnit");

    m_pAddLink       = m_pBuild->addAction("Set Link");
    m_pAddTrain      = m_pBuild->addAction("Create Train");

    connect(this,	       SIGNAL(customContextMenuRequested(const QPoint)),this,
          SLOT(contextMenuRequested(QPoint)));

    connect(m_pAddBuild     ,SIGNAL(triggered()),this,SLOT(addBuild()  ));

    connect(m_pActionStop ,SIGNAL(triggered()),this,SLOT(stopUnit() ));
    connect(m_pActionStart,SIGNAL(triggered()),this,SLOT(startUnit()));

    connect(m_pAddLink,SIGNAL(triggered()),this,SLOT(addLink()));
    connect(m_pAddTrain,SIGNAL(triggered()),this,SLOT(addTrain()));

    addTestRoad(&map);
    addTestObject(&map);
    addTestDynObject(&map);

    ui->setupUi(this);
}

int MainWindow::getObjectInMap(QPoint point)
{
    //str = QString::number(point.x()) + QString(" + ") + QString::number(point.y());
    if(coord[0] < point.x() && coord[0] + rect_width > point.x()
       && coord[1] < point.y() && coord[1] + rect_hight > point.y())
    {
        return 1;
    }

    if (isBuild() != -1 ) return 2;

    return 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::step()
{
    if (!stopUnitMove)
    {
        tainStep(&map);
    }
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


void MainWindow::paintEvent(QPaintEvent*)
{
    //create a QPainter and pass a pointer to the device.
    //A paint device can be a QWidget, a QPixmap or a QImage
    QPainter painter(this);

    paint_map_on_display(&painter);

    step();
}



bool isPainted(t_status status)
{
    if (status == FILL_OBJECT) return true;

    return false;
}

void paint_road(QPainter* painter, TMainRoad* road)
{
     painter->setPen(QPen(Qt::black) );
     painter->setBrush(QBrush(Qt::gray, Qt::SolidPattern));

     painter->drawRect(road->cur_pos.X*POINT_WIDTH, road->cur_pos.Y*POINT_HEIGHT, POINT_WIDTH, POINT_HEIGHT);
}

void paint_build(QPainter* painter, TMainObject* road)
{
    painter->setPen(QPen(Qt::black)); //,1,Qt::SolidLine,Qt::RoundCap) );
    painter->setBrush(QBrush(Qt::green, Qt::SolidPattern));

    painter->drawRect(road->cur_pos.X*POINT_WIDTH, road->cur_pos.Y*POINT_HEIGHT, POINT_WIDTH*BUILD_WIDTH, POINT_HEIGHT*BUILD_HEIGHT);
}

void paintDynObject(QPainter* painter, TMainDynObject* obj)
{
    painter->setPen(QPen(Qt::black)); //,1,Qt::SolidLine,Qt::RoundCap) );
    painter->setBrush(QBrush(Qt::red, Qt::SolidPattern));

    QRectF rect;// = QRectF(obj->cur_pos.X*POINT_WIDTH, obj->cur_pos.Y*POINT_HEIGHT, POINT_WIDTH, POINT_HEIGHT);

    QPainterPath path;
    if (obj->orientation == STEP_TOP)
    {
        rect = QRectF(obj->cur_pos.X*POINT_WIDTH, obj->cur_pos.Y*POINT_HEIGHT - static_cast<t_coordinate>(obj->left_path), POINT_WIDTH, POINT_HEIGHT);
        path.moveTo(rect.left() + (rect.width() / 2), rect.top());
        path.lineTo(rect.bottomLeft());
        path.lineTo(rect.bottomRight());
        path.lineTo(rect.left() + (rect.width() / 2), rect.top());
    }
    else if (obj->orientation == STEP_BOT)
    {
        rect = QRectF(obj->cur_pos.X*POINT_WIDTH, obj->cur_pos.Y*POINT_HEIGHT + static_cast<t_coordinate>(obj->left_path), POINT_WIDTH, POINT_HEIGHT);
        path.moveTo(rect.left() + (rect.width() / 2), rect.bottom());
        path.lineTo(rect.topLeft());
        path.lineTo(rect.topRight());
        path.lineTo(rect.left() + (rect.width() / 2), rect.bottom());
    }
    else if (obj->orientation == STEP_LEFT)
    {
        rect = QRectF(obj->cur_pos.X*POINT_WIDTH - static_cast<t_coordinate>(obj->left_path), obj->cur_pos.Y*POINT_HEIGHT, POINT_WIDTH, POINT_HEIGHT);
        path.moveTo(rect.left(), rect.top()+ (rect.height() / 2));
        path.lineTo(rect.topRight());
        path.lineTo(rect.bottomRight());
        path.lineTo(rect.left(), rect.top()+ (rect.height() / 2));
    }
    else
    {
        rect = QRectF(obj->cur_pos.X*POINT_WIDTH + static_cast<t_coordinate>(obj->left_path), obj->cur_pos.Y*POINT_HEIGHT, POINT_WIDTH, POINT_HEIGHT);
        path.moveTo(rect.right(), rect.top()+ (rect.height() / 2));
        path.lineTo(rect.topLeft());
        path.lineTo(rect.bottomLeft());
        path.lineTo(rect.right(), rect.top()+ (rect.height() / 2));
    }

    painter->fillPath(path, QBrush(QColor ("blue")));
}

void MainWindow::paint_map_on_display(QPainter* painter)
{
    for (unsigned i = 0; i < MAP_WIDTH; ++i)
    {
        for (unsigned j = 0; j < MAP_HEIGHT; ++j)
        {
            if (isPainted(map.field[i][j].status))
            {
                if (map.field[i][j].road.size() != 0)
                {
                    str = QString::number(i) + QString(" ") + QString::number(j);
                    paint_road(painter, map.field[i][j].road.front());
                }
                else if( map.field[i][j].object.size() != 0)
                {
                    TMainObject* build = map.field[i][j].object.front();
                    if (build->cur_pos.X == i && build->cur_pos.Y == j)
                    {
                        paint_build(painter, build);
                    }
                }
            }
        }
    }

    for (std::list<TMainDynObject*>::iterator i = map.dynObjects.begin(); i != map.dynObjects.end(); ++i)
    {
        paintDynObject(painter, *i);
    }
    //paint Dyn Objects


    painter->drawText(QRect(20, 20, 200, 50), Qt::AlignCenter, str);

 /*
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(QPen(Qt::black) ); //, 1, Qt::DashDotLine, Qt::RoundCap));
    painter->setBrush(QBrush(Qt::green, Qt::SolidPattern));


    painter->setPen(QPen(Qt::black,line_width));

    for (unsigned int i = 0; i < count_link; ++i )
    {
       painter->drawLine(  builds[links[i][0]][0] + rect_width/2, builds[links[i][0]][1] + rect_hight/2
                        , builds[links[i][1]][0] + rect_width/2, builds[links[i][1]][1] + rect_hight/2 );
    }

    painter->drawChord(450,225,20,20,0,360*16);

    for (unsigned int i = 0; i < count_rect; ++i )
    {
       painter->drawRect(builds[i][0],builds[i][1],rect_width,rect_hight);
    }

    for (unsigned int i = 0; i < count_train; ++i )
    {
        painter->drawRect( static_cast<int>(trains[i].p1.x()+trains[i].left_path[0])
                         ,static_cast<int>(trains[i].p1.y()+trains[i].left_path[1])
                         ,rect_width,rect_hight);
        str = QString::number(static_cast<int>(trains[i].p1.x()+trains[i].left_path[0]))
                + QString(" + ") + QString::number(static_cast<int>(trains[i].p1.y()+trains[i].left_path[1]));
    }

    painter->drawText(QRect(20, 20, 200, 50), Qt::AlignCenter, str);
*/
}
