/*
    rowadd.cpp - (c) Michael Weber, Jr. (2012)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "rowadd.h"
#include "ui_rowadd.h"
#include "steelbars.h"

Bar *stdBars[11] = {
    new Bar("#3", 0.375, 0.11),
    new Bar("#4", 0.500, 0.20),
    new Bar("#5", 0.625, 0.31),
    new Bar("#6", 0.750, 0.44),
    new Bar("#7", 0.875, 0.60),
    new Bar("#8", 1.000, 0.79),
    new Bar("#9", 1.128, 1.00),
    new Bar("#10", 1.270, 1.27),
    new Bar("#11", 1.410, 1.56),
    new Bar("#14", 1.693, 2.25),
    new Bar("#18", 2.257, 4.00)
};

RowAdd::RowAdd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RowAdd)
{
    ui->setupUi(this);

    setWindowTitle("Add Steel Bar Row");

    for(int i = 0; i < 11; i++)
        ui->comboBox->addItem(stdBars[i]->name);
    ui->comboBox->setCurrentIndex(0);
}

RowAdd::~RowAdd()
{
    delete ui;
}

void RowAdd::accept()
{
    num = ui->lineEdit->text().toInt();
    depth = ui->lineEdit_2->text().toDouble();
    if(ui->comboBox->currentIndex() < 0) area = 0.0;
    else area = stdBars[ui->comboBox->currentIndex()]->area * num;
    QDialog::accept();
}
