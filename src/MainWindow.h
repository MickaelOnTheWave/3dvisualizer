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
   void OnRendererError(const QString& message);
   void OnCameraDistanceChange(const int distance);
   void OnColorChoose();

   void OnActionOpenRenderData();

private:
   void InitializeRendering();
   void UpdateClearColor(const QColor color);
   void SetColorButtonIcon(const QColor color);

   Ui::MainWindow *ui;

   GenericDialog* renderDataWidget = nullptr;

   std::shared_ptr<Scene> scene = nullptr;
   std::shared_ptr<AbstractRenderer> renderer = nullptr;
   std::shared_ptr<OrbitCamera> camera = nullptr;
};
#endif // MAINWINDOW_H
