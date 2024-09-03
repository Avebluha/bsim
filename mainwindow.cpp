#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_connect(new ConnectionSettingsDialog)
    , m_modbus(new ModbusManager)
    , m_emulator(new EmulatorSettingsDialog)
    , m_sql(new SqlManager("QPSQL"))
    , m_chart(new QChart)
    , m_plot(new PlotManager(m_chart))
    , m_deviceModel(new DeviceModel(m_sql))
    , m_testModel(new TestModel(m_sql))
    , m_translator(new QTranslator)
{
    ui->setupUi(this);
    ui->cvGraphicPlot->setChart(m_chart);
    connect(ui->actionConnect, &QAction::triggered, this, &MainWindow::onConnect);
    connect(ui->actionDisconnect, &QAction::triggered, this, &MainWindow::onDisconnect);
    connect(ui->actionQuick_Connect, &QAction::triggered, this, &MainWindow::onQuickConnect);
    connect(m_modbus, &ModbusManager::connectionStatusChanged, this, &MainWindow::changeActionsConnectState);
    connect(m_modbus, &ModbusManager::connectionStatusChanged, this, &MainWindow::onConnectionStatusChanged);
    connect(m_emulator, &EmulatorSettingsDialog::dataUpdated, this, &MainWindow::onModelDataUpdated);
    connect(ui->cbActiveEmulation, &QCheckBox::checkStateChanged, this, &MainWindow::onActivateEmulatorStateChanged);
    connect(ui->actionBattery_Model, &QAction::triggered, m_emulator, &EmulatorSettingsDialog::exec);
    connect(m_plot, &PlotManager::voltageCalculated, this, &MainWindow::setVoltageToDevice);
    connect(ui->btnStart, &QPushButton::clicked, this, &MainWindow::onStart);
    connect(ui->btnStop, &QPushButton::clicked, this, &MainWindow::onStop);
    connect(ui->leTimeRangeMin, &QLineEdit::returnPressed, this, &MainWindow::onTimeRangeChanged);
    connect(ui->leTimeRangeMax, &QLineEdit::returnPressed, this, &MainWindow::onTimeRangeChanged);
    connect(ui->btnFullCharged, &QPushButton::clicked, this, [this](){m_plot->changePercent(100);});
    connect(ui->btnHalfCharged, &QPushButton::clicked, this, [this](){m_plot->changePercent(50);});
    connect(ui->btnOneThiedCharged, &QPushButton::clicked, this, [this](){m_plot->changePercent(33);});
    connect(m_plot, &PlotManager::percentChanged, this, [this](const float& percent){ui->pbCapacityValue->setValue(percent);});
    connect(ui->btnManageTestResults, &QPushButton::clicked, m_plot, &PlotManager::saveResults);
    connect(m_plot, &PlotManager::checkDevices, this, [this](){m_plot->devicesStatus(m_deviceModel && m_deviceModel->rowCount(QModelIndex()) == 0);});
    connect(m_plot, &PlotManager::dataToSaveReceived, this, [this](const QString& testName, const QList<TestResult> testResults){
        m_testModel->addTest(ui->lvDevices->model()->data(ui->lvDevices->currentIndex(), Qt::DisplayRole).toString(),
                             m_emulator->settings().modelName, testName, testResults);
    });
    connect(ui->lvDevices, &QListView::clicked, this, [this](const QModelIndex &index) {
        QString itemText = ui->lvDevices->model()->data(index, Qt::DisplayRole).toString();
        m_testModel->deviceChanged(itemText);
    });
    connect(ui->lvTests, &QListView::doubleClicked, this, [this](const QModelIndex& index){
        const auto testName = ui->lvTests->model()->data(index, Qt::DisplayRole).toString();
        m_plot->updatePlotFromTestData(m_testModel->getTestResult(testName));
    });
    connect(ui->btnAddDevice, &QPushButton::clicked, this, [this](){
        bool ok;
        QString name = QInputDialog::getText(this, "Add device", "Enter name:", QLineEdit::Normal, "", &ok);
        if (ok && !name.isEmpty()) {
            m_deviceModel->addDevice(name);
        }
    });
    connect(ui->btnRemoveDevice, &QPushButton::clicked, this, [this](){
        QModelIndexList indexes = ui->lvDevices->selectionModel()->selectedIndexes();
        std::sort(indexes.begin(), indexes.end(), [](const QModelIndex &a, const QModelIndex &b) {
            return a.row() > b.row();
        });
        for (const QModelIndex &index : indexes) {
            m_deviceModel->removeRows(index.row(), 1, QModelIndex());
        }
    });
    connect(ui->cbLanguage, &QComboBox::currentTextChanged, this, [this](const QString& text){
            if(m_translator->load("QtTranslation_" + text)) qApp->installTranslator(m_translator);
    });
    ui->lvTests->setModel(m_testModel);
    ui->lvDevices->setModel(m_deviceModel);
    m_plot->setupControlPanel(this);
    m_sql->setSettings("localhost", 5432, "emulator_db", "postgres", "1234");
    m_sql->connect();
    changeActionsConnectState(false);
    changeBatteryOptionsButtonsState(false);
    m_emulator->setSqlManager(m_sql);
    m_emulator->loadDefaultData();
    m_connect->loadSettings();
    m_deviceModel->loadDevicesFromDB();
}

