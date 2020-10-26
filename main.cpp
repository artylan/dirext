#include "widget.h"
#include "dirext.h"
#include "progressdialog.h"
#include <QApplication>
#include <QFileDialog>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QString file_name;
    if (QCoreApplication::arguments().count() != 2) {
        file_name = QFileDialog::getExistingDirectory(Q_NULLPTR, "Besuche Verzeichnis",
                                                      "c:/",
                                                      QFileDialog::ShowDirsOnly
                                                      | QFileDialog::DontResolveSymlinks);
        if (file_name == Q_NULLPTR) {
            qDebug() << "Sie haben kein Verzeichnis angegeben.";
            return 1;
        }
    } else {
        file_name = QCoreApplication::arguments().at(1);
        QFileInfo file_info(file_name);
        if (!file_info.isDir())
        {
            qDebug() << file_name << "ist kein Verzeichnis.";
            return 1;
        }
    }

    ProgressDialog dlg(Q_NULLPTR);
    dlg.show();
    dlg.raise();
    dlg.activateWindow();
    app.processEvents();

    dirext dirext{};
    QList<stats> stats_list = dirext.create_ext_map(file_name, app, dlg);

    dlg.hide();

    Widget w{stats_list, dlg.getProgress(), file_name};
    w.show();

    return app.exec();
}
