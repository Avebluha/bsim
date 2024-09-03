#include "testmodel.h"

#include <QMessageBox>

TestModel::TestModel(SqlManager *sql, QObject *parent)
    : QAbstractListModel{parent}
    , m_sql(sql)
{}

void TestModel::addTest(const QString &deviceName, const QString &batteryModel, const QString &testName, const QList<TestResult> testResults)
{
    const auto deviceId = m_sql->selectQuery("devices", QStringList("id"), QString("name='%1'").arg(deviceName));
    const auto batteryModelId = m_sql->selectQuery("battery_models", QStringList("id"), QString("name='%1'").arg(batteryModel));
    if(deviceId.isEmpty() || batteryModelId.isEmpty()) {
        QMessageBox::warning(0, "Error", "Not found device or battery model!");
        return;
    }
    const auto lastId = m_sql->insertData("tests", QStringList({"name", "device_id", "battery_model_id", "date"}),
                                          QList<QVariant>({testName, deviceId.constFirst().constFirst(), batteryModelId.constFirst().constFirst(), QDate::currentDate()}));
    if(!lastId.isValid()) return;

    for(const auto& testResult : testResults) {
        m_sql->insertData("test_results", QStringList({"state_of_charge", "capacity", "current", "voltage", "time", "test_id"}),
                          QList<QVariant>({testResult.stateOfCharge, testResult.capacity, testResult.current, testResult.voltage, testResult.time, lastId}));
    }
    beginResetModel();
    m_tests.insert(testName, testResults);
    endResetModel();
}

QList<TestResult> TestModel::getTestResult(const QString &testName) const
{
    return m_tests.value(testName);
}

void TestModel::deviceChanged(const QString &deviceName)
{
    beginResetModel();
    m_tests.clear();
    const auto deviceId = m_sql->selectQuery("devices", QStringList("id"), QString("name='%1'").arg(deviceName));
    if(deviceId.isEmpty()) {
        endResetModel();
        return;
    }
    const auto testsData = m_sql->selectQuery("tests", QStringList({"id", "name"}), QString("device_id=%1").arg(deviceId.constFirst().constFirst().toInt()));
    if(testsData.isEmpty()) {
        endResetModel();
        return;
    }
    QHash<QString, QList<TestResult>> tmp;
    for(const auto& testData : testsData) {
        const auto testResults = m_sql->selectQuery("test_results", QStringList({"state_of_charge", "capacity", "current", "voltage", "time"}),
                                                    QString("test_id=%1").arg(testData.constFirst().toInt()));
        QList<TestResult> tmpResult;
        for(const auto& testResult : testResults) {
            tmpResult.append(TestResult{testResult[0].toFloat(), testResult[1].toFloat(),testResult[2].toFloat(),testResult[3].toFloat(),testResult[4].toFloat()});
        }
        tmp.insert(testData.constLast().toString(), tmpResult);
    }
    m_tests = tmp;
    endResetModel();

}

int TestModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_tests.count();
}

QVariant TestModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || (role != Qt::DisplayRole && role != Qt::EditRole)) return QVariant();
    auto it = m_tests.begin();
    std::advance(it, index.row());
    return it.key();
}
