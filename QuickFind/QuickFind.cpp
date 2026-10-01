#include "QuickFind.h"

QuickFind::QuickFind(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    
    ui.resultView->verticalHeader()->setVisible(false); // 隐藏左侧默认行号，减少干扰

    // 防抖计时器
    searchTimer = new QTimer(this);
    searchTimer->setSingleShot(true);   // 单次触发，关键
    searchTimer->setInterval(300);

    // 信号连接
    // textChanged: 每次输入都重置 300ms 计时器
    connect(ui.keywordEdit, &QLineEdit::textChanged, this, &QuickFind::onKeywordChanged);

    // 计时器到时 -> 真正搜索
    connect(searchTimer, &QTimer::timeout, this, &QuickFind::doSearch);

    // Model 模型
    resultModel = new QStandardItemModel(0, 5, this);
    resultModel->setHorizontalHeaderLabels({ "序号", "文件名", "路径", "修改时间", "大小"});
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

// ToDo：将doSealed方法连接到真实搜索内核

void QuickFind::doSearch()
{
    QString keyword = ui.keywordEdit->text().trimmed();

    // 清空旧结果
    resultModel->removeRows(0, resultModel->rowCount());

    // 关键词为空就不加载
    if (keyword.isEmpty()) return;

    // 加载假数据（模拟搜索结果）
    // ToDo：换成真搜索逻辑
    QStringList fakeFiles = {
        "测试文件1", "测试文件2", "测试文件3",
        "测试文件4", "测试文件5", "测试文件6"
    };

    

    for (int i = 0; i < fakeFiles.size(); ++i) {
        QList<QStandardItem*> row;
        row << new QStandardItem(QString::number(i + 1))                          // 0: 序号
            << new QStandardItem(fakeFiles.at(i))                                 // 1: 文件名
            << new QStandardItem(QString("D:/测试/路径/%1").arg(fakeFiles.at(i))) // 2: 路径
            << new QStandardItem(QString("2小时前"))                              // 3: 修改时间
            << new QStandardItem(QString("5 MB"));                                // 4: 大小
        resultModel->appendRow(row);
    }
}
