#ifndef ADDTEXTUREWIDGET_H
#define ADDTEXTUREWIDGET_H

#include <QWidget>

namespace Ui {
class AddTextureWidget;
}

class AddTextureWidget : public QWidget
{
   Q_OBJECT

public:
   explicit AddTextureWidget(QWidget *parent = nullptr);
   ~AddTextureWidget();

private:
   Ui::AddTextureWidget *ui;
};

#endif // ADDTEXTUREWIDGET_H
