#include "connectionsettingsdialog.h"
#include "ui_connectionsettingsdialog.h"

ConnectionSettingsDialog::ConnectionSettingsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ConnectionSettingsDialog)
{
    ui->setupUi(this);
    for(const auto& port : QSerialPortInfo::availablePorts()) ui->cbPortName->addItem(port.portName());
    ui->cbParity->addItems({"No" , "Even", "Odd", "Space", "Mark"});
    ui->cbDataBits->addItems({"5","6","7","8"});
    ui->cbBaud->addItems({"1200","2400","4800","9600","19200","38400","57600","115200"});
    ui->cbStopBits->addItems({"1","2"});
    ui->leDelay->setText("250");
    ui->leResponseTimeout->setText("1000");
    m_settings.retries = ui->leResponseTimeout->text().toInt();
    connect(ui->btnConnect, &QPushButton::clicked, this, [this](){
        m_settings.portName = ui->cbPortName->currentText();
        m_settings.baud = ui->cbBaud->currentText().toInt();
        m_settings.parity = ui->cbParity->currentIndex();
        if(m_settings.parity > 0) m_settings.parity++;
        m_settings.dataBits = ui->cbDataBits->currentText().toInt();
        m_settings.stopBits = ui->cbStopBits->currentText().toInt();
        m_settings.delay = ui->leDelay->text().toInt();
        m_settings.retries = ui->leResponseTimeout->text().toInt();
        emit settingsUpdated(m_settings);
        accept();
    });
}

ConnectionSettings ConnectionSettingsDialog::settings() const {
    return m_settings;
}

ConnectionSettingsDialog::~ConnectionSettingsDialog()
{
    delete ui;
}

void ConnectionSettingsDialog::saveSettings() {
    QSettings settings("biba inc", "bsim");
    settings.beginGroup("ConnectionSettings");
    settings.setValue("portName", m_settings.portName);
    settings.setValue("baud", m_settings.baud);
    settings.setValue("parity", m_settings.parity);
    settings.setValue("dataBits", m_settings.dataBits);
    settings.setValue("stopBits", m_settings.stopBits);
    settings.setValue("delay", m_settings.delay);
    settings.setValue("retries", m_settings.retries);
    settings.endGroup();
}

void ConnectionSettingsDialog::loadSettings() {
    QSettings settings("biba inc", "bsim");
    settings.beginGroup("ConnectionSettings");
    m_settings.portName = settings.value("portName", "").toString();
    m_settings.baud = settings.value("baud", 9600).toInt();
    m_settings.parity = settings.value("parity", 0).toInt();
    m_settings.dataBits = settings.value("dataBits", 8).toInt();
    m_settings.stopBits = settings.value("stopBits", 1).toInt();
    m_settings.delay = settings.value("delay", 250).toInt();
    m_settings.retries = settings.value("retries", 1000).toInt();
    settings.endGroup();

    // Установка значений в UI
    ui->cbPortName->setCurrentText(m_settings.portName);
    ui->cbBaud->setCurrentText(QString::number(m_settings.baud));
    if (m_settings.parity > 0) m_settings.parity--;
    ui->cbParity->setCurrentIndex(m_settings.parity);
    ui->cbDataBits->setCurrentText(QString::number(m_settings.dataBits));
    ui->cbStopBits->setCurrentText(QString::number(m_settings.stopBits));
    ui->leDelay->setText(QString::number(m_settings.delay));
    ui->leResponseTimeout->setText(QString::number(m_settings.retries));
    emit settingsUpdated(m_settings);
}
