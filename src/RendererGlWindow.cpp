#include "RendererGlWindow.h"

#include "objects/GlRenderCube.h"

RendererGlWindow::RendererGlWindow(QWidget *parent)
  : QOpenGLWidget(parent)
{
   connect(&renderTimer, &QTimer::timeout, this, [this]() {update();});
}

void RendererGlWindow::SetRenderer(std::shared_ptr<GlRenderer> _renderer)
{
   renderer = _renderer;
   currentCamera = dynamic_cast<OrbitCamera*>(renderer->GetCamera());
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

   renderer->Initialize({new ShaderProgram("data/basic.vert", "data/singleTexture.frag", "Simple Texturing")});

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
      currentCamera->RotateInY(2.0f);

    renderer->Render();
    if (renderer->HasError())
        emit RendererError(QString::fromUtf8(renderer->GetError()));
}

void RendererGlWindow::AddObjects()
{
    const int channelCount = 3;
    const unsigned int whiteTextureId = renderer->AddTexture(Vector3(1,1,1), "Plain White");
    const unsigned int textureId = renderer->AddTexture("data/eye-blue.jpg", channelCount, "Eye");
    auto cubeMaterial = new Material("Eye");
    cubeMaterial->diffuseTextureId = textureId;
    cubeMaterial->specularTextureId = whiteTextureId;
    cubeMaterial->shininess = 20.f;
    renderer->AddMaterial(cubeMaterial);

    auto cube = new GlRenderCube(cubeMaterial, "EyedCube");
    cube->Initialize();
    Matrix4x4 cubePos = Matrix4x4::Scale(1.f);
    auto cubeInstance = new GlRenderedInstance(cube, cubePos, "Main Object");

    renderer->AddRenderObject(cubeInstance);
}
