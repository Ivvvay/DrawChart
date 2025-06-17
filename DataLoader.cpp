#include "DataLoader.h"

QList<DataStorage> SQLDataLoader::loadData(QString filePath) {
    QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE");
    dbase.setDatabaseName(filePath);
    QList<DataStorage> result;

    if (dbase.open()) {
        QSqlQuery query ("SELECT * FROM " + dbase.tables().takeFirst());

        int i = 0;
        while (query.next() && i < 10) {
            i++;
            DataStorage temp{query.value(0).toString(), query.value(1).toDouble()};
            result.push_back(temp);
        }
    } else {
        qDebug() << "sqlite was not opened";
    }
    return result;
}

QList<DataStorage> JSONDataLoader::loadData(QString filePath) {
    QString val;
    QFile file;
    file.setFileName(filePath);
    QList<DataStorage> result;

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        val = file.readAll();
        file.close();

        QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
        QJsonObject jsonObject = doc.object();
        QStringList keys (jsonObject.keys());

        int i = 0;
        QListIterator<QString> iterator(keys);
        while (iterator.hasNext() && i < 10) {
            QString key = iterator.next();
            double value = jsonObject.value(key).toDouble();

            DataStorage temp{key, value};
            result.push_back(temp);
            i++;
        }
    } else {
        qDebug() << "Json was not opened";
    }
    return result;
}
