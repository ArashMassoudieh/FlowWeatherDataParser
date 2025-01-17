#ifndef CSV_TABLE_WIDGET_H
#define CSV_TABLE_WIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

class CsvTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CsvTableWidget(QWidget *parent = nullptr);
    ~CsvTableWidget();

    bool loadCsv(const QString &filePath);

private:
    QTableWidget *tableWidget;
};

double convertToExcelDateTime(const QString &dateTimeString);
QStringList splitCsv(const QString &line);

#endif // CSV_TABLE_WIDGET_H
