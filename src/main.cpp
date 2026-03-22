/*
AutoQuick
*/

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>

int main(int argc, char* argv[]){
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() {
            qWarning() << "CRITICAL ERROR: QML Engine failed to load the file!";
            QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    
    // const QUrl url(u"qrc:/<your URI value from qt_add_qml_module in CMakeLists.txt>/<name of your qml file>)
    const QUrl url(u"qrc:/AutoQuick/assets/qml/main.qml"_qs);
    
    engine.load(url);

    return app.exec();
}