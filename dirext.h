#ifndef DIREXT_H
#define DIREXT_H

#include <QApplication>
#include <QList>
#include <QMap>
#include <QDir>
#include "progressdialog.h"
#include "stats.h"

class dirext
{
public:
    QList<stats> create_ext_map(QString &dir, QApplication &app, ProgressDialog &dlg);
    int progress;
private:
    //std::wstring get_extension(const fs::directory_entry& entry);
    void recourse_dir(QString dir, QApplication &app, ProgressDialog &dlg, QMap<QString, stats> &map);
};

#endif // DIREXT_H
