#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QTimer>
#include <QMenu>

#include "painter.h"
#include "animate.h"

#include "../../src/map/Map.h"
#include "../../src/algorithms/find_path.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);
    void paintEvent (QPaintEvent*);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *releaseEvent);
    void mouseMoveEvent(QMouseEvent *ev);

    int getObjectInMap(QPoint point);

private slots:
    void contextMenuRequested(QPoint point);
    void m_add_build();
    void m_add_road();
    void m_find_path();
    void m_set_path();
    void m_add_dyn_object();
    void m_ena_dis_move_obj();

private:
    Ui::MainWindow *ui;

    QMenu*   m_pBuild;
    QAction* m_pAddBuild;
    QAction* m_pAddRoad;
    QAction* m_pFindPath;
    QAction* m_pAddDynObj;
    QAction* m_pEnableMove;

    QMenu*   m_pDynObj;
    QAction* m_pSetPath;

    TMainObject* drag_obj;
    unsigned drag_state;

    QString     str, menu_label;
    QPoint      curPos;
    Map         map;
    Map         show_map;
    Find_path   find_path;
    bool        enable_to_move;

    // fill do List for dynObjs
    TMainDynObject* dynObj;
    std::vector<checkPoint> stations;

    unsigned menu_is_active;
};

#endif // MAINWINDOW_H
