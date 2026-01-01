#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include <QColorDialog>
#include "RenderDataWidget.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
   ui->setupUi(this);
   ui->stackedWidget->setCurrentWidget(ui->opengl);

   CreateRenderer();
   ui->openGLWidget->SetRenderer(renderer);

   connect(ui->actionOpenRenderData, &QAction::triggered, this, &MainWindow::OnActionOpenRenderData);

   connect(ui->wireframeBox, &QCheckBox::toggled, this, &MainWindow::OnEnableWireframe);
   connect(ui->openGLWidget, &RendererGlWindow::RendererError, this, &MainWindow::OnRendererError);
   connect(ui->animateBox, &QCheckBox::stateChanged, ui->openGLWidget, &RendererGlWindow::SetAnimation);
   connect(ui->distanceSlider, &QSlider::sliderMoved, this, &MainWindow::OnCameraDistanceChange);
   connect(ui->colorButton, &QAbstractButton::pressed, this, &MainWindow::OnColorChoose);

   ui->openGLWidget->SetAnimation(ui->animateBox->isChecked());

   SetColorButtonIcon(Qt::black);
}

MainWindow::~MainWindow()
{
   delete ui;
}

void MainWindow::OnEnableWireframe(const bool enabled)
{
   renderer->EnableWireframeMode(enabled);
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
    camera->CloseOut(0.1f);
}

void MainWindow::OnColorChoose()
{
   const QColor backgroundColor = QColorDialog::getColor(Qt::black, this, "Select the background color");
   UpdateClearColor(backgroundColor);
}

void MainWindow::OnActionOpenRenderData()
{
    if (!renderDataWidget)
    {
        auto contentWidget = new RenderDataWidget();
        contentWidget->SetRenderer(renderer.get());
        renderDataWidget = new GenericDialog(contentWidget, false, this);
        renderDataWidget->setMinimumSize(contentWidget->size());
    }
    renderDataWidget->show();
    renderDataWidget->raise();
    renderDataWidget->activateWindow();
}

void MainWindow::CreateRenderer()
{
   camera = std::make_shared<OrbitCamera>(Vector3(0.f, 0.f, 0.f));
   camera->CloseOut(4.0f);
   camera->RotateInX(20.f);

   renderer = std::make_shared<GlRenderer>(camera.get());
}

void MainWindow::UpdateClearColor(const QColor color)
{
   renderer->SetClearColor(color.redF(), color.greenF(), color.blueF());
   SetColorButtonIcon(color);
}

void MainWindow::SetColorButtonIcon(const QColor color)
{
   const int iconSize = 16;
   QPixmap pixmap(iconSize, iconSize);
   pixmap.fill(color);
   ui->colorButton->setIcon(pixmap);
   ui->colorButton->setIconSize(QSize(iconSize, iconSize));
}

