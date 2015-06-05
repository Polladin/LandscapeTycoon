
#include "painter.h"


void paint_map_on_display(QPainter* painter, Map* map)
{
    for (unsigned i = 0; i < MAP_WIDTH; ++i)
    {
        for (unsigned j = 0; j < MAP_HEIGHT; ++j)
        {
          //  if (isPainted(map->field[i][j].status))
          // {
                if( map->field[i][j].object.size() != 0)
                {
                    TMainObject* build = map->field[i][j].object.front();
                    if (build->cur_pos.X == i && build->cur_pos.Y == j)
                    {
                        paint_build(painter, build);
                    }
                }
                else if (map->field[i][j].road.size() != 0)
                {
                    //str = QString::number(i) + QString(" ") + QString::number(j);
                    paint_road(painter, map->field[i][j].road.front());
                }
         // }
        }
    }

    for (std::list<TMainDynObject*>::iterator i = map->dynObjects.begin(); i != map->dynObjects.end(); ++i)
    {
        paintDynObject(painter, *i);
    }
    //painter->drawText(QRect(20, 20, 200, 50), Qt::AlignCenter, str);
}

void paint_road(QPainter* painter, TMainRoad* road)
{
     painter->setPen(QPen(Qt::black) );
     painter->setBrush(QBrush(Qt::gray, Qt::SolidPattern));

     painter->drawRect(road->cur_pos.X*POINT_WIDTH, road->cur_pos.Y*POINT_HEIGHT, POINT_WIDTH, POINT_HEIGHT);
}

void paint_build(QPainter* painter, TMainObject* build)
{
    painter->setPen(QPen(Qt::black)); //,1,Qt::SolidLine,Qt::RoundCap) );
    painter->setBrush(QBrush(Qt::green, Qt::SolidPattern));

    QRect rect = QRect(build->cur_pos.X*POINT_WIDTH, build->cur_pos.Y*POINT_HEIGHT
                       , POINT_WIDTH*BUILD_WIDTH, POINT_HEIGHT*BUILD_HEIGHT);
    painter->drawRect(rect);

    if (build->goods.size() != 0)
    {
        if (build->type == obj_types::LUMBERJACK)
        {
            painter->drawText(rect, Qt::AlignCenter, QString("Lu-")+QString::number(((TLumberJack*)build)->get_wood_count()));
        }
        else if (build->type == obj_types::MINE)
        {
            painter->drawText(rect, Qt::AlignCenter, QString("Mi-")+QString::number(((TMine*)build)->get_good_count()));
        }
        else if (build->type == obj_types::WAREHOUSE)
        {
            painter->drawText(rect, Qt::AlignCenter, QString("Wa-")+QString::number(((TWareHouse*)build)->get_good_count()));
        }
        else
        {
            painter->drawText(rect, Qt::AlignCenter, QString::number(build->goods.begin()->count_good));
        }
        //painter->drawText(rect, Qt::AlignCenter, QString::number(build->goods.begin()->count_good));
    }
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


bool isPainted(t_status status)
{
    if (status == FILL_OBJECT) return true;

    return false;
}

inline QRect get_menu_rect(unsigned name)
{
    return  QRect(menu_coords[name][0], menu_coords[name][1],
                  menu_coords[name][2], menu_coords[name][3]);
}

void paint_debug_label(QPainter* painter, QString label)
{

    QRect label_rect        = get_menu_rect(LABEL);
    QRect but_OK_rect       = get_menu_rect(BUT_OK);
    QRect but_load_rect     = get_menu_rect(BUT_LOAD);
    QRect but_unload_rect   = get_menu_rect(BUT_UNLOAD);
    QRect but_save_rect     = get_menu_rect(BUT_SAVE);
    QRect but_loadXML_rect  = get_menu_rect(BUT_LOADXML);

    /////////////////////////////////
    //paint label
    painter->setPen(QPen(Qt::black) );
    painter->setBrush(QBrush(Qt::white, Qt::SolidPattern));

    painter->drawRect(label_rect);
    painter->drawText(label_rect, Qt::AlignCenter, label);


    ///////////////////////////////
    //paint buttons
    painter->setPen(QPen(Qt::black) );
    painter->setBrush(QBrush(Qt::gray, Qt::SolidPattern));

    painter->drawRect(but_OK_rect);
    painter->drawText(but_OK_rect, Qt::AlignCenter, QString("Ok"));
    painter->drawRect(but_load_rect);
    painter->drawText(but_load_rect, Qt::AlignCenter, QString("Load"));
    painter->drawRect(but_unload_rect);
    painter->drawText(but_unload_rect, Qt::AlignCenter, QString("Unload"));
    painter->drawRect(but_save_rect);
    painter->drawText(but_save_rect, Qt::AlignCenter, QString("Save"));
    painter->drawRect(but_loadXML_rect);
    painter->drawText(but_loadXML_rect, Qt::AlignCenter, QString("Load"));
}

int isButtonPress(Point p)
{
    for (unsigned i = 0; i < COUNT_BUT; ++i)
    {
        if (   menu_coords[i][0]                     <= p.X
            && menu_coords[i][0] + menu_coords[i][2] >= p.X
            && menu_coords[i][1]                     <= p.Y
            && menu_coords[i][1] + menu_coords[i][3] >= p.Y
           )
        {
            return i;
        }
    }

    return -1;
}
