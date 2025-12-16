#include "RenderDataWidget.h"
#include "ui_RenderDataWidget.h"

RenderDataWidget::RenderDataWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RenderDataWidget)
{
    ui->setupUi(this);

    ui->texturesView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->materialsView->setEditTriggers(QAbstractItemView::NoEditTriggers);
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
   const std::vector<GlTexture> textures = renderer->GetTextures();
   ui->texturesView->setRowCount(textures.size());
   ui->texturesView->setColumnCount(2);

   int i=0;
   for (const auto texture : textures)
   {
      AddToTable(ui->texturesView, i, 0, texture.textureId);
      AddToTable(ui->texturesView, i, 1, texture.GetName());
      ++i;
   }
}

void RenderDataWidget::FillMaterials()
{
    const std::vector<Material*> materials = renderer->GetMaterials();
    ui->materialsView->setRowCount(materials.size());
    ui->materialsView->setColumnCount(4);

    int i=0;
    for (const auto material : materials)
    {
        AddToTable(ui->materialsView, i, 0, material->GetName());
        AddToTable(ui->materialsView, i, 1, material->diffuseTextureId);
        AddToTable(ui->materialsView, i, 2, material->specularTextureId);
        AddToTable(ui->materialsView, i, 3, material->shininess);
        ++i;
    }
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
