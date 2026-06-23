/********************************************************************************
** Form generated from reading UI file 'playerinfowidget.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYERINFOWIDGET_H
#define UI_PLAYERINFOWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlayerInfoWidget
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *name;
    QLabel *xuid;
    QLabel *onlineStatus;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QComboBox *permissionLevel;
    QSpacerItem *verticalSpacer;
    QWidget *onlinePanel;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *onlineActions;
    QPushButton *kickUser;

    void setupUi(QWidget *PlayerInfoWidget)
    {
        if (PlayerInfoWidget->objectName().isEmpty())
            PlayerInfoWidget->setObjectName("PlayerInfoWidget");
        PlayerInfoWidget->resize(181, 339);
        verticalLayout = new QVBoxLayout(PlayerInfoWidget);
        verticalLayout->setObjectName("verticalLayout");
        name = new QLabel(PlayerInfoWidget);
        name->setObjectName("name");
        QFont font;
        font.setPointSize(15);
        font.setBold(true);
        name->setFont(font);
        name->setAlignment(Qt::AlignCenter);
        name->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByMouse);

        verticalLayout->addWidget(name);

        xuid = new QLabel(PlayerInfoWidget);
        xuid->setObjectName("xuid");
        xuid->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(xuid);

        onlineStatus = new QLabel(PlayerInfoWidget);
        onlineStatus->setObjectName("onlineStatus");
        onlineStatus->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(onlineStatus);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label_2 = new QLabel(PlayerInfoWidget);
        label_2->setObjectName("label_2");

        horizontalLayout->addWidget(label_2);

        permissionLevel = new QComboBox(PlayerInfoWidget);
        permissionLevel->addItem(QString());
        permissionLevel->addItem(QString());
        permissionLevel->addItem(QString());
        permissionLevel->setObjectName("permissionLevel");

        horizontalLayout->addWidget(permissionLevel);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 231, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        onlinePanel = new QWidget(PlayerInfoWidget);
        onlinePanel->setObjectName("onlinePanel");
        verticalLayout_2 = new QVBoxLayout(onlinePanel);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        onlineActions = new QGridLayout();
        onlineActions->setObjectName("onlineActions");
        kickUser = new QPushButton(onlinePanel);
        kickUser->setObjectName("kickUser");

        onlineActions->addWidget(kickUser, 0, 0, 1, 1);


        verticalLayout_2->addLayout(onlineActions);


        verticalLayout->addWidget(onlinePanel);


        retranslateUi(PlayerInfoWidget);

        QMetaObject::connectSlotsByName(PlayerInfoWidget);
    } // setupUi

    void retranslateUi(QWidget *PlayerInfoWidget)
    {
        PlayerInfoWidget->setWindowTitle(QCoreApplication::translate("PlayerInfoWidget", "Form", nullptr));
        name->setText(QCoreApplication::translate("PlayerInfoWidget", "TextLabel", nullptr));
        xuid->setText(QCoreApplication::translate("PlayerInfoWidget", "TextLabel", nullptr));
        onlineStatus->setText(QCoreApplication::translate("PlayerInfoWidget", "TextLabel", nullptr));
        label_2->setText(QCoreApplication::translate("PlayerInfoWidget", "Permission level:", nullptr));
        permissionLevel->setItemText(0, QCoreApplication::translate("PlayerInfoWidget", "Member", nullptr));
        permissionLevel->setItemText(1, QCoreApplication::translate("PlayerInfoWidget", "Operator", nullptr));
        permissionLevel->setItemText(2, QCoreApplication::translate("PlayerInfoWidget", "Visitor", nullptr));

        kickUser->setText(QCoreApplication::translate("PlayerInfoWidget", "Kick", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PlayerInfoWidget: public Ui_PlayerInfoWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYERINFOWIDGET_H
