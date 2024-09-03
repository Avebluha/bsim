#include "modbusmanager.h"

ModbusManager::ModbusManager(QObject *parent)
    : QObject(parent), modbusDevice(new QModbusRtuSerialClient(this)), timer(new QTimer(this))
{
    connect(modbusDevice, &QModbusClient::errorOccurred, this, &ModbusManager::handleError);
    connect(modbusDevice, &QModbusClient::stateChanged, this, &ModbusManager::onStateChanged);
    connect(timer, &QTimer::timeout, this, &ModbusManager::readRegisters);
}

void ModbusManager::setSettings(const ConnectionSettings &settings)
{
    //Установка параметров подключения
    modbusDevice->setConnectionParameter(QModbusDevice::SerialPortNameParameter, settings.portName);
    modbusDevice->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, settings.baud);
    modbusDevice->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, settings.dataBits);
    modbusDevice->setConnectionParameter(QModbusDevice::SerialParityParameter, settings.parity);
    modbusDevice->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, settings.stopBits);
    modbusDevice->setNumberOfRetries(settings.retries);
    delay = settings.delay;
}

void ModbusManager::startPeriodicRead() {
    timer->start(delay); // Устанавливаем интервал в миллисекундах
}

void ModbusManager::stopPeriodicRead() {
    timer->stop();
}

void ModbusManager::connectDevice() {
    if (!modbusDevice->connectDevice()) {
        qDebug() << "Connection failed:" << modbusDevice->errorString();
    } else {
        qDebug() << "Connected to Modbus server.";
    }
}

void ModbusManager::disconnectDevice() {
    if (modbusDevice->state() == QModbusDevice::ConnectedState)
        modbusDevice->disconnectDevice();
}

void ModbusManager::readRegisters() {
    if (modbusDevice->state() != QModbusDevice::ConnectedState) {
        qDebug() << "Device is not connected.";
        stopPeriodicRead();
        return;
    }
    QModbusDataUnit readUnit(QModbusDataUnit::HoldingRegisters, 0, 3);
    if (auto *reply = modbusDevice->sendReadRequest(readUnit, 1)) {
        if (!reply->isFinished())
            connect(reply, &QModbusReply::finished, this, &ModbusManager::readReady);
        else
            delete reply;
    } else {
        qDebug() << "Read error:" << modbusDevice->errorString();
    }
}

void ModbusManager::updateSettings(const ConnectionSettings &newSettings) {
    disconnectDevice();  // Отключаем текущее соединение
    // Обновление параметров подключения
    modbusDevice->setConnectionParameter(QModbusDevice::SerialPortNameParameter, newSettings.portName);
    modbusDevice->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, newSettings.baud);
    modbusDevice->setConnectionParameter(QModbusDevice::SerialParityParameter, newSettings.parity);
    modbusDevice->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, newSettings.dataBits);
    modbusDevice->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, newSettings.stopBits);
    modbusDevice->setNumberOfRetries(newSettings.retries);
    delay = newSettings.delay;
    connectDevice();  // Повторное подключение
}

void ModbusManager::write(quint16 value) {
    if (!modbusDevice || modbusDevice->state() != QModbusDevice::ConnectedState) {
        qDebug() << "Device is not connected or Modbus client is not initialized.";
        return;
    }
    QModbusDataUnit writeUnit(QModbusDataUnit::HoldingRegisters, 0, 1);  // Регистр 0, длина 1
    writeUnit.setValue(0, value);  // Установка значения в первый регистр блока
    QModbusReply *reply = modbusDevice->sendWriteRequest(writeUnit, 1);  // 1 - адрес устройства
    if (reply) {
        if (!reply->isFinished()) {
            // Подключение обработчика завершения запроса
            connect(reply, &QModbusReply::finished, this, [reply]() {
                if (reply->error() == QModbusDevice::NoError) {
                    qDebug() << "Successfully wrote value to register 0.";
                } else {
                    qDebug() << "Failed to write value to register 0:" << reply->errorString();
                }
                reply->deleteLater();
            });
        } else {
            // Удалить reply, если ответ уже получен
            reply->deleteLater();
        }
    } else {
        qDebug() << "Failed to send write request:" << modbusDevice->errorString();
    }
}

bool ModbusManager::isConnected() const
{
    return modbusDevice && modbusDevice->state() == QModbusDevice::ConnectedState;
}

void ModbusManager::handleError(QModbusDevice::Error error) {
    qDebug() << "Modbus error:" << error;
}

void ModbusManager::onStateChanged(QModbusDevice::State state) {
    if (state == QModbusDevice::ConnectedState) {
        qDebug() << "Device connected.";
        emit connectionStatusChanged(true);
    } else if (state == QModbusDevice::UnconnectedState) {
        qDebug() << "Device disconnected.";
        emit connectionStatusChanged(false);
    }
}

void ModbusManager::readReady() {
    auto reply = qobject_cast<QModbusReply *>(sender());
    if (!reply)
        return;
    if (reply->error() == QModbusDevice::NoError) {
        const QModbusDataUnit unit = reply->result();
        QVector<quint16> values;
        for (uint i = 0; i < unit.valueCount(); i++) {
            values.push_back(unit.value(i));
        }
        emit dataReceived(values);
    } else {
        qDebug() << "Read result error:" << reply->errorString();
    }
    reply->deleteLater();
}
