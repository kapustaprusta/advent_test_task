#pragma once

#include <QAction>

#include "ui_settings_window.h"
#include "../defs/defs.h"

namespace settings
{

class SettingsWindow final : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsWindow(const QString& app_name, const QString& app_ver, const defs::AppSettings& app_settings, QWidget* parent = Q_NULLPTR);
            ~SettingsWindow() = default;

public slots:
    void ChooseDatabaseFile();
    void ApplyButtonClicked();

signals:
    void SendAppSettings(const defs::AppSettings& app_settings);

private:
    Ui::settings_window ui_;

    QString app_name_;
    QString app_ver_;
    QString default_directory_;

    QAction* action_choose_database_file_;

    void InitFields(const QString& app_name, const QString& app_ver, const defs::AppSettings& app_settings);
    void MakeConnections();

    defs::AppSettings ReadSettingsFromUi();
};

} // settings