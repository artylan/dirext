#include "widget.h"
#include "ui_widget.h"
#include "customtablemodel.h"
#include "mynumberformatdelegate.h"
#include "myproxymodel.h"
#include "dirdialog.h"
#include "aboutdialog.h"
#include <QSettings>

constexpr char COMPANY[] = "WAS";
constexpr char PROG[] = "DirExtQt";
constexpr char WINDOW[] = "mainwindow";
constexpr char GEOMETRY[] = "geometry";
constexpr char MAXIMIZED[] = "maximized";
constexpr char POS[] = "pos";
constexpr char SIZE[] = "size";

Widget::Widget(QList<stats> stats_list, int progress, QString dir_path, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    stats_list(stats_list),
    progress(progress),
    dir_path(dir_path)
{
    ui->setupUi(this);

    ui->labelDir->setText(tr("Directory:") + " " + dir_path);
    ui->labelProgress->setText(tr("Number of inspected files:") + " " + QString::number(progress));

    CustomTableModel * model = new CustomTableModel(this, stats_list);
    MyProxyModel * proxyModel = new MyProxyModel(this);
    proxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
    proxyModel->setSourceModel(model);
    ui->tableView->setStyleSheet("QHeaderView::section { background-color:lightgray } QTableCornerButton::section {background-color: lightgray }");
    ui->tableView->setItemDelegateForColumn(1, new MyNumberFormatDelegate(this));
    ui->tableView->setItemDelegateForColumn(2, new MyNumberFormatDelegate(this));
    ui->tableView->setModel(proxyModel );
    ui->tableView->sortByColumn(0, Qt::AscendingOrder);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->setColumnWidth(0, 110);
    ui->tableView->setColumnWidth(1, 150);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    QHeaderView *verticalHeader = ui->tableView->verticalHeader();
    verticalHeader->setSectionResizeMode(QHeaderView::Fixed);
    verticalHeader->setDefaultSectionSize(20);

    loadSettings();
}

void Widget::closeEvent(QCloseEvent *event)
{
    saveSettings();
    QWidget::closeEvent(event);
}

void Widget::saveSettings()
{
    QSettings qsettings(COMPANY, PROG);
    qsettings.beginGroup(WINDOW);
    qsettings.setValue(GEOMETRY, saveGeometry());
    qsettings.setValue(MAXIMIZED, isMaximized());
    if ( !isMaximized()) {
        qsettings.setValue(POS, pos());
        qsettings.setValue(SIZE, size());
    }
    qsettings.endGroup();
}

void Widget::loadSettings()
{
    QSettings qsettings(COMPANY, PROG);
    qsettings.beginGroup(WINDOW);
    restoreGeometry(qsettings.value(GEOMETRY, saveGeometry()).toByteArray());
    move(qsettings.value(POS, pos()).toPoint());
    resize(qsettings.value(SIZE, size()).toSize());
    if ( qsettings.value(MAXIMIZED, isMaximized() ).toBool())
        showMaximized();
    qsettings.endGroup();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_tableView_doubleClicked(const QModelIndex &index)
{
    QModelIndex nIndex = ui->tableView->model()->index(index.row(), 0);
    auto extension = ui->tableView->model()->data(nIndex, Qt::DisplayRole).toString();
    QStringList dirList = getDirList(extension);
    DirDialog * dlg = new DirDialog(this, dirList, extension);
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->exec();
}

QStringList Widget::getDirList(QString ext)
{
    for (auto stat: stats_list) {
        if (stat.get_ext() == ext) {
            return stat.getDirList();
        }
    }
    return QStringList();
}


void Widget::on_aboutButton_clicked()
{
    AboutDialog * dlg = new AboutDialog(this);
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->exec();
}
