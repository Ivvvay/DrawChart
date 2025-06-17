#ifndef DATALOADER_H
#define DATALOADER_H

#include <QList>
#include <QFile>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QJsonDocument>
#include <QJsonObject>

struct DataStorage {
public:
    QString key;
    double value;
};

class IDataLoader {
public:
    virtual QList<DataStorage> loadData(QString filePath) = 0;
    virtual ~IDataLoader() = default;
};

class SQLDataLoader: public IDataLoader {
public:
    QList<DataStorage> loadData(QString filePath) override;
    ~SQLDataLoader() = default;
};

class JSONDataLoader: public IDataLoader {
public:
    QList<DataStorage> loadData(QString filePath) override;
    ~JSONDataLoader() = default;
};

#endif // DATALOADER_H
