
#ifndef SAVES_H
#define SAVES_H

#include <QFile>
#include <QTextStream>

#include <QDomDocument>
#include <QDomElement>
#include <QDomText>

#include "../../src/map/Map.h"


void save_road(std::list<TMainRoad*> const *object, QDomElement *tag, QDomDocument* doc)
{
    std::list<TMainRoad*>::const_iterator it  = object->begin();
    std::list<TMainRoad*>::const_iterator ite = object->end();

    for (; it != ite; ++it)
    {
        QDomElement tag_child = doc->createElement("Road");

        tag_child.setAttribute("X", (*it)->cur_pos.X);
        tag_child.setAttribute("Y", (*it)->cur_pos.Y);
        tag_child.setAttribute("road_id", (*it)->road_id);
        tag_child.setAttribute("road_type", (*it)->type);

        tag->appendChild(tag_child);
    }
}

void save_steps(std::vector<t_step> const *steps, QDomElement *tag, QDomDocument *doc)
{
    std::vector<t_step>::const_iterator it  = steps->begin();
    std::vector<t_step>::const_iterator ite = steps->end();

    QDomElement tag_step = doc->createElement("Steps");
    tag_step.setAttribute("size", steps->size());

    unsigned id=0;
    for (; it != ite; ++it, ++id)
    {
         QDomElement tag_child = doc->createElement("step");
         tag_child.setAttribute("id", id);
         tag_child.setAttribute("turn", (*it));

          tag_step.appendChild(tag_child);
    }

    tag->appendChild(tag_step);
}

void save_goods(std::list<Package> const *goods, QDomElement *tag, QDomDocument *doc)
{
    std::list<Package>::const_iterator it  = goods->begin();
    std::list<Package>::const_iterator ite = goods->end();

    for (; it != ite; ++it)
    {
        QDomElement tag_child = doc->createElement("Goods");
        tag_child.setAttribute("good_type",  (*it).good_type);
        tag_child.setAttribute("count_good", (*it).count_good);
        tag_child.setAttribute("width_good", (*it).width_good);

        tag->appendChild(tag_child);
    }

}

void save_main_objects(std::list<TMainObject*> const *object, Point cur_pos, QDomElement *tag, QDomDocument* doc)
{
    std::list<TMainObject*>::const_iterator it  = object->begin();
    std::list<TMainObject*>::const_iterator ite = object->end();

    for (; it != ite; ++it)
    {
        if( cur_pos.X == (*(it))->cur_pos.X && cur_pos.Y == (*(it))->cur_pos.Y)
        {
            QDomElement tag_child = doc->createElement("MainObjects");
            tag_child.setAttribute("X"          , (*it)->cur_pos.X  );
            tag_child.setAttribute("Y"          , (*it)->cur_pos.Y  );
            tag_child.setAttribute("object_id"  , (*it)->object_id  );
            tag_child.setAttribute("type"       , (*it)->type       );
            tag_child.setAttribute("loads"      , (*it)->loads      );

            save_goods(&(*it)->goods, &tag_child, doc);

            tag->appendChild(tag_child);
        }
    }

}


void save_package(std::list<Package> const *objects, QDomElement *tag, QDomDocument* doc)
{
    std::list<Package>::const_iterator it  = objects->begin();
    std::list<Package>::const_iterator ite = objects->end();

    for (; it != ite; ++it)
    {
         QDomElement tag_child = doc->createElement("Package");
         tag_child.setAttribute("good_type", (*it).good_type);
         tag_child.setAttribute("count_good", (*it).count_good);
         tag_child.setAttribute("width_good", (*it).width_good);

         tag->appendChild(tag_child);
    }
}

void save_check_points(std::vector<checkPoint> const *objects, QDomElement *tag, QDomDocument* doc)
{
    std::vector<checkPoint>::const_iterator it  = objects->begin();
    std::vector<checkPoint>::const_iterator ite = objects->end();

    for (; it != ite; ++it)
    {
        QDomElement tag_child = doc->createElement("CheckPoints");
        tag_child.setAttribute("X", static_cast<int>((*it).point.X));
        tag_child.setAttribute("Y", static_cast<int>((*it).point.Y));

        tag_child.setAttribute("get_all", static_cast<int>((*it).get_all));
        tag_child.setAttribute("put_all", static_cast<int>((*it).put_all));

        QDomElement tag_arrive = doc->createElement("doListArrive");
        save_package(&(*it).doListArrive, &tag_arrive, doc);
        tag_child.appendChild(tag_arrive);

        QDomElement tag_out = doc->createElement("doListOut");
        save_package(&(*it).doListOut, &tag_out, doc);
        tag_child.appendChild(tag_out);

        tag->appendChild(tag_child);
    }
}



