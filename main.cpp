#include "src/main_window/main_window.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    main_window::MainWindow main_window;
                            main_window.show();

    return QApplication::exec();
}