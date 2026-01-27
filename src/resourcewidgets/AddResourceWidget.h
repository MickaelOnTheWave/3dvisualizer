#ifndef ADDRESOURCEWIDGET_H
#define ADDRESOURCEWIDGET_H

#include <QWidget>

#include "scene/Scene.h"

class AddResourceWidget : public QWidget
{
public:
   explicit AddResourceWidget(QWidget *parent = nullptr)
      : QWidget(parent) {}
   virtual ~AddResourceWidget() = default;

   /**
    * @brief AddDataToRenderer
    * Adds the data in the widget as a new object in the renderer.
    * Each subclass knows how to create the object with the data from the UI and
    * add it to the renderer.
    *
    * @param renderer
    */
   virtual void AddDataToScene(Scene* scene) = 0;
signals:
};

#endif // ADDRESOURCEWIDGET_H
