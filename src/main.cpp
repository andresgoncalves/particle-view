#include <QtWidgets/QApplication>

#include "widgets/AppWindow.h"

int main(int argc, char **argv)
{
    auto app = QApplication{argc, argv};

    auto appWindow = new AppWindow{};
    appWindow->show();

    return app.exec();
}
