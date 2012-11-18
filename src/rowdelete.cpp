/*
    rowdelete.cpp - (c) Michael Weber, Jr. (2012)

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

#include "rowdelete.h"
#include "ui_rowdelete.h"

void RowDelete::setComboBox(QTableWidget *tableWidget)
{
    for(int i = 0; i < tableWidget->rowCount(); i++)
        ui->comboBox->addItem(QString('1'+i));
}

RowDelete::RowDelete(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RowDelete)
{
    ui->setupUi(this);

    setWindowTitle("Delete Steel Bar Row");
}

RowDelete::~RowDelete()
{
    delete ui;
}

void RowDelete::accept()
{
    selection = ui->comboBox->currentIndex();
    QDialog::accept();
}