void save_dyn_objects(std::list<TMainDynObject*> const *object, QDomElement *tag, QDomDocument* doc)
{
    std::list<TMainDynObject*>::const_iterator it  = object->begin();
    std::list<TMainDynObject*>::const_iterator ite = object->end();

    for (; it != ite; ++it)
    {
        QDomElement tag_child = doc->createElement("MainDynObjects");
        tag_child.setAttribute("X", (*it)->cur_pos.X);
        tag_child.setAttribute("Y", (*it)->cur_pos.Y);
        tag_child.setAttribute("orientation", (*it)->orientation);
        tag_child.setAttribute("left_path", (*it)->left_path);
        tag_child.setAttribute("loads", (*it)->loads);
        tag_child.setAttribute("max_loads", (*it)->max_loads);
        tag_child.setAttribute("state", (*it)->state);
        tag_child.setAttribute("speed", (*it)->speed);

        //save goods
        save_goods(&(*it)->goods, &tag_child, doc);

        //save steps
        save_steps(&(*it)->steps, &tag_child, doc);

        //save check points
        save_check_points(&(*it)->stations,&tag_child, doc);

        QDomElement tag_next_station = doc->createElement("next_station");
        std::vector<checkPoint>::iterator it_station  = (*it)->stations.begin();
        std::vector<checkPoint>::iterator ite_station = (*it)->stations.end();
        unsigned id = 0;
        for (; it_station != ite_station; ++it_station, ++id)
        {
            if ((*it)->next_station == it_station) break;
        }
        if (it_station != ite_station)
        {
            tag_next_station.setAttribute("next_station", id);
        }
        tag_child.appendChild(tag_next_station);

        tag->appendChild(tag_child);
    }

}



void load_goods (QDomElement *node, std::list<Package> *set)
{
    QString const name = "Goods";
    QDomElement elem_child = node->firstChildElement(name);

    while (!elem_child.isNull())
    {
        Package good;
        good.count_good = elem_child.attributeNode("count_good" ).nodeValue().toUInt();
        good.good_type  = elem_child.attributeNode("good_type"  ).nodeValue().toUInt();
        good.width_good = elem_child.attributeNode("width_good" ).nodeValue().toUInt();

        set->push_back(good);

        qDebug() << "good_type ="  << elem_child.attributeNode("good_type" ).nodeValue();
        qDebug() << "width_good =" << elem_child.attributeNode("width_good").nodeValue();
        qDebug() << "count_good =" << elem_child.attributeNode("count_good").nodeValue();

        elem_child = elem_child.nextSiblingElement(name);
    }

}

TMainObject* find_object(std::list<TMainObject*> *objects, TMainObject* obj)
{
    std::list<TMainObject*>::iterator it  = objects->begin();
    std::list<TMainObject*>::iterator ite = objects->end();

    for(; it != ite; ++it)
    {
        if (    (*(it))->cur_pos.X == obj->cur_pos.X
             && (*(it))->cur_pos.X == obj->cur_pos.Y
            )
            return *(it);
    }
    return 0;
}

void load_main_objects(QDomElement *node, std::list<TMainObject*> *objects, Map *map)
{
     QString const name = "MainObjects";
     QDomElement elem_child = node->firstChildElement(name);

     while (!elem_child.isNull())
     {
         TMainObject* obj = new TMainObject();

         obj->cur_pos.X = elem_child.attributeNode("X"          ).nodeValue().toUInt();
         obj->cur_pos.Y = elem_child.attributeNode("Y"          ).nodeValue().toUInt();
         obj->type      = elem_child.attributeNode("type"       ).nodeValue().toUInt();
         obj->object_id = elem_child.attributeNode("object_id"  ).nodeValue().toUInt();
         obj->loads     = elem_child.attributeNode("loads"      ).nodeValue().toUInt();

         qDebug() << "Local name " << elem_child.tagName();
         qDebug() << "First Child Node name id=" << elem_child.attributeNode("object_id").nodeValue();

         load_goods(&elem_child, &obj->goods);

         objects->push_back(obj);
         map->field[obj->cur_pos.X+1][obj->cur_pos.Y  ].object.push_back(obj);
         map->field[obj->cur_pos.X  ][obj->cur_pos.Y+1].object.push_back(obj);
         map->field[obj->cur_pos.X+1][obj->cur_pos.Y+1].object.push_back(obj);

         elem_child = elem_child.nextSiblingElement(name);
     }
}

