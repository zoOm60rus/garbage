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

private slots:
    void on_actionExit_triggered();
    QString ReadToFile(const QString &FilePath);

    void on_Enter_clicked();

    void on_actionOpen_file_triggered();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
