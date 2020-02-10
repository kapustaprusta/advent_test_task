#include <QIcon>
#include <QFile>
#include <QLineEdit>
#include <QValidator>
#include <QFileDialog>
#include <QMessageBox>

#include "settings_window.h"

namespace settings
{

SettingsWindow::SettingsWindow(const QString& app_name, const QString& app_ver,const defs::AppSettings& app_settings, QWidget* parent)
    : QDialog(parent)
{
    ui_.setupUi(this);

    setWindowTitle(app_name + " " + app_ver);

    InitFields(app_name, app_ver, app_settings);
    MakeConnections();
}

void SettingsWindow::ChooseDatabaseFile()
{
    const auto file_name = QFileDialog::getOpenFileName(this, tr("Choose SQLite file"), default_directory_, "*");

    if (!file_name.isEmpty())
    {
        default_directory_ = file_name;
        ui_.path_to_db_line_edit->setText(file_name);
    }
}

void SettingsWindow::ApplyButtonClicked()
{   
    const auto app_settings = ReadSettingsFromUi();

    if (!QFile::exists(app_settings.path_to_db))
    {
        QMessageBox::warning(this, app_name_ + " " + app_ver_, QString(tr("invalid path to database")));
        return;
    }

    SendAppSettings(app_settings);
    close();
}

defs::AppSettings SettingsWindow::ReadSettingsFromUi() const
{
    defs::AppSettings app_settings{};

    app_settings.cell_size = ui_.cell_size_line_edit->text().toInt();
    app_settings.cells_counter = ui_.cells_counter_line_edit->text().toInt();
    app_settings.path_to_db = ui_.path_to_db_line_edit->text();

    return app_settings;
}

void SettingsWindow::InitFields(const QString& app_name, const QString& app_ver, const defs::AppSettings& app_settings)
{
    app_name_          = app_name;
    app_ver_           = app_ver;
    default_directory_ = app_settings.path_to_db;

    ui_.cell_size_line_edit->setText(QString::number(app_settings.cell_size));
    ui_.cell_size_line_edit->setValidator(new QRegExpValidator(QRegExp("[0-9]{2}"), ui_.cell_size_line_edit));

    ui_.cells_counter_line_edit->setText(QString::number(app_settings.cells_counter));
    ui_.cells_counter_line_edit->setValidator(new QRegExpValidator(QRegExp("[0-9]{3}"), ui_.cells_counter_line_edit));

    ui_.path_to_db_line_edit->setText(app_settings.path_to_db);

    action_choose_database_file_ = ui_.path_to_db_line_edit->addAction(QIcon(":/path_finder/icons/open_folder.png"), QLineEdit::TrailingPosition);
}

void SettingsWindow::MakeConnections()
{
    connect(action_choose_database_file_, SIGNAL(triggered()), this, SLOT(ChooseDatabaseFile()));
    connect(ui_.apply_button            , SIGNAL(clicked  ()), this, SLOT(ApplyButtonClicked()));
}

} // settings