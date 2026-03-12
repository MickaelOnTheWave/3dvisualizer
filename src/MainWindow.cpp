#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include <QColorDialog>
#include "RenderDataWidget.h"
#include "renderers/OpenGlRenderer.h"
#include "scene/resources/geometries/Box.h"
#include "scene/resources/geometries/Triangle.h"


MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
   ui->setupUi(this);
   ui->stackedWidget->setCurrentWidget(ui->opengl);

   InitializeRendering();
   ui->openGLWidget->SetRenderingData(currentScene, renderer);

   connect(ui->actionOpenRenderData, &QAction::triggered, this, &MainWindow::OnActionOpenRenderData);

   connect(ui->wireframeBox, &QCheckBox::toggled, this, &MainWindow::OnEnableWireframe);
   connect(ui->openGLWidget, &RendererGlWindow::RendererError, this, &MainWindow::OnRendererErrors);
   connect(ui->animateBox, &QCheckBox::stateChanged, ui->openGLWidget, &RendererGlWindow::SetAnimation);
   connect(ui->distanceSlider, &QSlider::sliderMoved, this, &MainWindow::OnCameraDistanceChange);
   connect(ui->colorButton, &QAbstractButton::pressed, this, &MainWindow::OnColorChoose);

   ui->openGLWidget->SetAnimation(ui->animateBox->isChecked());

   SetColorButtonIcon(Qt::black);
}

MainWindow::~MainWindow()
{
   delete ui;
}

void MainWindow::OnEnableWireframe(const bool enabled)
{
   auto glRenderer = std::dynamic_pointer_cast<OpenGlRenderer>(renderer);
   glRenderer->EnableWireframeMode(enabled);
}

void MainWindow::OnRendererErrors(const QStringList& message)
{
   QString serializedMessage;
   for (const auto& m : message)
      serializedMessage += m + "\n";

   ui->errorMessage->setText(serializedMessage);
   ui->stackedWidget->setCurrentWidget(ui->errors);
}

void MainWindow::OnCameraDistanceChange(const int distance)
{
    const float sourceRange = ui->distanceSlider->maximum() - ui->distanceSlider->minimum();
    const float sourceMiddle = ui->distanceSlider->minimum() + sourceRange / 2.f;
    const float destinationRange = 0.01f;
    const float destinationMiddle = 4.0f;
    const float destinationDistance = ((distance - ui->distanceSlider->minimum()) / sourceRange) * destinationRange + (destinationMiddle - destinationRange);
    camera->CloseOut(0.1f);
}

void MainWindow::OnColorChoose()
{
   const QColor backgroundColor = QColorDialog::getColor(Qt::black, this, "Select the background color");
   UpdateClearColor(backgroundColor);
}

void MainWindow::OnActionOpenRenderData()
{
    if (!renderDataWidget)
    {
        auto contentWidget = new RenderDataWidget();
        contentWidget->SetScene(currentScene.get());
        renderDataWidget = new GenericDialog(contentWidget, false, this);
        renderDataWidget->setMinimumSize(contentWidget->size());
    }
    renderDataWidget->show();
    renderDataWidget->raise();
    renderDataWidget->activateWindow();
}

void MainWindow::InitializeRendering()
{
   camera = std::make_shared<OrbitCamera>(Vector3(0.f, 0.f, 0.f));
   //camera->CloseOut(4.0f);
   //camera->RotateInX(20.f);

   CreateDefaultScenes();
   renderer = std::make_shared<OpenGlRenderer>();
}

void MainWindow::CreateDefaultScenes()
{
   defaultScenes.push_back(CreateCubeScene());
   defaultScenes.push_back(CreateTriangleScene());
   defaultScenes.push_back(CreateTriangleSeaScene());
   currentScene = defaultScenes[1];
}

std::shared_ptr<Scene> MainWindow::CreateCubeScene()
{
   auto cubeScene = std::make_shared<Scene>();
   const unsigned int whiteTextureId = cubeScene->AddTexture(Vector3(1,1,1), "Plain White");
   const unsigned int eyeTextureId = cubeScene->AddTexture("data/eye-blue.jpg", "Eye Texture");

   Material eyeMaterial("Eye Material");
   eyeMaterial.diffuseTextureId = eyeTextureId;
   eyeMaterial.specularTextureId = whiteTextureId;
   eyeMaterial.shininess = 20.f;
   const unsigned int eyeMaterialId = cubeScene->AddMaterial(eyeMaterial);

   auto eyeCube = new Box();
   eyeCube->SetCenter(Vector3(0, 0, 0));
   eyeCube->SetSizes(Vector3(1, 1, 1));
   const unsigned int eyeCubeId = cubeScene->AddGeometry(eyeCube);

   const unsigned int eyeModelId = cubeScene->AddSinglePartModel(eyeCubeId, eyeMaterialId, "Eye Model");

   auto eyeInstance = new ModelInstance("Eye Instance 0");
   eyeInstance->SetModelId(eyeModelId);
   eyeInstance->SetTransform(Matrix4x4::Identity());
   eyeInstance->SetColor(Vector3(1, 0, 0));
   cubeScene->AddInstance(eyeInstance);

   auto defaultCamera = new Camera("Default Camera");
   const float aspectRatio = ui->openGLWidget->width() / static_cast<float>(ui->openGLWidget->height());
   defaultCamera->SetPerspectiveProjection(60_deg, aspectRatio);
   defaultCamera->LookAt(Vector3(0, 0, 3), Vector3(0,0,0));
   cubeScene->AddCamera(defaultCamera);
   return cubeScene;
}

