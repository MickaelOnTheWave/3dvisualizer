#ifndef DATAEDITORWIDGET_H
#define DATAEDITORWIDGET_H

#include <QWidget>

#include "models/AbstractDataModel.h"
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

   void SetRenderer(GlRenderer* _renderer);

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
   GlRenderer* renderer;
};

#endif // DATAEDITORWIDGET_H
