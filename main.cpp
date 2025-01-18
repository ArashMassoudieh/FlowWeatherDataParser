#include <QCoreApplication>
#include <QDebug>
#include "WatershedDischarge.h"
#include "csv_table_widget.h"
#include "BTC.h"

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    QString filePath = "../../Dropbox/HickeyRun/Watershed_discharge.csv"; // Path to your TSV file
    QList<WatershedDischarge> records = parseTSVFile(filePath);
    CTimeSeries<double> output;
    // Output parsed data for verification
    unsigned int counter = 0;
    for (const WatershedDischarge &record : records) {
        /*qDebug() << "Agency:" << record.agency_cd
                 << "Site No:" << record.site_no
                 << "Datetime:" << record.datetime.toString()
                 << "Time Zone:" << record.tz_cd
                 << "Discharge Value:" << record.discharge_value
                 << "Code:" << record.discharge_code;*/
        output.append(convertToExcelDateTime(record.datetime.toString("yyyy-MM-dd HH:mm"), "yyyy-MM-dd HH:mm"),record.discharge_value*pow(0.3048,3)*86400);
        counter++;
        if (counter%1000==0)
            cout<<counter << " records completed"<<endl;
    }
    output = output.make_uniform(1.0/24.0,41185.0);
    output.writefile("../../Dropbox/HickeyRun/flow.csv");
    qDebug()<<"Finished!";
    return 0;
}
