#ifndef RENDERDATAWIDGET_H
#define RENDERDATAWIDGET_H

#include <QWidget>

#include <QTableWidget>

#include "GlRenderer.h"
#include "TextureModel.h"

namespace Ui {
class RenderDataWidget;
}

class RenderDataWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RenderDataWidget(QWidget *parent = nullptr);
    ~RenderDataWidget();

    void SetRenderer(GlRenderer* _renderer);

public slots:
    void OnUpdateData();

private:
    void FillTextures();
    void FillMaterials();
    void FillObjects();
    void FillInstances();

    void AddToTable(QTableWidget* table, const int row, const int column, const int data) const;
    void AddToTable(QTableWidget* table, const int row, const int column, const std::string& data) const;
    void AddToTable(QTableWidget* table, const int row, const int column, const QString& label) const;

    Ui::RenderDataWidget *ui;

    GlRenderer* renderer = nullptr;
    TextureModel textureModel;
};

#endif // RENDERDATAWIDGET_H
