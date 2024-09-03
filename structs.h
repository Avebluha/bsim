#ifndef STRUCTS_H
#define STRUCTS_H

#include "qjsonarray.h"
#include "qjsonobject.h"
#include "qpoint.h"
#include <QSettings>
#include <QString>

enum ReadData {
    InputEMF, OutputVoltage, OutputCurrent
};

struct ConnectionSettings
{
    QString portName;
    int parity;
    int baud;
    int dataBits;
    int stopBits;
    int retries;
    int delay;

    void saveSettings(QSettings &settings) const {
        settings.setValue("portName", portName);
        settings.setValue("parity", parity);
        settings.setValue("baud", baud);
        settings.setValue("dataBits", dataBits);
        settings.setValue("stopBits", stopBits);
        settings.setValue("delay", delay);
        settings.setValue("retries", retries);
    }

    void loadSettings(QSettings &settings) {
        portName = settings.value("portName", "").toString();
        parity = settings.value("parity", 0).toInt();
        baud = settings.value("baud", 9600).toInt();
        dataBits = settings.value("dataBits", 8).toInt();
        stopBits = settings.value("stopBits", 1).toInt();
        delay = settings.value("delay", 250).toInt();
        retries = settings.value("retries", 1000).toInt();
    }
};

struct EmulatorSettings {
    QString modelName;
    double maxCapacity;
    QList<QPointF> modelData;
    // Функция возвращает минимальное напряжение, основываясь на последнем элементе списка
    QPair<double, double> findMinMaxVoltage() const {
        if (modelData.isEmpty()) {
            return {std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN()};
        }
        double minVoltage = std::numeric_limits<double>::max();
        double maxVoltage = std::numeric_limits<double>::lowest();
        for (const QPointF &point : modelData) {
            if (point.y() < minVoltage) minVoltage = point.y();
            if (point.y() > maxVoltage) maxVoltage = point.y();
        }
        return {minVoltage, maxVoltage};
    }
    QJsonObject toJson() const {
        QJsonObject obj;
        obj["modelName"] = modelName;
        obj["maxCapacity"] = maxCapacity;
        QJsonArray dataArray;
        for (const QPointF &point : modelData) {
            QJsonObject pointObj;
            pointObj["capacity"] = point.x();
            pointObj["voltage"] = point.y();
            dataArray.append(pointObj);
        }
        obj["modelData"] = dataArray;
        return obj;
    }
    static EmulatorSettings fromJson(const QJsonObject& obj) {
        EmulatorSettings settings;
        settings.modelName = obj["modelName"].toString();
        settings.maxCapacity = obj["maxCapacity"].toDouble();
        QJsonArray dataArray = obj["modelData"].toArray();
        for (const QJsonValue &value : dataArray) {
            QJsonObject pointObj = value.toObject();
            QPointF point(pointObj["capacity"].toDouble(), pointObj["voltage"].toDouble());
            settings.modelData.append(point);
        }
        return settings;
    }
};

struct TestResult
{
    float stateOfCharge;
    float capacity;
    float current;
    float voltage;
    float time;
};
#endif // STRUCTS_H
