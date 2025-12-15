#include "RenderDataWidget.h"
#include "ui_RenderDataWidget.h"

RenderDataWidget::RenderDataWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RenderDataWidget)
{
    ui->setupUi(this);
}

RenderDataWidget::~RenderDataWidget()
{
    delete ui;
}