MainWindow::~MainWindow()
{
    delete ui;
    m_connect->saveSettings();
}

void MainWindow::changeActionsConnectState(bool connected)
{
    ui->actionConnect->setEnabled(!connected);
    ui->actionQuick_Connect->setEnabled(!connected);
    ui->actionDisconnect->setEnabled(connected);
}

void MainWindow::changeBatteryOptionsButtonsState(bool activated)
{
    ui->btnFullCharged->setEnabled(activated);
    ui->btnHalfCharged->setEnabled(activated);
    ui->btnOneThiedCharged->setEnabled(activated);
}

void MainWindow::changeGraphicOptions(bool started)
{
    ui->btnStart->setEnabled(!started);
    ui->btnStop->setEnabled(started);
}

void MainWindow::onConnect()
{
    if(m_connect->exec() == QDialog::Accepted) {
        if(m_modbus->isConnected()) {
            m_modbus->updateSettings(m_connect->settings());
            return;
        }
        m_modbus->setSettings(m_connect->settings());
        m_modbus->connectDevice();
    }
}

void MainWindow::onQuickConnect()
{
    if(m_modbus->isConnected()) return;
    m_modbus->setSettings(m_connect->settings());
    m_modbus->connectDevice();
}

void MainWindow::onDisconnect()
{
    disconnect(m_modbus, &ModbusManager::dataReceived, m_plot, &PlotManager::updatePlotData);
    m_modbus->disconnectDevice();
}

void MainWindow::onSetValue()
{
    QString voltageText = ui->leSetValue->text();
    if (voltageText.isEmpty()) {
        qDebug() << "Voltage value is empty";
        return;
    }
    // Convert the voltage value to float
    bool conversionOk;
    m_currentVoltage = voltageText.toFloat(&conversionOk);
    if (!conversionOk) {
        qDebug() << "Failed to convert voltage value to float";
        return;
    }
    setVoltageToDevice(m_currentVoltage);
}

void MainWindow::onModelDataUpdated(const EmulatorSettings &data)
{
    m_plot->updateEmulatorSettings(data);
    m_minVoltage = data.findMinMaxVoltage().first;
    m_maxVoltage = data.findMinMaxVoltage().second;
    m_currentVoltage = m_maxVoltage;
    m_modelLoaded = true;
}

void MainWindow::onActivateEmulatorStateChanged(Qt::CheckState status)
{
    onStop();
    switch(status) {
    case Qt::Checked: {
        if(m_modelLoaded && m_modbus->isConnected()) {
            m_plot->setEmulating(true);
            changeBatteryOptionsButtonsState(true);
        }
        else ui->cbActiveEmulation->setCheckState(Qt::Unchecked);
    }
        break;
    default: {
        changeBatteryOptionsButtonsState(Qt::Unchecked);
        m_plot->setEmulating(false);
    }
        break;
    }
}

void MainWindow::onStart()
{
    if(!m_modbus->isConnected()) {
        QMessageBox::warning(this, "Warning!", "Device dieconnected!");
        return;
    }
    if(!m_modelLoaded) {
        QMessageBox::warning(this, "Warning!", "Model not loaded!");
        return;
    }
    const auto connSettings = m_connect->settings();
    m_plot->setDelay(connSettings.delay);
    connect(m_modbus, &ModbusManager::dataReceived, m_plot, &PlotManager::updatePlotData);
    m_modbus->startPeriodicRead();
    changeGraphicOptions(true);
}

void MainWindow::onStop()
{
    disconnect(m_modbus, &ModbusManager::dataReceived, m_plot, &PlotManager::updatePlotData);
    changeGraphicOptions(false);
    m_modbus->stopPeriodicRead();
}

void MainWindow::onTimeRangeChanged()
{
    bool ok1, ok2;
    const auto newRangeMin = ui->leTimeRangeMin->text().toFloat(&ok1);
    const auto newRangeMax = ui->leTimeRangeMax->text().toFloat(&ok2);
    if(ok1 && ok2) {
        m_plot->setRange(newRangeMin, newRangeMax);
    }
}

void MainWindow::onConnectionStatusChanged(bool connected)
{
    if(connected) {
        ui->lbConnectStatus->setText("Device connected");
        ui->lbConnectStatus->setStyleSheet("QLabel { color : green; }");
        changeActionsConnectState(connected);
    }
    else {
        ui->lbConnectStatus->setText("Device disconnected");
        ui->lbConnectStatus->setStyleSheet("QLabel { color : red; }");
        changeActionsConnectState(connected);
    }
}

void MainWindow::setVoltageToDevice(const float &voltage)
{
    // Входит ли значение в условия ограничения
    if (voltage >= m_minVoltage && voltage < m_maxVoltage) {
        // Преобразование напряжения
        const int scaledVoltage = static_cast<int>((voltage / m_maxVoltage) * 1024);
        m_modbus->write(scaledVoltage);
    } else {
        qCritical() << "Value out of range";
    }
}

void MainWindow::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }
}
