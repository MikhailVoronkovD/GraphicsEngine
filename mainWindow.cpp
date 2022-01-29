#include "mainWindow.h"
#include "paintWidget.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QPainter>
#include <QBrush>
#include <QDebug>

const int IdRole = Qt::UserRole;

MainWindow::MainWindow()

{
    paintWidget = new PaintWidget;

    figureComboBox = new QComboBox;
    figureComboBox->addItem("Line", PaintWidget::Line);
    figureComboBox->addItem("Points", PaintWidget::Points);
    figureComboBox->addItem("Polyline", PaintWidget::Polyline);
    figureComboBox->addItem("Polygon", PaintWidget::Polygon);
    figureComboBox->addItem("Rectangle", PaintWidget::Rect);
    figureComboBox->addItem("Rounded Rectangle", PaintWidget::RoundedRect);
    figureComboBox->addItem("Ellipse", PaintWidget::Ellipse);
    figureComboBox->addItem("Arc", PaintWidget::Arc);
    figureComboBox->addItem("Chord", PaintWidget::Chord);
    figureComboBox->addItem("Pie", PaintWidget::Pie);
    figureComboBox->addItem("Path", PaintWidget::Path);
    figureComboBox->addItem("Text", PaintWidget::Text);
    figureComboBox->addItem("Picture", PaintWidget::Pixmap);
    figureComboBox->addItem("Cube", PaintWidget::Cube);

    penWidthSpinBox = new QSpinBox;
    penWidthSpinBox->setRange(0, 10);
    penWidthSpinBox->setSpecialValueText("0");

    penStyleComboBox = new QComboBox;
    penStyleComboBox->addItem("Solid", static_cast<int>(Qt::SolidLine));
    penStyleComboBox->addItem("Dash", static_cast<int>(Qt::DashLine));
    penStyleComboBox->addItem("Dot", static_cast<int>(Qt::DotLine));
    penStyleComboBox->addItem("Dash Dot", static_cast<int>(Qt::DashDotLine));
    penStyleComboBox->addItem("Dash Dot Dot", static_cast<int>(Qt::DashDotDotLine));
    penStyleComboBox->addItem("None", static_cast<int>(Qt::NoPen));

    penCapComboBox = new QComboBox;
    penCapComboBox->addItem("Flat", Qt::FlatCap);
    penCapComboBox->addItem("Square", Qt::SquareCap);
    penCapComboBox->addItem("Round", Qt::RoundCap);

    penJoinComboBox = new QComboBox;
    penJoinComboBox->addItem("Miter", Qt::MiterJoin);
    penJoinComboBox->addItem("Bevel", Qt::BevelJoin);
    penJoinComboBox->addItem("Round", Qt::RoundJoin);

    brushStyleComboBox = new QComboBox;
    brushStyleComboBox->addItem("Linear Gradient", static_cast<int>(Qt::LinearGradientPattern));
    brushStyleComboBox->addItem("Radial Gradient", static_cast<int>(Qt::RadialGradientPattern));
    brushStyleComboBox->addItem(tr("Conical Gradient"), static_cast<int>(Qt::ConicalGradientPattern));
    brushStyleComboBox->addItem(tr("Texture"), static_cast<int>(Qt::TexturePattern));
    brushStyleComboBox->addItem(tr("Solid"), static_cast<int>(Qt::SolidPattern));
    brushStyleComboBox->addItem(tr("Horizontal"), static_cast<int>(Qt::HorPattern));
    brushStyleComboBox->addItem(tr("Vertical"), static_cast<int>(Qt::VerPattern));
    brushStyleComboBox->addItem(tr("Cross"), static_cast<int>(Qt::CrossPattern));
    brushStyleComboBox->addItem(tr("Backward Diagonal"), static_cast<int>(Qt::BDiagPattern));
    brushStyleComboBox->addItem(tr("Forward Diagonal"), static_cast<int>(Qt::FDiagPattern));
    brushStyleComboBox->addItem(tr("Diagonal Cross"), static_cast<int>(Qt::DiagCrossPattern));
    brushStyleComboBox->addItem(tr("Dense 1"), static_cast<int>(Qt::Dense1Pattern));
    brushStyleComboBox->addItem(tr("Dense 2"), static_cast<int>(Qt::Dense2Pattern));
    brushStyleComboBox->addItem(tr("Dense 3"), static_cast<int>(Qt::Dense3Pattern));
    brushStyleComboBox->addItem(tr("Dense 4"), static_cast<int>(Qt::Dense4Pattern));
    brushStyleComboBox->addItem(tr("Dense 5"), static_cast<int>(Qt::Dense5Pattern));
    brushStyleComboBox->addItem(tr("Dense 6"), static_cast<int>(Qt::Dense6Pattern));
    brushStyleComboBox->addItem(tr("Dense 7"), static_cast<int>(Qt::Dense7Pattern));
    brushStyleComboBox->addItem(tr("None"), static_cast<int>(Qt::NoBrush));

    createButton = new QPushButton("Create Figure");
    turnLeftButton = new QPushButton("Turn Left");
    turnRightButton = new QPushButton("Turn Right");
    zoomInButton = new QPushButton("Zoom In");
    zoomOutButton = new QPushButton("Zoom Out");
    animationButton = new QPushButton("Start animation");
    stopAnimationButton = new QPushButton("Stop animation");

    //---------------------------------------------------

    QHBoxLayout *mainLayout = new QHBoxLayout;

    QVBoxLayout *leftSide = new QVBoxLayout;
    leftSide->addWidget(paintWidget);
    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(turnLeftButton);
    buttonsLayout->addWidget(turnRightButton);
    buttonsLayout->addWidget(zoomInButton);
    buttonsLayout->addWidget(zoomOutButton);
    leftSide->addLayout(buttonsLayout);

    QVBoxLayout *rightSide = new QVBoxLayout;
    QFormLayout *controlsLayout = new QFormLayout;
    controlsLayout->addRow("Figure", figureComboBox);
    controlsLayout->addRow("Pen Width", penWidthSpinBox);
    controlsLayout->addRow("Pen Style", penStyleComboBox);
    controlsLayout->addRow("PenCap", penCapComboBox);
    controlsLayout->addRow("Pen Join", penJoinComboBox);
    controlsLayout->addRow("Brush Style", brushStyleComboBox);
    rightSide->addLayout(controlsLayout);
    rightSide->addWidget(animationButton);
    rightSide->addWidget(stopAnimationButton);
    rightSide->addWidget(createButton);

    mainLayout->addLayout(leftSide, 1);
    mainLayout->addLayout(rightSide);
    setLayout(mainLayout);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::animation);

    //------------------------------------------------------

    connect(figureComboBox, QOverload<int>::of(&QComboBox::activated), this, &MainWindow::figureChanged);
    connect(penWidthSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::penChanged);
    connect(penStyleComboBox, QOverload<int>::of(&QComboBox::activated), this, &MainWindow::penChanged);
    connect(penCapComboBox, QOverload<int>::of(&QComboBox::activated), this, &MainWindow::penChanged);
    connect(penJoinComboBox, QOverload<int>::of(&QComboBox::activated), this, &MainWindow::penChanged);
    connect(brushStyleComboBox, QOverload<int>::of(&QComboBox::activated), this, &MainWindow::brushChanged);
    connect(createButton, &QPushButton::clicked, this, &MainWindow::createFigure);
    connect(turnLeftButton, &QPushButton::clicked, this, &MainWindow::turnLeft);
    connect(turnRightButton, &QPushButton::clicked, this, &MainWindow::turnRight);
    connect(zoomInButton, &QPushButton::clicked, this, &MainWindow::zoomIncrease);
    connect(zoomOutButton, &QPushButton::clicked, this, &MainWindow::zoomDecrease);
    connect(animationButton, &QPushButton::clicked, this, &MainWindow::startAnimation);
    connect(stopAnimationButton, &QPushButton::clicked, this, &MainWindow::stopAnimation);

    figureChanged();
    penChanged();
    brushChanged();
    createFigure();
}

