#ifndef ADDMATERIALWIDGET_H
#define ADDMATERIALWIDGET_H

#include "AddResourceWidget.h"

namespace Ui {
class AddMaterialWidget;
}

class AddMaterialWidget : public AddResourceWidget
{
   Q_OBJECT

public:
   explicit AddMaterialWidget(QWidget *parent = nullptr);
   ~AddMaterialWidget();

   void AddDataToScene(Scene* scene) override;

private:
   Ui::AddMaterialWidget *ui;
};

#endif // ADDMATERIALWIDGET_H
