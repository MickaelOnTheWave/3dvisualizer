#ifndef RENDERERGLWINDOW_H
#define RENDERERGLWINDOW_H

#include <glad/glad.h>
#include <QOpenGLWidget>
#include <QTimer>

#include "GlRenderer.h"
#include "cameras/OrbitCamera.h"

class RendererGlWindow : public QOpenGLWidget
{
    Q_OBJECT

public:
   RendererGlWindow(QWidget* parent);

   GlRenderer* GetRenderer();
   void SetAnimation(const bool enabled);
   void SetCameraDistance(const float newDistance);

signals:
   void RendererError(const QString& message);

protected:
   void initializeGL() override;
   void resizeGL(int w, int h) override;
   void paintGL() override;

   GlRenderer* renderer = nullptr;
   OrbitCamera* camera = nullptr;

private:
   void AddObjects();

    QTimer renderTimer;
    bool animate = true;

};

#endif // RENDERERGLWINDOW_H
