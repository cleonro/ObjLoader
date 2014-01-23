#ifndef CARMWIDGET_H
#define CARMWIDGET_H

#include <QDialog>

namespace Ui {
class CarmWidget;
}

class CarmWidget : public QDialog
{
    Q_OBJECT
    
public:
    explicit CarmWidget(QWidget *parent = 0);
    ~CarmWidget();
    
protected slots:
    void Close();

private:
    Ui::CarmWidget *ui;
};

#endif // CARMWIDGET_H
