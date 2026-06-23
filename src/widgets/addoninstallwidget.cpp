/***
 *
 * This file is part of Minecraft Bedrock Server Console software.
 *
 * It is licenced under the GNU GPL Version 3.
 *
 * A copy of this can be found in the LICENCE file
 *
 * (c) Ian Clark
 *
 **
*/

#include "addoninstallwidget.h"
#include "addons/addonmanager.h"
#include "ui_addoninstallwidget.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QProgressDialog>
#include <QListWidget>
#include <QLabel>
#include <QPushButton>
#include <QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QUrl>
#include <QDebug>
#include <QCoreApplication>

AddonInstallWidget::AddonInstallWidget(AddonManager* addonManager, QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::AddonInstallWidget)
    , m_addonManager(nullptr)
    , m_progressDialog(nullptr)
    , m_uninstallButton(nullptr)
    , m_moveUpButton(nullptr)
    , m_moveDownButton(nullptr)
    , m_restartBanner(nullptr)
{
    ui->setupUi(this);

    // Set up drag-and-drop
    setAcceptDrops(true);

    // Default disabled state until manager is available
    setAddonManager(addonManager);

    // Create new buttons programmatically
    m_uninstallButton = new QPushButton(tr("Delete Addon"), this);
    m_uninstallButton->setEnabled(false);
    
    m_moveUpButton = new QPushButton(tr("Move Up"), this);
    m_moveUpButton->setEnabled(false);
    
    m_moveDownButton = new QPushButton(tr("Move Down"), this);
    m_moveDownButton->setEnabled(false);

    if (ui->horizontalLayout) {
        ui->horizontalLayout->insertWidget(2, m_uninstallButton);
        ui->horizontalLayout->insertWidget(3, m_moveUpButton);
        ui->horizontalLayout->insertWidget(4, m_moveDownButton);
    }

    // Connect signals
    connect(ui->installButton, &QPushButton::clicked, this, &AddonInstallWidget::onInstallButtonClicked);
    connect(ui->refreshButton, &QPushButton::clicked, this, &AddonInstallWidget::onRefreshButtonClicked);
    connect(m_uninstallButton, &QPushButton::clicked, this, &AddonInstallWidget::onUninstallButtonClicked);
    connect(m_moveUpButton, &QPushButton::clicked, this, &AddonInstallWidget::onMoveUpButtonClicked);
    connect(m_moveDownButton, &QPushButton::clicked, this, &AddonInstallWidget::onMoveDownButtonClicked);

    if (ui->packListWidget) {
        connect(ui->packListWidget, &QListWidget::itemSelectionChanged,
                this, &AddonInstallWidget::onPackListItemSelectionChanged);
        connect(ui->packListWidget, &QListWidget::itemDoubleClicked,
                this, &AddonInstallWidget::onPackListItemDoubleClicked);
    }

    // Build restart-required banner (hidden by default)
    m_restartBanner = new QFrame(this);
    m_restartBanner->setObjectName("restartBanner");
    m_restartBanner->setFrameShape(QFrame::StyledPanel);
    m_restartBanner->setStyleSheet(
        "QFrame#restartBanner {"
        "  background-color: #7a4f00;"
        "  border: 1px solid #cc8800;"
        "  border-radius: 4px;"
        "  padding: 2px;"
        "}"
    );

    QHBoxLayout* bannerLayout = new QHBoxLayout(m_restartBanner);
    bannerLayout->setContentsMargins(8, 4, 8, 4);

    QLabel* bannerIcon = new QLabel(QString::fromUtf8("\xe2\x9a\xa0"), m_restartBanner); // ⚠
    bannerIcon->setStyleSheet("color: #ffcc00; font-size: 14px;");

    QLabel* bannerText = new QLabel(
        tr("Server restart required — addon changes will take effect after restarting the Bedrock server."),
        m_restartBanner);
    bannerText->setStyleSheet("color: #ffe082; font-weight: bold;");
    bannerText->setWordWrap(true);

    QPushButton* bannerDismiss = new QPushButton(QString::fromUtf8("\xc3\x97"), m_restartBanner); // ×
    bannerDismiss->setFixedSize(20, 20);
    bannerDismiss->setFlat(true);
    bannerDismiss->setStyleSheet("color: #ffe082; font-weight: bold; border: none;");
    bannerDismiss->setToolTip(tr("Dismiss"));
    connect(bannerDismiss, &QPushButton::clicked, this, &AddonInstallWidget::hideRestartBanner);

    bannerLayout->addWidget(bannerIcon);
    bannerLayout->addWidget(bannerText, 1);
    bannerLayout->addWidget(bannerDismiss);

    // Insert the banner into the main vertical layout below the toolbar
    QVBoxLayout* mainLayout = qobject_cast<QVBoxLayout*>(layout());
    if (mainLayout) {
        mainLayout->insertWidget(1, m_restartBanner);
    }
    m_restartBanner->setVisible(false);

    // Initial refresh
    refreshPackList();
}

