#include <QtGui/QSurfaceFormat>
#include <QtWidgets/QApplication>

#include <fstream>
#include <iostream>

#include "loaders/Xb7StoryLoader.h"
#include "widgets/AppWindow.h"
#include "controllers/AppContext.h"

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

    auto firstScene = story.scenes.at(0);
    auto origin = (firstScene.geometryStart + firstScene.geometryEnd) / 2;

    std::cout << origin.x() << " " << origin.y() << " " << origin.z() << std::endl;

    auto appContext = AppContext{};

    auto appWindow = new AppWindow{appContext};
    appContext.viewController.setOrigin(origin);
    appContext.animationController.setStory(story);
    appWindow->show();

    return app.exec();
}
