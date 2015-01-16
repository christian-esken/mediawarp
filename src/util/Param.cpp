/*
 * Param.cpp
 *
 *  Created on: 15.01.2015
 *      Author: chris
 */

#include "Param.h"

#include <iostream>
#include <stdlib.h>

#include <QRegularExpression>

Param::Param(int argc, char *argv[])
{
	static char defaultOrderLiking[] = "RANDOM,ID";

	limit = 50;
	order = defaultOrderLiking;
//	mediaType = mediawarp::Constants::MediaType::ANY;
	unit = mediawarp::Constants::Unit::Title;

	if (argc == 1)
	{
		errorexit(QString(), 0);
	}

	if (argc >= 2)
	{
		QString arg(argv[1]);
		if (arg == "-h" || arg == "--help")
		{
			errorexit(QString(), 0);
		}

		bool ok;
		int limitArg = arg.toInt(&ok);
		if (!ok)
		{
			errorexit(QString("limit must be a number, but is: ") + arg, 1);
		}
		limit = limitArg;
	}

	if (argc >= 3)
	{
		QRegularExpression::PatternOption ci = QRegularExpression::CaseInsensitiveOption;
		QString selectType(argv[2]);
		if (QRegularExpression("^albums?$", ci).match(selectType).hasMatch())
			unit = mediawarp::Constants::Unit::Album;
		else if (QRegularExpression("^titles?$", ci).match(selectType).hasMatch())
			unit = mediawarp::Constants::Unit::Title;
		else if (QRegularExpression("^minutes?$", ci).match(selectType).hasMatch())
			unit = mediawarp::Constants::Unit::Duration;
		else
		{
			errorexit(QString("Unknown unit: ") + selectType, 1);
		}
	}

	if (argc >= 4)
	{
		order = QString(argv[3]);
	}

	if (argc >= 5)
	{
		filter = QString(argv[4]);
	}
}

Param::~Param()
{
}

void Param::errorexit(QString msg, int status)
{
	if (!msg.isEmpty())
	{
		std::cerr << msg.toUtf8().data() << std::endl;
	}
	std::cerr << "Usage: mediawarp [limit [unit [order [filter]]]]" << std::endl;
	std::cerr << "    limit     : Number of titles, albums or minutes to select." << std::endl;
	std::cerr << "    unit      : titles (Default), albums or minutes" << std::endl;
	std::cerr << "    order     : comma-separated sort order: LIKING,RANDOM (default),INDEX,NAME" << std::endl;
	std::cerr << "                Each may be prefixed by - or + to specify DESC or ASC sorting" << std::endl;
	std::cerr << "    filter    : comma-separated filters: Unheared, AudioBook, Podcast, Song" << std::endl;
	exit(status);
}


