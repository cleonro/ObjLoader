#include "carmwidget.h"
#include "ui_carmwidget.h"

CarmWidget::CarmWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CarmWidget)
{
    ui->setupUi(this);
}

CarmWidget::~CarmWidget()
{
    delete ui;
}

void CarmWidget::Close()
{
    this->close();
}
