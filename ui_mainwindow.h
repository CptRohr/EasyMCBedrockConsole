/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "widgets\onlineplayerwidget.h"
#include "widgets\serverconsolewidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QLineEdit *serverState;
    QSlider *difficultySlider;
    QLabel *difficultyLabel;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *startServer;
    QPushButton *stopServer;
    QPushButton *restartAfter;
    QLineEdit *restartAfterSeconds;
    QLabel *restartAfterLabel;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QFrame *onlineBarFrame;
    QHBoxLayout *horizontalLayout_10;
    OnlinePlayerWidget *onlineBar;
    QSpacerItem *horizontalSpacer;
    QLabel *nextBackupLabel;
    QHBoxLayout *horizontalLayout_7;
    QLabel *storageUsage;
    QProgressBar *storageUsedBar;
    ServerConsoleWidget *serverConsole;
    QWidget *tab_3;
    QHBoxLayout *playerListLayout;
    QTreeView *playerList;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_4;
    QLabel *invalidServerLocationLabel;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QLineEdit *serverFolder;
    QPushButton *selectServerFolder;
    QLabel *invalidBackupLocationLabel;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QLineEdit *backupFolder;
    QPushButton *selectBackupFolder;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_9;
    QCheckBox *restrictBackupsStorageUsage;
    QLineEdit *maxStorageUsageMiB;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_3;
    QCheckBox *restrictNumberOfBackups;
    QLineEdit *restrictNumberOfBackupsAmount;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout_11;
    QCheckBox *restrictBackupAge;
    QSlider *restrictBackupAgeSlider;
    QSpacerItem *verticalSpacer;
    QLabel *copyright;
    QWidget *tab_4;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout;
    QPushButton *instantBackup;
    QPushButton *scheduleBackup;
    QSpacerItem *horizontalSpacer_6;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_8;
    QCheckBox *doRegularBackups;
    QSlider *backupFrequencySlider;
    QSpacerItem *horizontalSpacer_4;
    QCheckBox *alwaysBackupOnTime;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_7;
    QGridLayout *gridLayout;
    QCheckBox *backupOnJoin;
    QCheckBox *backupOnLeave;
    QHBoxLayout *horizontalLayout_6;
    QLabel *backupDelayLabel;
    QSlider *backupDelaySlider;
    QSpacerItem *verticalSpacer_4;
    QWidget *tab_5;
    QVBoxLayout *verticalLayout_8;
    QScrollArea *serverPropertiesScrollArea;
    QWidget *scrollAreaWidgetContents;
    QHBoxLayout *horizontalLayout_12;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *saveConfigAndRestart;
    QPushButton *saveConfig;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(973, 593);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setUnifiedTitleAndToolBarOnMac(true);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label = new QLabel(centralwidget);
        label->setObjectName("label");

        horizontalLayout_3->addWidget(label);

        serverState = new QLineEdit(centralwidget);
        serverState->setObjectName("serverState");
        serverState->setMaximumSize(QSize(100, 16777215));
        serverState->setReadOnly(true);

        horizontalLayout_3->addWidget(serverState);

        difficultySlider = new QSlider(centralwidget);
        difficultySlider->setObjectName("difficultySlider");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(difficultySlider->sizePolicy().hasHeightForWidth());
        difficultySlider->setSizePolicy(sizePolicy1);
        difficultySlider->setMaximum(3);
        difficultySlider->setPageStep(1);
        difficultySlider->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(difficultySlider);

        difficultyLabel = new QLabel(centralwidget);
        difficultyLabel->setObjectName("difficultyLabel");

        horizontalLayout_3->addWidget(difficultyLabel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        startServer = new QPushButton(centralwidget);
        startServer->setObjectName("startServer");

        horizontalLayout_3->addWidget(startServer);

        stopServer = new QPushButton(centralwidget);
        stopServer->setObjectName("stopServer");

        horizontalLayout_3->addWidget(stopServer);

        restartAfter = new QPushButton(centralwidget);
        restartAfter->setObjectName("restartAfter");

        horizontalLayout_3->addWidget(restartAfter);

        restartAfterSeconds = new QLineEdit(centralwidget);
        restartAfterSeconds->setObjectName("restartAfterSeconds");
        restartAfterSeconds->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_3->addWidget(restartAfterSeconds);

        restartAfterLabel = new QLabel(centralwidget);
        restartAfterLabel->setObjectName("restartAfterLabel");

        horizontalLayout_3->addWidget(restartAfterLabel);


        verticalLayout->addLayout(horizontalLayout_3);

        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tab = new QWidget();
        tab->setObjectName("tab");
        verticalLayout_2 = new QVBoxLayout(tab);
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        onlineBarFrame = new QFrame(tab);
        onlineBarFrame->setObjectName("onlineBarFrame");
        onlineBarFrame->setMinimumSize(QSize(400, 0));
        onlineBarFrame->setAutoFillBackground(true);
        onlineBarFrame->setFrameShape(QFrame::StyledPanel);
        onlineBarFrame->setFrameShadow(QFrame::Plain);
        horizontalLayout_10 = new QHBoxLayout(onlineBarFrame);
        horizontalLayout_10->setSpacing(0);
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        horizontalLayout_10->setContentsMargins(0, 0, 0, 0);
        onlineBar = new OnlinePlayerWidget(onlineBarFrame);
        onlineBar->setObjectName("onlineBar");

        horizontalLayout_10->addWidget(onlineBar);


        horizontalLayout_2->addWidget(onlineBarFrame);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        nextBackupLabel = new QLabel(tab);
        nextBackupLabel->setObjectName("nextBackupLabel");

        horizontalLayout_2->addWidget(nextBackupLabel);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        storageUsage = new QLabel(tab);
        storageUsage->setObjectName("storageUsage");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(storageUsage->sizePolicy().hasHeightForWidth());
        storageUsage->setSizePolicy(sizePolicy2);

        horizontalLayout_7->addWidget(storageUsage);

        storageUsedBar = new QProgressBar(tab);
        storageUsedBar->setObjectName("storageUsedBar");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(storageUsedBar->sizePolicy().hasHeightForWidth());
        storageUsedBar->setSizePolicy(sizePolicy3);
        storageUsedBar->setValue(24);

        horizontalLayout_7->addWidget(storageUsedBar);


        verticalLayout_2->addLayout(horizontalLayout_7);

        serverConsole = new ServerConsoleWidget(tab);
        serverConsole->setObjectName("serverConsole");

        verticalLayout_2->addWidget(serverConsole);

        tabWidget->addTab(tab, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        playerListLayout = new QHBoxLayout(tab_3);
        playerListLayout->setObjectName("playerListLayout");
        playerList = new QTreeView(tab_3);
        playerList->setObjectName("playerList");
        playerList->setHeaderHidden(true);

        playerListLayout->addWidget(playerList);

        tabWidget->addTab(tab_3, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        verticalLayout_4 = new QVBoxLayout(tab_2);
        verticalLayout_4->setObjectName("verticalLayout_4");
        invalidServerLocationLabel = new QLabel(tab_2);
        invalidServerLocationLabel->setObjectName("invalidServerLocationLabel");
        invalidServerLocationLabel->setTextFormat(Qt::RichText);
        invalidServerLocationLabel->setOpenExternalLinks(true);

        verticalLayout_4->addWidget(invalidServerLocationLabel);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_2 = new QLabel(tab_2);
        label_2->setObjectName("label_2");

        horizontalLayout_4->addWidget(label_2);

        serverFolder = new QLineEdit(tab_2);
        serverFolder->setObjectName("serverFolder");

        horizontalLayout_4->addWidget(serverFolder);

        selectServerFolder = new QPushButton(tab_2);
        selectServerFolder->setObjectName("selectServerFolder");

        horizontalLayout_4->addWidget(selectServerFolder);


        verticalLayout_4->addLayout(horizontalLayout_4);

        invalidBackupLocationLabel = new QLabel(tab_2);
        invalidBackupLocationLabel->setObjectName("invalidBackupLocationLabel");
        invalidBackupLocationLabel->setTextFormat(Qt::RichText);
        invalidBackupLocationLabel->setMargin(0);

        verticalLayout_4->addWidget(invalidBackupLocationLabel);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(-1, -1, -1, 3);
        label_3 = new QLabel(tab_2);
        label_3->setObjectName("label_3");

        horizontalLayout_5->addWidget(label_3);

        backupFolder = new QLineEdit(tab_2);
        backupFolder->setObjectName("backupFolder");

        horizontalLayout_5->addWidget(backupFolder);

        selectBackupFolder = new QPushButton(tab_2);
        selectBackupFolder->setObjectName("selectBackupFolder");

        horizontalLayout_5->addWidget(selectBackupFolder);


        verticalLayout_4->addLayout(horizontalLayout_5);

        groupBox_2 = new QGroupBox(tab_2);
        groupBox_2->setObjectName("groupBox_2");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::Maximum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy4);
        verticalLayout_5 = new QVBoxLayout(groupBox_2);
        verticalLayout_5->setObjectName("verticalLayout_5");
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        restrictBackupsStorageUsage = new QCheckBox(groupBox_2);
        restrictBackupsStorageUsage->setObjectName("restrictBackupsStorageUsage");

        horizontalLayout_9->addWidget(restrictBackupsStorageUsage);

        maxStorageUsageMiB = new QLineEdit(groupBox_2);
        maxStorageUsageMiB->setObjectName("maxStorageUsageMiB");
        sizePolicy1.setHeightForWidth(maxStorageUsageMiB->sizePolicy().hasHeightForWidth());
        maxStorageUsageMiB->setSizePolicy(sizePolicy1);
        maxStorageUsageMiB->setMaximumSize(QSize(50, 16777215));
        maxStorageUsageMiB->setMaxLength(10);

        horizontalLayout_9->addWidget(maxStorageUsageMiB);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName("label_4");

        horizontalLayout_9->addWidget(label_4);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_3);

        restrictNumberOfBackups = new QCheckBox(groupBox_2);
        restrictNumberOfBackups->setObjectName("restrictNumberOfBackups");

        horizontalLayout_9->addWidget(restrictNumberOfBackups);

        restrictNumberOfBackupsAmount = new QLineEdit(groupBox_2);
        restrictNumberOfBackupsAmount->setObjectName("restrictNumberOfBackupsAmount");
        sizePolicy1.setHeightForWidth(restrictNumberOfBackupsAmount->sizePolicy().hasHeightForWidth());
        restrictNumberOfBackupsAmount->setSizePolicy(sizePolicy1);
        restrictNumberOfBackupsAmount->setMaximumSize(QSize(50, 16777215));
        restrictNumberOfBackupsAmount->setMaxLength(10);

        horizontalLayout_9->addWidget(restrictNumberOfBackupsAmount);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName("label_5");

        horizontalLayout_9->addWidget(label_5);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_5);


        verticalLayout_5->addLayout(horizontalLayout_9);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        restrictBackupAge = new QCheckBox(groupBox_2);
        restrictBackupAge->setObjectName("restrictBackupAge");
        QSizePolicy sizePolicy5(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(restrictBackupAge->sizePolicy().hasHeightForWidth());
        restrictBackupAge->setSizePolicy(sizePolicy5);

        horizontalLayout_11->addWidget(restrictBackupAge);

        restrictBackupAgeSlider = new QSlider(groupBox_2);
        restrictBackupAgeSlider->setObjectName("restrictBackupAgeSlider");
        restrictBackupAgeSlider->setMinimum(1);
        restrictBackupAgeSlider->setMaximum(365);
        restrictBackupAgeSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_11->addWidget(restrictBackupAgeSlider);


        verticalLayout_5->addLayout(horizontalLayout_11);


        verticalLayout_4->addWidget(groupBox_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::MinimumExpanding);

        verticalLayout_4->addItem(verticalSpacer);

        copyright = new QLabel(tab_2);
        copyright->setObjectName("copyright");

        verticalLayout_4->addWidget(copyright);

        tabWidget->addTab(tab_2, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName("tab_4");
        verticalLayout_6 = new QVBoxLayout(tab_4);
        verticalLayout_6->setObjectName("verticalLayout_6");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        instantBackup = new QPushButton(tab_4);
        instantBackup->setObjectName("instantBackup");

        horizontalLayout->addWidget(instantBackup);

        scheduleBackup = new QPushButton(tab_4);
        scheduleBackup->setObjectName("scheduleBackup");

        horizontalLayout->addWidget(scheduleBackup);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_6);


        verticalLayout_6->addLayout(horizontalLayout);

        groupBox = new QGroupBox(tab_4);
        groupBox->setObjectName("groupBox");
        verticalLayout_3 = new QVBoxLayout(groupBox);
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        doRegularBackups = new QCheckBox(groupBox);
        doRegularBackups->setObjectName("doRegularBackups");

        horizontalLayout_8->addWidget(doRegularBackups);

        backupFrequencySlider = new QSlider(groupBox);
        backupFrequencySlider->setObjectName("backupFrequencySlider");
        backupFrequencySlider->setMinimumSize(QSize(350, 0));
        backupFrequencySlider->setMinimum(1);
        backupFrequencySlider->setMaximum(48);
        backupFrequencySlider->setOrientation(Qt::Horizontal);

        horizontalLayout_8->addWidget(backupFrequencySlider);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_4);


        verticalLayout_3->addLayout(horizontalLayout_8);

        alwaysBackupOnTime = new QCheckBox(groupBox);
        alwaysBackupOnTime->setObjectName("alwaysBackupOnTime");

        verticalLayout_3->addWidget(alwaysBackupOnTime);


        verticalLayout_6->addWidget(groupBox);

        groupBox_3 = new QGroupBox(tab_4);
        groupBox_3->setObjectName("groupBox_3");
        verticalLayout_7 = new QVBoxLayout(groupBox_3);
        verticalLayout_7->setObjectName("verticalLayout_7");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        backupOnJoin = new QCheckBox(groupBox_3);
        backupOnJoin->setObjectName("backupOnJoin");

        gridLayout->addWidget(backupOnJoin, 0, 0, 1, 1);

        backupOnLeave = new QCheckBox(groupBox_3);
        backupOnLeave->setObjectName("backupOnLeave");

        gridLayout->addWidget(backupOnLeave, 1, 0, 1, 1);


        verticalLayout_7->addLayout(gridLayout);


        verticalLayout_6->addWidget(groupBox_3);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        backupDelayLabel = new QLabel(tab_4);
        backupDelayLabel->setObjectName("backupDelayLabel");
        QSizePolicy sizePolicy6(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(backupDelayLabel->sizePolicy().hasHeightForWidth());
        backupDelayLabel->setSizePolicy(sizePolicy6);

        horizontalLayout_6->addWidget(backupDelayLabel);

        backupDelaySlider = new QSlider(tab_4);
        backupDelaySlider->setObjectName("backupDelaySlider");
        backupDelaySlider->setMinimum(1);
        backupDelaySlider->setMaximum(240);
        backupDelaySlider->setOrientation(Qt::Horizontal);

        horizontalLayout_6->addWidget(backupDelaySlider);


        verticalLayout_6->addLayout(horizontalLayout_6);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_4);

        tabWidget->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName("tab_5");
        verticalLayout_8 = new QVBoxLayout(tab_5);
        verticalLayout_8->setObjectName("verticalLayout_8");
        serverPropertiesScrollArea = new QScrollArea(tab_5);
        serverPropertiesScrollArea->setObjectName("serverPropertiesScrollArea");
        serverPropertiesScrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 931, 418));
        serverPropertiesScrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_8->addWidget(serverPropertiesScrollArea);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName("horizontalLayout_12");
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_7);

        saveConfigAndRestart = new QPushButton(tab_5);
        saveConfigAndRestart->setObjectName("saveConfigAndRestart");

        horizontalLayout_12->addWidget(saveConfigAndRestart);

        saveConfig = new QPushButton(tab_5);
        saveConfig->setObjectName("saveConfig");

        horizontalLayout_12->addWidget(saveConfig);


        verticalLayout_8->addLayout(horizontalLayout_12);

        tabWidget->addTab(tab_5, QString());

        verticalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 973, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Server status:", nullptr));
        difficultyLabel->setText(QString());
        startServer->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        stopServer->setText(QCoreApplication::translate("MainWindow", "Stop", nullptr));
        restartAfter->setText(QCoreApplication::translate("MainWindow", "Restart after", nullptr));
        restartAfterSeconds->setInputMask(QCoreApplication::translate("MainWindow", "0000", nullptr));
        restartAfterSeconds->setText(QCoreApplication::translate("MainWindow", "60", nullptr));
        restartAfterLabel->setText(QCoreApplication::translate("MainWindow", "seconds", nullptr));
        nextBackupLabel->setText(QCoreApplication::translate("MainWindow", "Server status:", nullptr));
        storageUsage->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        storageUsedBar->setFormat(QCoreApplication::translate("MainWindow", "Backup: %v MiB used of %m MiB (%p%)", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "Console", "tab text"));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("MainWindow", "Users", "tab text"));
        invalidServerLocationLabel->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600; color:#ff0000;\">You must set the server locaton.</span><br/>This should be the root of your minecraft server, you can download the server <a href=\"https://www.minecraft.net/en-us/download/server/bedrock/\"><span style=\" text-decoration: underline; color:#007af4;\">from here.</span></a></p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Server location:", nullptr));
        selectServerFolder->setText(QCoreApplication::translate("MainWindow", "Select folder", nullptr));
        invalidBackupLocationLabel->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600; color:#ff0000;\">Invalid backup folder.</span><br/>Automatic backups will not function.</p></body></html>", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Backup folder:", nullptr));
        selectBackupFolder->setText(QCoreApplication::translate("MainWindow", "Select folder", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Backup storage", nullptr));
        restrictBackupsStorageUsage->setText(QCoreApplication::translate("MainWindow", "Limit backup folder usage to", nullptr));
        maxStorageUsageMiB->setInputMask(QCoreApplication::translate("MainWindow", "9000000000", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "MiB", nullptr));
        restrictNumberOfBackups->setText(QCoreApplication::translate("MainWindow", "Keep at most", nullptr));
        restrictNumberOfBackupsAmount->setInputMask(QCoreApplication::translate("MainWindow", "9000000000", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "backups", nullptr));
        restrictBackupAge->setText(QCoreApplication::translate("MainWindow", "Delete backups older than %Ln day(s)", nullptr));
        copyright->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Options", "tab text"));
#if QT_CONFIG(tooltip)
        instantBackup->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>This will backup the current state to a ZIP file.</p><p>You will be prompted for a location to save the file to.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        instantBackup->setText(QCoreApplication::translate("MainWindow", "Backup to ZIP file", nullptr));
#if QT_CONFIG(tooltip)
        scheduleBackup->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>This will request a backup be taken.</p><p>The backup will be saved into the configured backups folder.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        scheduleBackup->setText(QCoreApplication::translate("MainWindow", "Backup to backup folder", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Schedule", nullptr));
        doRegularBackups->setText(QCoreApplication::translate("MainWindow", "Schedule a backup at least every %Ln hours", nullptr));
#if QT_CONFIG(tooltip)
        alwaysBackupOnTime->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Checking this will ensure that backups happen every <span style=\" font-style:italic;\">x</span> hours regardless.</p><p>Otherwise if a backup is triggered for another reason, the countdown will be restarted.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        alwaysBackupOnTime->setText(QCoreApplication::translate("MainWindow", "...even if a backup has happened more recently", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "Events", nullptr));
        backupOnJoin->setText(QCoreApplication::translate("MainWindow", "Schedule a backup when a player joins", nullptr));
        backupOnLeave->setText(QCoreApplication::translate("MainWindow", "Schedule a backup when a player leaves", nullptr));
        backupDelayLabel->setText(QCoreApplication::translate("MainWindow", "Wait at least xxxxx minutes betweent backups", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QCoreApplication::translate("MainWindow", "Backup", "tab text"));
#if QT_CONFIG(tooltip)
        serverPropertiesScrollArea->setToolTip(QCoreApplication::translate("MainWindow", "Saves the current configuration to server.properties.", nullptr));
#endif // QT_CONFIG(tooltip)
        saveConfigAndRestart->setText(QCoreApplication::translate("MainWindow", "Save configuration and restart the server", nullptr));
        saveConfig->setText(QCoreApplication::translate("MainWindow", "Save configuration", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QCoreApplication::translate("MainWindow", "Server properties", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
