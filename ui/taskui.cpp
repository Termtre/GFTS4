#include "taskui.h"
#include "ui_taskui.h"

taskUI::taskUI(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::taskUI)
{
    ui->setupUi(this);
}

taskUI::~taskUI()
{
    delete ui;
}
