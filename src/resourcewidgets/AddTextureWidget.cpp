#include "AddTextureWidget.h"
#include "ui_AddTextureWidget.h"

AddTextureWidget::AddTextureWidget(QWidget *parent)
   : QWidget(parent)
   , ui(new Ui::AddTextureWidget)
{
   ui->setupUi(this);
}

AddTextureWidget::~AddTextureWidget()
{
   delete ui;
}
