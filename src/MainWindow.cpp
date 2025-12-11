#include "MainWindow.h"
#include "./ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->opengl);

    connect(ui->openGLWidget, &RendererGlWindow::RendererError, this, &MainWindow::OnRendererError);
    connect(ui->animateBox, &QCheckBox::stateChanged, ui->openGLWidget, &RendererGlWindow::SetAnimation);
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
