#include "front/App.h"
#include "front/header.h"

int32_t main(int32_t argc, char *argv[])
{
    QApplication a(argc, argv);

    App NNC(1000, 600);
    NNC.render();
    return QApplication::exec();
}