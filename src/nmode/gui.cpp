#include <QApplication>
#include <QDesktopWidget>

#include <nmode/NGui.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    NGui gui;
    gui.move(QApplication::desktop()->availableGeometry(&gui).topLeft() + QPoint(20, 20));
    gui.show();
    return app.exec();
}
