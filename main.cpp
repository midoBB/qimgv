#include <QApplication>
#include "settings.h"
#include "components/actionmanager/actionmanager.h"
#include "sharedresources.h"
#include "core.h"

void saveSettings() {
    delete settings;
}

int main(int argc, char *argv[]) {
    // enabling this breaks everything related to image scaling & painting
    // system font size is still honored so it should be fine for now
    QGuiApplication::setAttribute(Qt::AA_DisableHighDpiScaling);
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("greenpepper software");
    QCoreApplication::setOrganizationDomain("github.com/easymodo/qimgv");
    QCoreApplication::setApplicationName("qimgv");
    QCoreApplication::setApplicationVersion("0.52");

    // needed for mpv
    std::setlocale(LC_NUMERIC, "C");

    settings = Settings::getInstance();
    actionManager = ActionManager::getInstance();
    shrRes = SharedResources::getInstance();

    atexit(saveSettings);

    QFile file(":/res/styles/dark.qss");
    if(file.open(QFile::ReadOnly)) {
        QString StyleSheet = QLatin1String(file.readAll());
        qApp->setStyleSheet(StyleSheet);
    }

    Core core;
    if(a.arguments().length() > 1) {
        QString fileName = a.arguments().at(1);
        core.loadByPathBlocking(fileName);
    }
    core.showGui();

    return a.exec();
}
