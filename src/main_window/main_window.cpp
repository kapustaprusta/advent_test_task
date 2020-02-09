#include "main_window.h"
#include "../defs/defs.h"

namespace main_window
{

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    ui_.setupUi(this);

    setWindowTitle(app_name_ + " " + app_ver_);

    field_scene_ = new QGraphicsScene(this);
    randomizer_  = std::make_unique<random::Randomizer>(std::uniform_int_distribution<>(0, 1));

    field_scene_->setSceneRect(0, 0, 0, 0);
    ui_.field_view->setScene(field_scene_);

    connect(ui_.action_generate_field, SIGNAL(triggered()), this, SLOT(GenerateField()));
}

void MainWindow::GenerateField()
{
    auto size  = QSize (9, 9);
    auto coord = QPoint(0, 0);
    
    auto colors = defs::Colors{};

    for (int row = 0; row < 100; row++)
    {
        QList<cell::CellItem*> cells;

        for (int col = 0; col < 100; col++)
        {
            coord.setX(col);
            coord.setY(row);

            if (randomizer_->GetRandomValue())
            {
                cells.append(new cell::CellItem(size, coord, colors.black, field_scene_));
            }
            else
            {
                cells.append(new cell::CellItem(size, coord, colors.white, field_scene_));
            }

            field_scene_->addItem(cells.back());
            cells.back()->setPos(-500 + size.width() * col, -500 + size.height() * row);

            cell_items_.append(cells);
        }
    }
}

} // main_window