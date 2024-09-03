/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCharts/QChartView>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionQuick_Connect;
    QAction *actionConnect;
    QAction *actionDisconnect;
    QAction *actionBattery_Model;
    QAction *actionTests_Conducted;
    QWidget *centralwidget;
    QGridLayout *gridLayout_6;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_4;
    QChartView *cvGraphicPlot;
    QHBoxLayout *horizontalLayout;
    QLineEdit *leSetValue;
    QPushButton *btnSetValue;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_3;
    QLabel *lbConnectStatus;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QProgressBar *pbCapacityValue;
    QPushButton *btnFullCharged;
    QPushButton *btnHalfCharged;
    QPushButton *btnOneThiedCharged;
    QCheckBox *cbActiveEmulation;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QLineEdit *leTimeRangeMax;
    QLineEdit *leTimeRangeMin;
    QVBoxLayout *verticalLayout_2;
    QPushButton *btnStart;
    QPushButton *btnStop;
    QPushButton *btnManageTestResults;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_5;
    QListView *lvDevices;
    QVBoxLayout *verticalLayout_6;
    QPushButton *btnAddDevice;
    QPushButton *btnRemoveDevice;
    QSpacerItem *verticalSpacer_2;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_4;
    QListView *lvTests;
    QVBoxLayout *verticalLayout_7;
    QPushButton *btnAddTest;
    QPushButton *btnRemoveTest;
    QSpacerItem *verticalSpacer_4;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_2;
    QComboBox *cbLanguage;
    QMenuBar *menubar;
    QMenu *menuConnection_Settings;
    QMenu *menuEmulator_Settings;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1111, 926);
        actionQuick_Connect = new QAction(MainWindow);
        actionQuick_Connect->setObjectName("actionQuick_Connect");
        actionConnect = new QAction(MainWindow);
        actionConnect->setObjectName("actionConnect");
        actionDisconnect = new QAction(MainWindow);
        actionDisconnect->setObjectName("actionDisconnect");
        actionBattery_Model = new QAction(MainWindow);
        actionBattery_Model->setObjectName("actionBattery_Model");
        actionTests_Conducted = new QAction(MainWindow);
        actionTests_Conducted->setObjectName("actionTests_Conducted");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout_6 = new QGridLayout(centralwidget);
        gridLayout_6->setObjectName("gridLayout_6");
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName("splitter");
        splitter->setOrientation(Qt::Horizontal);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName("layoutWidget");
        verticalLayout_4 = new QVBoxLayout(layoutWidget);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        cvGraphicPlot = new QChartView(layoutWidget);
        cvGraphicPlot->setObjectName("cvGraphicPlot");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cvGraphicPlot->sizePolicy().hasHeightForWidth());
        cvGraphicPlot->setSizePolicy(sizePolicy);
        cvGraphicPlot->setStyleSheet(QString::fromUtf8("border: 1px solid"));

        verticalLayout_4->addWidget(cvGraphicPlot);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        leSetValue = new QLineEdit(layoutWidget);
        leSetValue->setObjectName("leSetValue");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(leSetValue->sizePolicy().hasHeightForWidth());
        leSetValue->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(leSetValue);

        btnSetValue = new QPushButton(layoutWidget);
        btnSetValue->setObjectName("btnSetValue");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(btnSetValue->sizePolicy().hasHeightForWidth());
        btnSetValue->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(btnSetValue);


        verticalLayout_4->addLayout(horizontalLayout);

        splitter->addWidget(layoutWidget);
        scrollArea = new QScrollArea(splitter);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setWidgetResizable(true);
        scrollArea->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 700, 864));
        gridLayout_3 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_3->setObjectName("gridLayout_3");
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        groupBox_4 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_4->setObjectName("groupBox_4");
        verticalLayout_3 = new QVBoxLayout(groupBox_4);
        verticalLayout_3->setObjectName("verticalLayout_3");
        lbConnectStatus = new QLabel(groupBox_4);
        lbConnectStatus->setObjectName("lbConnectStatus");
        lbConnectStatus->setStyleSheet(QString::fromUtf8("color: red;"));

        verticalLayout_3->addWidget(lbConnectStatus);


        verticalLayout_5->addWidget(groupBox_4);

        groupBox = new QGroupBox(scrollAreaWidgetContents);
        groupBox->setObjectName("groupBox");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy3);
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName("gridLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        pbCapacityValue = new QProgressBar(groupBox);
        pbCapacityValue->setObjectName("pbCapacityValue");
        sizePolicy1.setHeightForWidth(pbCapacityValue->sizePolicy().hasHeightForWidth());
        pbCapacityValue->setSizePolicy(sizePolicy1);
        pbCapacityValue->setStyleSheet(QString::fromUtf8("QProgressBar {\n"
"    border: 2px solid grey;\n"
"    border-radius: 5px;\n"
"}\n"
"\n"
"QProgressBar::chunk {\n"
"    background-color: #05B8CC;\n"
"    width: 20px;\n"
"}\n"
"\n"
"QProgressBar {\n"
"    border: 2px solid grey;\n"
"    border-radius: 5px;\n"
"    text-align: center;\n"
"}"));
        pbCapacityValue->setValue(24);

        verticalLayout->addWidget(pbCapacityValue);

        btnFullCharged = new QPushButton(groupBox);
        btnFullCharged->setObjectName("btnFullCharged");

        verticalLayout->addWidget(btnFullCharged);

        btnHalfCharged = new QPushButton(groupBox);
        btnHalfCharged->setObjectName("btnHalfCharged");

        verticalLayout->addWidget(btnHalfCharged);

        btnOneThiedCharged = new QPushButton(groupBox);
        btnOneThiedCharged->setObjectName("btnOneThiedCharged");

        verticalLayout->addWidget(btnOneThiedCharged);

        cbActiveEmulation = new QCheckBox(groupBox);
        cbActiveEmulation->setObjectName("cbActiveEmulation");

        verticalLayout->addWidget(cbActiveEmulation);


        gridLayout->addLayout(verticalLayout, 1, 0, 1, 1);


        verticalLayout_5->addWidget(groupBox);

        groupBox_2 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_2->setObjectName("groupBox_2");
        sizePolicy3.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy3);
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName("gridLayout_2");
        leTimeRangeMax = new QLineEdit(groupBox_2);
        leTimeRangeMax->setObjectName("leTimeRangeMax");

        gridLayout_2->addWidget(leTimeRangeMax, 1, 1, 1, 1);

        leTimeRangeMin = new QLineEdit(groupBox_2);
        leTimeRangeMin->setObjectName("leTimeRangeMin");

        gridLayout_2->addWidget(leTimeRangeMin, 1, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        btnStart = new QPushButton(groupBox_2);
        btnStart->setObjectName("btnStart");

        verticalLayout_2->addWidget(btnStart);

        btnStop = new QPushButton(groupBox_2);
        btnStop->setObjectName("btnStop");
        btnStop->setEnabled(false);

        verticalLayout_2->addWidget(btnStop);


        gridLayout_2->addLayout(verticalLayout_2, 0, 0, 1, 2);

        btnManageTestResults = new QPushButton(groupBox_2);
        btnManageTestResults->setObjectName("btnManageTestResults");

        gridLayout_2->addWidget(btnManageTestResults, 2, 0, 1, 2);


        verticalLayout_5->addWidget(groupBox_2);

        groupBox_6 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_6->setObjectName("groupBox_6");
        gridLayout_5 = new QGridLayout(groupBox_6);
        gridLayout_5->setObjectName("gridLayout_5");
        lvDevices = new QListView(groupBox_6);
        lvDevices->setObjectName("lvDevices");

        gridLayout_5->addWidget(lvDevices, 1, 0, 1, 1);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName("verticalLayout_6");
        btnAddDevice = new QPushButton(groupBox_6);
        btnAddDevice->setObjectName("btnAddDevice");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(btnAddDevice->sizePolicy().hasHeightForWidth());
        btnAddDevice->setSizePolicy(sizePolicy4);
        btnAddDevice->setMinimumSize(QSize(15, 0));

        verticalLayout_6->addWidget(btnAddDevice);

        btnRemoveDevice = new QPushButton(groupBox_6);
        btnRemoveDevice->setObjectName("btnRemoveDevice");
        sizePolicy4.setHeightForWidth(btnRemoveDevice->sizePolicy().hasHeightForWidth());
        btnRemoveDevice->setSizePolicy(sizePolicy4);
        btnRemoveDevice->setMinimumSize(QSize(15, 0));

        verticalLayout_6->addWidget(btnRemoveDevice);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_2);


        gridLayout_5->addLayout(verticalLayout_6, 1, 1, 1, 1);


        verticalLayout_5->addWidget(groupBox_6);

        groupBox_5 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_5->setObjectName("groupBox_5");
        gridLayout_4 = new QGridLayout(groupBox_5);
        gridLayout_4->setObjectName("gridLayout_4");
        lvTests = new QListView(groupBox_5);
        lvTests->setObjectName("lvTests");

        gridLayout_4->addWidget(lvTests, 0, 0, 1, 1);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName("verticalLayout_7");
        btnAddTest = new QPushButton(groupBox_5);
        btnAddTest->setObjectName("btnAddTest");
        sizePolicy4.setHeightForWidth(btnAddTest->sizePolicy().hasHeightForWidth());
        btnAddTest->setSizePolicy(sizePolicy4);
        btnAddTest->setMinimumSize(QSize(15, 0));

        verticalLayout_7->addWidget(btnAddTest);

        btnRemoveTest = new QPushButton(groupBox_5);
        btnRemoveTest->setObjectName("btnRemoveTest");
        sizePolicy4.setHeightForWidth(btnRemoveTest->sizePolicy().hasHeightForWidth());
        btnRemoveTest->setSizePolicy(sizePolicy4);
        btnRemoveTest->setMinimumSize(QSize(15, 0));

        verticalLayout_7->addWidget(btnRemoveTest);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_4);


        gridLayout_4->addLayout(verticalLayout_7, 0, 1, 1, 1);


        verticalLayout_5->addWidget(groupBox_5);

        groupBox_3 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_3->setObjectName("groupBox_3");
        horizontalLayout_2 = new QHBoxLayout(groupBox_3);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        cbLanguage = new QComboBox(groupBox_3);
        cbLanguage->addItem(QString());
        cbLanguage->addItem(QString());
        cbLanguage->setObjectName("cbLanguage");

        horizontalLayout_2->addWidget(cbLanguage);


        verticalLayout_5->addWidget(groupBox_3);


        gridLayout_3->addLayout(verticalLayout_5, 0, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);
        splitter->addWidget(scrollArea);

        gridLayout_6->addWidget(splitter, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1111, 20));
        menuConnection_Settings = new QMenu(menubar);
        menuConnection_Settings->setObjectName("menuConnection_Settings");
        menuEmulator_Settings = new QMenu(menubar);
        menuEmulator_Settings->setObjectName("menuEmulator_Settings");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuConnection_Settings->menuAction());
        menubar->addAction(menuEmulator_Settings->menuAction());
        menuConnection_Settings->addAction(actionQuick_Connect);
        menuConnection_Settings->addSeparator();
        menuConnection_Settings->addAction(actionConnect);
        menuConnection_Settings->addAction(actionDisconnect);
        menuEmulator_Settings->addAction(actionBattery_Model);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "bsim_v9", nullptr));
        actionQuick_Connect->setText(QCoreApplication::translate("MainWindow", "Quick Connect", nullptr));
        actionConnect->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        actionDisconnect->setText(QCoreApplication::translate("MainWindow", "Disconnect", nullptr));
        actionBattery_Model->setText(QCoreApplication::translate("MainWindow", "Battery Model", nullptr));
        actionTests_Conducted->setText(QCoreApplication::translate("MainWindow", "Tests Conducted", nullptr));
        btnSetValue->setText(QCoreApplication::translate("MainWindow", "Set Value", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "Status", nullptr));
        lbConnectStatus->setText(QCoreApplication::translate("MainWindow", "Device disconnected", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Battery Options", nullptr));
        btnFullCharged->setText(QCoreApplication::translate("MainWindow", "Full Charged", nullptr));
        btnHalfCharged->setText(QCoreApplication::translate("MainWindow", "Half Charged", nullptr));
        btnOneThiedCharged->setText(QCoreApplication::translate("MainWindow", "One Third Charged", nullptr));
        cbActiveEmulation->setText(QCoreApplication::translate("MainWindow", "Active Emulation", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Graphic Options", nullptr));
#if QT_CONFIG(tooltip)
        leTimeRangeMax->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        leTimeRangeMax->setPlaceholderText(QCoreApplication::translate("MainWindow", "Max Time Range Value", nullptr));
#if QT_CONFIG(tooltip)
        leTimeRangeMin->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        leTimeRangeMin->setText(QString());
        leTimeRangeMin->setPlaceholderText(QCoreApplication::translate("MainWindow", "Min Time Range Value", nullptr));
        btnStart->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        btnStop->setText(QCoreApplication::translate("MainWindow", "Stop", nullptr));
        btnManageTestResults->setText(QCoreApplication::translate("MainWindow", "Manage Test Results", nullptr));
        groupBox_6->setTitle(QCoreApplication::translate("MainWindow", "Devices", nullptr));
        btnAddDevice->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        btnRemoveDevice->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("MainWindow", "Tests Conducted", nullptr));
        btnAddTest->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        btnRemoveTest->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "Language", nullptr));
        cbLanguage->setItemText(0, QCoreApplication::translate("MainWindow", "en_US", nullptr));
        cbLanguage->setItemText(1, QCoreApplication::translate("MainWindow", "ru_RU", nullptr));

        menuConnection_Settings->setTitle(QCoreApplication::translate("MainWindow", "Connection", nullptr));
        menuEmulator_Settings->setTitle(QCoreApplication::translate("MainWindow", "Emulator", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
