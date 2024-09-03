#include "emulatorsettingsdialog.h"
#include "qevent.h"
#include "ui_emulatorsettingsdialog.h"

EmulatorSettingsDialog::EmulatorSettingsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EmulatorSettingsDialog)
{
    ui->setupUi(this);
    createModel();
    connect(ui->btnLoad, &QPushButton::clicked, this, &EmulatorSettingsDialog::onLoadFromJson);
    connect(ui->btnSave, &QPushButton::clicked, this, &EmulatorSettingsDialog::onSaveToJson);
    connect(ui->btnChangeName, &QPushButton::clicked, this, &EmulatorSettingsDialog::onChangeModelName);
    connect(ui->cbModelName, &QComboBox::activated, this, &::EmulatorSettingsDialog::updateUI);
    connect(ui->btnSaveToDB, &QPushButton::clicked, this, &EmulatorSettingsDialog::saveModelToDatabase);
}

EmulatorSettingsDialog::~EmulatorSettingsDialog()
{
    delete ui;
}

void EmulatorSettingsDialog::EmulatorSettingsDialog::updateUI(int index) {
    // Обновление интерфейса на основе выбранной модели
    const auto& settings = m_listSettings.at(index);
    const auto voltages = settings.findMinMaxVoltage();
    ui->leMinVoltage->setText(QString::number(voltages.first));
    ui->leMaxVoltage->setText(QString::number(voltages.second));
    ui->leMaxCapacity->setText(QString::number(settings.maxCapacity));
    m_batteryModel->setData(settings.modelData);
    updateModel(settings.modelData);
}

void EmulatorSettingsDialog::updateCurrentModel()
{
    int currentIndex = ui->cbModelName->currentIndex();
    if (currentIndex == -1) return;  // Проверка на валидность индекса
    // Обновляем данные модели на основе данных из UI
    EmulatorSettings &currentSetting = m_listSettings[currentIndex];
    currentSetting.maxCapacity = ui->leMaxCapacity->text().toFloat();
    currentSetting.modelData = m_batteryModel->getData();
    emit dataUpdated(m_listSettings[currentIndex]);
}

void EmulatorSettingsDialog::EmulatorSettingsDialog::createModel()
{
    m_batteryModel = new BatteryModel();
    m_delegate = new DoubleSpinBoxDelegate();
    ui->tvBatteryModel->setModel(m_batteryModel);
    ui->tvBatteryModel->verticalHeader()->hide();
    ui->tvBatteryModel->horizontalHeader()->setStretchLastSection(true);
    ui->tvBatteryModel->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tvBatteryModel->setItemDelegateForColumn(1, m_delegate);
}

void EmulatorSettingsDialog::addSettings(const EmulatorSettings &settings)
{
    m_listSettings.append(settings);
    updateModel(settings.modelData);
    updateModelNames();
}

void EmulatorSettingsDialog::updateModel(const QList<QPointF> &data)
{
    m_batteryModel->setData(data);
}

void EmulatorSettingsDialog::EmulatorSettingsDialog::updateModelNames()
{
    ui->cbModelName->clear();  // Очищаем текущий список имен
    QMap<QString, int> nameCount;  // Используем QMap для удобства сортировки
    for (const auto& setting : m_listSettings) {
        QString baseName = setting.modelName;
        int count = nameCount[baseName]++;

        if (count > 0) {  // Если имя уже встречалось, добавляем номер к имени
            ui->cbModelName->addItem(baseName + " " + QString::number(count));
        } else {
            ui->cbModelName->addItem(baseName);
        }
    }
    // Если в комбобоксе есть элементы, устанавливаем выбор на первый элемент
    if (!m_listSettings.isEmpty()) {
        ui->cbModelName->setCurrentIndex(ui->cbModelName->count()-1);
        emit ui->cbModelName->activated(ui->cbModelName->count()-1);
    }
}

void EmulatorSettingsDialog::closeEvent(QCloseEvent *event) {
    Q_UNUSED(event);
    updateSettingsAndClose();
}

