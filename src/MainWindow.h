#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
   void UpdateClearColor(const QColor color);
   void SetColorButtonIcon(const QColor color);

   Ui::MainWindow *ui;

   GenericDialog* renderDataWidget = nullptr;
};
#endif // MAINWINDOW_H
