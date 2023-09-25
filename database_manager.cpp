#include "database_manager.hpp"
#include <QDir>
#include <QFile>
#include <QDataStream>
#include <QDebug>

QDataStream &operator<<(QDataStream &out, const DiseaseInfo &disease)
{
    out << disease.name
        << disease.symptoms
        << disease.consequences
        << disease.medicines
        << disease.procedures;
    return out;
}

QDataStream &operator>>(QDataStream &in, DiseaseInfo &disease)
{
    in >> disease.name
        >> disease.symptoms
        >> disease.consequences
        >> disease.medicines
        >> disease.procedures;
    return in;
}

void DatabaseManager::LoadTestDatabase()
{
    diseases_database.clear();

    struct DiseaseInfo dis;
    dis.name = "Туберкулёз";
    dis.symptoms = "кашель, слабость, повышенная утомляемость, боль в грудной клетке";
    dis.consequences = "лёгочное кровотечение, плеврит, пневмония";
    dis.medicines = "изониазид, рифампицин";
    dis.procedures = "электролечение, лазеротерапия, теплолечение";
    diseases_database.push_back(dis);
    //
    dis.name = "Авитаминоз";
    dis.symptoms = "повышенная утомляемость, нарушения сна, апатия, сонливость";
    dis.consequences = "потеря обоняния, куриная слепота, анемия, мочекаменная болезнь";
    dis.medicines = "витаминные комплексы и монопрепараты";
    dis.procedures = "назначение диеты, капельницы";
    diseases_database.push_back(dis);
    //
    dis.name = "Абсцесс печени";
    dis.symptoms = "тяжесть в правом подреберье, снижение массы тела, пожелтение кожи, увеличение печени, диарея, выраженная потливость";
    dis.consequences = "осложнение течения аппендицита и желчнокаменной болезни, заражение крови, летальный исход";
    dis.medicines = "антибактериальные или противопаразитные, противогельминтные препараты";
    dis.procedures = "тонкоигольная биопсия абсцесса";
    diseases_database.push_back(dis);
    //
    dis.name = "Нейродермит";
    dis.symptoms = "кожный зуд, многочисленные высыпания, чрезмерная сухость кожи, образование эрозий и корочек, изменение цвета кожи";
    dis.consequences = "образование эрозий и язв, бактериальная инфекция";
    dis.medicines = "антигистаминные, седативные средства, витамины";
    dis.procedures = "физиотерапия, психотерапия";
    diseases_database.push_back(dis);
    //
    dis.name = "Геморрой";
    dis.symptoms = "зуд в области анального отверстия, запоры, метеоризм, кровотечение, появление геморроидальных узлов";
    dis.consequences = "сильные боли, гнойная инфекция, рак прямой кишки";
    dis.medicines = "антикоагулянты в виде мазей или ректальных свечей, нестероидные противовоспалительные средства и спазмолитики, мягкие слабительные";
    dis.procedures = "склеротерапия, лигирование, инфракрасная фотокоагуляция";
    diseases_database.push_back(dis);
}

void DatabaseManager::LoadDatabase()
{
    try
    { // работаем с файлами с осторожностью
        QFile file;
        //qDebug() << QDir::currentPath();
        //QDir::setCurrent(QDir::homePath()); // Текущая папка C:/Users/Username
        file.setFileName(kDatabaseFile);

        if (file.open(QIODevice::ReadOnly)) {
            qDebug() << "Файл успешно открыт для чтения!";
            QDataStream in(&file);
            in >> diseases_database;
            file.close();
        }
    } catch (...)
    {
        qDebug() << "Загрузка каталога: неудалось загрузить!";
    }
}

void DatabaseManager::SaveDatabase()
{
    try
    {
        QFile file;
        //QDir::setCurrent(QDir::homePath()); // Текущая папка = C:/Users/Username
        file.setFileName(kDatabaseFile);

        if (file.open(QIODevice::WriteOnly)) {      // Открытие "C:/Users/Username/database.txt"
            qDebug() << "Файл успешно открыт для записи!";
            QDataStream out(&file);
            QList<DiseaseInfo> DirectoryToSave;
            for(const auto &i: diseases_database)
                if (i.name != "")
                    DirectoryToSave.push_back(i);

            out << DirectoryToSave;
            file.close();
        }
    } catch (...)
    {
        qDebug() << "Сохранение каталога: неудалось загрузить!";
    }
}