void load_road(QDomElement *node, std::list<TMainRoad*> *road)
{
    QString const name = "Road";
    QDomElement elem_child = node->firstChildElement(name);

    while (!elem_child.isNull())
    {
        TMainRoad *p_road = new TMainRoad();

        p_road->cur_pos.X   = elem_child.attributeNode("X").nodeValue().toUInt();
        p_road->cur_pos.Y   = elem_child.attributeNode("Y").nodeValue().toUInt();
        p_road->road_id     = elem_child.attributeNode("road_id").nodeValue().toUInt();
        p_road->type        = elem_child.attributeNode("road_type").nodeValue().toUInt();

        road->push_back(p_road);

        qDebug() << "Road X ="  << elem_child.attributeNode("X").nodeValue()
                 << "Y ="       << elem_child.attributeNode("Y").nodeValue()
                 << "id ="      << elem_child.attributeNode("road_id").nodeValue()
                 << "type ="    << elem_child.attributeNode("road_type").nodeValue();

        elem_child = elem_child.nextSiblingElement(name);
    }
}


void load_steps(QDomElement *node, std::vector<t_step> *steps)
{
    QString const name = "step";
    QDomElement elem_child = node->firstChildElement("Steps");

    if(!elem_child.isNull())
    {
        QDomElement elem_steps = elem_child.firstChildElement(name);

        steps->resize(elem_child.attributeNode("size").nodeValue().toUInt());

        while (!elem_steps.isNull())
        {
            qDebug() << "step id =" << elem_steps.attributeNode("id").nodeValue()
                     << "turn ="    << elem_steps.attributeNode("turn").nodeValue();

            (*steps)[elem_steps.attributeNode("id").nodeValue().toUInt()] = elem_steps.attributeNode("turn").nodeValue().toUInt();
            elem_steps = elem_steps.nextSiblingElement(name);
        }
    }
}


void load_package(QDomElement *node, std::list<Package> *goods)
{
    QString const name = "Package";
    QDomElement elem_child = node->firstChildElement(name);

    while (!elem_child.isNull())
    {
        qDebug() << "Package good_type =" << elem_child.attributeNode("good_type").nodeValue()
                 << "count_good ="        << elem_child.attributeNode("count_good").nodeValue()
                 << "width_good ="        << elem_child.attributeNode("width_good").nodeValue();

        Package pack;
        pack.count_good = elem_child.attributeNode("count_good").nodeValue().toUInt();
        pack.good_type  = elem_child.attributeNode("good_type" ).nodeValue().toUInt();
        pack.width_good = elem_child.attributeNode("width_good").nodeValue().toUInt();

        goods->push_back(pack);
        elem_child = elem_child.nextSiblingElement(name);
    }
}

void load_check_points(QDomElement *node, std::vector<checkPoint> *stations, std::vector<checkPoint>::iterator *next_station)
{
    QString const name = "CheckPoints";
    QDomElement elem_child = node->firstChildElement(name);

    while (!elem_child.isNull())
    {
        checkPoint ch_point;

        ch_point.point.X =  elem_child.attributeNode("X").nodeValue().toUInt();
        ch_point.point.Y =  elem_child.attributeNode("Y").nodeValue().toUInt();

        ch_point.get_all =  elem_child.attributeNode("get_all").nodeValue().toUInt();
        ch_point.put_all =  elem_child.attributeNode("put_all").nodeValue().toUInt();

        qDebug() << "CheckPoint get_all =" << elem_child.attributeNode("get_all").nodeValue()
                 << "put_all ="            << elem_child.attributeNode("put_all").nodeValue();

        QDomElement elem_arrive = elem_child.firstChildElement("doListArrive");
        if (!elem_arrive.isNull())
        {
            qDebug() << "doArrive";
            load_package(&elem_arrive, &ch_point.doListArrive);
        }

        QDomElement elem_out = elem_child.firstChildElement("doListOut");
        if (!elem_out.isNull())
        {
            qDebug() << "doListOut";
            load_package(&elem_out, &ch_point.doListOut);
        }

        stations->push_back(ch_point);
        elem_child = elem_child.nextSiblingElement(name);
    }

    QDomElement elem_next_station = node->firstChildElement("next_station");
    if (!elem_next_station.isNull())
    {
        (*next_station) = stations->begin() + elem_next_station.attributeNode("next_station").nodeValue().toUInt();
    }
    else
    {
        (*next_station) = stations->begin();
    }

}