void AddonInstallWidget::setAddonManager(AddonManager* addonManager)
{
    if (m_addonManager) {
        disconnect(m_addonManager, nullptr, this, nullptr);
    }

    m_addonManager = addonManager;
    bool managerReady = (m_addonManager && m_addonManager->isReady());

    if (ui->installButton) ui->installButton->setEnabled(managerReady);
    if (ui->refreshButton) ui->refreshButton->setEnabled(managerReady);
    if (ui->packListWidget) ui->packListWidget->setEnabled(managerReady);

    bool hasSelection = ui->packListWidget && ui->packListWidget->currentItem() != nullptr;
    int currentRow = ui->packListWidget ? ui->packListWidget->currentRow() : -1;
    int count = ui->packListWidget ? ui->packListWidget->count() : 0;

    if (m_uninstallButton) m_uninstallButton->setEnabled(managerReady && hasSelection);
    if (m_moveUpButton) m_moveUpButton->setEnabled(managerReady && hasSelection && currentRow > 0);
    if (m_moveDownButton) m_moveDownButton->setEnabled(managerReady && hasSelection && currentRow != -1 && currentRow < count - 1);

    if (!managerReady) {
        if (ui->detailsLabel) {
            ui->detailsLabel->setText(tr("Addon manager is not ready. Set a valid Bedrock server root folder and choose a valid Bedrock server installation."));
        }
    }

    if (m_addonManager) {
        connect(m_addonManager, &AddonManager::installationProgress,
                this, &AddonInstallWidget::onInstallationProgress);

        connect(m_addonManager, &AddonManager::installationCompleted,
                this, &AddonInstallWidget::onInstallationCompleted);

        connect(m_addonManager, &AddonManager::error,
                this, &AddonInstallWidget::onInstallerError);
    }

    if (managerReady) {
        refreshPackList();
    }
}

AddonInstallWidget::~AddonInstallWidget()
{
    delete ui;
}

void AddonInstallWidget::refreshPackList()
{
    if (!ui->packListWidget) {
        return;
    }

    ui->packListWidget->clear();

    if (!m_addonManager || !m_addonManager->isReady()) {
        if (ui->statusLabel) {
            ui->statusLabel->setText(tr("Addon manager is not ready. Please set a valid Bedrock server root folder."));
        }
        return;
    }

    QVector<PackInfo> packs = m_addonManager->getInstalledPacks();

    for (const auto& pack : packs) {
        QString displayText = QString("%1 v%2 (%3)")
                             .arg(pack.name, pack.versionString(), pack.packType);
        QListWidgetItem* item = new QListWidgetItem(displayText, ui->packListWidget);
        item->setData(Qt::UserRole, pack.uuid);
        ui->packListWidget->addItem(item);
    }

    if (ui->statusLabel) {
        ui->statusLabel->setText(QString("Total packs installed: %1").arg(packs.size()));
    }
}

void AddonInstallWidget::dragEnterEvent(QDragEnterEvent* event)
{
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    }
}

void AddonInstallWidget::dropEvent(QDropEvent* event)
{
    const QMimeData* mimeData = event->mimeData();

    if (mimeData->hasUrls()) {
        for (const QUrl& url : mimeData->urls()) {
            QString filePath = url.toLocalFile();
            QFileInfo fileInfo(filePath);

            if (fileInfo.suffix().toLower() == "mcaddon" ||
                fileInfo.suffix().toLower() == "mcpack" ||
                fileInfo.suffix().toLower() == "zip" ||
                fileInfo.isDir()) {
                qDebug() << "Installing dropped file:" << filePath;
                BulkInstallResult result = m_addonManager->installAddon(filePath);
                showInstallationResult(result);
                refreshPackList();
                if (result.successCount() > 0) {
                    showRestartBanner();
                }
                break; // Process only first file
            }
        }
    }
}

