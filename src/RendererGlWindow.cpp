#include "RendererGlWindow.h"

#include "scene/resources/Camera.h"
#include "scene/resources/geometries/Box.h"

RendererGlWindow::RendererGlWindow(QWidget *parent)
  : QOpenGLWidget(parent)
{
   connect(&renderTimer, &QTimer::timeout, this, [this]() {update();});
}

void RendererGlWindow::SetRenderer(std::shared_ptr<AbstractRenderer> _renderer)
{
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

   CreateDefaultScenes();

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

    renderer->Render(defaultScenes.front());
    if (renderer->HasError())
        emit RendererError(QString::fromUtf8(renderer->GetError()));
}

void RendererGlWindow::CreateDefaultScenes()
{
   Scene cubeScene;
   const unsigned int whiteTextureId = cubeScene.AddTexture(Vector3(1,1,1), "Plain White");
   const unsigned int eyeTextureId = cubeScene.AddTexture("data/eye-blue.jpg", "Eye Texture");

   Material eyeMaterial("Eye Material");
   eyeMaterial.diffuseTextureId = eyeTextureId;
   eyeMaterial.specularTextureId = whiteTextureId;
   eyeMaterial.shininess = 20.f;
   const unsigned int eyeMaterialId = cubeScene.AddMaterial(eyeMaterial);

   auto eyeCube = new Box();
   eyeCube->SetCenter(Vector3(0, 0, 0));
   eyeCube->SetSizes(Vector3(1, 1, 1));
   const unsigned int eyeCubeId = cubeScene.AddGeometry(eyeCube);

   const unsigned int eyeModelId = cubeScene.AddSinglePartModel(eyeCubeId, eyeMaterialId, "Eye Model");

   auto eyeInstance = new ModelInstance("Eye Instance 0");
   eyeInstance->SetModelId(eyeModelId);
   eyeInstance->SetTransform(Matrix4x4::Identity());
   eyeInstance->SetColor(Vector3(1, 0, 0));
   cubeScene.AddInstance(eyeInstance);

   auto defaultCamera = new Camera("Default Camera");
   cubeScene.AddCamera(defaultCamera);

   defaultScenes.push_back(cubeScene);
}
