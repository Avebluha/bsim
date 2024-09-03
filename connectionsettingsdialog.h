#ifndef CONNECTIONSETTINGSDIALOG_H
#define CONNECTIONSETTINGSDIALOG_H

#include "structs.h"
#include <QDialog>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QSettings>

namespace Ui {
class ConnectionSettingsDialog;
}

class ConnectionSettingsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ConnectionSettingsDialog(QWidget *parent = nullptr);
    ~ConnectionSettingsDialog();

    void loadSettings();
    void saveSettings();
    ConnectionSettings settings() const;

signals:
    void settingsUpdated(const ConnectionSettings &settings);

private:
    Ui::ConnectionSettingsDialog *ui;
    ConnectionSettings m_settings;
};

#endif // CONNECTIONSETTINGSDIALOG_H
