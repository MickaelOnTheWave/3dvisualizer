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
   AddEditor(ui->objectsBox, &objectModel, new AddTextureWidget());
   AddEditor(ui->instancesBox, &instanceModel, new AddTextureWidget());
}

RenderDataWidget::~RenderDataWidget()
{
   delete ui;
}

void RenderDataWidget::SetRenderer(GlRenderer* _renderer)
{
   renderer = _renderer;
   for (const auto editor : editorWidgets)
      editor->SetRenderer(renderer);
   OnUpdateData();
}

void RenderDataWidget::OnUpdateData()
{
   textureModel.Reset(renderer->GetTextures());
   materialModel.Reset(renderer->GetMaterials());
   objectModel.Reset(renderer->ComputeRenderObjectsList());
   instanceModel.Reset(renderer->ComputeInstancesList());
}

void RenderDataWidget::AddEditor(QGroupBox* container, IDataModel* model, AddResourceWidget* resourceWidget)
{
   auto editorWidget = new DataEditorWidget(model, resourceWidget);
   container->layout()->addWidget(editorWidget);
   editorWidgets.push_back(editorWidget);
}
