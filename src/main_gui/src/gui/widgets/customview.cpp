#include "customview.h"

CustomView::CustomView(QWidget *parent) : QGraphicsView(parent)
{
  sceene = new QGraphicsScene(this);
  setScene(sceene);
}

CustomView::~CustomView()
{
  if (mySelection) {
    sceene->removeItem(mySelection);
    delete mySelection;
  }
  setScene(nullptr);
  delete sceene;
}

void CustomView::wheelEvent(QWheelEvent *event)
{
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    double scaleFactor = 1.15;
    if (event->delta() > 0)
    {
        scale(scaleFactor,  scaleFactor);
    } else {
      scale(1 / scaleFactor,  1 / scaleFactor);
    }
}

void CustomView::mouseMoveEvent(QMouseEvent *event)
{
	QGraphicsView::mouseMoveEvent(event);
	if (actType != 3 || !mySelection) return;
	QPointF mousePosition2 = mapToScene(event->pos());
	qreal x, y, width, height;	
	if (mousePosition2.x() > mousePosition.x()) { x = mousePosition.x(); width = mousePosition2.x() - x; }
	else { x = mousePosition2.x(); width = mousePosition.x() - x; }
	if (mousePosition2.y() > mousePosition.y()) { y = mousePosition.y(); height = mousePosition2.y() - y; }
	else { y = mousePosition2.y(); height = mousePosition.y() - y; }
	mySelection->setRect(x, y, width, height);
}

void CustomView::mousePressEvent(QMouseEvent *event)
{	
    mousePosition = mapToScene(event->pos());
    if (actType<3)
    { //
      //    myDialog->bacteriaColor(mousePosition.x(), mousePosition.y(), actType);
    } else {
		mySelection = new QGraphicsRectItem(mousePosition.x(), mousePosition.y(), 0, 0);
		mySelection->setPen(QPen(Qt::yellow));
		//mySelection->setZValue(333);		
    sceene->addItem(mySelection);
		mySelection->show();
	}
}

void CustomView::mouseReleaseEvent(QMouseEvent *event)
{
    QPointF SecondMousePosition = mapToScene(event->pos());
  if (3 == actType && mySelection)
	{
    sceene->removeItem(mySelection);
		delete mySelection;
    mySelection = nullptr;
    //myDialog->changeImage(mousePosition.x(), mousePosition.y(), SecondMousePosition.x(), SecondMousePosition.y());
	}
}


void CustomView::showImg(ITask1_Result *img)
{
  if (ITask1_Result::isValid(img)
      && img->mat_cols > 0 && img->mat_rows > 0 && img->mat_data)
  {
    QImage imgIn= QImage(img->mat_data, img->mat_cols, img->mat_rows, QImage::Format_RGB888);
    if (curImg)
    {
       sceene->removeItem(curImg); delete curImg;
    }
    curImg = new QGraphicsPixmapItem(QPixmap::fromImage(imgIn));
    sceene->addItem(curImg);
    sceene->setSceneRect(0, 0, img->mat_cols, img->mat_rows);
    setScene(sceene);
    fitInView(0, 0, img->mat_cols, img->mat_rows, Qt::KeepAspectRatio);
        //ui->edWidth->setText(QString::number(sweets->max_x+1));
        //ui->edHeight->setText(QString::number(sweets->max_y+1));
        //ui->edBackColor->setText(QString::number(sweets->backColor));
  }
} // showImg
