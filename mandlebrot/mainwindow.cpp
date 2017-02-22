#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("MandleBrot & Julia Set");
    a=0;
    b=0;
    dimX=800;
    dimY=800;
    ui->label->hide();
    ui->label_2->hide();
    ui->lineEdit->hide();
    ui->lineEdit_2->hide();
    ui->pushButton->hide();
    ui->pushButton_3->hide();
    ui->horizontalSlider->hide();
    ui->verticalSlider->hide();
    img=QImage(dimX,dimY,QImage::Format_Grayscale8);
    update();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//MAP
double MainWindow::map(double valore, double da, double a,double obda,double oba){
    if(da<a){
        if(valore>=da && valore<=a){
            int range=a-da;
            double perc=(valore-da)/range;
            return obda+((oba-obda)*perc);
        }
        else
            return 0;
    }
    else if(da>a){
        if(valore<=da && valore>=a){
            int range=da-a;
            double perc=(valore-a)/range;
            return obda+((oba-obda)*perc);
        }
        else
            return 0;
    }
    else return 0;

}

//UPDATE
void MainWindow::update(){
    double ca=a;
    double cb=b;
    bool mandlebrot;
    if(ui->radioButton->isChecked())
        mandlebrot=true;
    if(ui->radioButton_2->isChecked())
        mandlebrot=false;
    for(int i=0;i<dimX;i++){
        for(int j=0;j<dimY;j++){
            double corda=map(i,0,dimX,-2,2);
            double cordb=map(j,0,dimY,-2,2);
            int nit=100;
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
                int infinity=16;
                if(newa>infinity || newa<-infinity || newb>infinity || newb<-infinity)
                    diverge=true;
            }
            int col=map(k,2,nit,255,0);
            img.setPixelColor(i,(dimY-1)-j,QColor(col,col,col));
        }
    }
    ui->label_3->setPixmap(QPixmap::fromImage(img));
    ui->label_3->show();
}

void MainWindow::on_pushButton_clicked()
{
    int randa=qrand()%10000;
    int randb=qrand()%10000;
    a=map(randa,0,10000,-1,1);
    b=map(randb,0,10000,-1,1);
    ui->lineEdit->setText(QString::number(a));
    ui->lineEdit_2->setText(QString::number(b));
    update();
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    double i= arg1.toDouble();
    a=i;
    //update();
}

void MainWindow::on_lineEdit_2_textChanged(const QString &arg1)
{
    double i= arg1.toDouble();
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
    ui->label->hide();
    ui->label_2->hide();
    ui->lineEdit->hide();
    ui->lineEdit_2->hide();
    ui->pushButton->hide();
    ui->pushButton_3->hide();
    ui->horizontalSlider->hide();
    ui->verticalSlider->hide();
    update();
}

void MainWindow::on_radioButton_2_clicked()
{
    a=-0.4;
    b=0.6;
    ui->label->show();
    ui->label_2->show();
    ui->lineEdit->show();
    ui->lineEdit_2->show();
    ui->pushButton->show();
    ui->pushButton_3->show();
    ui->horizontalSlider->show();
    ui->verticalSlider->show();
    update();
}

void MainWindow::on_pushButton_3_clicked()
{
    update();
}
