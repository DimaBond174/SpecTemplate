#ifndef CUSTOMVIEW_H
#define CUSTOMVIEW_H

#include <QGraphicsView>
#include <QtWidgets>
#include <QWidget>
#include <i/itasks/itask1.h>

class CustomView : public QGraphicsView
{
public:
  CustomView(QWidget *parent = nullptr);
  virtual ~CustomView();

  void showImg(ITask1_Result *img);

  int actType  {  -1  };
  QPointF mousePosition;

protected:
  QGraphicsRectItem * mySelection  {  nullptr  };
  QGraphicsScene * sceene;
  QGraphicsPixmapItem *curImg {  nullptr  };
  virtual void wheelEvent(QWheelEvent *event);
  virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mousePressEvent(QMouseEvent *event) ;
  virtual void mouseReleaseEvent(QMouseEvent *event);
};

#endif // CUSTOMVIEW_H
