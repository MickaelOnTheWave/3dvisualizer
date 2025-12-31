#include "DataEditorWidget.h"
#include "ui_DataEditorWidget.h"

DataEditorWidget::DataEditorWidget(IDataModel* model, QWidget* parent)
   : QWidget(parent)
   , ui(new Ui::DataEditorWidget)
{
   ui->setupUi(this);
   SetModel(model);
}

DataEditorWidget::~DataEditorWidget()
{
   delete ui;
}

void DataEditorWidget::SetModel(IDataModel* model)
{
   ui->tableView->setModel(model);
   ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

   auto *header = ui->tableView->horizontalHeader();
   for (int i=0; i<model->rowCount(); ++i)
      header->setSectionResizeMode(i, model->GetSizingAtColumn(i));
}