void load_dyn_objects(QDomElement *node, std::list<TMainDynObject*> *objects,  std::list<TMainDynObject*> *objects2)
{
    QString const name = "MainDynObjects";
    QDomElement elem_child = node->firstChildElement(name);

    std::list<Package> goods;

    while (!elem_child.isNull())
    {
        qDebug() << "DynObj left_path ="    << elem_child.attributeNode("left_path").nodeValue()
                 << "loads ="               << elem_child.attributeNode("loads").nodeValue()
                 << "max_loads ="           << elem_child.attributeNode("left_path").nodeValue();

        TMainDynObject* obj = new TMainDynObject();

        obj->loads      = elem_child.attributeNode("loads"      ).nodeValue().toUInt();
        obj->max_loads  = elem_child.attributeNode("max_loads"  ).nodeValue().toUInt();
        obj->speed      = elem_child.attributeNode("speed"      ).nodeValue().toUInt();
        obj->state      = elem_child.attributeNode("state"      ).nodeValue().toUInt();
        obj->cur_pos.X  = elem_child.attributeNode("X"          ).nodeValue().toUInt();
        obj->cur_pos.Y  = elem_child.attributeNode("Y"          ).nodeValue().toUInt();
        obj->orientation= elem_child.attributeNode("orientation").nodeValue().toUInt();
        obj->left_path  = elem_child.attributeNode("left_path"  ).nodeValue().toFloat();

        load_goods(&elem_child, &obj->goods);
        load_steps(&elem_child, &obj->steps);
        load_check_points(&elem_child, &obj->stations, &obj->next_station);

        objects->push_back(obj);
        objects2->push_back(obj);
        elem_child = elem_child.nextSiblingElement(name);
    }
}

void load_field(QDomElement *node, Map *map)
{
    QString const name = "Field";
    QDomElement elem_child = node->firstChildElement(name);

    while (!elem_child.isNull())
    {
        unsigned X = elem_child.attributeNode("X").nodeValue().toUInt();
        unsigned Y = elem_child.attributeNode("Y").nodeValue().toUInt();

        map->field[X][Y].status = elem_child.attributeNode("status").nodeValue().toUInt();

        qDebug() << "First Child Node name =" << elem_child.tagName()
                 << "X =" << X
                 << "Y =" << Y
                 << "status =" << elem_child.attributeNode("status").nodeValue();

        load_road(&elem_child, &map->field[X][Y].road);

        load_main_objects(&elem_child, &map->field[X][Y].object, map);

        load_dyn_objects(&elem_child, &map->field[X][Y].dynObjects, &map->dynObjects);

        elem_child = elem_child.nextSiblingElement(name);
    }
}


///////////////////////////////////////////////////////////
/// Main load
///
int load(Map* map)
{
    QFile inFile( "..\\..\\MyML.xml" );
    if( !inFile.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
      qDebug( "Failed to open file for reading." );
      return 0;
    }

    QDomDocument document;
    if( !document.setContent( &inFile ) )
    {
      qDebug( "Failed to parse the file into a DOM tree." );
      inFile.close();
      return 0;
    }

    inFile.close();

    QDomElement documentElement = document.documentElement();
    qDebug() << "Main Node name =" <<  documentElement.nodeName();

    map->clear();
    //QDomElement node = documentElement.firstChild().toElement();
    QDomElement node = documentElement.toElement();

    if (!node.isNull())
    {
        load_field(&node, map);

        //node = node.nextSibling().toElement();
    }
//    while (!node.isNull())
//    {
//        unsigned X = node.attributeNode("X").nodeValue().toUInt();
//        unsigned Y = node.attributeNode("Y").nodeValue().toUInt();
//        qDebug() << "First Child Node name =" << node.tagName()
//                 << "X =" << X
//                 << "Y =" << Y;

//        load_main_objects(&node);

//        node = node.nextSibling().toElement();
//    }
}

