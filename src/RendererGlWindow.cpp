#include "RendererGlWindow.h"

RendererGlWindow::RendererGlWindow(QWidget *parent)
  : QOpenGLWidget(parent)
{
   connect(&renderTimer, &QTimer::timeout, this, [this]() {update();});
}

void RendererGlWindow::SetRenderingData(std::shared_ptr<Scene> _scene,
                                        std::shared_ptr<AbstractRenderer> _renderer)
{
   scene = _scene;
   renderer = _renderer;
}

void RendererGlWindow::SetAnimation(const bool enabled)
{
    animate = enabled;
    if (animate)
        renderTimer.start(15);
    else
        renderTimer.stop();
}

void RendererGlWindow::initializeGL()
{
    if (!gladLoadGL())
    {
        emit RendererError(QString::fromUtf8("Failed to initialize Glad"));
        return;
    }

   //renderer->Initialize({new ShaderProgram("data/basic.vert", "data/singleTexture.frag", "Simple Texturing")});
   renderer->Initialize();

   renderer->SetClearColor(0.0f, 0.0f, 0.0f);

   //renderer->PrepareRendering();
   if (renderer->HasError())
       emit RendererError(QString::fromUtf8(renderer->GetError()));
}

void RendererGlWindow::resizeGL(int w, int h)
{
}

void RendererGlWindow::paintGL()
{
    //if (animate)
    //  currentCamera->RotateInY(2.0f);

    renderer->Render(*scene.get());
    if (renderer->HasError())
        emit RendererError(QString::fromUtf8(renderer->GetError()));
}
