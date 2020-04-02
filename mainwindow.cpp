#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>
#include <QLineEdit>
#include <QToolButton>
#include <QVariant>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix("C:/Users/ASUS/Desktop/xcircuit figures/rl_circuit3");
    ui->label_pic->setPixmap(pix);
    connect(ui->toolButton,SIGNAL(clicked()),this,SLOT(onclicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::onclicked()
{
    solver();
}
void MainWindow::solver()
{
    double h=1/(10000.0);
    double V=ui->lineEdit->text().toDouble();
    double R=ui->lineEdit_2->text().toDouble();
    double L=ui->lineEdit_3->text().toDouble();
    double i0=ui->lineEdit_4->text().toDouble();
    QVector<double> t(1000002),i(1000002);
    t[0]=0;
    i[0]=i0;



    for(double n=1;n<1000001;n++)
    {
        double didt=(V*sin(0.01*t[n-1])-i[n-1]*R)/L;

        t[n]=n/10000.0;
        i[n]=i[n-1]+(h*didt);

    }

    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(t,i);
    ui->customPlot->xAxis->setLabel("t");
    ui->customPlot->yAxis->setLabel("i");
    ui->customPlot->xAxis->setRange(0,100);
    ui->customPlot->yAxis->setRange(20,0);
    ui->customPlot->replot();

}
