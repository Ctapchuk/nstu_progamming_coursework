#ifndef DATABASE_MANAGER_HPP
#define DATABASE_MANAGER_HPP
#include <QList>
#include <QString>

struct DiseaseInfo {
    QString name;
    QString symptoms;
    QString consequences;
    QString medicines;
    QString procedures;
};

class DatabaseManager
{
private:
    const inline static QString kDatabaseFile = "diseasesDB";
    inline static QList<DiseaseInfo> diseases_database;
    inline static bool Is_DatabaseChanged = false;
    static void LoadTestDatabase();
    static void LoadDatabase();
    static void SaveDatabase();

friend class MainWindow;
};

#endif // DATABASE_MANAGER_HPP
