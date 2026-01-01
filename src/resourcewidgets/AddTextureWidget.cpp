#include "AddTextureWidget.h"
#include "ui_AddTextureWidget.h"

AddTextureWidget::AddTextureWidget(QWidget *parent)
   : AddResourceWidget(parent)
   , ui(new Ui::AddTextureWidget)
{
   ui->setupUi(this);
}

AddTextureWidget::~AddTextureWidget()
{
   delete ui;
}

QStringList AddTextureWidget::AddDataToRenderer(GlRenderer* renderer)
{
   const std::string textureName = ui->nameEdit->text().toUtf8().constData();

   ImageData imageData;
   const unsigned int textureId = renderer->AddTexture(imageData, textureName);
   return {QString::number(textureId), ui->nameEdit->text()};
}
