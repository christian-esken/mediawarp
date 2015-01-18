#include "SQLiteConnection.h"

#include <QDebug>

#include <exception>

/**
 * Tries to opens a connection to the given database.
 * 
 */
SQLiteConnection::SQLiteConnection()
{
	_open = false;
	_isInTransaction = false;
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
bool SQLiteConnection::open(QString dbname, QString connName, bool create)
{
	//QSqlDatabase
	db = QSqlDatabase::addDatabase("QSQLITE", connName);
	//db.setHostName("localhost");
	if (!create)
	{
		db.setConnectOptions("QSQLITE_OPEN_READONLY");
	}
	db.setDatabaseName(dbname.toUtf8());

	if (db.open())
	{
		_open = true;
	}

	return _open;
}

/**
 * Runs a SQL query (SELECT, UPDATE, DELETE, CREATE TABLE, ...). IN cas of errors, a td::runtime_error is thrown.
 *
 * @param sql
 * @return A QSqlQuery* object that holds the result
 */
QSqlQuery* SQLiteConnection::runQuery(const QString& sql)
{
	if (! isOpen())
	{
		return 0;
	}

	QSqlQuery* query = new QSqlQuery(sql, db);
	bool ok = query->exec();
	if (!ok)
	{
		throw std::runtime_error(std::string("Query failed: error=" ) + qPrintable(query->lastError().text())
			+ ", sql=" + qPrintable(sql));

	}
	return query;
}

void SQLiteConnection::execPreparedQuery(QSqlQuery* query)
{
	bool ok = query->exec();
	if (!ok)
	{
		throw std::runtime_error(std::string("Query failed: error=" ) + qPrintable(query->lastError().text())
			+ ", sql=" + qPrintable(query->lastQuery()));

	}
}

/**
 * Prepares a QSqlQuery and starts a transaction
 * @param sql
 * @return
 */
QSqlQuery* SQLiteConnection::getPreparedQuery(QString sql)
{
	QSqlQuery* query = new QSqlQuery(db);
	query->prepare(sql);
	db.transaction();
	_isInTransaction = true;
	return query;
}

void SQLiteConnection::commit()
{
	if (_isInTransaction)
	{
		db.commit();
		_isInTransaction = false;
	}
}


bool SQLiteConnection::isOpen()
{
	return _open;
}

