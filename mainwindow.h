#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QWidget>
#include <QTimer>
#include <QMenu>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

     void onCustomContextMenu(const QPoint& pos); // this is a slot

protected:
    void changeEvent(QEvent *e);
    void paintEvent(QPaintEvent*); //Added this line
    void mousePressEvent(QMouseEvent *event);
    int getObjectInMap(QPoint point);

    void step();

    int isBuild();

private slots:
  void contextMenuRequested(QPoint point)
  {
      QPoint globalPoint = mapToGlobal(point);
      curPos.setX(point.x());
      curPos.setY(point.y());
      int objId = getObjectInMap(point);
      switch (objId)
      {
          case 0: m_pContextMenu->popup(globalPoint);
              break;
          case 1: m_pUnit->popup(globalPoint);
            break;
          case 2: m_pBuild->popup(globalPoint);
            break;
      }

  };

  void addBuild();
  void addLink();
  void addTrain();

  void stopUnit()
  {
      stopUnitMove = true;
  };

  void startUnit()
  {
      stopUnitMove = false;
  };

private:
    Ui::MainWindow *ui;

    int coord[2], init_coord[2];
    double left_path[2];
    bool stop;
    QString str;

  QMenu*   m_pContextMenu;
  QAction* m_pAddBuild;

  QMenu*   m_pUnit;
  QAction* m_pActionStop;
  QAction* m_pActionStart;

  QMenu*   m_pBuild;
  QAction* m_pAddLink;
  QAction* m_pAddTrain;

  bool stopUnitMove;

  unsigned int state;
  unsigned int fromBuild;

  QPoint curPos;
};

#endif // MAINWINDOW_H
