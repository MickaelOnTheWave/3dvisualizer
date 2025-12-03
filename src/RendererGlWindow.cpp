#include "RendererGlWindow.h"

#include "cameras/OrbitCamera.h"
#include "objects/GlRenderCube.h"

RendererGlWindow::RendererGlWindow(QWidget *parent)
  : QOpenGLWidget(parent)
{
}

GlRenderer* RendererGlWindow::GetRenderer()
{
   return renderer;
}

void RendererGlWindow::initializeGL()
{
    if (!gladLoadGL())
    {
        emit RendererError(QString::fromUtf8("Failed to initialize Glad"));
        return;
    }

   AbstractGlCamera* defaultCamera = new OrbitCamera(Vector3(0.f, 0.f, 0.f));
   renderer = new GlRenderer(defaultCamera);

   renderer->Initialize({new ShaderProgram("data/basic.vert", "data/basic.frag")});

   renderer->SetClearColor(0.0f, 0.0f, 0.0f);

   AddObjects();

   renderer->PrepareRendering();
   if (renderer->HasError())
       emit RendererError(QString::fromUtf8(renderer->GetError()));
}

void RendererGlWindow::resizeGL(int w, int h)
{
}

void RendererGlWindow::paintGL()
{
    renderer->Render();
    if (renderer->HasError())
        emit RendererError(QString::fromUtf8(renderer->GetError()));
}

void RendererGlWindow::AddObjects()
{
    auto cubeMaterial = new Material("material");
    auto cube = new GlRenderCube(cubeMaterial);
    auto cubeInstance = new GlRenderedInstance(cube, Matrix4x4::Identity());

    renderer->AddRenderObject(cubeInstance);
}
