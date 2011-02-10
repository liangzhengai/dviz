#ifndef GLSceneTypeCurrentWeather_H
#define GLSceneTypeCurrentWeather_H

#include "GLSceneGroupType.h"

#include <QNetworkReply>

/** \class GLSceneTypeCurrentWeather
	A basic 'current weather conditions' scene type.
	
	Parameters:
		- Location - Can be a ZIP code or a location name (Chicago, IL)
		- UpdateTime - Time in seconds to wait between reloading the weather data from the server
	 
	Fields Required:
		- Location
			- Text
			- Example: Chicago, IL
			- This will be the 'normalized' location returned by the server, not the raw location given as a parameter.
			- Optional
		- Condition
			- Text
			- Example: Partly Cloudy
		- Temp
			- Text
			- Example: 9*
		- Icon
			- Svg
		- Wind
			- Text
			- Example: Wind: SW at 9 mph
			- Optional
*/			


class GLSceneTypeCurrentWeather : public GLSceneType
{
	Q_OBJECT
	
	Q_PROPERTY(QString location READ location WRITE setLocation);
	Q_PROPERTY(int updateTime READ updateTime WRITE setUpdateTime);
	
public:
	GLSceneTypeCurrentWeather(QObject *parent=0);
	virtual ~GLSceneTypeCurrentWeather() {};
	
	virtual QString id()		{ return "e0f44600-aa86-4332-a35f-efeb0088db4a"; }
	virtual QString title()		{ return "Current Weather Conditions"; }
	virtual QString description()	{ return "Displays the current weather conditions (wind, temperature, cloud cover) for a given location."; }
	
	QString location() { return m_params["location"].toString(); }
	int updateTime() { return m_params["updateTime"].toInt(); }
	
public slots:
	virtual void setLiveStatus (bool flag=true);
	
	/** Overridden to intercept changes to the 'location' parameter. */
	virtual void setParam(QString param, QVariant value);
	
	/** Set the current location to \a local.
		\a local may be any valid location descriptor accepted by Google, 
		such as a zip/postal code, a city/state pair such as "Chicago, IL", etc. */
	void setLocation(const QString& local) { setParam("location", local); }
	
	/** Set the time to wait between updates to \a seconds */
	void setUpdateTime(int seconds) { setParam("updateTime", seconds); }
		
	/** Reload the weather data for the current 'location' parameter. */
	void reloadData();
	
private slots:
	void requestData(const QString &location);
	void handleNetworkData(QNetworkReply *networkReply);
	void parseData(const QString &data);

private:
	QString extractIcon(const QString &data);
	
private:
	QHash<QString, QString> m_icons;
	
	QTimer m_reloadTimer;
};

#endif