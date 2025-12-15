#ifndef RENDERDATAWIDGET_H
#define RENDERDATAWIDGET_H

#include <QWidget>

#include "GlRenderer.h"

namespace Ui {
class RenderDataWidget;
}

class RenderDataWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RenderDataWidget(QWidget *parent = nullptr);
    ~RenderDataWidget();

    void SetRenderer(GlRenderer* _renderer);

public slots:
    void OnUpdateData();

private:
    Ui::RenderDataWidget *ui;

    GlRenderer* renderer = nullptr;
};

#endif // RENDERDATAWIDGET_H
