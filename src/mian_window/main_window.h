#pragma once

#include "ui_main_window.h"

namespace main_window
{

class MainWindow final : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = Q_NULLPTR);
    ~MainWindow() = default;

private:
    Ui::main_window ui_;
};

} // main_window