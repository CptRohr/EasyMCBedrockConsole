#ifndef ADDONINSTALLWIDGET_H
#define ADDONINSTALLWIDGET_H

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

#include <QWidget>
#include <memory>

class AddonManager;
class QListWidget;
class QListWidgetItem;
class QPushButton;
class QLabel;
class QFrame;
class QProgressDialog;
struct BulkInstallResult;

namespace Ui { class AddonInstallWidget; }

/**
 * @class AddonInstallWidget
 * @brief UI widget for browsing and installing addon packs.
 *
 * Provides:
 * - Install button and file picker
 * - Progress display during installation
 * - List of installed packs
 * - Pack details panel
 */
class AddonInstallWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AddonInstallWidget(AddonManager* addonManager, QWidget* parent = nullptr);
    ~AddonInstallWidget();

    /**
     * @brief Refresh the list of installed packs.
     */
    void refreshPackList();
    void setAddonManager(AddonManager* addonManager);

protected:
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;

private slots:
    void onInstallButtonClicked();
    void onRefreshButtonClicked();
    void onPackListItemSelectionChanged();
    void onPackListItemDoubleClicked(QListWidgetItem* item);
    void onUninstallButtonClicked();
    void onMoveUpButtonClicked();
    void onMoveDownButtonClicked();
    void onInstallationProgress(const QString& currentFile, int progressPercent);
    void onInstallationCompleted(const BulkInstallResult& result);
    void onInstallerError(const QString& errorMessage);

private:
    /**
     * @brief Show installation result dialog.
     */
    void showInstallationResult(const BulkInstallResult& result);

    /**
     * @brief Update the detail panel for selected pack.
     */
    void updateDetailPanel();

    /**
     * @brief Show the restart-required banner.
     */
    void showRestartBanner();

    /**
     * @brief Hide the restart-required banner.
     */
    void hideRestartBanner();

    Ui::AddonInstallWidget* ui;
    AddonManager* m_addonManager;
    QProgressDialog* m_progressDialog;
    QPushButton* m_uninstallButton;
    QPushButton* m_moveUpButton;
    QPushButton* m_moveDownButton;
    QFrame* m_restartBanner;
};

#endif // ADDONINSTALLWIDGET_H
