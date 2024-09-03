#ifndef EMULATORSETTINGSDIALOG_H
#define EMULATORSETTINGSDIALOG_H

#include "batterymodel.h"
#include "doublespinboxdelegate.h"
#include "structs.h"
#include "sqlmanager.h"
#include <QDialog>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>
#include <QItemDelegate>

namespace Ui {
class EmulatorSettingsDialog;
}

class EmulatorSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EmulatorSettingsDialog(QWidget *parent = nullptr);
    ~EmulatorSettingsDialog();

    void setSqlManager(SqlManager *sql);
    void loadDefaultData();
    EmulatorSettings settings() const;

signals:
    void dataUpdated(const EmulatorSettings &settings);

private:
    Ui::EmulatorSettingsDialog *ui;
    QList<EmulatorSettings> m_listSettings;
    DoubleSpinBoxDelegate *m_delegate;
    BatteryModel *m_batteryModel;
    SqlManager *m_sql;

private:
    void createModel();
    void updateUI(int index);
    void updateCurrentModel();
    void addSettings(const EmulatorSettings &settings);
    void updateModel(const QList<QPointF> &data);
    void saveModelToDatabase();

    void updateModelNames();
    void closeEvent(QCloseEvent *event);
    void updateSettingsAndClose();
private slots:
    void onLoadFromJson();
    void onSaveToJson();
    void onChangeModelName();
};

#endif // EMULATORSETTINGSDIALOG_H
