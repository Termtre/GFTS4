#ifndef TASKUI_H
#define TASKUI_H

#include <QWidget>

namespace Ui {
class taskUI;
}

class taskUI : public QWidget
{
    Q_OBJECT

public:
    explicit taskUI(QWidget *parent = nullptr);
    ~taskUI();

private:
    Ui::taskUI *ui;
};

#endif // TASKUI_H
