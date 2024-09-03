#include "sqlmanager.h"
#include "qdebug.h"

SqlManager::SqlManager(const QString& driver, QObject *parent)
    : QObject{parent}
{
    m_db = QSqlDatabase::addDatabase(driver);
}

void SqlManager::setSettings(const QString &hostName, const int &port, const QString &dataBase, const QString &username, const QString &password)
{
    m_db.setHostName(hostName);
    m_db.setPort(port);
    m_db.setDatabaseName(dataBase);
    m_db.setUserName(username);
    m_db.setPassword(password);
}

bool SqlManager::connect()
{
    if(m_db.open()) {
        qDebug() << "Connected to db";
        return true;
    }
    else {
        qDebug() << "Failed to connect" << m_db.lastError();
        return false;
    }
}

void SqlManager::disconnect()
{
    m_db.close();
}

void SqlManager::addDevice(const QString& deviceName) {
    const QString tableName = "devices";
    const QStringList columns = {"name"};
    const QVariantList data = {deviceName};
    insertData(tableName, columns, data);
}

QVariant SqlManager::insertData(const QString &tableName, const QStringList &columns, const QVariantList &data) {
    // Проверяем, что количество столбцов соответствует количеству данных
    if (columns.size() != data.size()) {
        qDebug() << "The number of columns and data items must match.";
        return QVariant();
    }
    // Формируем строку для вставки данных
    QString queryStr = QString("INSERT INTO %1 (").arg(tableName);
    queryStr += columns.join(", ") + ") VALUES (";
    QStringList placeholders;
    for (int i = 0; i < columns.size(); ++i) {
        placeholders << "?";
    }
    queryStr += placeholders.join(", ") + ")";
    QSqlQuery query(m_db);
    // Подготавливаем SQL-запрос
    if (!query.prepare(queryStr)) {
        qDebug() << "Failed to prepare query:" << query.lastError().text();
        return QVariant();
    }
    // Привязываем данные к запросу
    for (int i = 0; i < data.size(); ++i) {
        query.addBindValue(data[i]);
    }
    // Выполняем запрос
    if (!query.exec()) {
        qDebug() << "Insert failed:" << query.lastError().text();
        return QVariant();
    }
    const QVariant lastId = query.lastInsertId();
    if(!lastId.isValid()) {
        qDebug() << "Failed to retrieve last inserted ID.";
        return QVariant();
    }
    return lastId;
}

QStringList SqlManager::createSelectQuery(const QStringList &columns, const QStringList &tables, const QStringList &joins) {
    if (tables.isEmpty()) {
        qDebug() << "No tables provided for SQL query creation";
        return {};
    }
    QString queryStr;
    // Проверяем, указаны ли столбцы. Если нет, используем '*'
    if (columns.isEmpty()) {
        queryStr = "SELECT * FROM " + tables[0];
    } else {
        queryStr = "SELECT " + columns.join(", ") + " FROM " + tables[0];
    }
    // Добавляем JOIN только если они указаны и их количество соответствует количеству таблиц - 1
    if (!joins.isEmpty() && tables.size() - 1 == joins.size()) {
        for (int i = 0; i < joins.size(); ++i) {
            queryStr += " JOIN " + tables[i + 1] + " ON " + joins[i];
        }
    }
    queryStr += ';';
    qDebug() << queryStr;
    QSqlQuery query(m_db);
    if (!query.exec(queryStr)) {
        qDebug() << "Failed to execute query:" << query.lastError().text();
        return {};
    }
    QStringList results;
    while (query.next()) {
        QStringList row;
        for (int i = 0; i < query.record().count(); ++i) {
            row.append(query.value(i).toString());
        }
        results.append(row.join(", "));
    }
    return results;
}

QList<QList<QVariant>> SqlManager::selectQuery(const QString &table_name, const QList<QString> &columns, const QString &whereClause)
{
    QList<QList<QVariant>> results;
    QSqlQuery query(m_db);
    QString columnsToSelect = columns.isEmpty() ? "*" : columns.join(", ");
    QString queryStr = "SELECT " + columnsToSelect + " FROM " + table_name;
    if (!whereClause.isEmpty()) {
        queryStr += " WHERE " + whereClause;
    }
    if (!query.exec(queryStr)) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return results; // Возвращаем пустой список в случае ошибки
    }
    while (query.next()) {
        QList<QVariant> rowData;
        for (int i = 0; i < query.record().count(); ++i) {
            rowData.append(query.value(i));
        }
        results.append(rowData);
    }
    return results;
}

bool SqlManager::deleteRecord(const QString &tableName, const QMap<QString, QVariant> &conditions) {
    QSqlQuery query(m_db);
    // Формируем начальную часть запроса
    QString sql = QString("DELETE FROM %1").arg(tableName);
    // Добавляем условия
    if (!conditions.isEmpty()) {
        QStringList conditionStrings;
        for(auto it = conditions.begin(); it != conditions.end(); ++it) {
            conditionStrings.append(QString("%1 = :%1").arg(it.key()));
        }
        sql += " WHERE " + conditionStrings.join(" AND ");
    }
    query.prepare(sql);
    // Привязываем значения к параметрам
    for(auto it = conditions.begin(); it != conditions.end(); ++it) {
        query.bindValue(":" + it.key(), conditions[it.key()]);
    }
    if (!query.exec()) {
        qDebug() << "Failed to delete record:" << query.lastError().text() << "SQL: " << sql;
        return false;
    }
    return true;
}

bool SqlManager::updateRecord(const QString &tableName, const QString &columnName, const QVariant &newValue, const QString &condition) {
    QSqlQuery query(m_db);
    QString sql = QString("UPDATE %1 SET %2 = :newValue WHERE %3").arg(tableName, columnName, condition);
    query.prepare(sql);
    qDebug() << sql;
    query.bindValue(":newValue", newValue);
    if (!query.exec()) {
        qDebug() << "Error:" << query.lastError().text();
        return false;
    }
    return true;
}