int saves(Map* map)
{
    QDomDocument doc("MyML");
    QDomElement root = doc.createElement("Map");
    doc.appendChild(root);

    for (unsigned i = 5; i < 18; ++i)
    {
       for (unsigned j = 5; j < 18; ++j)
       {
           QDomElement tag = doc.createElement("Field");

           tag.setAttribute("X", i);
           tag.setAttribute("Y", j);
           tag.setAttribute("status", map->field[i][j].status);

           save_road(&map->field[i][j].road, &tag, &doc);

           save_main_objects(&map->field[i][j].object, Point(i,j), &tag, &doc);

           save_dyn_objects(&map->field[i][j].dynObjects, &tag, &doc);

           root.appendChild(tag);
       }
    }

    QFile outFile1( "..\\..\\MyML.xml" );
    if( !outFile1.open( QIODevice::WriteOnly | QIODevice::Text ) )
    {
      qDebug( "Failed to open file for writing." );
      return 0;
    }

    QTextStream stream1( &outFile1 );
    stream1 << doc.toString();

    outFile1.close();




//    QDomText t = doc.createTextNode("Hello World");
//    tag.appendChild(t);

//    QString xml = doc.toString();


//    QDomDocument doc("mydocument");
    QFile file("..\\..\\mydocument.xml");

    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug("ERROR file didn't open");
        return 0;
    }

    if (!doc.setContent(&file)) {
        qDebug("ERROR file didn't set contex");
        file.close();
        return 0;
    }
    file.close();

    // print out the element names of all elements that are direct children
    // of the outermost element.
    QDomElement docElem = doc.documentElement();

    QDomNode n = docElem.firstChild();
    while(!n.isNull()) {
        QDomElement e = n.toElement(); // try to convert the node to an element.
        QDomNode nn = e.firstChild();
        if (!nn.isNull())
        {
            qDebug() << qPrintable(nn.toElement().tagName());
        }
        if(!e.isNull())
        {
            qDebug() << qPrintable(e.tagName()); // the node really is an element.
        }
        n = n.nextSibling();
    }

    // Here we append a new element to the end of the document
    QDomElement elem = doc.createElement("img");
    elem.setAttribute("src", "myimage.png");
    docElem.appendChild(elem);



  QFile inFile( "..\\..\\simple.xml" );
  if( !inFile.open( QIODevice::ReadOnly | QIODevice::Text ) )
  {
    qDebug( "Failed to open file for reading." );
    return 0;
  }

  QDomDocument document;
  if( !document.setContent( &inFile ) )
  {
    qDebug( "Failed to parse the file into a DOM tree." );
    inFile.close();
    return 0;
  }

  inFile.close();

  QDomElement documentElement = document.documentElement();
  QDomNodeList elements = documentElement.elementsByTagName( "id" );

  for (unsigned i = 0; i < 10; ++i)
  {
       QDomElement bar = document.createElement( QString("id") );
       //bar.setNodeValue(QString::number(i));
       bar.setAttribute(QString("attr"), i);
       documentElement.insertAfter(bar, QDomNode() );
  }




//  if( elements.size() == 0 )
//  {
//    QDomElement bar = document.createElement( "bar" );
//    documentElement.insertBefore( bar, QDomNode() );
//  }
//  else if( elements.size() == 1 )
//  {
//    QDomElement bar = elements.at(0).toElement();

//    QDomElement baz = document.createElement( "baz" );
//    baz.setAttribute( "count", QString::number( bar.elementsByTagName( "baz" ).size() + 1 ) );

//    bar.appendChild( baz );
//  }

  QFile outFile( "..\\..\\simple-modified.xml" );
  if( !outFile.open( QIODevice::WriteOnly | QIODevice::Text ) )
  {
    qDebug( "Failed to open file for writing." );
    return 0;
  }

  QTextStream stream( &outFile );
  stream << document.toString();

  outFile.close();

  //load(map);

  return 0;
}


#endif
