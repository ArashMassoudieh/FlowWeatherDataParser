#include "WatershedDischarge.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QString>
#include <QDateTime>
#include <QTimeZone>

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


