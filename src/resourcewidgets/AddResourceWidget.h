#ifndef ADDRESOURCEWIDGET_H
#define ADDRESOURCEWIDGET_H

#include <QWidget>

#include "GlRenderer.h"

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
    * add it to the renderer. It also knows which fields are used for display and
    * returns the relevant ones ready to add in a new row.
    *
    * @param renderer
    * @return The list of data fields to add in the views
    */
   virtual QStringList AddDataToRenderer(GlRenderer* renderer) = 0;
signals:
};

#endif // ADDRESOURCEWIDGET_H
