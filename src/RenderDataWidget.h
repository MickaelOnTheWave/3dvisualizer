#ifndef RENDERDATAWIDGET_H
#define RENDERDATAWIDGET_H

#include <QWidget>

namespace Ui {
class RenderDataWidget;
}

class RenderDataWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RenderDataWidget(QWidget *parent = nullptr);
    ~RenderDataWidget();

private:
    Ui::RenderDataWidget *ui;
};

#endif // RENDERDATAWIDGET_H
