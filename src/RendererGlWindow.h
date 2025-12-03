#ifndef RENDERERGLWINDOW_H
#define RENDERERGLWINDOW_H

#include <glad/glad.h>
#include <QOpenGLWidget>


#include "GlRenderer.h"

class RendererGlWindow : public QOpenGLWidget
{
    Q_OBJECT

public:
   RendererGlWindow(QWidget* parent);

   GlRenderer* GetRenderer();

signals:
   void RendererError(const QString& message);

protected:
   void initializeGL() override;
   void resizeGL(int w, int h) override;
   void paintGL() override;

   GlRenderer* renderer = nullptr;

private:
   void AddObjects();

};

#endif // RENDERERGLWINDOW_H
