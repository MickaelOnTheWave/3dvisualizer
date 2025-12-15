#include "GenericDialog.h"
#include "ui_GenericDialog.h"

GenericDialog::GenericDialog(QWidget* contentWidget, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::GenericDialog)
{
    ui->setupUi(this);

    contentWidget->setParent(this);
    setWindowTitle(contentWidget->windowTitle());
    ui->verticalLayout->addWidget(contentWidget);
}

GenericDialog::~GenericDialog()
{
    delete ui;
}
