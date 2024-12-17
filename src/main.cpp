#include <QApplication>
#include <QLabel>

int main(int argc, char **argv)
{
    auto app = QApplication{argc, argv};

    auto label = QLabel("Hello, from particle-view!");
    label.setContentsMargins(24, 16, 24, 16);
    label.show();

    return app.exec();
}
