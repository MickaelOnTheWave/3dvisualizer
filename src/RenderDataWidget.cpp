#include "RenderDataWidget.h"
#include "ui_RenderDataWidget.h"

#include "DataEditorWidget.h"

RenderDataWidget::RenderDataWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RenderDataWidget)
{
   ui->setupUi(this);

   ui->materialsBox->layout()->addWidget(new DataEditorWidget(&materialModel));
   ui->texturesBox->layout()->addWidget(new DataEditorWidget(&textureModel));
   ui->objectsBox->layout()->addWidget(new DataEditorWidget(&objectModel));
   ui->instancesBox->layout()->addWidget(new DataEditorWidget(&instanceModel));
}

RenderDataWidget::~RenderDataWidget()
{
   delete ui;
}

void RenderDataWidget::SetRenderer(GlRenderer* _renderer)
{
   renderer = _renderer;
   OnUpdateData();
}

void RenderDataWidget::OnUpdateData()
{
   textureModel.Reset(renderer->GetTextures());
   materialModel.Reset(renderer->GetMaterials());
   objectModel.Reset(renderer->ComputeRenderObjectsList());
   instanceModel.Reset(renderer->ComputeInstancesList());
}
