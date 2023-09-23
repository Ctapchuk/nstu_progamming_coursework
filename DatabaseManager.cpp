#include "DatabaseManager.hpp"
#include <QDir>
#include <QFile>
#include <QDataStream>
#include <QDebug>

QDataStream & operator<<(QDataStream &out, const DiseaseInfo &disease)
{
    out << disease.Name
        << disease.Symptoms
        << disease.Consequences
        << disease.RecMedicines
        << disease.RecProcedures;
    return out;
}

QDataStream & operator>>(QDataStream & in, DiseaseInfo & disease)
{
    in >> disease.Name
        >> disease.Symptoms
        >> disease.Consequences
        >> disease.RecMedicines
        >> disease.RecProcedures;
    return in;
}

void DatabaseManager::LoadTestDatabase() {
    DiseasesDatabase.clear();
    struct DiseaseInfo dis;
    dis.Name = "Туберкулёз";
    dis.Symptoms = "кашель, слабость, повышенная утомляемость, боль в грудной клетке";
    dis.Consequences = "лёгочное кровотечение, плеврит, пневмония";
    dis.RecMedicines = "изониазид, рифампицин";
    dis.RecProcedures = "электролечение, лазеротерапия, теплолечение";
    DiseasesDatabase.push_back(dis);
    //
    dis.Name = "Авитаминоз";
    dis.Symptoms = "повышенная утомляемость, нарушения сна, апатия, сонливость";
    dis.Consequences = "потеря обоняния, куриная слепота, анемия, мочекаменная болезнь";
    dis.RecMedicines = "витаминные комплексы и монопрепараты";
    dis.RecProcedures = "назначение диеты, капельницы";
    DiseasesDatabase.push_back(dis);
    //
    dis.Name = "Абсцесс печени";
    dis.Symptoms = "тяжесть в правом подреберье, снижение массы тела, пожелтение кожи, увеличение печени, диарея, выраженная потливость";
    dis.Consequences = "осложнение течения аппендицита и желчнокаменной болезни, заражение крови, летальный исход";
    dis.RecMedicines = "антибактериальные или противопаразитные, противогельминтные препараты";
    dis.RecProcedures = "тонкоигольная биопсия абсцесса";
    DiseasesDatabase.push_back(dis);
    //
    dis.Name = "Нейродермит";
    dis.Symptoms = "кожный зуд, многочисленные высыпания, чрезмерная сухость кожи, образование эрозий и корочек, изменение цвета кожи";
    dis.Consequences = "образование эрозий и язв, бактериальная инфекция";
    dis.RecMedicines = "антигистаминные, седативные средства, витамины";
    dis.RecProcedures = "физиотерапия, психотерапия";
    DiseasesDatabase.push_back(dis);
    //
    dis.Name = "Геморрой";
    dis.Symptoms = "зуд в области анального отверстия, запоры, метеоризм, кровотечение, появление геморроидальных узлов";
    dis.Consequences = "сильные боли, гнойная инфекция, рак прямой кишки";
    dis.RecMedicines = "антикоагулянты в виде мазей или ректальных свечей, нестероидные противовоспалительные средства и спазмолитики, мягкие слабительные";
    dis.RecProcedures = "склеротерапия, лигирование, инфракрасная фотокоагуляция";
    DiseasesDatabase.push_back(dis);
}

void DatabaseManager::LoadDatabase()
{
    try
    { // работаем с файлами с осторожностью
        QFile file;
        QDir::setCurrent(QDir::homePath()); // Текущая папка C:/Users/Username
        file.setFileName(DatabaseFile);

        if (file.open(QIODevice::ReadOnly)) {
            qDebug() << "Файл успешно открыт для чтения!";
            QDataStream in(&file);
            in >> DiseasesDatabase;
            file.close();
        }
    } catch (...)
    {
        qDebug() << "Загрузка каталога: неудалось загрузить!";
    }
}

void DatabaseManager::SaveDatabase() {
    try
    {
        QFile file;
        QDir::setCurrent(QDir::homePath()); // Текущая папка = C:/Users/Username
        file.setFileName(DatabaseFile);

        if (file.open(QIODevice::WriteOnly)) {      // Открытие "C:/Users/Username/database.txt"
            qDebug() << "Файл успешно открыт для записи!";
            QDataStream out(&file);
            QList<DiseaseInfo> DirectoryToSave;
            for(const auto &i: DiseasesDatabase)
                if (i.Name != "")
                    DirectoryToSave.push_back(i);

            out << DirectoryToSave;
            file.close();

        }
    } catch (...)
    {
        qDebug() << "Сохранение каталога: неудалось загрузить!";
    }

}
