#ifndef STATS_H
#define STATS_H

#include <QString>

class stats {
private:
    QString ext;
    qint64 count;
    qint64 size;
public:
    void set_ext(QString ext) { this->ext = ext; }
    void incCount(qint64  inc) { count += inc; }
    void incSize(qint64 inc) { size += inc; }
    QString get_ext() const { return ext; }
    qint64 get_count() const { return count; }
    qint64 get_size() const { return size; }
};

#endif // STATS_H