void EmulatorSettingsDialog::loadDefaultData()
{
    const auto batteryModels = m_sql->selectQuery("battery_models", QStringList({"id", "name", "max_capacity"}));
    if(batteryModels.isEmpty()) return;
    for(const auto& model : batteryModels) {
        const auto dataModels = m_sql->selectQuery("data_models", QStringList({"state_of_charge", "voltage"}),
                                                   QString("battery_model_id=%1").arg(model.constFirst().toInt()));
        if(!dataModels.isEmpty()) {
            QList<QPointF> data;
            for(const auto& point : dataModels) {
                data.append(QPointF(point.constFirst().toInt(),point.constLast().toFloat()));
            }
            EmulatorSettings tmpSettings = {
                model[1].toString(),
                model[2].toFloat(),
                data
            };
            m_listSettings.append(tmpSettings);
            updateModel(data);
            updateModelNames();
            updateCurrentModel();
        }
    }
}

void EmulatorSettingsDialog::setSqlManager(SqlManager *sql)
{
    m_sql = sql;
}

void EmulatorSettingsDialog::saveModelToDatabase() {
    updateCurrentModel();  // Обновляем текущие настройки модели
    int currentIndex = ui->cbModelName->currentIndex();
    if (currentIndex == -1) return;
    const EmulatorSettings &currentSetting = m_listSettings[currentIndex];
    const auto modelName = m_sql->selectQuery("battery_models", QStringList("id"), QString("name='%1'").arg(currentSetting.modelName));
    if(!modelName.isEmpty()) {
        QMessageBox::warning(0, "Error", "Current model already exist!");
        return;
    }
    const QVariant lastId = m_sql->insertData("battery_models", QStringList({"name", "max_capacity"}),
                                                    QVariantList({currentSetting.modelName, currentSetting.maxCapacity}));
    if(!lastId.isValid()) {
        qDebug() << "Failed to retrieve last inserted ID.";
        return;
    }
    for(int i = 0; i < currentSetting.modelData.size(); ++i) {
        m_sql->insertData("data_models", QStringList({"state_of_charge", "battery_model_id", "voltage"}),
                   QVariantList({currentSetting.modelData[i].x(),lastId.toInt(), currentSetting.modelData[i].y()}));
    }
}

EmulatorSettings EmulatorSettingsDialog::settings() const
{
    return m_listSettings.at(ui->cbModelName->currentIndex());
}

void EmulatorSettingsDialog::EmulatorSettingsDialog::updateSettingsAndClose() {
    updateCurrentModel();
    hide();
}

void EmulatorSettingsDialog::onLoadFromJson() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open JSON File", "", "JSON Files (*.json)");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
            addSettings(EmulatorSettings::fromJson(doc.object()));
            QMessageBox::information(this, "Info", "Model loaded successfully!");
        }
    }
}

void EmulatorSettingsDialog::onSaveToJson() {
    updateCurrentModel();
    QString fileName = QFileDialog::getSaveFileName(this, "Save JSON File", "", "JSON Files (*.json)");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QJsonObject settingsObj = m_listSettings[ui->cbModelName->currentIndex()].toJson();
            QJsonDocument doc(settingsObj);
            file.write(doc.toJson());
            QMessageBox::information(this, "Info", "Model saved successfully!");
        }
    }
}

void EmulatorSettingsDialog::onChangeModelName()
{
    const auto currentIndex = ui->cbModelName->currentIndex();
    if (currentIndex == -1) return;
    const auto settings = m_listSettings.at(currentIndex);
    bool ok;
    const QString oldName = settings.modelName;
    QString newValue = QInputDialog::getText(this, tr("Input"), tr("Enter new name:"), QLineEdit::Normal,
                                             QString("Bat_min-%1_max_%2_cap_%3mAh").arg(settings.findMinMaxVoltage().first)
                                                 .arg(settings.findMinMaxVoltage().second)
                                                 .arg(settings.maxCapacity), &ok);
    if (ok) {
        QString tableName = "battery_models";
        QString columnName = "name";
        QString condition = "name = '" + oldName + "'"; // Используем старое название как ключ
        if (!m_sql->updateRecord(tableName, columnName, newValue, condition)) {
            QMessageBox::warning(this, tr("Database Error"), tr("Failed to update the model name in the database."));
            // В случае ошибки, восстанавливаем старое имя в интерфейсе
            m_listSettings[currentIndex].modelName = oldName;
            ui->cbModelName->setItemText(currentIndex, oldName);
        }
        if (!m_sql->updateRecord(tableName, columnName, newValue, condition)) {
            QMessageBox::warning(this, tr("Database Error"), tr("Failed to update the model name in the database."));
        }
        m_listSettings[ui->cbModelName->currentIndex()].modelName = newValue;
        ui->cbModelName->setItemText(ui->cbModelName->currentIndex(), newValue);
    }
}
