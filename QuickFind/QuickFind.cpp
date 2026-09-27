#include "QuickFind.h"

QuickFind::QuickFind(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    
    ui.resultView->verticalHeader()->setVisible(false); // 隐藏左侧默认行号

    // 可选：固定左侧序号列宽，避免数字变长时表头宽度跳
    ui.resultView->verticalHeader()->setFixedWidth(40);


    resultModel = new QStandardItemModel(0, 4, this); 
    resultModel->setHorizontalHeaderLabels({ "#", "文件名", "路径", "行号" });
    ui.resultView->setModel(resultModel);
    ui.resultView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    ui.resultView->setColumnWidth(0, 40);


    // ---- Model ----
    resultModel = new QStandardItemModel(0, 3, this);
    resultModel->setHorizontalHeaderLabels({ "文件名", "路径", "行号" });
    ui.resultView->setModel(resultModel);
    ui.resultView->horizontalHeader()->setStretchLastSection(true);

    // ---- 防抖计时器 ----
    searchTimer = new QTimer(this);
    searchTimer->setSingleShot(true);   // 单次触发，关键
    searchTimer->setInterval(300);

    // ---- 信号连接 ----
    // textChanged: 每次输入都重置 300ms 计时器
    connect(ui.keywordEdit, &QLineEdit::textChanged,
        this, &QuickFind::onKeywordChanged);

    // 计时器到时 -> 真正搜索
    connect(searchTimer, &QTimer::timeout,
        this, &QuickFind::doSearch);

    // 构造函数中
    resultModel = new QStandardItemModel(0, 4, this);
    resultModel->setHorizontalHeaderLabels({ "序号", "文件名", "路径", "行号" });
    ui.resultView->setModel(resultModel);

    // 配合之前的列宽设置，避免挤压
    ui.resultView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    ui.resultView->setColumnWidth(0, 40); // 序号列宽
    ui.resultView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch); // 路径列拉伸
}

QuickFind::~QuickFind()
{}

void QuickFind::onKeywordChanged()
{
    // 输入任何字符都重置计时器
    // 300ms 内再次输入 -> 取消上一次，重新计 300ms
    searchTimer->start(300);
}

void QuickFind::doSearch()
{
    QString keyword = ui.keywordEdit->text().trimmed();

    // 清空旧结果
    resultModel->removeRows(0, resultModel->rowCount());

    // 关键词为空就不加载
    if (keyword.isEmpty())
        return;

    // ---- 加载假数据（模拟搜索结果）----
    // ToDo：换成真搜索逻辑
    QStringList fakeFiles = {
        "main.cpp", "QuickFind.cpp", "QuickFind.h",
        "utils.cpp", "utils.h", "mainwindow.cpp"
    };

    

    for (int i = 0; i < fakeFiles.size(); ++i) {
        QList<QStandardItem*> row;
        row << new QStandardItem(QString::number(i + 1))          // 0: 序号
            << new QStandardItem(fakeFiles.at(i))                 // 1: 文件名
            << new QStandardItem(QString("D:/project/src/%1").arg(fakeFiles.at(i))) // 2: 路径
            << new QStandardItem(QString::number(10 + i * 3));    // 3: 行号
        resultModel->appendRow(row);
    }
}
