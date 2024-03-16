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
        koef = 2.;//1.3;
#endif

        double lenghtX = abs(MaxX - MinX) / koef;
        double lenghtY = abs(MaxY - MinY) / koef;
        double ZoomMinX = MinX;
        double ZoomMaxX = MaxX;
        double ZoomMinY = MinY;
        double ZoomMaxY = MaxY;

        if(event->angleDelta().y() > 0)
        {
            //ZoomMinX = cur.x() - (cur.x() - MinX) / koef;
            //ZoomMaxX = cur.x() - (cur.x() - MaxX) / koef;
            //ZoomMinY = cur.y() - (cur.y() - MinY) / koef;
            //ZoomMaxY = cur.y() - (cur.y() - MaxY) / koef;

            ZoomMinX /= koef;
            ZoomMaxX /= koef;
            ZoomMinY /= koef;
            ZoomMaxY /= koef;
        }
        else
        {
            //ZoomMinX = cur.x() - (cur.x() - MinX) * koef;
            //ZoomMaxX = cur.x() - (cur.x() - MaxX) * koef;
            //ZoomMinY = cur.y() - (cur.y() - MinY) * koef;
            //ZoomMaxY = cur.y() - (cur.y() - MaxY) * koef;

            ZoomMinX *= koef;
            ZoomMaxX *= koef;
            ZoomMinY *= koef;
            ZoomMaxY *= koef;
        }

        axisX->setRange(ZoomMinX, ZoomMaxX);
        axisY->setRange(ZoomMinY, ZoomMaxY);
    }
}

void CustomView::mousePressEvent(QMouseEvent *event)
{
    if (0)
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
    if (0)
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
