#include "customview.h"

CustomView::CustomView(QWidget* parent) : QChartView(parent)
{

}

void CustomView::zoomIt(bool zoom)
{
    itZoom = zoom;
}

void CustomView::wheelEvent(QWheelEvent *event)
{
    if (itZoom)
    {
        QPointF cur = this->chart()->mapToValue(event->position());

        QValueAxis *axisX = (QValueAxis*)this->chart()->axes(Qt::Horizontal).at(0);
        QValueAxis *axisY = (QValueAxis*)this->chart()->axes(Qt::Vertical).at(0);

        MinX = axisX->min();
        MaxX = axisX->max();
        MinY = axisY->min();
        MaxY = axisY->max();

        double koef;
#ifdef __APPLE__
        koef = 1.1;
#else
        koef = 1.5;
#endif

        double ZoomMinX;
        double ZoomMaxX;
        double ZoomMinY;
        double ZoomMaxY;

        if(event->angleDelta().y() > 0)
        {
            ZoomMinX = cur.x() - (cur.x() - MinX) / koef;
            ZoomMaxX = cur.x() - (cur.x() - MaxX) / koef;
            ZoomMinY = cur.y() - (cur.y() - MinY) / koef;
            ZoomMaxY = cur.y() - (cur.y() - MaxY) / koef;
        }
        else
        {
            ZoomMinX = cur.x() - (cur.x() - MinX) * koef;
            ZoomMaxX = cur.x() - (cur.x() - MaxX) * koef;
            ZoomMinY = cur.y() - (cur.y() - MinY) * koef;
            ZoomMaxY = cur.y() - (cur.y() - MaxY) * koef;
        }

        axisX->setRange(ZoomMinX, ZoomMaxX);
        axisY->setRange(ZoomMinY, ZoomMaxY);
    }
}

void CustomView::mousePressEvent(QMouseEvent *event)
{
    if (itZoom)
    {
        if (event->button() == Qt::LeftButton)
        {
            oldPoint = event->pos();
            isPress = true;
        }
    }
}

void CustomView::mouseMoveEvent(QMouseEvent *event)
{
    if (itZoom)
    {
        if(isPress)
        {
            QPoint pointDiff = event->pos() - oldPoint;
            this->chart()->scroll(-pointDiff.x(), pointDiff.y());
        }

        oldPoint = event->pos();
    }
}

void CustomView::mouseReleaseEvent(QMouseEvent *event)
{
    isPress = false;
}
