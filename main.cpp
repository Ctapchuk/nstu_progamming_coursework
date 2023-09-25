#include "mainwindow.hpp"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QLibraryInfo>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Загрузка Qt локализации
    QTranslator Translator;
    if (Translator.load(":/qt_" + QLocale::system().name()))
    {
        qDebug() << "Локализация загружена!";
        a.installTranslator(&Translator);
    }

    // Инициализация интерфейса
    MainWindow w;
    w.show();
    return a.exec();
}
