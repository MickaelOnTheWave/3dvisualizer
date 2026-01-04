#include "DataEditorWidget.h"
#include "ui_DataEditorWidget.h"

#include "GenericDialog.h"

DataEditorWidget::DataEditorWidget(IDataModel* _model, AddResourceWidget* _resourceWidget, QWidget* parent)
   : QWidget(parent)
   , ui(new Ui::DataEditorWidget),
   model(_model),
   resourceWidget(_resourceWidget)
{
   ui->setupUi(this);
   InitializeModel();

   connect(ui->addButton, &QPushButton::clicked, this, &DataEditorWidget::OnAddResource);
}

DataEditorWidget::~DataEditorWidget()
{
   delete ui;
}

void DataEditorWidget::SetRenderer(GlRenderer* _renderer)
{
   renderer = _renderer;
}

void DataEditorWidget::OnAddResource()
{
   auto resourceDialog= new GenericDialog(resourceWidget, true, this);
   resourceDialog->setMinimumSize(resourceWidget->size());

   connect(resourceDialog, &QDialog::accepted, [this, resourceDialog]() {
      OnNewResourceConfirmed();
      resourceDialog->close();
   });
   connect(resourceDialog, &QDialog::rejected, [resourceDialog]() {
      resourceDialog->close();
   });

   resourceDialog->show();
   resourceDialog->raise();
   resourceDialog->activateWindow();
}

void DataEditorWidget::OnNewResourceConfirmed()
{
   const QStringList modelData = resourceWidget->AddDataToRenderer(renderer);
   AddToModel(modelData);
}

void DataEditorWidget::InitializeModel()
{
   ui->tableView->setModel(model);
   ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

   auto *header = ui->tableView->horizontalHeader();
   for (int i=0; i<model->rowCount(); ++i)
      header->setSectionResizeMode(i, model->GetSizingAtColumn(i));
}

void DataEditorWidget::AddToModel(const QStringList rowData)
{
   const int rowIndex = model->rowCount();
   model->insertRow(rowIndex);

   for (int i=0; i<rowData.count(); ++i)
   {
      const QModelIndex index = model->index(rowIndex, i);
      model->setData(index, rowData[i]);
   }
}
