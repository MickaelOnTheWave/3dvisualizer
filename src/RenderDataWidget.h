#ifndef RENDERDATAWIDGET_H
#define RENDERDATAWIDGET_H

#include <QWidget>

#include <QGroupBox>
#include <QTableWidget>

#include "DataEditorWidget.h"
#include "models/InstanceModel.h"
#include "models/MaterialModel.h"
#include "models/ObjectModel.h"
#include "models/TextureModel.h"
#include "renderers/AbstractRenderer.h"

namespace Ui {
class RenderDataWidget;
}

class RenderDataWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RenderDataWidget(QWidget *parent = nullptr);
    ~RenderDataWidget();

    void SetScene(Scene* _scene);

public slots:
    void OnUpdateData();

private:
    void AddEditor(QGroupBox* container,
                  IDataModel* model,
                  AddResourceWidget* resourceWidget);

    Ui::RenderDataWidget *ui;

    Scene* scene;
    TextureModel textureModel;
    MaterialModel materialModel;
    ObjectModel objectModel;
    InstanceModel instanceModel;

    std::vector<DataEditorWidget*> editorWidgets;
};

#endif // RENDERDATAWIDGET_H
