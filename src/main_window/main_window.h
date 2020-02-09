#pragma once

#include <QList>
#include <memory>
#include <QString>
#include <QGraphicsScene>

#include "ui_main_window.h"
#include "../cell_item/cell_item.h"
#include "../randomizer/randomizer.h"

namespace main_window
{

class MainWindow final : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = Q_NULLPTR);
            ~MainWindow() = default;

public slots:
    void GenerateField();

private:
    Ui::main_window ui_;

    const QString app_name_ = "Path Finder";
    const QString app_ver_  = "(v1.0.0)";

    QGraphicsScene*               field_scene_;
    QList<QList<cell::CellItem*>> cell_items_;

    std::unique_ptr<random::Randomizer> randomizer_;
};

} // main_window