#ifndef DIREXT_H
#define DIREXT_H

#include <QApplication>
#include <QMap>
#include <QList>
#include "progressdialog.h"
#include "stats.h"

class dirext
{
public:
    QList<stats> create_ext_map(QString &dir, QApplication &app, ProgressDialog &dlg);

private:
    int progress;
    void recourse_dir(QString dir, QApplication &app, ProgressDialog &dlg, QMap<QString, stats> &map);
};

#endif // DIREXT_H
