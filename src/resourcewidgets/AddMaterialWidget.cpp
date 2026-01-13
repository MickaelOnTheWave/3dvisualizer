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

void AddMaterialWidget::AddDataToRenderer(GlRenderer* renderer)
{
   const std::string materialName = ui->nameEdit->text().toUtf8().constData();

   auto material = new Material(materialName);
   material->diffuseTextureId = ui->diffuseBox->value();
   material->specularTextureId = ui->specularBox->value();
   material->shininess = ui->shininessSpin->value();

   renderer->AddMaterial(material);
}
