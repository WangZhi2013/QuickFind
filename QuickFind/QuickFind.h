#pragma once

#include <QtWidgets/QMainWindow>
#include <QStandardItemModel>
#include <QTimer>
#include "ui_QuickFind.h"

class QuickFind : public QMainWindow
{
    Q_OBJECT

public:
    QuickFind(QWidget *parent = nullptr);
    ~QuickFind();

private slots:
    void onKeywordChanged();   // 文本变化 → 重置计时器
    void doSearch();           // 计时器超时 → 真正加载假数据

private:
    Ui::QuickFindClass ui;

    QStandardItemModel* resultModel = nullptr;
    QTimer* searchTimer = nullptr;
};

