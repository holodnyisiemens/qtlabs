#include <QtTest>
#include <QCoreApplication>
#include "../lab2/dialog.h"
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QMessageBox>

class test_sample : public QObject {
    Q_OBJECT

public:
    test_sample();
    ~test_sample();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_input_a();
    void test_input_b();
    void test_button();
    void test_switch_components();
    void test_clear_list();
    void test_full_cycle();
    void test_not_integer_a();
    void test_not_integer_b();
    void test_not_positive_a();
    void test_not_positive_b();
    void test_a_more_b();

private:
    Dialog * mainDialog;
    QLineEdit * lineEditA;
    QLineEdit * lineEditB;
    QPushButton * pushButton;
    QListWidget * listWidget;
    bool seenMessage;
    QString messageText;
    void close_messagebox();
};

void test_sample::close_messagebox() {
    QMessageBox * msgbox =
        qobject_cast<QMessageBox *>(QApplication::activeModalWidget());
    if(msgbox) {
        seenMessage = true;
        messageText = msgbox->text();
        msgbox->close();
    }
}

test_sample::test_sample() {
}

test_sample::~test_sample() {
}

void test_sample::initTestCase() {
    mainDialog = new Dialog();
    lineEditA = mainDialog->findChild<QLineEdit *>("lineEditA");
    lineEditB = mainDialog->findChild<QLineEdit *>("lineEditB");
    pushButton = mainDialog->findChild<QPushButton *>("pushButton");
    listWidget = mainDialog->findChild<QListWidget *>("listWidget");
    mainDialog->show();
}

void test_sample::cleanupTestCase() {
    delete mainDialog;
}

void test_sample::test_input_a() {
    // имитируем событие щелчка левой кнопкой мыши на поле ввода A
    QTest::mouseClick(lineEditA, Qt::LeftButton);
    // имитируем нажатие последовательности клавиш 123
    QTest::keyClicks(lineEditA, "123");
    // сравниваем введенное значение с образцом
    QCOMPARE(lineEditA->text(), QString("123"));
    // очищаем поле ввода
    lineEditA->clear();
}

void test_sample::test_input_b() {
    // имитируем событие щелчка левой кнопкой мыши на поле ввода B
    QTest::mouseClick(lineEditB, Qt::LeftButton);
    // имитируем нажатие последовательности клавиш 123
    QTest::keyClicks(lineEditB, "123");
    // сравниваем введенное значение с образцом
    QCOMPARE(lineEditB->text(), QString("123"));
    // очищаем поле ввода
    lineEditB->clear();
}

void test_sample::test_button() {
    // отсоединяем слот обработки данных
    QObject::disconnect(pushButton, SIGNAL(clicked()), mainDialog,
                        SLOT(calculate()));
    // создаем объект инспектора сигналов, реагирующего на сигнал clicked() кнопки
    QSignalSpy clickSpy(pushButton, SIGNAL(clicked()));
    // имитируем событие нажатия кнопки
    QTest::mouseClick(pushButton, Qt::LeftButton);
    // проверяем, что инспектор зафиксировал одно событие
    QCOMPARE(clickSpy.count(), 1);
    // присоединяем слот обработки данных обратно
    QObject::connect(pushButton, SIGNAL(clicked()), mainDialog,
                     SLOT(calculate()));
}

void test_sample::test_switch_components() {
    QTest::mouseClick(lineEditA, Qt::LeftButton);
    QVERIFY(lineEditA->hasFocus());
    QTest::keyClick(lineEditA, Qt::Key::Key_Tab);
    QVERIFY(lineEditB->hasFocus());
    QTest::keyClick(lineEditA, Qt::Key::Key_Tab);
    QVERIFY(pushButton->hasFocus());
    QTest::keyClick(pushButton, Qt::Key::Key_Tab);
    QVERIFY(listWidget->hasFocus());
    QTest::keyClick(pushButton, Qt::Key::Key_Tab);
    QVERIFY(lineEditA->hasFocus());
}

void test_sample::test_clear_list() {
    // устанавливаем текст в полях ввода A и B
    lineEditA->setText("10");
    lineEditB->setText("20");
    // генерируем событие нажатия кнопки
    pushButton->click();
    // проверяем количество значений в списке
    QCOMPARE(listWidget->count(), 4);
    // повторно нажимаем кнопку
    pushButton->click();
    // и проверяем количество значений
    QCOMPARE(listWidget->count(), 4);
}

void test_sample::test_full_cycle() {
    lineEditA->clear();
    lineEditB->clear();
    QTest::keyClicks(mainDialog->focusWidget(), "10");
    QTest::keyClick(mainDialog, Qt::Key::Key_Tab);
    QTest::keyClicks(mainDialog->focusWidget(), "20");
    QTest::mouseClick(pushButton, Qt::LeftButton);
    QCOMPARE(listWidget->count(), 4);
    std::vector<QString> result;
    for(int i = 0; i < listWidget->count(); ++i) {
        result.push_back(listWidget->item(i)->text());
    }
    QCOMPARE(result, std::vector<QString>({QString("11"),
                                           QString("13"), QString("17"), QString("19")}));
}

void test_sample::test_not_integer_a() {
    lineEditA->setText("");
    lineEditB->setText("20");
    seenMessage = false;
    // через 100 мс выполняем функцию close_messagebox()
    QTimer::singleShot(100, this, &test_sample::close_messagebox);
    pushButton->click();
    if(!seenMessage) {
        QFAIL("No messagebox");
    }
    QCOMPARE(messageText, "A must be an integer");
}

void test_sample::test_not_integer_b() {
    lineEditA->setText("10");
    lineEditB->setText("");
    seenMessage = false;
    // через 100 мс выполняем функцию close_messagebox()
    QTimer::singleShot(100, this, &test_sample::close_messagebox);
    pushButton->click();
    if(!seenMessage) {
        QFAIL("No messagebox");
    }
    QCOMPARE(messageText, "B must be an integer");
}

void test_sample::test_not_positive_a() {
    lineEditA->setText("-1");
    lineEditB->setText("3");
    seenMessage = false;
    // через 100 мс выполняем функцию close_messagebox()
    QTimer::singleShot(100, this, &test_sample::close_messagebox);
    pushButton->click();
    if(!seenMessage) {
        QFAIL("No messagebox");
    }
    QCOMPARE(messageText, "A must be positive");
}

void test_sample::test_not_positive_b() {
    lineEditA->setText("1");
    lineEditB->setText("-3");
    seenMessage = false;
    // через 100 мс выполняем функцию close_messagebox()
    QTimer::singleShot(100, this, &test_sample::close_messagebox);
    pushButton->click();
    if(!seenMessage) {
        QFAIL("No messagebox");
    }
    QCOMPARE(messageText, "B must be positive");
}

void test_sample::test_a_more_b() {
    lineEditA->setText("10");
    lineEditB->setText("9");
    seenMessage = false;
    // через 100 мс выполняем функцию close_messagebox()
    QTimer::singleShot(100, this, &test_sample::close_messagebox);
    pushButton->click();
    if(!seenMessage) {
        QFAIL("No messagebox");
    }
    QCOMPARE(messageText, "A must be less than B");
}

QTEST_MAIN(test_sample)

#include "tst_test_sample.moc"
