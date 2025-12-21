#include "DataEditorWidget.h"
#include "ui_DataEditorWidget.h"

DataEditorWidget::DataEditorWidget(QWidget *parent)
   : QWidget(parent)
   , ui(new Ui::DataEditorWidget)
{
   ui->setupUi(this);
}

DataEditorWidget::~DataEditorWidget()
{
   delete ui;
}

void DataEditorWidget::SetModel(QAbstractTableModel* model)
{
   ui->tableView->setModel(model);
   ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

   auto *header = ui->tableView->horizontalHeader();
   //header->setSectionResizeMode(0, QHeaderView::ResizeToContents);
   //header->setSectionResizeMode(1, QHeaderView::Stretch);
}
