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

void MainWindow::GenerateField()
{
    auto coord  = QPoint(0, 0);
    auto colors = defs::Colors{};

    cell_items_.clear();
    field_scene_->clear();

    for (int row = 0; row < app_settings_.cells_counter; row++)
    {
        QList<cell::CellItem*> cells;
        for (int col = 0; col < app_settings_.cells_counter; col++)
        {
            coord.setX(col);
            coord.setY(row);

            if (randomizer_->GetRandomValue())
            {
                cells.append(new cell::CellItem(QSize(app_settings_.cell_size, app_settings_.cell_size), coord, colors.black, field_scene_));
            }
            else
            {
                cells.append(new cell::CellItem(QSize(app_settings_.cell_size, app_settings_.cell_size), coord, colors.white, field_scene_));
            }

            field_scene_->addItem(cells.back());
            cells.back()->setPos(app_settings_.cell_size * col, app_settings_.cell_size * row);
        }

        cell_items_.append(cells);
    }
}

void MainWindow::ReceiveAppSettings(const defs::AppSettings& app_settings)
{
    app_settings_ = app_settings;
    ui_.status_bar->showMessage(QString("settings applied"), 2000);
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

    field_scene_ = new QGraphicsScene(this);
    field_scene_->setSceneRect(0, 0, 0, 0);
    ui_.field_view->setScene(field_scene_);
}

void MainWindow::MakeConnections()
{
    connect(ui_.action_generate_field, SIGNAL(triggered()), this, SLOT(GenerateField()));
    connect(ui_.action_settings, SIGNAL(triggered()), settings_window_.get(), SLOT(exec()));

    connect(settings_window_.get(), SIGNAL(SendAppSettings(const defs::AppSettings&)), this, SLOT(ReceiveAppSettings(const defs::AppSettings&)));
}

} // main_window