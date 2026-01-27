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

void AddMaterialWidget::AddDataToScene(Scene* scene)
{
   const std::string materialName = ui->nameEdit->text().toUtf8().constData();

   Material material(materialName);
   material.diffuseTextureId = ui->diffuseBox->value();
   material.specularTextureId = ui->specularBox->value();
   material.shininess = ui->shininessSpin->value();

   scene->AddMaterial(material);
}
