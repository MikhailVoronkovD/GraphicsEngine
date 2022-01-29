#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "paintWidget.h"
#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QSpinBox>
#include <QCheckBox>
#include <QPushButton>
#include <QWheelEvent>
#include <QTimer>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

private slots:
    void figureChanged();
    void penChanged();
    void brushChanged();
    void createFigure();
    void turnLeft();
    void turnRight();
    void zoomIncrease();
    void zoomDecrease();
    void animation();
    void startAnimation();
    void stopAnimation();

private:
    PaintWidget *paintWidget;

    QComboBox *figureComboBox;
    QSpinBox *penWidthSpinBox;
    QComboBox *penStyleComboBox;
    QComboBox *penCapComboBox;
    QComboBox *penJoinComboBox;
    QComboBox *brushStyleComboBox;

    QPushButton *createButton;
    QPushButton *turnLeftButton;
    QPushButton *turnRightButton;
    QPushButton *zoomInButton;
    QPushButton *zoomOutButton;
    QPushButton *animationButton;
    QPushButton *stopAnimationButton;

    QTimer *timer;

    int valueZoom = -1;

protected:
    void wheelEvent (QWheelEvent *event);
};
#endif // MAINWINDOW_H
