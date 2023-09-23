#include "mainwindow.hpp"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QLibraryInfo>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Загрузка Qt локализации
    QTranslator qtBaseTranslator;
    if (qtBaseTranslator.load("qt_" + QLocale::system().name(),
                              QLibraryInfo::path(QLibraryInfo::TranslationsPath)))
    {
        qDebug() << "qtBaseTranslator ok";
        a.installTranslator(&qtBaseTranslator);
    }

    // Инициализация интерфейса
    MainWindow w;
    w.show();
    return a.exec();
}
