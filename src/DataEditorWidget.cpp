#include "DataEditorWidget.h"
#include "ui_DataEditorWidget.h"

#include "GenericDialog.h"

// TEMP
#include "resourcewidgets/AddTextureWidget.h"

DataEditorWidget::DataEditorWidget(IDataModel* model, QWidget* parent)
   : QWidget(parent)
   , ui(new Ui::DataEditorWidget)
{
   ui->setupUi(this);
   SetModel(model);

   connect(ui->addButton, &QPushButton::clicked, this, &DataEditorWidget::OnAddResource);
}

DataEditorWidget::~DataEditorWidget()
{
   delete ui;
}

void DataEditorWidget::OnAddResource()
{
   auto contentWidget = new AddTextureWidget();
   auto addResourceWidget = new GenericDialog(contentWidget, true, this);
   addResourceWidget->setMinimumSize(contentWidget->size());

   connect(addResourceWidget, &QDialog::accepted, this, &DataEditorWidget::OnNewResourceConfirmed);
   connect(addResourceWidget, &QDialog::rejected, [addResourceWidget]() {
      addResourceWidget->close();
   });

   addResourceWidget->show();
   addResourceWidget->raise();
   addResourceWidget->activateWindow();
}

void DataEditorWidget::OnNewResourceConfirmed()
{

}

void DataEditorWidget::SetModel(IDataModel* model)
{
   ui->tableView->setModel(model);
   ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

   auto *header = ui->tableView->horizontalHeader();
   for (int i=0; i<model->rowCount(); ++i)
      header->setSectionResizeMode(i, model->GetSizingAtColumn(i));
}
