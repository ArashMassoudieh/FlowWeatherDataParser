#ifndef CSV_TABLE_WIDGET_H
#define CSV_TABLE_WIDGET_H


#include <QStringList>
#include <QFile>
#include <QTextStream>


class WeatherReader
{

public:
    explicit WeatherReader();
    ~WeatherReader();

    bool loadCsv(const QString &filePath);

private:
    
};

double convertToExcelDateTime(const QString &dateTimeString, const QString& format);
QStringList splitCsv(const QString &line);

#endif // CSV_TABLE_WIDGET_H
