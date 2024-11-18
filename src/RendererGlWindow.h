#ifndef RENDERERGLWINDOW_H
#define RENDERERGLWINDOW_H

#include <QOpenGLWidget>

class RendererGlWindow : public QOpenGLWidget
{
public:
   RendererGlWindow(QWidget* parent);

protected:
   void initializeGL() override;
   void resizeGL(int w, int h) override;
   void paintGL() override;
};

#endif // RENDERERGLWINDOW_H
