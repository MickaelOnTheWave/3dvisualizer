#ifndef DATAEDITORWIDGET_H
#define DATAEDITORWIDGET_H

#include <QWidget>

#include <QAbstractTableModel>

namespace Ui {
class DataEditorWidget;
}

class DataEditorWidget : public QWidget
{
   Q_OBJECT

public:
   explicit DataEditorWidget(QWidget *parent = nullptr);
   ~DataEditorWidget();

   void SetModel(QAbstractTableModel* model);


private:
   Ui::DataEditorWidget *ui;
};

#endif // DATAEDITORWIDGET_H
