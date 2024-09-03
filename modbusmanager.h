#ifndef MODBUSMANAGER_H
#define MODBUSMANAGER_H

#include <structs.h>

#include <QVariant>
#include <QModbusRtuSerialClient>
#include <QModbusDataUnit>
#include <QSerialPort>
#include <QTimer>

class ModbusManager : public QObject {
    Q_OBJECT

public:
    ModbusManager(QObject *parent = nullptr);

    void setSettings(const ConnectionSettings& settings);
    void startPeriodicRead();
    void stopPeriodicRead();
    void connectDevice();
    void disconnectDevice();
    void readRegisters();
    void updateSettings(const ConnectionSettings& newSettings);
    void write(quint16 value);
    bool isConnected() const;

signals:
    void connectionStatusChanged(bool connected);
    void dataReceived(const QVector<quint16>& data);

private slots:
    void handleError(QModbusDevice::Error error);
    void onStateChanged(QModbusDevice::State state);
    void readReady();

private:
    QModbusClient *modbusDevice;
    QTimer *timer;
    int delay;
};


#endif // MODBUSMANAGER_H
