#pragma once

#include <QList>
#include <QString>
#include <memory>
#include <optional>

#include "ui_main_window.h"
#include "../cell_item/cell_item.h"
#include "../randomizer/randomizer.h"
#include "../settings_window/settings_window.h"
#include "../settings_manager/settings_manager.h"
#include "../database_proxy/database_proxy.h"
#include "../route_builder/route_builder.h"

namespace main_window
{

class MainWindow final : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = Q_NULLPTR);
    ~MainWindow();

public slots:
    void GenerateField(const defs::FieldModel& field_model = {});
    void SaveField();
    void LoadField();
    void ReceiveAppSettings(const defs::AppSettings& app_settings);
    void ReceiveMetadata(const defs::CellType& type, const QPoint& coordinates);

private:
    Ui::main_window ui_;

    const int min_nodes_list_size_ = 2;

    const QString app_name_ = "PathFinder";
    const QString app_ver_  = "(v1.0.0)";
    const QString db_type_  = "QSQLITE";

    std::optional<QPoint> start_;
    std::optional<QPoint> finish_;
    std::vector<QPoint> route_nodes_;

    std::unique_ptr<QGraphicsScene> field_scene_;
    QList<QList<cell::CellItem*>> cell_items_;

    settings::SettingsManager* settings_manager_;
    std::unique_ptr<random::Randomizer> randomizer_;
    std::unique_ptr<settings::SettingsWindow> settings_window_;
    std::unique_ptr<database::DatabaseProxy> database_proxy_;
    std::unique_ptr<route::RouteBuilder> route_builder_;

    defs::AppSettings app_settings_;

    void InitFields();
    defs::FieldModel MakeFieldModel();
    void MakeConnections() const;
    void ConnectWithCells() const;
    void BuildRoute();
};

} // main_window