
#include "paint_map.h"
#include "global_painter.h"

void paint_map_on_display(QPainter* painter)
{
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(QPen(Qt::black) ); //, 1, Qt::DashDotLine, Qt::RoundCap));
    painter->setBrush(QBrush(Qt::green, Qt::SolidPattern));
    //painter->drawEllipse(200, 80, 400, 240);


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

//     painter->drawRect(coord[0],coord[1],rect_width,rect_hight);
//    str = QString::number(count_train);


    //painter->drawRect(coord[0],coord[1],rect_width,rect_hight);

    for (unsigned int i = 0; i < count_train; ++i )
    {
        painter->drawRect( static_cast<int>(trains[i].p1.x()+trains[i].left_path[0])
                         ,static_cast<int>(trains[i].p1.y()+trains[i].left_path[1])
                         ,rect_width,rect_hight);
 //       str = QString::number(static_cast<int>(trains[i].p1.x()+trains[i].left_path[0]))
 //               + QString(" + ") + QString::number(static_cast<int>(trains[i].p1.y()+trains[i].left_path[1]));
    }

    painter->drawText(QRect(20, 20, 200, 50), Qt::AlignCenter, str);
}
