#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <cmath>

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

void tainStep()
{
    for (unsigned int i = 0; i < count_train; ++i)
    {
        if (trains[i].state == TRAIN_FORWARD)
        {
            if (    std::abs(trains[i].p2.x() - trains[i].p1.x()) <= std::abs(trains[i].left_path[0])
                 && std::abs(trains[i].p2.y() - trains[i].p1.y()) <= std::abs(trains[i].left_path[1]))
            {
                trains[i].state = TRAIN_BACK;
                trains[i].left_path[0] = 0;
                trains[i].left_path[1] = 0;
                int x = trains[i].p1.x(), y = trains[i].p1.y();
                trains[i].p1.setX(trains[i].p2.x());
                trains[i].p1.setY(trains[i].p2.y());
                trains[i].p2.setX(x);
                trains[i].p2.setY(y);
            }
            else
            {
                trains[i].left_path[0] += trains[i].speed_x;
                trains[i].left_path[1] += trains[i].speed_y;
            }
        }
        else if (trains[i].state == TRAIN_BACK)
        {
            if (   std::abs(trains[i].p2.x() - trains[i].p1.x()) <= std::abs(trains[i].left_path[0])
                && std::abs(trains[i].p2.y() - trains[i].p1.y()) <= std::abs(trains[i].left_path[1]))
            {
                trains[i].state = TRAIN_FORWARD;
                trains[i].left_path[0] = 0;
                trains[i].left_path[1] = 0;
                int x = trains[i].p1.x(), y = trains[i].p1.y();
                trains[i].p1.setX(trains[i].p2.x());
                trains[i].p1.setY(trains[i].p2.y());
                trains[i].p2.setX(x);
                trains[i].p2.setY(y);
            }
            else
            {
                trains[i].left_path[0] -= trains[i].speed_x;
                trains[i].left_path[1] -= trains[i].speed_y;
            }
        }
    }
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
        tainStep();
//        if (!stop)
//        {
//            left_path[0] += (600 - 100) / 100.0;
//            left_path[1] += (100 - 250) / 100.0;
//            coord[0] = init_coord[0] + (int)left_path[0]; // 1000; //600
//            coord[1] = init_coord[1] + (int)left_path[1]; //100
//        }
//        else
//        {
//            left_path[0] -= (600 - 100) / 100.0;
//            left_path[1] -= (100 - 250) / 100.0;
//            coord[0] = init_coord[0] + (int)left_path[0]; // 1000; //600
//            coord[1] = init_coord[1] + (int)left_path[1]; //100
//        }
//        if( coord[0] >= 600 || coord[1] <= 100) stop = true;
//        if( coord[0] <= 100 || coord[1] >= 250) stop = false;
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

    //a simple line
//    painter.drawLine(1,1,100,100);

//    //create a black pen that has solid line
//    //and the width is 2.
//    QPen myPen(Qt::black, 2, Qt::SolidLine);
//    painter.setPen(myPen);
//    painter.drawLine(100,100,100,1);

//    //draw a point
//    myPen.setColor(Qt::red);
//    painter.drawPoint(110,110);

//    //draw a polygon
//    QPolygon polygon;
//    polygon << QPoint(130, 140) << QPoint(180, 170)
//             << QPoint(180, 140) << QPoint(220, 110)
//             << QPoint(140, 100);
//     painter.drawPolygon(polygon);

     //draw an ellipse
     //The setRenderHint() call enables antialiasing, telling QPainter to use different
     //color intensities on the edges to reduce the visual distortion that normally
     //occurs when the edges of a shape are converted into pixels
     painter.setRenderHint(QPainter::Antialiasing, true);
     painter.setPen(QPen(Qt::black) ); //, 1, Qt::DashDotLine, Qt::RoundCap));
     painter.setBrush(QBrush(Qt::green, Qt::SolidPattern));
     //painter.drawEllipse(200, 80, 400, 240);


     painter.setPen(QPen(Qt::black,line_width));

     for (unsigned int i = 0; i < count_link; ++i )
     {
        painter.drawLine(  builds[links[i][0]][0] + rect_width/2, builds[links[i][0]][1] + rect_hight/2
                         , builds[links[i][1]][0] + rect_width/2, builds[links[i][1]][1] + rect_hight/2 );
     }

     painter.drawChord(450,225,20,20,0,360*16);

     for (unsigned int i = 0; i < count_rect; ++i )
     {
        painter.drawRect(builds[i][0],builds[i][1],rect_width,rect_hight);
     }

//     painter.drawRect(coord[0],coord[1],rect_width,rect_hight);
     str = QString::number(count_train);


     //painter.drawRect(coord[0],coord[1],rect_width,rect_hight);

     for (unsigned int i = 0; i < count_train; ++i )
     {
         painter.drawRect( static_cast<int>(trains[i].p1.x()+trains[i].left_path[0])
                          ,static_cast<int>(trains[i].p1.y()+trains[i].left_path[1])
                          ,rect_width,rect_hight);
         str = QString::number(static_cast<int>(trains[i].p1.x()+trains[i].left_path[0]))
                 + QString(" + ") + QString::number(static_cast<int>(trains[i].p1.y()+trains[i].left_path[1]));
     }

     painter.drawText(QRect(20, 20, 200, 50), Qt::AlignCenter, str);

     step();
}
