#include "App.h"

int32_t main(int32_t argc, char *argv[]) {
    QApplication a(argc, argv);

    App NNC(800, 600);
    NNC.render();
    return QApplication::exec();
}