std::shared_ptr<Scene> MainWindow::CreateTriangleScene()
{
   auto scene = std::make_shared<Scene>();
   const unsigned int modelId = CreateTriangleModel(scene);

   auto instance = new ModelInstance("Instance 0");
   instance->SetModelId(modelId);
   auto debugging = Matrix4x4::Translation(0, 0, -3);
   debugging.Transpose();
   instance->SetTransform(debugging);
   instance->SetColor(Vector3(0, 1, 0));
   scene->AddInstance(instance);

   auto defaultCamera = new Camera("Default Camera");
   const float aspectRatio = ui->openGLWidget->width() / static_cast<float>(ui->openGLWidget->height());
   defaultCamera->SetPerspectiveProjection(60_deg, aspectRatio);
   defaultCamera->LookAt(Vector3(-2, 2, 5), Vector3(0,0,0));
   scene->AddCamera(defaultCamera);
   return scene;
}

std::shared_ptr<Scene> MainWindow::CreateTriangleSeaScene()
{
   auto scene = std::make_shared<Scene>();
   CreateTriangleModel(scene);

   Vector3 startingPos(-10, -5, -10);
   const Vector3 instanceCount(10, 3, 8);
   const Vector3 intervals(2, 5, 2);
   Vector3 color(1, 0, 0);
   AddInstances(scene, startingPos, instanceCount, intervals, color, "Red");

   startingPos.SetZ(2);
   color = Vector3(0, 1, 0);
   AddInstances(scene, startingPos, instanceCount, intervals, color, "Green");

   auto defaultCamera = new Camera("Default Camera");
   const float aspectRatio = ui->openGLWidget->width() / static_cast<float>(ui->openGLWidget->height());
   defaultCamera->SetPerspectiveProjection(60_deg, aspectRatio);
   //defaultCamera->LookAt(Vector3(-2, 2, 2), Vector3(0,0,0));
   defaultCamera->LookAt(Vector3(0, 0, 1), Vector3(0,0,0));
   scene->AddCamera(defaultCamera);
   return scene;
}

unsigned int MainWindow::CreateTriangleModel(std::shared_ptr<Scene> scene)
{
   const unsigned int simpleTextureId = scene->AddTexture(Vector3(1,0,0), "Plain Red");
   const unsigned int whiteTextureId = scene->AddTexture(Vector3(1,1,1), "Plain White");

   Material material("Material");
   material.diffuseTextureId = simpleTextureId;
   material.specularTextureId = whiteTextureId;
   material.shininess = 20.f;
   const unsigned int materialId = scene->AddMaterial(material);

   auto geometry = new Triangle();
   geometry->point1 = Vector3(0, 0, 0);
   geometry->point2 = Vector3(1, 0, 0);
   geometry->point3 = Vector3(0, 1, 0);
   const unsigned int geometryId = scene->AddGeometry(geometry);

   return scene->AddSinglePartModel(geometryId, materialId, "Triangle Model");
}

void MainWindow::AddInstances(std::shared_ptr<Scene> scene, const Vector3 startingPosition, const Vector3 instanceCount,
                              const Vector3 intervals, const Vector3 color, const std::string& labelBase)
{
   Model* model = scene->FindModelByName("Triangle Model");
   if (!model)
      return;
   for (int instX = 0; instX < instanceCount.X(); ++instX)
   {
      for (int instY = 0; instY < instanceCount.Y(); ++instY)
      {
         for (int instZ = 0; instZ < instanceCount.Z(); ++instZ)
         {
            const Vector3 diffPos(instX * intervals.X(), instY * intervals.Y(), instY * intervals.Z());
            const Vector3 position = startingPosition + diffPos;
            const auto transform = Matrix4x4::Translation(position);
            const std::string name = labelBase + " " + std::to_string(instZ);

            auto instance = new ModelInstance(name);
            instance->SetModelId(model->GetId());
            instance->SetTransform(transform);
            instance->SetColor(color);
            scene->AddInstance(instance);
         }
      }
   }
}

void MainWindow::UpdateClearColor(const QColor color)
{
   renderer->SetClearColor(color.redF(), color.greenF(), color.blueF());
   SetColorButtonIcon(color);
}

void MainWindow::SetColorButtonIcon(const QColor color)
{
   const int iconSize = 16;
   QPixmap pixmap(iconSize, iconSize);
   pixmap.fill(color);
   ui->colorButton->setIcon(pixmap);
   ui->colorButton->setIconSize(QSize(iconSize, iconSize));
}

