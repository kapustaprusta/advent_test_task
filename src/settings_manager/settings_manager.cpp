#include "settings_manager.h"

namespace settings
{

SettingsManager* SettingsManager::p_instance_;
QMutex           SettingsManager::make_instance_mutex_;

void SettingsManager::Initialize(const QString& org, const QString& app)
{
    org_ = org;
    app_ = app;

    p_settings_ = std::make_shared<QSettings>(QSettings::NativeFormat, QSettings::UserScope, org_, app_);
}

bool SettingsManager::WriteAppSettings(const defs::AppSettings& app_settings)
{
    if (!p_settings_)
    {
        return false;
    }

    QMutexLocker ml(&write_mutex_);

    p_settings_->beginGroup("AppSettings");

    p_settings_->setValue("cell_size", app_settings.cell_size);
    p_settings_->setValue("cells_counter", app_settings.cells_counter);
    p_settings_->setValue("path_to_db", app_settings.path_to_db);

    p_settings_->endGroup();

    return true;
}

defs::AppSettings SettingsManager::ReadAppSettings()
{
    if (!p_settings_)
    {
        return {};
    }

    QMutexLocker ml(&read_mutex_);

    defs::AppSettings app_settings{};

    p_settings_->beginGroup("AppSettings");

    app_settings.cell_size = p_settings_->value("cell_size", app_settings.cell_size).toInt();
    app_settings.cells_counter = p_settings_->value("cells_counter", app_settings.cells_counter).toInt();
    app_settings.path_to_db = p_settings_->value("path_to_db", app_settings.path_to_db).toString();

    p_settings_->endGroup();

    return app_settings;
}

bool SettingsManager::WriteWindowProperties(const defs::WindowProperties& window_properties) const
{
    if (!p_settings_)
    {
        return false;
    }

    p_settings_->beginGroup("WindowProperties");

    p_settings_->setValue("size", window_properties.size);
    p_settings_->setValue("position", window_properties.position);

    p_settings_->endGroup();

    return true;
}

defs::WindowProperties SettingsManager::ReadWindowProperties() const
{
    if (!p_settings_)
    {
        return {};
    }

    defs::WindowProperties window_properties{};

    p_settings_->beginGroup("WindowProperties");

    window_properties.size = p_settings_->value("size", window_properties.size).toSize();
    window_properties.position = p_settings_->value("position", window_properties.position).toPoint();

    p_settings_->endGroup();

    return window_properties;
}

void SettingsManager::SetOrganizationName(const QString& org)
{ 
    org_ = org;
}

void SettingsManager::SetApplicationName(const QString& app)
{
    app_ = app;
}

QString SettingsManager::GetOrganizationName() const
{
    return org_;
}

QString SettingsManager::GetApplicationName() const
{
    return app_;
}

}