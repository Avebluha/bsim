#ifndef DEVICEMODEL_H
#define DEVICEMODEL_H

#include "sqlmanager.h"
#include <QObject>
#include <QAbstractListModel>

class DeviceModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit DeviceModel(SqlManager* sql, QObject *parent = nullptr);

    void addDevice(const QString& device);
    void loadDevicesFromDB();
    void setData(const QStringList& deviceNames);

private:
    QStringList m_devices;
    SqlManager *m_sql;
    const QString m_tableName = "devices";
    const QString m_column = "name";

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool removeRows(int row, int count, const QModelIndex &parent);
    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
    void setData(int index, const QString &value);
};

#endif // DEVICEMODEL_H
