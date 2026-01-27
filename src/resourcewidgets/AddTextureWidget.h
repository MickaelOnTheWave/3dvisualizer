#ifndef ADDTEXTUREWIDGET_H
#define ADDTEXTUREWIDGET_H

#include "AddResourceWidget.h"

#include "renderers/AbstractRenderer.h"

namespace Ui {
class AddTextureWidget;
}

class AddTextureWidget : public AddResourceWidget
{
   Q_OBJECT

public:
   explicit AddTextureWidget(QWidget *parent = nullptr);
   ~AddTextureWidget();

   void AddDataToScene(Scene* scene) override;

private slots:
   void OnChoosePlainColor();
   void OnChooseFile();

private:
   Ui::AddTextureWidget *ui;
};

#endif // ADDTEXTUREWIDGET_H
