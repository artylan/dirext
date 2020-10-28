#ifndef DIRDIALOG_H
#define DIRDIALOG_H

#include <QDialog>

namespace Ui {
class DirDialog;
}

class DirDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DirDialog(QWidget *parent = nullptr, QStringList dirList = QStringList(), QString extension = QString());
    ~DirDialog();

private slots:
    void on_listView_doubleClicked(const QModelIndex &index);

private:
    Ui::DirDialog *ui;
    QStringList dirList;
    QString extension;
};

#endif // DIRDIALOG_H
