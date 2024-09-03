#include "batterymodel.h"

BatteryModel::BatteryModel(QObject *parent) : QAbstractTableModel{parent}
{}

int BatteryModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_data.count();
}

int BatteryModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return 2;
}

void BatteryModel::setData(const QList<QPointF> &data) {
    beginResetModel();
    m_data = data;
    endResetModel();
}

QVariant BatteryModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= m_data.size() || (role != Qt::DisplayRole && role != Qt::EditRole))
        return QVariant();
    const QPointF &point = m_data.at(index.row());
    if (index.column() == 0)
        return point.x();
    else if (index.column() == 1)
        return point.y();
    return QVariant();
}

bool BatteryModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (index.column() != 1 || role != Qt::EditRole || index.row() >= m_data.size() || !value.isValid())
        return false;
    QPointF &point = m_data[index.row()];
    bool ok;
    double newValue = value.toDouble(&ok);
    if (!ok) return false;
    if (index.column() == 1) {
        point.setY(newValue);
        emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});
        return true;
    }
    return false;
}

Qt::ItemFlags BatteryModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return Qt::NoItemFlags;
    if (index.column() == 1)
        return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
    return QAbstractTableModel::flags(index);
}

QList<QPointF> BatteryModel::getData() const {
    return m_data;
}

QVariant BatteryModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0: return QStringLiteral("SOC(%)");
        case 1: return QStringLiteral("Voltage(V)");
        default: return QVariant();
        }
    }
    return QVariant();
}
