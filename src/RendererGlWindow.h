#ifndef RENDERERGLWINDOW_H
#define RENDERERGLWINDOW_H

#include <QOpenGLWidget>

#include "GlRenderer.h"

class RendererGlWindow : public QOpenGLWidget
{
public:
   RendererGlWindow(QWidget* parent);

   GlRenderer* GetRenderer();

protected:
   void initializeGL() override;
   void resizeGL(int w, int h) override;
   void paintGL() override;

   GlRenderer* renderer = nullptr;
};

#endif // RENDERERGLWINDOW_H
