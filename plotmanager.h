#ifndef PLOTMANAGER_H
#define PLOTMANAGER_H

#include "qcheckbox.h"
#include "qmainwindow.h"
#include "structs.h"
#include "interpolator.h"
#include <QValueAxis>
#include <QLineSeries>
#include <QObject>
#include <QChart>
#include <QInputDialog>
#include <QTime>
#include <QFile>

class PlotManager : public QObject
{
    Q_OBJECT

public:
    explicit PlotManager(QChart* chart, QObject *parent = nullptr);

    void addDataToPlot();
    void updateSeriesNames();
    void clearPlot();
    void setDelay(const int &delay);
    void setupControlPanel(QMainWindow *mainWindow);
    void setEmulating(bool isEmulating);
    void setRange(const float& timeRangeMin, const float& timeRangeMax);
    void changePercent(const float& percent);
    void devicesStatus(bool isEmpty);

signals:
    void voltageCalculated(const float& voltage);
    void percentChanged(const float& percent);
    void emulatingFinished();
    void dataToSaveReceived(const QString& testName, const QList<TestResult> testResults);
    void checkDevices();


public slots:
    void updatePlotData(const QList<quint16> &dataPoints);
    void updateEmulatorSettings(const EmulatorSettings &settings);
    void updatePlotFromTestData(const QList<TestResult> &testResults);
    void saveResults();

private:
    QChart *m_chart;
    QLineSeries *m_seriesEMF;
    QLineSeries *m_seriesVoltage;
    QLineSeries *m_seriesCurrent;
    QLineSeries *m_seriesCapacity;
    QValueAxis *m_xAxis, *m_yAxis, *m_yAxis2, *m_yAxis3;
    QList<float> m_scaledData;
    QList<TestResult> m_testResults;
    Interpolator *m_interpolator;
    QToolBar *m_toolbar;
    QCheckBox *m_checkEMF;
    QCheckBox *m_checkVoltage;
    QCheckBox *m_checkCurrent;
    QCheckBox *m_checkCapacity;
    QPushButton *m_btnClearPlot;
    float m_time = 0, m_range = 20, m_maxVoltage, m_minVoltage, m_maxCapacity, m_capacity;
    int m_delay;
    bool m_isEmulating = false;
    bool m_deviceIsEmpty = true;

private:
    void scaleDataFromDevice(const QList<quint16> &dataPoints);
    void createPlot();
    void updatePlotFromTestData(const QString &testName);
};

#endif // PLOTMANAGER_H
