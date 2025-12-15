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
    const std::vector<unsigned int> textures = renderer->GetTextures();
    ui->texturesView->setRowCount(textures.size());
    ui->texturesView->setColumnCount(2);

    int i=0;
    for (const auto textureId : textures)
    {
        auto rowId = new QTableWidgetItem(QString::number(textureId));
        auto rowName = new QTableWidgetItem("Undefined");
        ui->texturesView->setItem(i, 0, rowId);
        ui->texturesView->setItem(i, 1, rowName);
        ++i;
    }

    const std::vector<Material*> materials = renderer->GetMaterials();
    ui->materialsView->setRowCount(materials.size());
    ui->materialsView->setColumnCount(4);

    i=0;
    for (const auto material : materials)
    {
        auto rowName = new QTableWidgetItem(QString::fromLatin1(material->name));
        ui->materialsView->setItem(i, 0, rowName);
        auto rowDiffuse = new QTableWidgetItem(QString::number(material->diffuseTextureId));
        ui->materialsView->setItem(i, 1, rowDiffuse);
        auto rowSpecular = new QTableWidgetItem(QString::number(material->specularTextureId));
        ui->materialsView->setItem(i, 2, rowSpecular);
        auto rowShininess = new QTableWidgetItem(QString::number(material->shininess));
        ui->materialsView->setItem(i, 3, rowShininess);
        ++i;
    }
}
