/********************************************************************************
** Form generated from reading UI file 'emulatorsettingsdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EMULATORSETTINGSDIALOG_H
#define UI_EMULATORSETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_EmulatorSettingsDialog
{
public:
    QGridLayout *gridLayout_4;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *leMaxCapacity;
    QComboBox *cbModelName;
    QLabel *label_5;
    QLineEdit *leMinVoltage;
    QLabel *label_7;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_2;
    QLineEdit *leMaxVoltage;
    QLabel *label_6;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QTableView *tvBatteryModel;
    QPushButton *btnChangeName;
    QPushButton *btnSave;
    QPushButton *btnLoad;
    QPushButton *btnSaveToDB;

    void setupUi(QDialog *EmulatorSettingsDialog)
    {
        if (EmulatorSettingsDialog->objectName().isEmpty())
            EmulatorSettingsDialog->setObjectName("EmulatorSettingsDialog");
        EmulatorSettingsDialog->resize(302, 386);
        gridLayout_4 = new QGridLayout(EmulatorSettingsDialog);
        gridLayout_4->setObjectName("gridLayout_4");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        groupBox = new QGroupBox(EmulatorSettingsDialog);
        groupBox->setObjectName("groupBox");
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        label = new QLabel(groupBox);
        label->setObjectName("label");

        gridLayout->addWidget(label, 0, 0, 1, 1);

        leMaxCapacity = new QLineEdit(groupBox);
        leMaxCapacity->setObjectName("leMaxCapacity");

        gridLayout->addWidget(leMaxCapacity, 3, 1, 1, 2);

        cbModelName = new QComboBox(groupBox);
        cbModelName->setObjectName("cbModelName");

        gridLayout->addWidget(cbModelName, 0, 1, 1, 3);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName("label_5");

        gridLayout->addWidget(label_5, 1, 3, 1, 1);

        leMinVoltage = new QLineEdit(groupBox);
        leMinVoltage->setObjectName("leMinVoltage");

        gridLayout->addWidget(leMinVoltage, 2, 1, 1, 2);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName("label_7");

        gridLayout->addWidget(label_7, 3, 3, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        leMaxVoltage = new QLineEdit(groupBox);
        leMaxVoltage->setObjectName("leMaxVoltage");

        gridLayout->addWidget(leMaxVoltage, 1, 1, 1, 2);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName("label_6");

        gridLayout->addWidget(label_6, 2, 3, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(EmulatorSettingsDialog);
        groupBox_2->setObjectName("groupBox_2");
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setObjectName("gridLayout_3");
        tvBatteryModel = new QTableView(groupBox_2);
        tvBatteryModel->setObjectName("tvBatteryModel");

        gridLayout_3->addWidget(tvBatteryModel, 0, 0, 1, 2);

        btnChangeName = new QPushButton(groupBox_2);
        btnChangeName->setObjectName("btnChangeName");

        gridLayout_3->addWidget(btnChangeName, 2, 0, 1, 2);

        btnSave = new QPushButton(groupBox_2);
        btnSave->setObjectName("btnSave");

        gridLayout_3->addWidget(btnSave, 4, 0, 1, 1);

        btnLoad = new QPushButton(groupBox_2);
        btnLoad->setObjectName("btnLoad");

        gridLayout_3->addWidget(btnLoad, 4, 1, 1, 1);

        btnSaveToDB = new QPushButton(groupBox_2);
        btnSaveToDB->setObjectName("btnSaveToDB");

        gridLayout_3->addWidget(btnSaveToDB, 3, 0, 1, 2);


        verticalLayout->addWidget(groupBox_2);


        gridLayout_4->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(EmulatorSettingsDialog);

        QMetaObject::connectSlotsByName(EmulatorSettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *EmulatorSettingsDialog)
    {
        EmulatorSettingsDialog->setWindowTitle(QCoreApplication::translate("EmulatorSettingsDialog", "Model Setup", nullptr));
        groupBox->setTitle(QCoreApplication::translate("EmulatorSettingsDialog", "Model Settings", nullptr));
        label->setText(QCoreApplication::translate("EmulatorSettingsDialog", "Model", nullptr));
        label_5->setText(QCoreApplication::translate("EmulatorSettingsDialog", "V", nullptr));
        label_7->setText(QCoreApplication::translate("EmulatorSettingsDialog", "mAh", nullptr));
        label_3->setText(QCoreApplication::translate("EmulatorSettingsDialog", "Min Voltage", nullptr));
        label_4->setText(QCoreApplication::translate("EmulatorSettingsDialog", "Max Capacity", nullptr));
        label_2->setText(QCoreApplication::translate("EmulatorSettingsDialog", "Max Voltage", nullptr));
        label_6->setText(QCoreApplication::translate("EmulatorSettingsDialog", "V", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("EmulatorSettingsDialog", "Model Data", nullptr));
        btnChangeName->setText(QCoreApplication::translate("EmulatorSettingsDialog", "Change Model Name", nullptr));
        btnSave->setText(QCoreApplication::translate("EmulatorSettingsDialog", "Save to Json", nullptr));
        btnLoad->setText(QCoreApplication::translate("EmulatorSettingsDialog", "Load from Json", nullptr));
        btnSaveToDB->setText(QCoreApplication::translate("EmulatorSettingsDialog", "Save to DB", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EmulatorSettingsDialog: public Ui_EmulatorSettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EMULATORSETTINGSDIALOG_H
