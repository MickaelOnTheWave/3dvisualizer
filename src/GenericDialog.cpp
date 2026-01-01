#include "GenericDialog.h"
#include "ui_GenericDialog.h"

GenericDialog::GenericDialog(QWidget* contentWidget, bool showCloseButtons, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::GenericDialog)
{
   ui->setupUi(this);

   contentWidget->setParent(this);
   setWindowTitle(contentWidget->windowTitle());
   ui->verticalLayout->insertWidget(0, contentWidget);
   ui->closeButtonBox->setVisible(showCloseButtons);

   connect(ui->closeButtonBox, &QDialogButtonBox::accepted, this, &GenericDialog::accepted);
   connect(ui->closeButtonBox, &QDialogButtonBox::rejected, this, &GenericDialog::rejected);
}

GenericDialog::~GenericDialog()
{
    delete ui;
}
