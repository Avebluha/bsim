#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "connectionsettingsdialog.h"
#include "devicemodel.h"
#include "emulatorsettingsdialog.h"
#include "modbusmanager.h"
#include "plotmanager.h"
#include "testmodel.h"
#include <QMainWindow>
#include <QTranslator>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void percentChanged(const float& percent);

private:
    Ui::MainWindow *ui;
    ConnectionSettingsDialog *m_connect;
    ModbusManager *m_modbus;
    EmulatorSettingsDialog *m_emulator;
    SqlManager *m_sql;
    QChart *m_chart;
    PlotManager *m_plot;
    float m_currentVoltage = 0;
    float m_minVoltage = 0;
    float m_maxVoltage = 0;
    bool m_modelLoaded = false;
    DeviceModel *m_deviceModel;
    TestModel *m_testModel;
    QTranslator *m_translator;

private:
    void changeActionsConnectState(bool connected);
    void changeBatteryOptionsButtonsState(bool activated);
    void changeGraphicOptions(bool started);
    void onQuickConnect();
    void setVoltageToDevice(const float &voltage);
    void changeEvent(QEvent *event);
    void onConnectionStatusChanged(bool connected);
private slots:
    void onConnect();
    void onDisconnect();
    void onSetValue();
    void onModelDataUpdated(const EmulatorSettings& data);
    void onActivateEmulatorStateChanged(Qt::CheckState status);
    void onStart();
    void onStop();
    void onTimeRangeChanged();
};
#endif // MAINWINDOW_H
