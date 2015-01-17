
#ifndef X_QSqlDatabase
#define X_QSqlDatabase


#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>

class SQLiteConnection
{
public:
  SQLiteConnection();
  ~SQLiteConnection();

  bool open(QString dbname, QString connName, bool create);
  QSqlQuery* runQuery(const QString& sql);
  bool isOpen();
  void close();

private:
  QSqlDatabase db;  
  bool _open;
};

#endif
