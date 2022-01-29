#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QPen>
#include <QPainter>

class PaintWidget : public QWidget
{
    Q_OBJECT

public:
    enum Figures {Line, Points, Polyline, Polygon, Rect, RoundedRect, Ellipse, Arc,
                  Chord, Pie, Path, Text, Pixmap, Cube};

    explicit PaintWidget(QWidget* parent = nullptr);

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

    void restoreDefaults();
    double getZoom();

public slots:
    void setFigure(PaintWidget::Figures figure);
    void setPen(const QPen &pen);
    void setBrush(const QBrush &brush);
    void setAngle(int x);
    void setZoom(double x);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Figures figure;
    QPen pen;
    QBrush brush;
    QPixmap pixmap;
    int w = 0, h = 0;
    int turnAngle = 0;
    double zoom = 1;

};


#endif // PAINTWIDGET_H
