#ifndef RENDERERGLWINDOW_H
#define RENDERERGLWINDOW_H

#include <glad/glad.h>
#include <QOpenGLWidget>
#include <QTimer>

//#include "GlRenderer.h"
#include "renderers/AbstractRenderer.h"
#include "scene/Scene.h"

class RendererGlWindow : public QOpenGLWidget
{
    Q_OBJECT

public:
   RendererGlWindow(QWidget* parent);

   void SetRenderingData(std::shared_ptr<Scene> _scene,
                         std::shared_ptr<AbstractRenderer> _renderer);

   void SetAnimation(const bool enabled);

signals:
   void RendererError(const QString& message);

protected:
   void initializeGL() override;
   void resizeGL(int w, int h) override;
   void paintGL() override;

private:
   std::shared_ptr<Scene> scene;
   std::shared_ptr<AbstractRenderer> renderer;

   QTimer renderTimer;
   bool animate = true;
};

#endif // RENDERERGLWINDOW_H
