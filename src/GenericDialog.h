#ifndef GENERICDIALOG_H
#define GENERICDIALOG_H

#include <QDialog>

namespace Ui {
class GenericDialog;
}

class GenericDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GenericDialog(QWidget* contentWidget, bool showCloseButtons, QWidget *parent = nullptr);
    ~GenericDialog();

private:
    Ui::GenericDialog *ui;
};

#endif // GENERICDIALOG_H
