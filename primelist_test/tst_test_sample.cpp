#include "../primelist_library/primelist_library.h"
#include <QtTest>

class test_sample : public QObject
{
    Q_OBJECT

public:
    test_sample();
    ~test_sample();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void absense_of_one();
    void including_upper_in_list();
    void including_lower_in_list();
    void test_out_of_range_with_zero_a();
    void test_out_of_range_with_zero_b();
    void test_out_of_range_with_negative_a();
    void test_out_of_range_with_negative_b();
    void test_domain_error_with_big_a();
    void test_domain_error_on_border();
    void test_a_equal_b();
    void test_efficiency();
};

test_sample::test_sample()
{

}

test_sample::~test_sample()
{

}

void test_sample::initTestCase()
{

}

void test_sample::cleanupTestCase()
{

}

void test_sample::absense_of_one()
{
    QCOMPARE(primelist(1, 2), std::vector<int>({2}));
}

void test_sample::including_upper_in_list()
{
    QCOMPARE(primelist(4, 5), std::vector<int>({5}));
}

void test_sample::including_lower_in_list()
{
    QCOMPARE(primelist(3, 4), std::vector<int>({3}));
}

void test_sample::test_out_of_range_with_zero_a()
{
    try {
        primelist(0, 3);
        QFAIL("No exception");
    } catch (std::out_of_range & e) {
        QCOMPARE(e.what(), "A must be positive");
    } catch (...) {
        QFAIL("Wrong exception");
    }
}

void test_sample::test_out_of_range_with_zero_b()
{
    try {
        primelist(2, 0);
        QFAIL("No exception");
    } catch (std::out_of_range & e) {
        QCOMPARE(e.what(), "B must be positive");
    } catch (...) {
        QFAIL("Wrong exception");
    }
}

void test_sample::test_out_of_range_with_negative_a()
{
    try {
        primelist(-1, 3);
        QFAIL("No exception");
    } catch (std::out_of_range & e) {
        QCOMPARE(e.what(), "A must be positive");
    } catch (...) {
        QFAIL("Wrong exception");
    }
}

void test_sample::test_out_of_range_with_negative_b()
{
    try {
        primelist(2, -1);
        QFAIL("No exception");
    } catch (std::out_of_range & e) {
        QCOMPARE(e.what(), "B must be positive");
    } catch (...) {
        QFAIL("Wrong exception");
    }
}

void test_sample::test_domain_error_with_big_a()
{
    try {
        primelist(100, 10);
        QFAIL("No exception");
    } catch (std::domain_error & e) {
        QCOMPARE(e.what(), "A must be equal or less than B");
    } catch (...) {
        QFAIL("Wrong exception");
    }
}

void test_sample::test_domain_error_on_border()
{
    try {
        primelist(10, 9);
        QFAIL("No exception");
    } catch (std::domain_error & e) {
        QCOMPARE(e.what(), "A must be equal or less than B");
    } catch (...) {
        QFAIL("Wrong exception");
    }
}

void test_sample::test_a_equal_b()
{
    QCOMPARE(primelist(7, 7), std::vector<int>({7}));
}

void test_sample::test_efficiency()
{
    QBENCHMARK {
        primelist(10000, 99999);
    }
}

QTEST_APPLESS_MAIN(test_sample)

#include "tst_test_sample.moc"
