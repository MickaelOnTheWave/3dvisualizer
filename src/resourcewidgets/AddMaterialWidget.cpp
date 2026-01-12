#include "AddMaterialWidget.h"
#include "ui_AddMaterialWidget.h"

AddMaterialWidget::AddMaterialWidget(QWidget *parent)
   : AddResourceWidget(parent)
   , ui(new Ui::AddMaterialWidget)
{
   ui->setupUi(this);
}

AddMaterialWidget::~AddMaterialWidget()
{
   delete ui;
}

QStringList AddMaterialWidget::AddDataToRenderer(GlRenderer* renderer)
{
   const std::string materialName = ui->nameEdit->text().toUtf8().constData();

   auto material = new Material(materialName);
   material->diffuseTextureId = 1;
   material->specularTextureId = 1;
   material->shininess = ui->shininessSpin->value();

   renderer->AddMaterial(material);
   //return {ui->nameEdit->text()};
   return {};
}
