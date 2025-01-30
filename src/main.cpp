#include <QtGui/QSurfaceFormat>
#include <QtWidgets/QApplication>

#include <fstream>
#include <iostream>

#include "loaders/Xb7StoryLoader.h"
#include "widgets/AppWindow.h"

int main(int argc, char **argv)
{
    auto app = QApplication{argc, argv};

    QSurfaceFormat surfaceFormat;
    surfaceFormat.setVersion(3, 3);
    surfaceFormat.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(surfaceFormat);

    if (argc < 2)
    {
        std::cerr << "Invalid arguments" << std::endl;
        return 1;
    }

    auto input = std::ifstream{argv[1]};
    auto story = Xb7StoryLoader::getInstance().load(input);

    auto appWindow = new AppWindow{};
    appWindow->getAppWidget()->getStoryController()->setStory(story);
    appWindow->show();

    return app.exec();
}
