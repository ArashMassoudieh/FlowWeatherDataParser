#include "WatershedDischarge.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QString>
#include <QDateTime>

// Function to parse the TSV file
QList<WatershedDischarge> parseTSVFile(const QString &filePath) {
    QList<WatershedDischarge> records;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Unable to open file:" << filePath;
        return records;
    }

    QTextStream in(&file);
    QString headerLine = in.readLine(); // Read the header row
    QString unitLine = in.readLine();   // Read the second row (units)

    // Check if the file has valid data
    if (headerLine.isEmpty() || unitLine.isEmpty()) {
        qWarning() << "File appears to be empty or improperly formatted.";
        return records;
    }

    // Process each data line
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.trimmed().isEmpty()) continue;

        QStringList fields = line.split('\t');
        if (fields.size() < 6) { // Ensure sufficient columns are present
            qWarning() << "Skipping malformed line:" << line;
            continue;
        }

        WatershedDischarge record;
        record.agency_cd = fields[0];
        record.site_no = fields[1];
        record.datetime = QDateTime::fromString(fields[2], "yyyy-MM-dd HH:mm");
        record.tz_cd = fields[3];
        record.discharge_value = fields[4].toDouble();
        record.discharge_code = fields[5];

        records.append(record);
    }

    file.close();
    return records;
}

double convertToExcelDateTime(const QString &inputDateTime) {
    // Define the input date format
    QString inputFormat = "yyyy-MM-dd HH:mm";

    // Parse the input string to QDateTime
    QDateTime dateTime = QDateTime::fromString(inputDateTime, inputFormat);
    if (!dateTime.isValid()) {
        qWarning() << "Invalid date/time format:" << inputDateTime;
        return -1; // Return an invalid value
    }

    // Define the base date for Excel (January 1, 1900)
    QDateTime excelBaseDate(QDate(1900, 1, 1), QTime(0, 0, 0), Qt::UTC);

    // Calculate the difference in days and convert to Excel date number
    qint64 secondsDiff = excelBaseDate.secsTo(dateTime);
    double excelDate = secondsDiff / 86400.0 + 1; // 86400 seconds in a day, +1 for Excel day 1

    // Account for Excel's leap year bug (1900 is incorrectly treated as a leap year)
    if (dateTime.date() > QDate(1900, 2, 28)) {
        excelDate += 1;
    }

    return excelDate;
}
