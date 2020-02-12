#include <QMessageBox>

#include "main_window.h"
#include "../defs/defs.h"

namespace main_window
{

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    ui_.setupUi(this);

    setWindowTitle(app_name_ + " " + app_ver_);
     
    InitFields();
    MakeConnections();
}

MainWindow::~MainWindow()
{
    settings_manager_->WriteAppSettings(app_settings_);
    settings_manager_->WriteWindowProperties(defs::WindowProperties{size(), pos()});
}

void MainWindow::GenerateField(const defs::FieldModel& field_model)
{
    auto coord  = QPoint(0, 0);
    auto colors = defs::Colors{};

    field_scene_ = std::make_unique<QGraphicsScene>(this);
    ui_.field_view->setScene(field_scene_.get());
    cell_items_.clear();

    for (auto row = 0; row < app_settings_.cells_counter; row++)
    {
        QList<cell::CellItem*> cells;
        for (auto col = 0; col < app_settings_.cells_counter; col++)
        {
            coord.setX(col);
            coord.setY(row);

            if (field_model.colors.isEmpty())
            {
                cells.append(new cell::CellItem(QSize(app_settings_.cell_size, app_settings_.cell_size), coord, defs::Color(randomizer_->GetRandomValue())));
            }
            else
            {
                cells.append(new cell::CellItem(QSize(app_settings_.cell_size, app_settings_.cell_size), coord, defs::Color(field_model.colors.at(row*app_settings_.cells_counter + col).digitValue())));
            }

            field_scene_->addItem(cells.back());
            cells.back()->setPos(app_settings_.cell_size * col, app_settings_.cell_size * row);
        }

        cell_items_.append(cells);
    }

    start_.reset();
    finish_.reset();
    route_nodes_.clear();

    ConnectWithCells();
}

void MainWindow::SaveField()
{
    if (cell_items_.empty())
    {
        QMessageBox::warning(this, app_name_ + " " + app_ver_, QString(tr("nothing to save")));
        return;
    }

    database_proxy_->Delete();
    const auto field_model = MakeFieldModel();

    if (!database_proxy_->Create(field_model))
    {
        QMessageBox::warning(this, app_name_ + " " + app_ver_, QString(tr("can't write to database")));
        return;
    }

    ui_.status_bar->showMessage(QString("field was successfully saved"), 2000);
}

defs::FieldModel MainWindow::MakeFieldModel()
{
    auto field_model = defs::FieldModel{};
    for (const auto& row : cell_items_)
    {
        for (const auto& col : row)
        {
            field_model.colors.append(QString::number(int(col->GetColor())));
        }
    }

    return field_model;
}

void MainWindow::LoadField()
{
    auto field_model = defs::FieldModel{};
    if (!database_proxy_->Read(field_model))
    {
        QMessageBox::warning(this, app_name_ + " " + app_ver_, QString(tr("can't load field from database")));
        return;
    }

    GenerateField(field_model);
    ui_.status_bar->showMessage(QString("field was successfully loaded"), 2000);
}

void MainWindow::ReceiveAppSettings(const defs::AppSettings& app_settings)
{
    if (app_settings_.path_to_db != app_settings.path_to_db)
    {
        database_proxy_ = std::make_unique<database::DatabaseProxy>();
        database_proxy_->Init(db_type_, app_settings.path_to_db);
    }

    app_settings_ = app_settings;
    ui_.status_bar->showMessage(QString("settings was successfully applied"), 2000);
}

void MainWindow::ReceiveMetadata(const defs::CellType& type, const QPoint& coordinates)
{
    if (type == defs::CellType::START)
    {
        if (finish_->x() == coordinates.x() && finish_->y() == coordinates.y())
        {
            finish_.reset();
        }

        if (!start_.has_value())
        {
            start_.emplace(coordinates);
        }
        else
        {
            if (start_->x() != coordinates.x() || start_->y() != coordinates.y())
            {
                cell_items_[start_->y()][start_->x()]->Reset();
                start_.emplace(coordinates);
            }
        }
    }
    else if (type == defs::CellType::FINISH)
    {
        if (start_->x() == coordinates.x() && start_->y() == coordinates.y())
        {
            start_.reset();
        }

        if (!finish_.has_value())
        {
            finish_.emplace(coordinates);
        }
        else
        {
            if (finish_->x() != coordinates.x() || finish_->y() != coordinates.y())
            {
                cell_items_[finish_->y()][finish_->x()]->Reset();
                finish_.emplace(coordinates);
            }
        }
    }

    if (start_.has_value() && finish_.has_value())
    {
        BuildRoute();
    }
}

void MainWindow::BuildRoute()
{
    if (route_nodes_.size() > min_nodes_list_size_)
    {
        for (auto point_index = 1; point_index < route_nodes_.size()-1; point_index++)
        {
            if (route_nodes_[point_index].x() == start_->x() && route_nodes_[point_index].y() == start_->y() ||
                route_nodes_[point_index].x() == finish_->x() && route_nodes_[point_index].y() == finish_->y())
            {
                continue;
            }

            cell_items_[route_nodes_[point_index].y()][route_nodes_[point_index].x()]->SetType(defs::CellType::DEFAULT);
        }
    }

    route_builder_->Reset(start_.value(), finish_.value());
    route_nodes_ = route_builder_->Build();

    if (route_nodes_.size() <= 2)
    {
        ui_.status_bar->showMessage("can't build the route", 2000);
        return;
    }

    for (auto point_index = 1; point_index < route_nodes_.size() - 1; point_index++)
    {
        cell_items_[route_nodes_[point_index].y()][route_nodes_[point_index].x()]->SetType(defs::CellType::ROUTE);
    }
}

void MainWindow::InitFields()
{
    settings_manager_ = settings::SettingsManager::MakeInstance();
    settings_manager_->Initialize();

    app_settings_           = settings_manager_->ReadAppSettings();
    const auto window_props = settings_manager_->ReadWindowProperties();

    resize(window_props.size);
    move(window_props.position);

    randomizer_       = std::make_unique<random::Randomizer>(std::uniform_int_distribution<>(0, 1));
    settings_window_  = std::make_unique<settings::SettingsWindow>(app_name_, app_ver_, app_settings_);
    database_proxy_   = std::make_unique<database::DatabaseProxy>();
    route_builder_    = std::make_unique<route::RouteBuilder>();

    if (!database_proxy_->Init(db_type_, app_settings_.path_to_db) || !database_proxy_->Read(defs::FieldModel{}))
    {
        ui_.action_load_field->setEnabled(false);
    }
}

void MainWindow::MakeConnections() const
{
    connect(ui_.action_generate_field, SIGNAL(triggered()), this, SLOT(GenerateField()));
    connect(ui_.action_save_field, SIGNAL(triggered()), this, SLOT(SaveField()));
    connect(ui_.action_load_field, SIGNAL(triggered()), this, SLOT(LoadField()));
    connect(ui_.action_settings, SIGNAL(triggered()), settings_window_.get(), SLOT(exec()));
    connect(settings_window_.get(), SIGNAL(SendAppSettings(const defs::AppSettings&)), this, SLOT(ReceiveAppSettings(const defs::AppSettings&)));
}

void MainWindow::ConnectWithCells() const
{
    for (const auto& row : cell_items_)
    {
        for (const auto& col : row)
        {
            connect(col, SIGNAL(SendMetadata(const defs::CellType&, const QPoint&)), this, SLOT(ReceiveMetadata(const defs::CellType&, const QPoint&)));
        }
    }
}

} // main_window