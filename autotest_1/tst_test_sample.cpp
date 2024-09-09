#include <chrono>
#include <QString>
#include <QtTest>
#include <thread>

// add necessary includes here

class test_sample : public QObject
{
    Q_OBJECT

    int x;
    QString s;

public:
    test_sample();
    ~test_sample();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_succeed();
    void test_fail();
    void test_compare_pass();
    void test_compare_fail();
    void test_verify();
    void test_benchmark();
};

test_sample::test_sample()
{

}

test_sample::~test_sample()
{

}

void test_sample::initTestCase()
{
    x = 10;
    s = "control value";
}

void test_sample::cleanupTestCase()
{

}

void test_sample::test_succeed()
{

}

void test_sample::test_fail()
{
    QFAIL("Test failed");
}

void test_sample::test_compare_pass()
{
    QString v = "control value";
    QCOMPARE(v, s);
}

void test_sample::test_compare_fail()
{
    QString v = "Control value";
    QCOMPARE(v, s);
}

void test_sample::test_verify()
{
    QVERIFY(x > 0);
}

void test_sample::test_benchmark()
{
    QBENCHMARK
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

QTEST_APPLESS_MAIN(test_sample)

#include "tst_test_sample.moc"
