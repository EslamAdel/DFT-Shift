#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QImage>
#include <QLabel>
extern "C"
{
#include "imgtest.h"
}
double XshiftValue = 0;
double YshiftValue = 0;

void updateShiftedImage(int x, int y);

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->horizontalSlider->setMinimum(-124);
    ui->horizontalSlider_2->setMinimum(-124);
    ui->horizontalSlider->setMaximum(124);
    ui->horizontalSlider_2->setMaximum(124);
    QImage image(500, 500, QImage::Format_Indexed8);
    image.setColorCount(2);
    image.setColor(0, qRgb(0, 0, 0));
    image.setColor(1, qRgb(255, 255, 255));
    image.fill(0);
    //for(int i=0;i<100;i++)
    int z, w;
    for (z = 0; z < 500; z++)
    {
        for (w = 0; w < 500; w++)
        {
            if (z >= 125 && z <= 374 && w >= 125 && w <= 374)
                image.setPixel(z, w, 1);
        }
    }

    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label_2->setPixmap(QPixmap::fromImage(image));
    ui->label_5->setText(tr("Click to Get the shift value\n"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    ui->label_5->setText(tr("Shift Value in X : %1\nShift Value in Y :%2\n ")
                             .arg(XshiftValue)
                             .arg(YshiftValue));
}

void MainWindow::on_horizontalSlider_sliderReleased()
{
    //change the shift value in x
    XshiftValue = mainCode(ui->horizontalSlider->sliderPosition(), 0);
    //reset the Y slider and Yshiftvalue
    ui->horizontalSlider_2->setSliderPosition(0);
    YshiftValue = 0;
    //update the shifted image label
    this->updateShiftedImage(ui->horizontalSlider->sliderPosition(), 0);
}

void MainWindow::on_horizontalSlider_2_sliderReleased()
{
    //change the shift value in y
    YshiftValue = mainCode(0, ui->horizontalSlider_2->sliderPosition());
    //reset the slider in x and XshiftValue
    ui->horizontalSlider->setSliderPosition(0);
    XshiftValue = 0;
    //update the shifted image label
    this->updateShiftedImage(0, -ui->horizontalSlider_2->sliderPosition());
}

void MainWindow::updateShiftedImage(int x, int y)
{
    QImage image(500, 500, QImage::Format_Indexed8);
    image.setColorCount(2);
    image.setColor(0, qRgb(0, 0, 0));
    image.setColor(1, qRgb(255, 255, 255));
    int z, w;
    image.fill(0);
    for (z = 0; z < 500; z++)
    {
        for (w = 0; w < 500; w++)
        {
            if (z >= (125 + x) && z <= (374 + x) && w >= (125 + y) && w <= (374 + y))
                image.setPixel(z, w, 1);
        }
    }
    ui->label_2->setPixmap(QPixmap::fromImage(image));
}
