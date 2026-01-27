#ifndef DATAEDITORWIDGET_H
#define DATAEDITORWIDGET_H

#include <memory>
#include <QWidget>

#include "models/AbstractDataModel.h"
#include "renderers/AbstractRenderer.h"
#include "resourcewidgets/AddResourceWidget.h"

namespace Ui {
class DataEditorWidget;
}

class DataEditorWidget : public QWidget
{
   Q_OBJECT

public:
   explicit DataEditorWidget(IDataModel* _model,
                             AddResourceWidget* _resourceWidget,
                             QWidget *parent = nullptr);
   ~DataEditorWidget();

   void SetScene(Scene* _scene);

signals:
   void RequestDataRefresh();

private slots:
   void OnAddResource();
   void OnNewResourceConfirmed();

private:
   void InitializeModel();

   Ui::DataEditorWidget *ui;
   AddResourceWidget* resourceWidget;
   IDataModel* model;
   Scene* scene;
};

#endif // DATAEDITORWIDGET_H
