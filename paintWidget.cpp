#include "paintWidget.h"

#include <QPainter>
#include <QPainterPath>

PaintWidget::PaintWidget(QWidget* parent)
    :QWidget(parent)
{
    figure = Polygon;
    pixmap.load(":/res/images/c++.jpg");


    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
}

QSize PaintWidget::minimumSizeHint() const
{
    return QSize(200, 150);
}

QSize PaintWidget::sizeHint() const
{
    return QSize(800, 600);
}

void PaintWidget::setFigure(Figures figure)
{
    this->figure = figure;
}

void PaintWidget::setPen(const QPen &pen)
{
    this->pen = pen;
}

void PaintWidget::setBrush(const QBrush &brush)
{
    this->brush = brush;
}

void PaintWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    w = width();
    h = height();

    QPoint points[4] = {
        QPoint(w * 0.15, h * 0.1),
        QPoint(w * 0.65, h * 0.2),
        QPoint(w * 0.85, h * 0.85),
        QPoint(w * 0.1, h * 0.8)
    };

    QRect rect(w * 0.1, h * 0.1, w * 0.8, h * 0.8);

    QPainterPath path;
    path.moveTo(w * 0.1, h * 0.85);
    path.lineTo(w * 0.2, h * 0.15);
    path.cubicTo(w * 0.8, 0, w * 0.6, h * 0.5, w * 0.85, h * 0.85);

    QPainterPath cube;
    cube.moveTo(w * 0.1, h * 0.3);
    cube.lineTo(w * 0.3, h * 0.1);
    cube.lineTo(w * 0.9, h * 0.1);
    cube.lineTo(w * 0.7, h * 0.3);
    cube.lineTo(w * 0.1, h * 0.3);
    cube.lineTo(w * 0.1, h * 0.9);
    cube.lineTo(w * 0.3, h * 0.7);
    cube.lineTo(w * 0.9, h * 0.7);
    cube.lineTo(w * 0.7, h * 0.9);
    cube.lineTo(w * 0.1, h * 0.9);
    cube.moveTo(w * 0.3, h * 0.7);
    cube.lineTo(w * 0.3, h * 0.1);
    cube.moveTo(w * 0.9, h * 0.1);
    cube.lineTo(w * 0.9, h * 0.7);
    cube.moveTo(w * 0.7, h * 0.9);
    cube.lineTo(w * 0.7, h * 0.3);

    int angle = 30 * 16;
    int length = 120 * 16;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(palette().dark().color());
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(QRect(0, 0, width() - 1, height() - 1));

    painter.setPen(pen);
    painter.setBrush(brush);

    QFont font = painter.font();
    font.setPixelSize(50);
    painter.setFont(font);

    painter.translate(w / 2, h / 2);
    painter.rotate(turnAngle);
    painter.scale(zoom, zoom);

    painter.translate(-(w/2), -(h/2));

    switch(figure)
    {
    case Line:
        painter.drawLine(rect.bottomLeft(), rect.topRight());
        break;
    case Points:
        painter.drawPoints(points, 4);
        break;
    case Polyline:
        painter.drawPolyline(points, 4);
        break;
    case Polygon:
        painter.drawPolygon(points, 4);
        break;
    case Rect:
        painter.drawRect(rect);
        break;
    case RoundedRect:
        painter.drawRoundedRect(rect, 25, 25, Qt::RelativeSize);
        break;
    case Ellipse:
        painter.drawEllipse(rect);
        break;
    case Arc:
        painter.drawArc(rect, angle, length);
        break;
    case Chord:
        painter.drawChord(rect, angle, length);
        break;
    case Pie:
        painter.drawPie(rect, angle, length);
        break;
    case Path:
        painter.drawPath(path);
        break;
    case Text:
        painter.drawText(rect, Qt::AlignCenter, "C++ rulezzz!");
        break;
    case Pixmap:
        painter.drawPixmap(w * 0.4, h * 0.3, pixmap);
        break;
    case Cube:
        painter.drawPath(cube);
    }

    painter.restore();

}

void PaintWidget::setAngle(int x)
{
    turnAngle += x;
    update();
}

void PaintWidget::restoreDefaults()
{
    turnAngle = 0;
    zoom = 1;
}

void PaintWidget::setZoom(double x)
{
    zoom += x;
    if (zoom < 0.1)
        zoom = 0.1;
    update();
}

double PaintWidget::getZoom()
{
    return zoom;
}













