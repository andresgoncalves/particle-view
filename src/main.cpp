#include <QtGui/QSurfaceFormat>
#include <QtWidgets/QApplication>

#include "widgets/AppWindow.h"

int main(int argc, char **argv)
{
    auto app = QApplication{argc, argv};

    QSurfaceFormat surfaceFormat;
    surfaceFormat.setVersion(3, 3);
    surfaceFormat.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(surfaceFormat);

    auto appWindow = new AppWindow{};
    appWindow->show();

    return app.exec();
}
