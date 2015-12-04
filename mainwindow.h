#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void updateShiftedImage(int x,int y);

private slots:
    void on_pushButton_clicked();

    void on_horizontalSlider_2_sliderReleased();

    void on_horizontalSlider_sliderReleased();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
