#include "RendererGlWindow.h"

#include "cameras/OrbitCamera.h"
#include "objects/GlRenderCube.h"

RendererGlWindow::RendererGlWindow(QWidget *parent)
  : QOpenGLWidget(parent)
{
    connect(&renderTimer, &QTimer::timeout, this, [this]() {update();});
}

GlRenderer* RendererGlWindow::GetRenderer()
{
   return renderer;
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

   camera = new OrbitCamera(Vector3(0.f, 0.f, 0.f));
    camera->CloseOut(4.0f);
   camera->RotateInX(20.f);

   renderer = new GlRenderer(camera);

   renderer->Initialize({new ShaderProgram("data/basic.vert", "data/singleTexture.frag")});

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
    if (animate)
        camera->RotateInY(2.0f);

    renderer->Render();
    if (renderer->HasError())
        emit RendererError(QString::fromUtf8(renderer->GetError()));
}

void RendererGlWindow::AddObjects()
{
    const int channelCount = 3;
    const unsigned int whiteTextureId = renderer->AddTexture(Vector3(1,1,1));
    const unsigned int textureId = renderer->AddTexture("data/eye-blue.jpg", channelCount);
    auto cubeMaterial = new Material("material");
    cubeMaterial->diffuseTextureId = textureId;
    cubeMaterial->specularTextureId = whiteTextureId;
    cubeMaterial->shininess = 20.f;
    renderer->AddMaterial(cubeMaterial);

    auto cube = new GlRenderCube(cubeMaterial);
    cube->Initialize();
    Matrix4x4 cubePos = Matrix4x4::Scale(1.f);
    auto cubeInstance = new GlRenderedInstance(cube, cubePos);

    renderer->AddRenderObject(cubeInstance);
}
