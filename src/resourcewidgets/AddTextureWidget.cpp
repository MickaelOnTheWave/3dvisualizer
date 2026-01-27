#include "AddTextureWidget.h"
#include "ui_AddTextureWidget.h"

#include <QColorDialog>
#include <QFileDialog>

AddTextureWidget::AddTextureWidget(QWidget *parent)
   : AddResourceWidget(parent)
   , ui(new Ui::AddTextureWidget)
{
   ui->setupUi(this);

   connect(ui->colorButton, &QPushButton::clicked, this, &AddTextureWidget::OnChoosePlainColor);
   connect(ui->fileButton, &QPushButton::clicked, this, &AddTextureWidget::OnChooseFile);
}

AddTextureWidget::~AddTextureWidget()
{
   delete ui;
}

void AddTextureWidget::AddDataToScene(Scene* scene)
{
   const std::string textureName = ui->nameEdit->text().toUtf8().constData();

   // TODO Get real data
   ImageData imageData;
   scene->AddTexture(Vector3(0, 1, 1), textureName);
}

void AddTextureWidget::OnChoosePlainColor()
{
   const QColor color = QColorDialog::getColor(Qt::black, this, "Select the color");

   const int iconSize = 16;
   QPixmap pixmap(iconSize, iconSize);
   pixmap.fill(color);
   ui->previewLabel->setPixmap(pixmap);
}

void AddTextureWidget::OnChooseFile()
{
   const QString file = QFileDialog::getOpenFileName(this, "Select the texture file");

   QPixmap pixmap(file);
   ui->previewLabel->setPixmap(pixmap);
}

