#include "AddObjectWidget.h"
#include "ui_AddObjectWidget.h"

#include "objects/GlRenderCube.h"
#include "objects/GlRenderPlane.h"
#include "objects/GlRenderSpherePolar.h"

AddObjectWidget::AddObjectWidget(QWidget *parent)
   : AddResourceWidget(parent)
   , ui(new Ui::AddObjectWidget)
{
   ui->setupUi(this);
}

AddObjectWidget::~AddObjectWidget()
{
   delete ui;
}

void AddObjectWidget::AddDataToScene(Scene* scene)
{
   const std::string objectName = ui->nameEdit->text().toUtf8().constData();

   auto modelInstance = new ModelInstance("New Instance");

   const unsigned int modelId =999;
   modelInstance->SetModelId(modelId);
   //Material* material = renderer->GetMaterial(ui->materialBox->value());

/*   if (ui->typeCombo->currentText() == "Cube")
   {
      auto object = new GlRenderCube(material, objectName);
   }
   else if (ui->typeCombo->currentText() == "Plane")
   {
      auto object = new GlRenderPlane(material);
   }
   else if (ui->typeCombo->currentText() == "Sphere")
   {
      auto object = new GlRenderSpherePolar(material);
   }*/


   scene->AddInstance(modelInstance);
}
