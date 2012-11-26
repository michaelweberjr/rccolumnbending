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
    //ui->tableWidget->adjustSize();
    ui->tableWidget->setRowCount(6);
}

void Results::setResults(Algorithm *data)
{
    for(int i = 0; i < 6; i++)
    {
        QString point("Point ");
        point.append('1' + i + (i == 5 ? 1 : 0));
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(point));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(data->results[i][0]/1000)));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(data->results[i][1]/1000/12)));
    }

    // Set up the graphes
    ui->widget->yAxis->setLabel("Axial Force (kip)");
    ui->widget->xAxis->setLabel("Bending Moment (kip-in)");
    double maxMoment = 0;
    for(int i = 0; i < data->graphCount; i++)
        if(data->unfactoredPoints[i][1] > maxMoment) maxMoment = data->unfactoredPoints[i][1];
    ui->widget->xAxis->setRange(0, maxMoment * 1.1 / 1000 / 12);
    ui->widget->yAxis->setRange(data->unfactoredPoints[data->graphCount-1][0] * 1.1 / 1000, data->unfactoredPoints[0][0] * 1.1 / 1000);

    // Add the data
    QVector<double> x1(data->graphCount), y1(data->graphCount), x2(data->graphCount), y2(data->graphCount);
    for(int i = 0; i < data->graphCount; i++)
    {
        y1[i] = data->unfactoredPoints[i][0]/1000;
        x1[i] = data->unfactoredPoints[i][1]/1000/12;
        y2[i] = data->factoredPoints[i][0]/1000;
        x2[i] = data->factoredPoints[i][1]/1000/12;
    }
    QCPCurve *curve1 = new QCPCurve(ui->widget->xAxis, ui->widget->yAxis);
    ui->widget->addPlottable(curve1);
    curve1->setData(x1, y1);
    curve1->setPen(QPen(Qt::blue));
    QCPCurve *curve2 = new QCPCurve(ui->widget->xAxis, ui->widget->yAxis);
    ui->widget->addPlottable(curve2);
    curve2->setData(x2, y2);
    curve2->setPen(QPen(Qt::red));

    ui->widget->setRangeDrag(Qt::Horizontal | Qt::Vertical);
    ui->widget->setRangeZoom(Qt::Horizontal | Qt::Vertical);

    ui->widget->replot();
}

Results::~Results()
{
    delete ui;
}
