#ifndef DATAEDITORWIDGET_H
#define DATAEDITORWIDGET_H

#include <QWidget>

#include "models/AbstractDataModel.h"

namespace Ui {
class DataEditorWidget;
}

class DataEditorWidget : public QWidget
{
   Q_OBJECT

public:
   explicit DataEditorWidget(IDataModel* model, QWidget *parent = nullptr);
   ~DataEditorWidget();

private slots:
   void OnAddResource();
   void OnNewResourceConfirmed();

private:
   void SetModel(IDataModel* model);

   Ui::DataEditorWidget *ui;
};

#endif // DATAEDITORWIDGET_H
