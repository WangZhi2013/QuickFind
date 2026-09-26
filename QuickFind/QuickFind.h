#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QuickFind.h"

class QuickFind : public QMainWindow
{
    Q_OBJECT

public:
    QuickFind(QWidget *parent = nullptr);
    ~QuickFind();

private:
    Ui::QuickFindClass ui;
};

