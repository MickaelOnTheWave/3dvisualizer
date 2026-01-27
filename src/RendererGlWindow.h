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

   void SetRenderer(std::shared_ptr<AbstractRenderer> _renderer);

   void SetAnimation(const bool enabled);

signals:
   void RendererError(const QString& message);

protected:
   void initializeGL() override;
   void resizeGL(int w, int h) override;
   void paintGL() override;

private:
   // TODO check - this probably belongs to main app, not gl window

   void CreateDefaultScenes();

   std::vector<Scene> defaultScenes;
   std::shared_ptr<AbstractRenderer> renderer;

   QTimer renderTimer;
   bool animate = true;
};

#endif // RENDERERGLWINDOW_H
