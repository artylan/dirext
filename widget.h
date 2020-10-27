#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "stats.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QList<stats> stats_list, int progress, QString dir_path, QWidget *parent = nullptr);
    ~Widget();

    QList<stats> get_stats_list();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_tableView_doubleClicked(const QModelIndex &index);

private:
    Ui::Widget *ui;
    QList<stats> stats_list;
    int progress;
    QString dir_path;

    void saveSettings();
    void loadSettings();
    QStringList getDirList(QString ext);
};

#endif // WIDGET_H
