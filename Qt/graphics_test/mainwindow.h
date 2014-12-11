#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QTimer>
#include <QMenu>

#include "../../src/map/Map.h"


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

private:
    Ui::MainWindow *ui;

    QMenu*   m_pBuild;
    QAction* m_pAddBuild;

    TMainObject* drag_obj;
    unsigned drag_state;

    QString str;
    QPoint curPos;
    Map map;
};

#endif // MAINWINDOW_H
