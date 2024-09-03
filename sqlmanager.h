#ifndef SQLMANAGER_H
#define SQLMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QPointF>
#include <QSqlRecord>
#include <QVariant>
#include <QVariantList>

class SqlManager : public QObject
{
    Q_OBJECT
public:
    explicit SqlManager(const QString& driver, QObject *parent = nullptr);

    void setSettings(const QString& hostName, const int& port, const QString& dataBase, const QString& username, const QString& password);
    bool connect();
    void disconnect();
    QList<QList<QVariant>> selectQuery(const QString& table_name, const QList<QString>& columns = QList<QString>(), const QString &whereClause = "");
    QStringList createSelectQuery(const QStringList &columns, const QStringList &tables, const QStringList &joins);
    void addDevice(const QString &deviceName);
    QVariant insertData(const QString &tableName, const QStringList &columns, const QVariantList &data);
    bool deleteRecord(const QString &tableName, const QMap<QString, QVariant> &conditions);
    bool updateRecord(const QString &tableName, const QString &columnName, const QVariant &newValue, const QString &condition);
private:
    QSqlDatabase m_db;

};

#endif // SQLMANAGER_H
