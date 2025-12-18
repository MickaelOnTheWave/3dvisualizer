#ifndef RENDERERGLWINDOW_H
#define RENDERERGLWINDOW_H

#include <glad/glad.h>
#include <QOpenGLWidget>
#include <QTimer>

#include "cameras/OrbitCamera.h"
#include "GlRenderer.h"

class RendererGlWindow : public QOpenGLWidget
{
    Q_OBJECT

public:
   RendererGlWindow(QWidget* parent);

   void SetRenderer(std::shared_ptr<GlRenderer> _renderer);

   void SetAnimation(const bool enabled);

signals:
   void RendererError(const QString& message);

protected:
   void initializeGL() override;
   void resizeGL(int w, int h) override;
   void paintGL() override;

private:
   void AddObjects();

   std::shared_ptr<GlRenderer> renderer;
   OrbitCamera* currentCamera;
   QTimer renderTimer;
   bool animate = true;
};

#endif // RENDERERGLWINDOW_H
