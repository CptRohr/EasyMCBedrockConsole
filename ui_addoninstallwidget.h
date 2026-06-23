/********************************************************************************
** Form generated from reading UI file 'addoninstallwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDONINSTALLWIDGET_H
#define UI_ADDONINSTALLWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddonInstallWidget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *installButton;
    QPushButton *refreshButton;
    QSpacerItem *horizontalSpacer;
    QLabel *statusLabel;
    QHBoxLayout *horizontalLayout_2;
    QListWidget *packListWidget;
    QLabel *detailsLabel;

    void setupUi(QWidget *AddonInstallWidget)
    {
        if (AddonInstallWidget->objectName().isEmpty())
            AddonInstallWidget->setObjectName("AddonInstallWidget");
        AddonInstallWidget->resize(800, 600);
        verticalLayout = new QVBoxLayout(AddonInstallWidget);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        installButton = new QPushButton(AddonInstallWidget);
        installButton->setObjectName("installButton");

        horizontalLayout->addWidget(installButton);

        refreshButton = new QPushButton(AddonInstallWidget);
        refreshButton->setObjectName("refreshButton");

        horizontalLayout->addWidget(refreshButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        statusLabel = new QLabel(AddonInstallWidget);
        statusLabel->setObjectName("statusLabel");

        horizontalLayout->addWidget(statusLabel);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        packListWidget = new QListWidget(AddonInstallWidget);
        packListWidget->setObjectName("packListWidget");
        packListWidget->setMinimumWidth(300);

        horizontalLayout_2->addWidget(packListWidget);

        detailsLabel = new QLabel(AddonInstallWidget);
        detailsLabel->setObjectName("detailsLabel");
        detailsLabel->setAlignment(Qt::AlignTop|Qt::AlignLeft);
        detailsLabel->setWordWrap(true);

        horizontalLayout_2->addWidget(detailsLabel);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(AddonInstallWidget);

        QMetaObject::connectSlotsByName(AddonInstallWidget);
    } // setupUi

    void retranslateUi(QWidget *AddonInstallWidget)
    {
        AddonInstallWidget->setWindowTitle(QCoreApplication::translate("AddonInstallWidget", "Addon Library", nullptr));
        installButton->setText(QCoreApplication::translate("AddonInstallWidget", "Install Addon...", nullptr));
        refreshButton->setText(QCoreApplication::translate("AddonInstallWidget", "Refresh", nullptr));
        statusLabel->setText(QCoreApplication::translate("AddonInstallWidget", "Total packs installed: 0", nullptr));
        detailsLabel->setText(QCoreApplication::translate("AddonInstallWidget", "Select a pack to view details", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddonInstallWidget: public Ui_AddonInstallWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDONINSTALLWIDGET_H
