#ifndef WATERSHEDDISCHARGE_H
#define WATERSHEDDISCHARGE_H

#include <QString>
#include <QDateTime>
#include <QList>

// Struct to represent each row in the file
struct WatershedDischarge {
    QString agency_cd;
    QString site_no;
    QDateTime datetime;
    QString tz_cd;
    double discharge_value; // 70047_00060
    QString discharge_code; // 70047_00060_cd
};

// Function declaration for parsing the TSV file
QList<WatershedDischarge> parseTSVFile(const QString &filePath);


#endif // WATERSHEDDISCHARGE_H
