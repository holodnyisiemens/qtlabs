#include "dialog.h"
#include "ui_dialog.h"

#include <primelist_library.h>

#include <QDebug>
#include <QMessageBox>
#include <stdexcept>

Dialog::Dialog(QWidget * parent)
    : QDialog(parent)
    , ui(new Ui::Dialog) {
    ui->setupUi(this);
}

Dialog::~Dialog() {
    delete ui;
}

void Dialog::calculate() {
    try {
        // очистка списка вывода
        ui->listWidget->clear();
        bool isAOK, isBOK;
        int a = ui->lineEditA->text().toInt(&isAOK);
        int b = ui->lineEditB->text().toInt(&isBOK);
        if(!isAOK) {
            throw std::invalid_argument("A must be an integer");
        }
        if(!isBOK) {
            throw std::invalid_argument("B must be an integer");
        }
        // вызов функции получения списка простых чисел
        for(int n : primelist(a, b)) {
            ui->listWidget->addItem(QString::number(n));
        }
    } catch(std::exception const & e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}
