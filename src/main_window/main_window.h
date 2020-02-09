#pragma once

#include <QList>
#include <memory>
#include <QString>
#include <QGraphicsScene>

#include "ui_main_window.h"
#include "../cell_item/cell_item.h"
#include "../randomizer/randomizer.h"
#include "../settings_window/settings_window.h"
#include "../settings_manager/settings_manager.h"
#include "../database_proxy/database_proxy.h"

namespace main_window
{

class MainWindow final : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = Q_NULLPTR);
            ~MainWindow();

public slots:
    void GenerateField();
    void SaveField();
    void ReceiveAppSettings(const defs::AppSettings& app_settings);

private:
    Ui::main_window ui_;

    const QString app_name_ = "Path Finder";
    const QString app_ver_  = "(v1.0.0)";
    const QString db_type_  = "QSQLITE";

    QGraphicsScene*               field_scene_;
    QList<QList<cell::CellItem*>> cell_items_;

    settings::SettingsManager*                settings_manager_;
    std::unique_ptr<random::Randomizer>       randomizer_;
    std::unique_ptr<settings::SettingsWindow> settings_window_;
    std::unique_ptr<database::DatabaseProxy>  database_proxy_;

    defs::AppSettings app_settings_;

    void InitFields();
    void MakeConnections();
};

} // main_window