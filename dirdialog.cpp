#include "dirdialog.h"
#include "ui_dirdialog.h"
#include <QStringListModel>
#include <QClipboard>
#include <QDesktopServices>
#include <QUrl>

DirDialog::DirDialog(QWidget *parent, QStringList dirList, QString extension) :
    QDialog(parent),
    ui(new Ui::DirDialog),
    dirList(dirList),
    extension(extension)
{
    ui->setupUi(this);

    ui->labelExtension->setText(tr("Extension:") + " " + extension);
    ui->label->setText(tr("Number of directories:") + " " + QString::number(dirList.size()));

    QStringListModel *model = new QStringListModel(this);
    model->setStringList(dirList);
    ui->listView->setModel(model);
}

DirDialog::~DirDialog()
{
    delete ui;
}

void DirDialog::on_listView_doubleClicked(const QModelIndex &index)
{
    auto dir = ui->listView->model()->data(index, Qt::DisplayRole).toString();
    QClipboard *myClipboard = QApplication::clipboard();
    myClipboard->setText(dir);

    QDesktopServices::openUrl( QUrl::fromLocalFile( dir ) );
}
