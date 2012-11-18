/*
    mainwindow.cpp - (c) Michael Weber, Jr. (2012)

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

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Reinforced Concrete Column Interaction");

    helpAction = new QAction("Help", NULL);
    connect(helpAction, SIGNAL(triggered()), this, SLOT(help()));
    aboutAction = new QAction("About", NULL);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));
    helpMenu = new QMenu("Help");
    helpMenu->addAction(helpAction);
    helpMenu->addAction(aboutAction);
    ui->menuBar->addMenu(helpMenu);

    ui->tableWidget->setColumnCount(3);
    QStringList *list = new QStringList();
    list->append("Number of Bars");
    list->append("Bar Area (in^2)");
    list->append("Depth to Bars (in)");
    ui->tableWidget->setHorizontalHeaderLabels(*list);
    ui->tableWidget->adjustSize();

    data = new Algorithm();
    tableWidget = ui->tableWidget;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_3_clicked()
{
    data->fc = ui->lineEdit->text().toDouble();
    data->fs = ui->lineEdit_2->text().toDouble()*1000;
    data->Es = ui->lineEdit_3->text().toDouble()*1000;
    data->b = ui->lineEdit_4->text().toDouble();
    data->h = ui->lineEdit_5->text().toDouble();
    data->tension_strain = ui->lineEdit_6->text().toDouble();
    data->tied = ui->radioButton->isChecked();

    data->steelRows = ui->tableWidget->rowCount();
    data->barrows = new BarRow[data->steelRows];
    for(int i = 0; i < data->steelRows; i++)
    {
        data->barrows[i].count = ui->tableWidget->item(i, 0)->text().toInt();
        data->barrows[i].area = ui->tableWidget->item(i, 1)->text().toDouble();
        data->barrows[i].depth = ui->tableWidget->item(i, 2)->text().toDouble();
    }

    //data->dump();

    data->calculate();

    Results *results = new Results(this);
    results->setResults(data->results);
    results->exec();
    delete results;
}

void MainWindow::on_pushButton_2_clicked()
{
    RowDelete *rowDelete = new RowDelete(this);
    rowDelete->setComboBox(ui->tableWidget);
    if(rowDelete->exec())
    {
        ui->tableWidget->removeRow(rowDelete->selection);
    }

    delete rowDelete;
}

void MainWindow::on_pushButton_clicked()
{
    RowAdd *rowAdd = new RowAdd(this);
    if(rowAdd->exec())
    {
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->setRowCount(row+1);
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(rowAdd->num)));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(rowAdd->area)));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(rowAdd->depth)));
    }

    delete rowAdd;
}

void MainWindow::about()
{
    About *aboutWindow = new About(this);
    aboutWindow->exec();
}

void MainWindow::help()
{
    Help *helpWindow = new Help(this);
    helpWindow->exec();
}
