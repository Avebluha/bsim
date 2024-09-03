#include "plotmanager.h"
#include "qpushbutton.h"

#include <QCheckBox>
#include <QFile>
#include <QMessageBox>
#include <QToolBar>

PlotManager::PlotManager(QChart *chart, QObject *parent) :
    QObject{parent},
    m_chart(chart),
    m_seriesEMF(new QLineSeries),
    m_seriesVoltage(new QLineSeries),
    m_seriesCurrent(new QLineSeries),
    m_seriesCapacity(new QLineSeries),
    m_xAxis(new QValueAxis),
    m_yAxis(new QValueAxis),
    m_yAxis2(new QValueAxis),
    m_yAxis3(new QValueAxis),
    m_interpolator(new Interpolator)
{
    createPlot();
}

void PlotManager::createPlot() {
    m_chart->addSeries(m_seriesEMF);
    m_chart->addSeries(m_seriesVoltage);
    m_chart->addSeries(m_seriesCurrent);
    m_chart->addSeries(m_seriesCapacity);
    m_chart->addAxis(m_yAxis, Qt::AlignLeft);
    m_chart->addAxis(m_yAxis2, Qt::AlignRight);
    m_chart->addAxis(m_yAxis3, Qt::AlignRight);
    m_chart->addAxis(m_xAxis, Qt::AlignBottom);
    m_seriesEMF->attachAxis(m_yAxis);
    m_seriesEMF->attachAxis(m_xAxis);
    m_seriesEMF->setName("EMF");
    m_seriesVoltage->attachAxis(m_yAxis);
    m_seriesVoltage->attachAxis(m_xAxis);
    m_seriesVoltage->setName("Voltage");
    m_seriesCurrent->attachAxis(m_yAxis2);
    m_seriesCurrent->attachAxis(m_xAxis);
    m_seriesCurrent->setName("Current");
    m_seriesCapacity->attachAxis(m_yAxis3);
    m_seriesCapacity->attachAxis(m_xAxis);
    m_seriesCapacity->setName("Capacity");
    m_seriesEMF->setColor(Qt::red);
    m_seriesVoltage->setColor(Qt::green);
    m_seriesCurrent->setColor(Qt::blue);
    m_seriesCapacity->setColor(QColor(190, 32, 240));
    // Настройка осей
    m_yAxis->setRange(3.0, 4.2);
    m_yAxis->setLabelFormat("%.2f");
    m_yAxis->setTitleText("Output Voltage (V)");
    m_yAxis2->setRange(-512*4.2/(1024*50*0.1),512*4.2/(1024*50*0.1));
    m_yAxis2->setLabelFormat("%.4f");
    m_yAxis2->setTitleText("Output Current (A)");
    m_yAxis3->setRange(0,m_maxCapacity);
    m_yAxis3->setLabelFormat("%.2f");
    m_yAxis3->setTitleText("Capacity (mAh)");
    m_xAxis->setRange(0, m_range);
    m_xAxis->setLabelFormat("%i");
    m_xAxis->setTitleText("Time (sec)");
}

void PlotManager::setupControlPanel(QMainWindow *mainWindow) {
    m_toolbar = new QToolBar;
    m_checkEMF = new QCheckBox("Show EMF");
    m_checkVoltage = new QCheckBox("Show Voltage");
    m_checkCurrent = new QCheckBox("Show Current");
    m_checkCapacity = new QCheckBox("Show Capacity");
    m_btnClearPlot = new QPushButton("Clear Plot");
    m_toolbar->addWidget(m_checkEMF);
    m_toolbar->addWidget(m_checkVoltage);
    m_toolbar->addWidget(m_checkCurrent);
    m_toolbar->addWidget(m_checkCapacity);
    m_toolbar->addWidget(m_btnClearPlot);
    // Подключение сигналов к слотам для управления видимостью серий
    connect(m_checkEMF, &QCheckBox::toggled, m_seriesEMF, &QLineSeries::setVisible);
    connect(m_checkVoltage, &QCheckBox::toggled, m_seriesVoltage, &QLineSeries::setVisible);
    connect(m_checkCurrent, &QCheckBox::toggled, m_seriesCurrent, &QLineSeries::setVisible);
    connect(m_checkCapacity, &QCheckBox::toggled, m_seriesCapacity, &QLineSeries::setVisible);
    connect(m_btnClearPlot, &QPushButton::clicked, this, &PlotManager::clearPlot);
    // Предварительная активация чекбоксов
    mainWindow->addToolBar(m_toolbar);
    m_checkEMF->setChecked(true);
    m_checkVoltage->setChecked(true);
    m_checkCurrent->setChecked(true);
    m_checkCapacity->setChecked(true);
}

void PlotManager::setEmulating(bool isEmulating)
{
    m_isEmulating = isEmulating;
}

void PlotManager::setRange(const float &timeRangeMin, const float &timeRangeMax)
{
    if(timeRangeMin > timeRangeMax || timeRangeMax < 0 || timeRangeMin < 0) return;
    m_range = timeRangeMax - timeRangeMin;
    m_xAxis->setRange(timeRangeMin, timeRangeMax);
}

void PlotManager::addDataToPlot()
{
    m_seriesEMF->append(m_time, m_scaledData[InputEMF]);
    m_seriesVoltage->append(m_time, m_scaledData[OutputVoltage]);
    m_seriesCurrent->append(m_time, m_scaledData[OutputCurrent]);
    m_seriesCapacity->append(m_time, m_capacity);
}