void AddonInstallWidget::onInstallButtonClicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        "Install Addon Pack", "",
        "Bedrock Packs (*.mcaddon *.mcpack *.zip);;All Files (*)");

    if (!fileName.isEmpty()) {
        BulkInstallResult result = m_addonManager->installAddon(fileName);
        showInstallationResult(result);
        refreshPackList();
        if (result.successCount() > 0) {
            showRestartBanner();
        }
    }
}

void AddonInstallWidget::onRefreshButtonClicked()
{
    refreshPackList();
}

void AddonInstallWidget::onPackListItemSelectionChanged()
{
    updateDetailPanel();
}

void AddonInstallWidget::onPackListItemDoubleClicked(QListWidgetItem* item)
{
    // Could open a detail/edit dialog here
    qDebug() << "Double-clicked pack:" << item->text();
}

void AddonInstallWidget::onInstallationProgress(const QString& currentFile, int progressPercent)
{
    if (!m_progressDialog) {
        m_progressDialog = new QProgressDialog("Installing addon...", "Cancel", 0, 100, this);
        m_progressDialog->setWindowModality(Qt::WindowModal);
        m_progressDialog->show();
    }

    m_progressDialog->setLabelText(currentFile);
    m_progressDialog->setValue(progressPercent);
    QCoreApplication::processEvents(QEventLoop::ExcludeUserInputEvents);

    if (progressPercent >= 100) {
        if (m_progressDialog) {
            m_progressDialog->deleteLater();
            m_progressDialog = nullptr;
        }
    }
}

void AddonInstallWidget::onInstallationCompleted(const BulkInstallResult& result)
{
    if (m_progressDialog) {
        m_progressDialog->deleteLater();
        m_progressDialog = nullptr;
    }

    showInstallationResult(result);
    refreshPackList();
    if (result.successCount() > 0) {
        showRestartBanner();
    }
}

void AddonInstallWidget::onInstallerError(const QString& errorMessage)
{
    if (m_progressDialog) {
        m_progressDialog->deleteLater();
        m_progressDialog = nullptr;
    }

    QMessageBox::critical(this, "Installation Error", errorMessage);
}

void AddonInstallWidget::showInstallationResult(const BulkInstallResult& result)
{
    int alreadyInstalledCount = 0;
    for (const auto& res : result.results) {
        if (res.status == InstallResult::AlreadyInstalled) {
            alreadyInstalledCount++;
        }
    }

    QString message = QString("Installation Results:\n\n")
                     + QString("Successful: %1\n").arg(result.successCount())
                     + QString("Already installed: %1\n").arg(alreadyInstalledCount)
                     + QString("Failed: %1\n\n").arg(result.failureCount());

    for (const auto& res : result.results) {
        QString icon;
        if (res.status == InstallResult::Success) {
            icon = QString::fromUtf8("\xe2\x9c\x93"); // checkmark
        } else if (res.status == InstallResult::AlreadyInstalled) {
            icon = QString::fromUtf8("\xe2\x84\xb9"); // info
        } else {
            icon = QString::fromUtf8("\xe2\x9c\x97"); // cross
        }
        message += QString("%1 %2: %3\n").arg(icon, res.packName, res.message);
    }

    QMessageBox::information(this, "Installation Complete", message);
}

void AddonInstallWidget::onUninstallButtonClicked()
{
    if (!ui->packListWidget || !m_addonManager || !m_addonManager->isReady()) {
        return;
    }

    QListWidgetItem* item = ui->packListWidget->currentItem();
    if (!item) {
        return;
    }

    QString uuid = item->data(Qt::UserRole).toString();
    PackInfo pack = m_addonManager->getPack(uuid);
    if (pack.id == -1) {
        return;
    }

    QMessageBox::StandardButton reply = QMessageBox::question(this,
        tr("Delete Addon"),
        tr("Are you sure you want to delete the addon '%1'? This will permanently delete its files from the server.").arg(pack.name),
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        if (m_addonManager->uninstallPack(uuid, true)) {
            refreshPackList();
            updateDetailPanel();
            showRestartBanner();
        } else {
            QMessageBox::warning(this, tr("Delete Error"), tr("Failed to delete addon: %1").arg(m_addonManager->lastError()));
        }
    }
}

