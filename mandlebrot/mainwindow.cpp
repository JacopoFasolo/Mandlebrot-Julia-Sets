#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("MandleBrot & Julia Set");
    dimX=800;
    dimY=800;
    img=QImage(dimX,dimY,QImage::Format_Grayscale8);
    update();
}

MainWindow::~MainWindow()
{
    delete ui;
}

double MainWindow::map(int valore, int da, int a,int obda,int oba){
    int range=a-da;
    double perc=static_cast<double>(valore)/static_cast<double>(range);
    return static_cast<double>(obda)+((oba-obda)*perc);
}

void MainWindow::update(){
    double ca=ui->lineEdit->text().toDouble();
    double cb=ui->lineEdit_2->text().toDouble();
    qDebug()<<ca<<cb;
    bool mandlebrot;
    if(ui->radioButton->isChecked())
        mandlebrot=true;
    if(ui->radioButton_2->isChecked())
        mandlebrot=false;
    for(int i=0;i<dimX;i++){
        for(int j=0;j<dimY;j++){
            double corda=map(i,0,dimX,-2,2);
            double cordb=map(j,0,dimY,-2,2);
            int nit=50;
            double newa=corda;
            double newb=cordb;
            double nnewa=0.00;
            double nnewb=0.00;
            bool diverge=false;
            int k=0;
            for(;k<nit && !diverge;++k){
                nnewa=(newa*newa)-(newb*newb);
                nnewb=(2.00*newa*newb);
                if(mandlebrot){
                    newa=nnewa+corda;
                    newb=nnewb+cordb;
                }
                else{
                    newa=nnewa+ca;
                    newb=nnewb+cb;
                }
                if(newa+newb>16 || newa+newb<-16)
                    diverge=true;
            }
                img.setPixelColor(i,j,QColor(k*5,k*5,k*5,255));

        }
    }
    ui->label_3->setPixmap(QPixmap::fromImage(img));
    ui->label_3->show();
}

void MainWindow::on_pushButton_clicked()
{
    ui->lineEdit->setText(QString::number(0));
    ui->lineEdit_2->setText(QString::number(0));
    ui->horizontalSlider->setValue(0);
    ui->verticalSlider->setValue(0);
    a=0.00;
    b=0.00;
    update();
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    double i= arg1.toDouble();
    ui->horizontalSlider->setValue(i*5000);
    a=i;
    //update();
}

void MainWindow::on_lineEdit_2_textChanged(const QString &arg1)
{
    double i= arg1.toDouble();
    ui->verticalSlider->setValue(i*5000);
    b=i;
    //update();
}

void MainWindow::on_verticalSlider_valueChanged(int value)
{
    b=static_cast<double>(value)/5000;
    ui->lineEdit_2->setText(QString::number(b));
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    a=static_cast<double>(value)/5000;
    ui->lineEdit->setText(QString::number(a));
}

void MainWindow::on_verticalSlider_sliderReleased()
{
    update();
}

void MainWindow::on_horizontalSlider_sliderReleased()
{
    update();
}

void MainWindow::on_radioButton_clicked()
{
    update();
}

void MainWindow::on_radioButton_2_clicked()
{
    update();
}

void MainWindow::on_pushButton_3_clicked()
{
    update();
}
