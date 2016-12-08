#include <QString>
#include <QtTest>
#include "Report.h"

class TestReport : public QObject
{
    Q_OBJECT

public:
    TestReport(){storageLocation = "C:\\Users\\Joe\\Documents\\Touchless-Manufacturing\\Arm_Data_Storage.xml";}

private:
    Report report;
    string storageLocation;

private Q_SLOTS:
    void testLoadReportXMLDocument();
    void testSaveReportXMLDocument();
    void testIsDigitString();
    void testValidateUptime();
    void testValidateDate();
};

void TestReport::testLoadReportXMLDocument()
{
    bool returnValue = report.loadXMLFile(storageLocation.c_str());
    QCOMPARE(returnValue, bool(true));
}

void TestReport::testSaveReportXMLDocument()
{
    report.loadXMLFile(storageLocation.c_str());
    bool returnValue = report.saveXMLFile(storageLocation.c_str());
    QCOMPARE(returnValue, bool(true));
}

void TestReport::testIsDigitString()
{
    string digitString = "1234";
    QCOMPARE(report.isDigitString(digitString), bool(true));
}

void TestReport::testValidateUptime()
{
    QCOMPARE(report.validateUptime("03:12:34"), bool(true));
}

void TestReport::testValidateDate()
{
    QCOMPARE(report.validateDate("12-12-2016"), bool(true));
}

QTEST_APPLESS_MAIN(TestReport)

#include "tst_testreport.moc"
