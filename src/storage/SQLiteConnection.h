
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

  QSqlQuery* getPreparedQuery(QString sql);
  void execPreparedQuery(QSqlQuery* query);
  void commit();


  bool isOpen();
  void close();

private:
  QSqlDatabase db;  
  bool _open;
  bool _isInTransaction;
};

#endif
