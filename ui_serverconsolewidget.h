/********************************************************************************
** Form generated from reading UI file 'serverconsolewidget.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVERCONSOLEWIDGET_H
#define UI_SERVERCONSOLEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ServerConsoleWidget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *commandEdit;
    QPushButton *sendButton;
    QHBoxLayout *horizontalLayout_13;
    QPlainTextEdit *serverOutput;

    void setupUi(QWidget *ServerConsoleWidget)
    {
        if (ServerConsoleWidget->objectName().isEmpty())
            ServerConsoleWidget->setObjectName("ServerConsoleWidget");
        ServerConsoleWidget->resize(476, 382);
        verticalLayout = new QVBoxLayout(ServerConsoleWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        commandEdit = new QLineEdit(ServerConsoleWidget);
        commandEdit->setObjectName("commandEdit");

        horizontalLayout_3->addWidget(commandEdit);

        sendButton = new QPushButton(ServerConsoleWidget);
        sendButton->setObjectName("sendButton");

        horizontalLayout_3->addWidget(sendButton);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(2);
        horizontalLayout_13->setObjectName("horizontalLayout_13");
        serverOutput = new QPlainTextEdit(ServerConsoleWidget);
        serverOutput->setObjectName("serverOutput");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(200);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(serverOutput->sizePolicy().hasHeightForWidth());
        serverOutput->setSizePolicy(sizePolicy);
        serverOutput->setFocusPolicy(Qt::WheelFocus);
        serverOutput->setReadOnly(true);

        horizontalLayout_13->addWidget(serverOutput);


        verticalLayout->addLayout(horizontalLayout_13);


        retranslateUi(ServerConsoleWidget);
        QObject::connect(commandEdit, &QLineEdit::returnPressed, sendButton, qOverload<>(&QPushButton::animateClick));

        QMetaObject::connectSlotsByName(ServerConsoleWidget);
    } // setupUi

    void retranslateUi(QWidget *ServerConsoleWidget)
    {
        ServerConsoleWidget->setWindowTitle(QCoreApplication::translate("ServerConsoleWidget", "ServerConsoleTabWidget", nullptr));
        sendButton->setText(QCoreApplication::translate("ServerConsoleWidget", "Send", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ServerConsoleWidget: public Ui_ServerConsoleWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVERCONSOLEWIDGET_H
