/********************************************************************************
** Form generated from reading UI file 'connectionsettingsdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNECTIONSETTINGSDIALOG_H
#define UI_CONNECTIONSETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ConnectionSettingsDialog
{
public:
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLineEdit *leResponseTimeout;
    QLabel *label;
    QLabel *label_3;
    QLabel *label_2;
    QLabel *label_5;
    QLineEdit *leDelay;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_4;
    QLabel *label_8;
    QComboBox *cbStopBits;
    QComboBox *cbParity;
    QComboBox *cbDataBits;
    QComboBox *cbBaud;
    QComboBox *cbPortName;
    QLabel *label_9;
    QPushButton *btnConnect;

    void setupUi(QDialog *ConnectionSettingsDialog)
    {
        if (ConnectionSettingsDialog->objectName().isEmpty())
            ConnectionSettingsDialog->setObjectName("ConnectionSettingsDialog");
        ConnectionSettingsDialog->resize(340, 300);
        gridLayout_3 = new QGridLayout(ConnectionSettingsDialog);
        gridLayout_3->setObjectName("gridLayout_3");
        groupBox = new QGroupBox(ConnectionSettingsDialog);
        groupBox->setObjectName("groupBox");
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        leResponseTimeout = new QLineEdit(groupBox);
        leResponseTimeout->setObjectName("leResponseTimeout");

        gridLayout->addWidget(leResponseTimeout, 5, 1, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName("label");

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName("label_5");

        gridLayout->addWidget(label_5, 5, 0, 1, 1);

        leDelay = new QLineEdit(groupBox);
        leDelay->setObjectName("leDelay");

        gridLayout->addWidget(leDelay, 6, 1, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName("label_6");

        gridLayout->addWidget(label_6, 6, 0, 1, 1);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName("label_7");

        gridLayout->addWidget(label_7, 4, 0, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName("label_8");

        gridLayout->addWidget(label_8, 5, 2, 1, 1);

        cbStopBits = new QComboBox(groupBox);
        cbStopBits->setObjectName("cbStopBits");

        gridLayout->addWidget(cbStopBits, 4, 1, 1, 2);

        cbParity = new QComboBox(groupBox);
        cbParity->setObjectName("cbParity");

        gridLayout->addWidget(cbParity, 3, 1, 1, 2);

        cbDataBits = new QComboBox(groupBox);
        cbDataBits->setObjectName("cbDataBits");

        gridLayout->addWidget(cbDataBits, 2, 1, 1, 2);

        cbBaud = new QComboBox(groupBox);
        cbBaud->setObjectName("cbBaud");

        gridLayout->addWidget(cbBaud, 1, 1, 1, 2);

        cbPortName = new QComboBox(groupBox);
        cbPortName->setObjectName("cbPortName");

        gridLayout->addWidget(cbPortName, 0, 1, 1, 2);

        label_9 = new QLabel(groupBox);
        label_9->setObjectName("label_9");

        gridLayout->addWidget(label_9, 6, 2, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        btnConnect = new QPushButton(groupBox);
        btnConnect->setObjectName("btnConnect");

        gridLayout_2->addWidget(btnConnect, 1, 0, 1, 1);


        gridLayout_3->addWidget(groupBox, 0, 0, 1, 1);


        retranslateUi(ConnectionSettingsDialog);

        QMetaObject::connectSlotsByName(ConnectionSettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *ConnectionSettingsDialog)
    {
        ConnectionSettingsDialog->setWindowTitle(QCoreApplication::translate("ConnectionSettingsDialog", "Connection Setup", nullptr));
        groupBox->setTitle(QCoreApplication::translate("ConnectionSettingsDialog", "Serial Settings", nullptr));
        label->setText(QCoreApplication::translate("ConnectionSettingsDialog", "Port", nullptr));
        label_3->setText(QCoreApplication::translate("ConnectionSettingsDialog", "Data Bits", nullptr));
        label_2->setText(QCoreApplication::translate("ConnectionSettingsDialog", "Baud", nullptr));
        label_5->setText(QCoreApplication::translate("ConnectionSettingsDialog", "Response Timeout", nullptr));
        label_6->setText(QCoreApplication::translate("ConnectionSettingsDialog", "Delay between Polls", nullptr));
        label_7->setText(QCoreApplication::translate("ConnectionSettingsDialog", "Stop Bits", nullptr));
        label_4->setText(QCoreApplication::translate("ConnectionSettingsDialog", "Parity", nullptr));
        label_8->setText(QCoreApplication::translate("ConnectionSettingsDialog", "[ms]", nullptr));
        label_9->setText(QCoreApplication::translate("ConnectionSettingsDialog", "[ms]", nullptr));
        btnConnect->setText(QCoreApplication::translate("ConnectionSettingsDialog", "Connect", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConnectionSettingsDialog: public Ui_ConnectionSettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECTIONSETTINGSDIALOG_H
