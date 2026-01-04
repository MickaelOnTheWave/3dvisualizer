#ifndef ADDTEXTUREWIDGET_H
#define ADDTEXTUREWIDGET_H

#include "AddResourceWidget.h"

namespace Ui {
class AddTextureWidget;
}

class AddTextureWidget : public AddResourceWidget
{
   Q_OBJECT

public:
   explicit AddTextureWidget(QWidget *parent = nullptr);
   ~AddTextureWidget();

   QStringList AddDataToRenderer(GlRenderer* renderer) override;

private slots:
   void OnChoosePlainColor();
   void OnChooseFile();

private:
   Ui::AddTextureWidget *ui;
};

#endif // ADDTEXTUREWIDGET_H
