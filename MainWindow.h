//
// Created by christian on 6/30/25.
//
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "ContactBook.h"
#include <QStandardItem>
#include <QMainWindow>
#include <QObject>

class MainWindow final : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void onAddClicked();
    void onRemoveClicked();
    void onExitClicked();

    void onSave();
    void onOpenFile();

private:
    Ui::MainWindow ui{};
    QStandardItemModel *model;
};

#endif // MAINWINDOW_H
