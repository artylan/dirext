#ifndef STATS_H
#define STATS_H

#include <QString>
#include <QSet>
#include <algorithm>

class stats {
private:
    QString ext;
    qint64 count;
    qint64 size;
    QSet<QString> dirs;
public:
    void set_ext(QString ext) { this->ext = ext; }
    void incCount(qint64  inc) { count += inc; }
    void incSize(qint64 inc) { size += inc; }
    QString get_ext() const { return ext; }
    qint64 get_count() const { return count; }
    qint64 get_size() const { return size; }
    void addDir(QString dir) { dirs.insert(dir); }
    QStringList getDirList() const {
        QStringList result{};
        for (auto dir: dirs)
            result.append(dir);
        result.sort(Qt::CaseInsensitive);
        return result;
    }
};

#endif // STATS_H
