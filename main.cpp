#include <QCoreApplication>
#include <QDebug>
#include "WatershedDischarge.h"
#include "csv_table_widget.h"
#include "BTC.h"

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    QString filePath = "/home/hoomanmoradpour/Dropbox/HickeyRun/Watershed_discharge.csv"; // Path to your TSV file
    QList<WatershedDischarge> records = parseTSVFile(filePath);
    CTimeSeries<double> output;
    // Output parsed data for verification
    for (const WatershedDischarge &record : records) {
        /*qDebug() << "Agency:" << record.agency_cd
                 << "Site No:" << record.site_no
                 << "Datetime:" << record.datetime.toString()
                 << "Time Zone:" << record.tz_cd
                 << "Discharge Value:" << record.discharge_value
                 << "Code:" << record.discharge_code;*/
        output.append(convertToExcelDateTime(record.datetime.toString("yyyy-MM-dd HH:mm"), "yyyy-MM-dd HH:mm"),record.discharge_value*pow(0.3048,3)*86400);

    }
    output.writefile("/home/hoomanmoradpour/Dropbox/HickeyRun/flow.csv");
    qDebug()<<"Finished!";
    return 0;
}
