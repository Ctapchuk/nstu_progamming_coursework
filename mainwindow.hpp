#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_listWidget_itemClicked(QListWidgetItem *item);
    void on_pushButton_add_clicked();
    void on_pushButton_delete_clicked();
    void on_pushButton_edit_clicked();
    void on_pushButton_loadTest_clicked();
    void on_pushButton_save_clicked();

private:
    Ui::MainWindow *ui;
    bool Is_SaveData();
    void LoadItemsFromDirectory();
    void LoadItemsFromTestDirectory();
    void UpdateItems();
    void closeEvent (QCloseEvent *event);
};
#endif // MAINWINDOW_HPP
