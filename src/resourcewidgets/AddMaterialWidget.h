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

   QStringList AddDataToRenderer(GlRenderer* renderer) override;

private:
   Ui::AddMaterialWidget *ui;
};

#endif // ADDMATERIALWIDGET_H