void PlotManager::updateSeriesNames()
{
    m_seriesEMF->setName(QString("EMF(%1V)").arg(m_scaledData[InputEMF], 0, 'f', 2));
    m_seriesVoltage->setName(QString("Voltage(%1V)").arg(m_scaledData[OutputVoltage], 0, 'f', 2));
    m_seriesCurrent->setName(QString("Current(%1A)").arg(m_scaledData[OutputCurrent], 0, 'f', 4));
    m_seriesCapacity->setName(QString("Capacity(%1mAh)").arg(m_capacity, 0, 'f', 2));
}

void PlotManager::clearPlot() {
    m_seriesEMF->clear();
    m_seriesVoltage->clear();
    m_seriesCurrent->clear();
    m_seriesCapacity->clear();
    m_time = 0;
    m_xAxis->setRange(m_time, m_time + m_range);
}

void PlotManager::setDelay(const int &delay)
{
    m_delay = delay;
}

void PlotManager::updatePlotData(const QList<quint16> &dataPoints)
{
    m_scaledData.clear();
    scaleDataFromDevice(dataPoints);
    updateSeriesNames();
    m_time += 0.001 * m_delay;
    if(m_time > m_range) m_xAxis->setRange(m_time - m_range, m_time);
    addDataToPlot();
    if(m_isEmulating) {
        if(m_capacity < 0) return;
        m_capacity -= m_scaledData[OutputCurrent]/36*0.001*m_delay;
        float percent = m_capacity/m_maxCapacity*100;
        const float voltage = m_interpolator->functionResult(percent);
        emit voltageCalculated(voltage);
        emit percentChanged(percent);
        TestResult tmpResult = {
            percent,
            m_capacity,
            m_scaledData[OutputCurrent],
            voltage,
            m_time
        };
        m_testResults.append(tmpResult);
    }
}

void PlotManager::updateEmulatorSettings(const EmulatorSettings &settings)
{
    const auto voltages = settings.findMinMaxVoltage();
    m_maxVoltage = voltages.second;
    m_minVoltage = voltages.first;
    m_capacity = m_maxCapacity = settings.maxCapacity;
    m_interpolator->interpolateData(settings.modelData);
    m_yAxis->setRange(m_minVoltage, m_maxVoltage);
    m_yAxis->setLabelFormat("%.2f");
    m_yAxis2->setRange(-512*m_maxVoltage/(1024*50*0.1),512*m_maxVoltage/(1024*50*0.1));
    m_yAxis2->setLabelFormat("%.4f");
    m_yAxis3->setRange(0,m_maxCapacity);
    m_yAxis3->setLabelFormat("%.2f");
    m_xAxis->setRange(0, m_range);
    m_xAxis->setLabelFormat("%i");
    emit percentChanged(m_capacity/m_maxCapacity*100);
}

void PlotManager::updatePlotFromTestData(const QList<TestResult> &testResults)
{
    if (testResults.isEmpty()) {
        QMessageBox::warning(nullptr, "Data Error", "No data available for the specified test.");
        return;
    }
    clearPlot();
    for(const auto& testResult : testResults) {
        m_seriesCapacity->append(testResult.time, testResult.capacity);
        m_seriesCurrent->append(testResult.time, testResult.current);
        m_seriesVoltage->append(testResult.time, testResult.voltage);
        qDebug() << testResult.time << testResult.current << testResult.capacity << testResult.voltage;
    }
}

void PlotManager::changePercent(const float &percent)
{
    m_capacity = m_maxCapacity * percent / 100;
    emit percentChanged(percent);
    updateSeriesNames();
}

void PlotManager::devicesStatus(bool isEmpty)
{
    m_deviceIsEmpty = isEmpty;
}

void PlotManager::scaleDataFromDevice(const QList<quint16> &dataPoints)
{
    m_scaledData.append(dataPoints[InputEMF]*m_maxVoltage/1024);
    m_scaledData.append(dataPoints[OutputVoltage]*m_maxVoltage/1024);
    m_scaledData.append((dataPoints[OutputCurrent]-512)*m_maxVoltage/(1024*50*0.1));
}

void PlotManager::saveResults()
{
    emit checkDevices();
    int req = QMessageBox::question(nullptr,"Save results", "Save test results?",
                                    QMessageBox::Yes | QMessageBox::No);
    if(req == QMessageBox::Yes) {
        if(m_testResults.isEmpty()) {
            QMessageBox::warning(0, "Warning!", "No data to save!");
            return;
        }
        if(m_deviceIsEmpty) {
            QMessageBox::warning(0, "Warning!", "No devices to test!");
            return;
        }
        bool ok;
        QString testName = QInputDialog::getText(0, "Set test name", "Enter name:", QLineEdit::Normal, "", &ok);
        if (ok && !testName.isEmpty()) {
            emit dataToSaveReceived(testName, m_testResults);
        }
        else {
            QMessageBox::warning(0, "Warning!", "Uncorrect test name!");
            return;
        }

        QFile file(QString("%1_data_%2.csv").arg(testName, QTime::currentTime().toString()));
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug() << "Error: Cannot open file for writing.";
            return;
        }
        QTextStream out(&file);
        // Запись заголовков столбцов
        out << "SOC (%), Capacity (mAh), Current (A), Voltage (V), Time\n";
        for(const auto& testResult : m_testResults) {
            out << testResult.stateOfCharge << ',' << testResult.capacity
                << ',' << testResult.current << ',' << testResult.voltage << ',' << testResult.time << '\n';
        }
        file.close();
        QMessageBox::information(nullptr, "Info", "Data written successfully.");
        m_testResults.clear();
    }
}
