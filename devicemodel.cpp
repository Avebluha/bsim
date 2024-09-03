#include "devicemodel.h"

DeviceModel::DeviceModel(SqlManager *sql, QObject *parent)
    : QAbstractListModel{parent},
    m_sql(sql)
{
}

void DeviceModel::addDevice(const QString &device)
{
    if(m_devices.contains(device)) return;
    int rowCount = this->rowCount(QModelIndex());
    this->insertRows(rowCount, 1);
    this->setData(rowCount, device);
    m_sql->insertData(m_tableName, QStringList(m_column), QList<QVariant>({device}));
}

void DeviceModel::loadDevicesFromDB()
{
    const auto deviceNames = m_sql->createSelectQuery(QStringList(m_column), QStringList(m_tableName), QStringList());
    this->setData(deviceNames);
}

void DeviceModel::setData(const QStringList &deviceNames)
{
    beginResetModel();
    m_devices = deviceNames;
    endResetModel();
}

bool DeviceModel::insertRows(int position, int rows, const QModelIndex &index)  {
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position + rows - 1);
    for (int row = 0; row < rows; ++row) {
        m_devices.insert(position, "");
    }
    endInsertRows();
    return true;
}

void DeviceModel::setData(int index, const QString &value) {
    if (index >= 0 && index < m_devices.size()) {
        m_devices[index] = value;
        emit dataChanged(createIndex(index, 0), createIndex(index, 0));
    }
}

int DeviceModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_devices.count();
}

QVariant DeviceModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || (role != Qt::DisplayRole && role != Qt::EditRole)) return QVariant();
    return m_devices[index.row()];
}

bool DeviceModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole || index.row() >= m_devices.size() || !value.isValid())
        return false;
    qDebug() << value;
    if(value.toString().isEmpty()) return false;
    const QString oldValue = m_devices.at(index.row());
    m_devices[index.row()] = value.toString();
    m_sql->updateRecord(m_tableName, m_column, value.toString(), QString("%1='%2'").arg(m_column, oldValue));
    return true;
}

Qt::ItemFlags DeviceModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;
    return QAbstractListModel::flags(index) | Qt::ItemIsEditable;
}

bool DeviceModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (parent.isValid())
        return false; // В этом примере поддерживается только список верхнего уровня
    if (row < 0 || count <= 0 || row + count > m_devices.size())
        return false; // Проверяем, что индексы находятся в допустимых пределах
    beginRemoveRows(QModelIndex(), row, row + count - 1);
    for (int i = 0; i < count; ++i) {
        QMap<QString, QVariant> map;
        map.insert(m_column, m_devices.at(row));
        m_sql->deleteRecord(m_tableName, map);
        m_devices.removeAt(row);
    }
    endRemoveRows();
    return true;
}
