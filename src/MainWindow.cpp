#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include "RenderDataWidget.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->opengl);

    connect(ui->actionOpenRenderData, &QAction::triggered, this, &MainWindow::OnActionOpenRenderData);

    connect(ui->openGLWidget, &RendererGlWindow::RendererError, this, &MainWindow::OnRendererError);
    connect(ui->animateBox, &QCheckBox::stateChanged, ui->openGLWidget, &RendererGlWindow::SetAnimation);
    connect(ui->distanceSlider, &QSlider::sliderMoved, this, &MainWindow::OnCameraDistanceChange);
}

MainWindow::~MainWindow()
{
   delete ui;
}

void MainWindow::OnRendererError(const QString& message)
{
    ui->errorMessage->setText(message);
    ui->stackedWidget->setCurrentWidget(ui->errors);
}

void MainWindow::OnCameraDistanceChange(const int distance)
{
    const float sourceRange = ui->distanceSlider->maximum() - ui->distanceSlider->minimum();
    const float sourceMiddle = ui->distanceSlider->minimum() + sourceRange / 2.f;
    const float destinationRange = 0.01f;
    const float destinationMiddle = 4.0f;
    const float destinationDistance = ((distance - ui->distanceSlider->minimum()) / sourceRange) * destinationRange + (destinationMiddle - destinationRange);
    ui->openGLWidget->SetCameraDistance(0.1f);
}

void MainWindow::OnActionOpenRenderData()
{
    if (!renderDataWidget)
        renderDataWidget = new GenericDialog(new RenderDataWidget(), this);
    renderDataWidget->show();
    renderDataWidget->raise();
    renderDataWidget->activateWindow();
}

