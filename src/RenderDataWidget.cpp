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
   FillTextures();
   FillMaterials();
   FillObjects();
   FillInstances();
}

void RenderDataWidget::FillTextures()
{
   textureModel.Reset(renderer->GetTextures());
}

void RenderDataWidget::FillMaterials()
{
   materialModel.Reset(renderer->GetMaterials());
}

void RenderDataWidget::FillObjects()
{
   objectModel.Reset(renderer->ComputeRenderObjectsList());
}

void RenderDataWidget::FillInstances()
{
   instanceModel.Reset(renderer->ComputeInstancesList());
}

void RenderDataWidget::AddToTable(QTableWidget* table, const int row, const int column, const int data) const
{
    AddToTable(table, row, column, QString::number(data));
}

void RenderDataWidget::AddToTable(QTableWidget* table, const int row, const int column, const std::string& data) const
{
    AddToTable(table, row, column, QString::fromLatin1(data));
}

void RenderDataWidget::AddToTable(QTableWidget* table, const int row, const int column, const QString& label) const
{
    auto rowObject = new QTableWidgetItem(label);
    table->setItem(row, column, rowObject);
}
