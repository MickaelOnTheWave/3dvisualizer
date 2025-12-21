#include "RenderDataWidget.h"
#include "ui_RenderDataWidget.h"

#include "DataEditorWidget.h"

RenderDataWidget::RenderDataWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RenderDataWidget)
{
   ui->setupUi(this);

   auto materialEditor = new DataEditorWidget();
   materialEditor->SetModel(&materialModel);
   ui->materialsBox->layout()->addWidget(materialEditor);

   ui->texturesView->setModel(&textureModel);
   ui->texturesView->setEditTriggers(QAbstractItemView::NoEditTriggers);

   auto *header = ui->texturesView->horizontalHeader();
   header->setSectionResizeMode(0, QHeaderView::ResizeToContents);
   header->setSectionResizeMode(1, QHeaderView::Stretch);
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
    const std::vector<GlRenderObject*> objects = renderer->ComputeRenderObjectsList();
    ui->objectsView->setRowCount(objects.size());
    ui->objectsView->setColumnCount(2);

    int i=0;
    for (const auto obj : objects)
    {
        AddToTable(ui->objectsView, i, 0, obj->GetName());
        AddToTable(ui->objectsView, i, 1, obj->GetMaterial()->GetName());
        ++i;
    }
}

void RenderDataWidget::FillInstances()
{
    const std::vector<GlRenderedInstance*> instances = renderer->ComputeInstancesList();
    ui->instancesView->setRowCount(instances.size());
    ui->instancesView->setColumnCount(2);

    int i=0;
    for (const auto instance : instances)
    {
        AddToTable(ui->instancesView, i, 0, instance->GetName());
        AddToTable(ui->instancesView, i, 1, instance->GetRenderObject()->GetName());
        ++i;
    }
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