MainWindow::~MainWindow()
{
}

void MainWindow::figureChanged()
{
    PaintWidget::Figures figure = PaintWidget::Figures(
                figureComboBox->itemData(figureComboBox->currentIndex(), IdRole).toInt());
    paintWidget->setFigure(figure);
}

void MainWindow::penChanged()
{
    int width = penWidthSpinBox->value();
    Qt::PenStyle style = Qt::PenStyle(
                penStyleComboBox->itemData(penStyleComboBox->currentIndex(), IdRole).toInt());
    Qt::PenCapStyle cap = Qt::PenCapStyle(
                penCapComboBox->itemData(penCapComboBox->currentIndex(), IdRole).toInt());
    Qt::PenJoinStyle join = Qt::PenJoinStyle(
                penJoinComboBox->itemData(penJoinComboBox->currentIndex(), IdRole).toInt());

    paintWidget->setPen(QPen(Qt::black, width, style, cap, join));
}

void MainWindow::brushChanged()
{
    Qt::BrushStyle style = Qt::BrushStyle(
                brushStyleComboBox->itemData(brushStyleComboBox->currentIndex(), IdRole).toInt());

    if (style == Qt::LinearGradientPattern) {
        QLinearGradient linearGradient(0, 0, width(), height());
        linearGradient.setColorAt(0.0, Qt::red);
        linearGradient.setColorAt(0.2, Qt::green);
        linearGradient.setColorAt(1.0, Qt::blue);
        paintWidget->setBrush(linearGradient);

    } else if (style == Qt::RadialGradientPattern) {
        QRadialGradient radialGradient(width()/3, height()/2, width() / 2);
        radialGradient.setColorAt(0.0, Qt::red);
        radialGradient.setColorAt(0.2, Qt::green);
        radialGradient.setColorAt(1.0, Qt::blue);
        paintWidget->setBrush(radialGradient);
    } else if (style == Qt::ConicalGradientPattern) {
        QConicalGradient conicalGradient(50, 50, 120);
        conicalGradient.setColorAt(0.0, Qt::red);
        conicalGradient.setColorAt(0.2, Qt::green);
        conicalGradient.setColorAt(1.0, Qt::blue);
        paintWidget->setBrush(conicalGradient);
    } else if (style == Qt::TexturePattern) {
        paintWidget->setBrush(QBrush(QPixmap(":/res/images/picture.jpg")));
    } else {
        paintWidget->setBrush(QBrush(Qt::lightGray, style));
    }
}

void MainWindow::createFigure()
{
    paintWidget->restoreDefaults();
    paintWidget->update();
}

void MainWindow::turnLeft()
{
    paintWidget->setAngle(-10);
}

void MainWindow::turnRight()
{
    paintWidget->setAngle(10);
}

void MainWindow::zoomIncrease()
{
    paintWidget->setZoom(0.1);
}

void MainWindow::zoomDecrease()
{
    paintWidget->setZoom(-0.1);
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
    QPoint numDegrees = event->angleDelta() / 8;

    if (!numDegrees.isNull())
    {
        if(numDegrees.y() > 0)
        {
            zoomIncrease();
        }
        else
        {
            zoomDecrease();
        }
    }
    event->accept();
}

void MainWindow::animation()
{
    paintWidget->setAngle(1);
    if(paintWidget->getZoom() == 0.1 || paintWidget->getZoom() > 1)
        valueZoom *= -1;
    paintWidget->setZoom(valueZoom * 0.01);
}

void MainWindow::startAnimation()
{
    timer->start(30);
}

void MainWindow::stopAnimation()
{
    timer->stop();
}












