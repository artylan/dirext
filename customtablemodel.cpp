#include "customtablemodel.h"
#include <QFont>
#include <QBrush>
#include <QTime>

CustomTableModel::CustomTableModel(QObject * parent, QList<stats> stats_list ) : QAbstractTableModel(parent), stats_list(stats_list)
{
}

int CustomTableModel::rowCount(const QModelIndex&) const
{
    return stats_list.size();
}

int CustomTableModel::columnCount(const QModelIndex&) const
{
    return 3;
}

QVariant CustomTableModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();

    stats stats = stats_list.at(row);

    switch(role)
    {
        case Qt::DisplayRole: {
            if (col == 0) {
                return stats.get_ext();
            } else if (col == 1) {
                return QVariant(stats.get_count());
            } else  if (col == 2) {
                return QVariant(stats.get_size());
            }
        }
        break;

    case Qt::TextAlignmentRole:

        if(col ==0)
        {
            return Qt::AlignLeft;
        } else {
            return Qt::AlignRight;
        }

        break;

    }
    return QVariant();
}

QVariant CustomTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if( role == Qt::DisplayRole)
    {
        if( orientation == Qt::Horizontal)
        {
            switch (section) {
            case 0:
                return QString("Erweiterung");
                break;
            case 1:
                return QString("Anzahl");
                break;
            case 2:
                return QString("Größe");
                break;
            default:
                return QString("Default");
                break;
            }
        }
        if( orientation == Qt::Vertical)
        {
          return QString::number(section + 1);
        }

    }
    return QVariant();

}
