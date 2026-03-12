#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "cameras/OrbitCamera.h"
#include "renderers/AbstractRenderer.h"
#include "GenericDialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
   Q_OBJECT

public:
   MainWindow(QWidget *parent = nullptr);
   ~MainWindow();

private slots:
   void OnEnableWireframe(const bool enabled);
   void OnRendererErrors(const QStringList& message);
   void OnCameraDistanceChange(const int distance);
   void OnColorChoose();

   void OnActionOpenRenderData();

private:
   void InitializeRendering();
   void UpdateClearColor(const QColor color);
   void SetColorButtonIcon(const QColor color);

   void CreateDefaultScenes();
   std::shared_ptr<Scene> CreateCubeScene();
   std::shared_ptr<Scene> CreateTriangleScene();
   std::shared_ptr<Scene> CreateTriangleSeaScene();

   unsigned int CreateTriangleModel(std::shared_ptr<Scene> scene);
   void AddInstances(std::shared_ptr<Scene> scene, const Vector3 startingPosition,
                     const Vector3 instanceCount, const Vector3 intervals,
                     const Vector3 color, const std::string& labelBase);

   Ui::MainWindow *ui;

   GenericDialog* renderDataWidget = nullptr;

   std::vector<std::shared_ptr<Scene>> defaultScenes;
   std::shared_ptr<Scene> currentScene = nullptr;
   std::shared_ptr<AbstractRenderer> renderer = nullptr;
   std::shared_ptr<OrbitCamera> camera = nullptr;
};
#endif // MAINWINDOW_H
