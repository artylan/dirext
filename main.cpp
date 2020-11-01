#include "widget.h"
#include "dirext.h"
#include "progressdialog.h"
#include <QApplication>
#include <QTranslator>
#include <QFileDialog>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTranslator translator;
    // look up :/translations/dirext_de.qm
    if (translator.load(QLocale(), QLatin1String("dirextqt"), QLatin1String("_"), QLatin1String(":/translations")))
        QCoreApplication::installTranslator(&translator);

    QString file_name;
    if (QCoreApplication::arguments().count() < 2) {
        file_name = QFileDialog::getExistingDirectory(Q_NULLPTR, QObject::tr("Inspect directory"),
                                                      "c:/",
                                                      QFileDialog::ShowDirsOnly
                                                      | QFileDialog::DontResolveSymlinks);
        if (file_name == Q_NULLPTR) {
            qDebug() << QObject::tr("You haven't specified a directory.");
            return 1;
        }
    } else {
        file_name = QCoreApplication::arguments().at(1);
        QFileInfo file_info(file_name);
        if (!file_info.isDir())
        {
            qDebug() << file_name << QObject::tr("doesn't exist or isn't a directory.");
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
