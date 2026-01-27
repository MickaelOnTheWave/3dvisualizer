#ifndef ADDOBJECTWIDGET_H
#define ADDOBJECTWIDGET_H

#include "AddResourceWidget.h"

#include "scene/Scene.h"

namespace Ui {
class AddObjectWidget;
}

class AddObjectWidget : public AddResourceWidget
{
   Q_OBJECT

public:
   explicit AddObjectWidget(QWidget *parent = nullptr);
   virtual ~AddObjectWidget();

   void AddDataToScene(Scene* _scene) override;

private:
   Ui::AddObjectWidget *ui;
};

#endif // ADDOBJECTWIDGET_H
