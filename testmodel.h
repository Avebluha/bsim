#ifndef TESTMODEL_H
#define TESTMODEL_H

#include "sqlmanager.h"
#include "structs.h"
#include <QObject>
#include <QAbstractListModel>
#include <QVariant>
#include <QDate>

class TestModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit TestModel(SqlManager *sql, QObject *parent = nullptr);
    void addTest(const QString& deviceName, const QString& batteryModel, const QString& testName, const QList<TestResult> testResults);
    QList<TestResult> getTestResult(const QString& testName) const;

public slots:
    void deviceChanged(const QString& deviceName);

private:
    QHash<QString, QList<TestResult>> m_tests;
    SqlManager *m_sql;
    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
};

#endif // TESTMODEL_H
