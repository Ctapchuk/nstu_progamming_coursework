#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H
#include <QList>
#include <QString>

using namespace std;

struct DiseaseInfo {
    QString Name;
    QString Symptoms;
    QString Consequences;
    QString RecMedicines;
    QString RecProcedures;
};

class DatabaseManager
{
private:
    inline static QString DatabaseFile = "database.txt";
    inline static QList<DiseaseInfo> DiseasesDatabase;
    inline static bool Is_DatabaseChanged = false;
    static void LoadTestDatabase();
    static void LoadDatabase();
    static void SaveDatabase();

friend class MainWindow;
};

#endif // DATABASEMANAGER_H
