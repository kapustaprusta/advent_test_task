#pragma once

#include <QMutex>
#include <QString>
#include <QSettings>
#include <QMutexLocker>

#include "../defs/defs.h"

namespace settings
{

class SettingsManager
{
public:
    static SettingsManager* MakeInstance()
    {
        QMutexLocker ml(&make_instance_mutex_);

        static MemoryDefender mem_defender;
        if (!p_instance_)
        {
            p_instance_ = new SettingsManager;
        }

        return p_instance_;
    }

    void Initialize(const QString& org = "TEST", const QString& app = "Path Finder");

    SettingsManager(const SettingsManager&) = delete;
    SettingsManager(const SettingsManager&&) = delete;

    SettingsManager& operator=(const SettingsManager&) = delete; 
    SettingsManager& operator=(const SettingsManager&&) = delete;

    bool WriteAppSettings(const defs::AppSettings& settings_storage);
    bool WriteWindowProperties(const defs::WindowProperties& window_properties) const;

    defs::WindowProperties ReadWindowProperties() const;
    defs::AppSettings ReadAppSettings();

    void SetOrganizationName(const QString& org);
    void SetApplicationName(const QString& app);

    QString GetOrganizationName() const;
    QString GetApplicationName() const;

private:
    QMutex read_mutex_;
    QMutex write_mutex_;
    static QMutex make_instance_mutex_;

    QString org_;
    QString app_;

    std::shared_ptr<QSettings> p_settings_;
    static SettingsManager* p_instance_;

     SettingsManager() = default;
    ~SettingsManager() = default;

    class MemoryDefender
    {
    public:
        MemoryDefender(){}
        ~MemoryDefender(){delete p_instance_;}
    };
};

} // settings