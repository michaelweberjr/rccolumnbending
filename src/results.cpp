/*
    results.cpp - (c) Michael Weber, Jr. (2012)

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

#include "results.h"
#include "ui_results.h"

Results::Results(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Results)
{
    ui->setupUi(this);

    setWindowTitle("Results");

    ui->tableWidget->setColumnCount(3);
    QStringList *list = new QStringList();
    list->append("");
    list->append("Axial Force (kip)");
    list->append("Bending Moment (kip-ft)");
    ui->tableWidget->setHorizontalHeaderLabels(*list);
    ui->tableWidget->adjustSize();
    ui->tableWidget->setRowCount(6);
}

void Results::setResults(double results[6][2])
{
    for(int i = 0; i < 6; i++)
    {
        QString point("Point ");
        point.append('1' + i + (i == 5 ? 1 : 0));
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(point));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(results[i][0]/1000)));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(results[i][1]/1000/12)));
    }
}

Results::~Results()
{
    delete ui;
}
