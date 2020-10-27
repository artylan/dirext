#include "dirext.h"
#include <QDir>
#include <QDebug>

QList<stats> dirext::create_ext_map(QString &dir, QApplication &app, ProgressDialog &dlg) {
    QMap<QString, stats> ext_map{};

    progress = 0;

    recourse_dir(dir, app, dlg, ext_map);

    QList<stats> result;
    for (auto entry : ext_map) {
        result.push_back(entry);
    }
    dlg.setProgress(progress);
    return result;
}

void dirext::recourse_dir(QString dir, QApplication &app, ProgressDialog &dlg, QMap<QString, stats> &ext_map)
{
    QFileInfoList entries = QDir(dir).entryInfoList(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Files | QDir::NoSymLinks);
    for (const auto &entry: entries) {
        if (entry.isDir()) {
            recourse_dir(entry.absoluteFilePath(), app, dlg, ext_map);
        } else if (entry.isFile()) {
            QString ext = entry.suffix();
            if (ext.isEmpty()) {
                ext = "<noext>";
            } else {
                ext = "." + ext;
            }
            stats& stats = ext_map[ext];
            stats.set_ext(ext);
            stats.incCount(1);
            stats.incSize(entry.size());
            stats.addDir(dir);

            ++progress;
            if (progress % 1000 == 0) {
                dlg.setProgress(progress);
                app.processEvents();
            }
        }
        if (dlg.isCanceled()) {
            return;
        }
    }
}


