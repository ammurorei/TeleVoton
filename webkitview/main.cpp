#include <QApplication>
#include "html5applicationviewer.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Html5ApplicationViewer viewer;
    viewer.setOrientation(Html5ApplicationViewer::ScreenOrientationAuto);
    viewer.showExpanded();
    viewer.resize(640, 480);
    viewer.loadFile(QLatin1String("html/welcome_page.html"));

    return app.exec();
}
