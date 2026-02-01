#include "RenderDataWidget.h"
#include "ui_RenderDataWidget.h"

#include "resourcewidgets/AddMaterialWidget.h"
#include "resourcewidgets/AddTextureWidget.h"

RenderDataWidget::RenderDataWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RenderDataWidget)
{
   ui->setupUi(this);

   AddEditor(ui->materialsBox, &materialModel, new AddMaterialWidget());
   AddEditor(ui->texturesBox, &textureModel, new AddTextureWidget());
   AddEditor(ui->geometriesBox, &geometryModel, new AddTextureWidget());
   AddEditor(ui->modelsBox, &modelModel, new AddTextureWidget());
   AddEditor(ui->instancesBox, &instanceModel, new AddTextureWidget());
}

RenderDataWidget::~RenderDataWidget()
{
   delete ui;
}

void RenderDataWidget::SetScene(Scene* _scene)
{
   scene = _scene;
   for (const auto editor : editorWidgets)
      editor->SetScene(scene);
   OnUpdateData();
}

void RenderDataWidget::OnUpdateData()
{
   textureModel.Reset(scene->GetTextures());
   materialModel.Reset(scene->GetMaterials());
   geometryModel.Reset(scene->GetGeometries());
   modelModel.Reset(scene->GetModels());
   //objectModel.Reset(scene->ComputeRenderObjectsList());
   //instanceModel.Reset(scene->ComputeInstancesList());
}

void RenderDataWidget::AddEditor(QGroupBox* container, IDataModel* model, AddResourceWidget* resourceWidget)
{
   auto editorWidget = new DataEditorWidget(model, resourceWidget);
   container->layout()->addWidget(editorWidget);
   editorWidgets.push_back(editorWidget);

   connect(editorWidget, &DataEditorWidget::RequestDataRefresh, this, &RenderDataWidget::OnUpdateData);
}
