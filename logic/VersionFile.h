#pragma once

#include <QString>
#include <QStringList>
#include <memory>
#include "logic/OpSys.h"
#include "logic/OneSixRule.h"
class VersionFinal;

struct VersionFile
{
	int order;
	QString name;
	QString fileId;
	QString version;
	// TODO use the mcVersion to determine if a version file should be removed on update
	QString mcVersion;
	QString filename;
	// TODO requirements
	// QMap<QString, QString> requirements;
	QString id;
	QString mainClass;
	QString overwriteMinecraftArguments;
	QString addMinecraftArguments;
	QString removeMinecraftArguments;
	QString processArguments;
	QString type;
	QString releaseTime;
	QString time;
	QString assets;
	int minimumLauncherVersion = -1;

	bool shouldOverwriteTweakers = false;
	QStringList overwriteTweakers;
	QStringList addTweakers;
	QStringList removeTweakers;

	struct Library
	{
		QString name;
		QString url;
		QString hint;
		QString absoluteUrl;
		bool applyExcludes = false;
		QStringList excludes;
		bool applyNatives = false;
		QList<QPair<OpSys, QString>> natives;
		bool applyRules = false;
		QList<std::shared_ptr<Rule>> rules;

		// user for '+' libraries
		enum InsertType
		{
			Apply,
			Append,
			Prepend,
			Replace
		};
		InsertType insertType = Append;
		QString insertData;
		enum DependType
		{
			Soft,
			Hard
		};
		DependType dependType = Soft;

		static Library fromJson(const QJsonObject &libObj, const QString &filename,
								bool &isError);
	};
	bool shouldOverwriteLibs = false;
	QList<Library> overwriteLibs;
	QList<Library> addLibs;
	QList<QString> removeLibs;

	enum ApplyError
	{
		LauncherVersionError,
		OtherError,
		NoApplyError
	};

	static VersionFile fromJson(const QJsonDocument &doc, const QString &filename,
								const bool requireOrder, bool &isError,
								const bool isFTB = false);

	static std::shared_ptr<OneSixLibrary> createLibrary(const Library &lib);
	int findLibrary(QList<std::shared_ptr<OneSixLibrary>> haystack, const QString &needle);
	ApplyError applyTo(VersionFinal *version);
};