void AddonInstallWidget::onMoveUpButtonClicked()
{
    if (!ui->packListWidget || !m_addonManager || !m_addonManager->isReady()) {
        return;
    }

    int currentRow = ui->packListWidget->currentRow();
    if (currentRow <= 0) {
        return;
    }

    QListWidgetItem* currentItem = ui->packListWidget->item(currentRow);
    QListWidgetItem* aboveItem = ui->packListWidget->item(currentRow - 1);
    if (!currentItem || !aboveItem) {
        return;
    }

    QString currentUuid = currentItem->data(Qt::UserRole).toString();
    QString aboveUuid = aboveItem->data(Qt::UserRole).toString();

    if (m_addonManager->swapPacksOrder(currentUuid, aboveUuid)) {
        refreshPackList();
        ui->packListWidget->setCurrentRow(currentRow - 1);
        updateDetailPanel();
        showRestartBanner();
    } else {
        QMessageBox::warning(this, tr("Error"), tr("Failed to change order: %1").arg(m_addonManager->lastError()));
    }
}

void AddonInstallWidget::onMoveDownButtonClicked()
{
    if (!ui->packListWidget || !m_addonManager || !m_addonManager->isReady()) {
        return;
    }

    int currentRow = ui->packListWidget->currentRow();
    if (currentRow == -1 || currentRow >= ui->packListWidget->count() - 1) {
        return;
    }

    QListWidgetItem* currentItem = ui->packListWidget->item(currentRow);
    QListWidgetItem* belowItem = ui->packListWidget->item(currentRow + 1);
    if (!currentItem || !belowItem) {
        return;
    }

    QString currentUuid = currentItem->data(Qt::UserRole).toString();
    QString belowUuid = belowItem->data(Qt::UserRole).toString();

    if (m_addonManager->swapPacksOrder(currentUuid, belowUuid)) {
        refreshPackList();
        ui->packListWidget->setCurrentRow(currentRow + 1);
        updateDetailPanel();
        showRestartBanner();
    } else {
        QMessageBox::warning(this, tr("Error"), tr("Failed to change order: %1").arg(m_addonManager->lastError()));
    }
}

void AddonInstallWidget::updateDetailPanel()
{
    if (!ui->packListWidget) {
        return;
    }

    QListWidgetItem* item = ui->packListWidget->currentItem();
    
    bool hasSelection = (item != nullptr);
    int currentRow = ui->packListWidget->currentRow();
    int count = ui->packListWidget->count();
    bool managerReady = (m_addonManager && m_addonManager->isReady());

    if (m_uninstallButton) m_uninstallButton->setEnabled(managerReady && hasSelection);
    if (m_moveUpButton) m_moveUpButton->setEnabled(managerReady && hasSelection && currentRow > 0);
    if (m_moveDownButton) m_moveDownButton->setEnabled(managerReady && hasSelection && currentRow != -1 && currentRow < count - 1);

    if (!item) {
        if (ui->detailsLabel) {
            ui->detailsLabel->setText("No pack selected");
        }
        return;
    }

    QString uuid = item->data(Qt::UserRole).toString();
    PackInfo pack = m_addonManager->getPack(uuid);

    if (pack.id == -1) {
        if (ui->detailsLabel) {
            ui->detailsLabel->setText("Pack not found");
        }
        return;
    }

    QString details = QString("Name: %1\n"
                             "UUID: %2\n"
                             "Version: %3\n"
                             "Type: %4\n"
                             "Author: %5\n"
                             "Description: %6\n"
                             "Path: %7")
                     .arg(pack.name, pack.uuid, pack.versionString(), pack.packType,
                          pack.author, pack.description, pack.installPath);

    if (ui->detailsLabel) {
        ui->detailsLabel->setText(details);
    }
}

void AddonInstallWidget::showRestartBanner()
{
    if (m_restartBanner) {
        m_restartBanner->setVisible(true);
    }
}

void AddonInstallWidget::hideRestartBanner()
{
    if (m_restartBanner) {
        m_restartBanner->setVisible(false);
    }
}
