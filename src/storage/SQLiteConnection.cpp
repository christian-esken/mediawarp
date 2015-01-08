#include "SQLiteConnection.h"

#include <QDebug>

/**
 * Tries to opens a connection to the given database.
 * 
 */
SQLiteConnection::SQLiteConnection()
{
	_open = false;
}

SQLiteConnection::~SQLiteConnection()
{
	close();
}

void SQLiteConnection::close()
{
	if (_open)
	{
		_open = false;
		db.close();
	}
}

/**
 * Tries to opens a connection to the given database.
 *
 * @param dbname The filename of the SQLite DB
 * @param create If true, the Database will be automatically be created on #open() if it does not exist.
 *
 * @return true, if the connection could be opened.
 */
bool SQLiteConnection::open(QString dbname, bool create)
{
	//QSqlDatabase
	db = QSqlDatabase::addDatabase("QSQLITE");
	//db.setHostName("localhost");
	db.setConnectOptions("QSQLITE_OPEN_READONLY");
	db.setDatabaseName(dbname.toUtf8());

	if (db.open())
	{
		_open = true;
	}

	return _open;
}

/**
 * Exmaple_ 
 * QSqlQuery* query = runQuery("SELECT * FROM user;");
 while (query.next())
 {
 ...
 }
 delete query;
 */
QSqlQuery* SQLiteConnection::runQuery(const QString& sql)
{
	if (! isOpen())
	{
		return 0;
	}

	QSqlQuery* query = new QSqlQuery(sql, db);
	bool ok = query->exec();
	qDebug() << "SQL status=" << ok << ",  sql=" << sql;
	return query;
}

bool SQLiteConnection::isOpen()
{
	return _open;
}

