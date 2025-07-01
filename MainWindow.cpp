//
// Created by christian on 6/30/25.
//

#include "MainWindow.h"
#include <QStandardItem>
#include <QInputDialog>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    ui.setupUi(this);

    model = new QStandardItemModel(this);
    model->setColumnCount(3);
    model->setHorizontalHeaderLabels({"Name", "Phone Number", "Email"});

    connect(ui.AddButton, &QPushButton::clicked, this, &MainWindow::onAddClicked);
    connect(ui.RemoveButton, &QPushButton::clicked, this, &MainWindow::onRemoveClicked);
    connect(ui.ExitButton, &QPushButton::clicked, this, &MainWindow::onExitClicked);
    connect(ui.AddButton, &QPushButton::clicked, this, &MainWindow::onAddClicked);
    connect(ui.RemoveButton, &QPushButton::clicked, this, &MainWindow::onRemoveClicked);
    connect(ui.ExitButton, &QPushButton::clicked, this, &MainWindow::onExitClicked);
    connect(ui.actionSave, &QAction::triggered, this, &MainWindow::onSave);
    connect(ui.actionOpen_File, &QAction::triggered, this, &MainWindow::onOpenFile);

}
void MainWindow::onAddClicked()
{
    bool ok;

    QString name = QInputDialog::getText(
        this,
        tr("Add Contact"),
        tr("Name:"),
        QLineEdit::Normal,
        QString(),
        &ok
    );
    if (!ok || name.trimmed().isEmpty()) {
        // User canceled or entered empty name
        return;
    }

    QString phone = QInputDialog::getText(
        this,
        tr("Add Contact"),
        tr("Phone Number:"),
        QLineEdit::Normal,
        QString(),
        &ok
    );
    QString email = QInputDialog::getText(
    this,
    tr("Add Contact"),
    tr("Email:"),
    QLineEdit::Normal,
    QString(),
    &ok
    );
    if (!ok) {
        // User canceled
        return;
    }

    QList<QStandardItem*> rowItems;
    rowItems << new QStandardItem(name)
             << new QStandardItem(phone)
             << new QStandardItem(email);

    model->appendRow(rowItems);

    ui.tableView->resizeColumnsToContents();
}

void MainWindow::onRemoveClicked()
{
    QModelIndexList selection = ui.tableView->selectionModel()->selectedRows();
    if (selection.isEmpty()) {
        QMessageBox::information(this, tr("Remove Contact"), tr("No row selected."));
        return;
    }
    std::ranges::sort(selection.begin(), selection.end(),
        [](const QModelIndex &a, const QModelIndex &b) {
            return a.row() > b.row();
        });
    for (const QModelIndex &row : selection) {
        model->removeRow(row.row());
    }
}

void MainWindow::onExitClicked()
{
    // Save data and exit
    onSave();
    close();
}
void MainWindow::onSave() {
    QString fileName = QFileDialog::getSaveFileName(this, "Save Contacts", "", tr("CSV Files (*.csv)"));
    if (fileName.isEmpty()) {
        return;
    }
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "Error", "Cannot open file for writing");
        return;
    }

    QTextStream out(&file);

    QStringList headers;
    for (int col = 0; col < model->columnCount(); ++col)
    {
        headers << model->headerData(col, Qt::Horizontal).toString();
    }
    out << headers.join(",") << "\n";

    // 2) Write each row
    for (int row = 0; row < model->rowCount(); ++row)
    {
        QStringList rowValues;
        for (int col = 0; col < model->columnCount(); ++col)
        {
            QString cell = model->item(row, col)->text();

            // Optional: escape quotes/commas
            cell.replace("\"", "\"\"");
            if (cell.contains(',') || cell.contains('"'))
                cell = "\"" + cell + "\"";

            rowValues << cell;
        }
        out << rowValues.join(",") << "\n";
    }

    file.close();
}

void MainWindow::onOpenFile() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open Contacts", "", "CSV Files (*.csv);;All Files (*)");
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "Error", "Cannot open file for reading");
        return;
    }

    QTextStream in(&file);

    QString headerLine = in.readLine();

    model->removeRows(0, model->rowCount()); // Clear existing data

    while (!in.atEnd())
    {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        QStringList fields = line.split(',');
        if (fields.size() >= 2)
        {
            QList<QStandardItem *> rowItems;
            rowItems << new QStandardItem(fields[0]) << new QStandardItem(fields[1]);
            model->appendRow(rowItems);
        }
    }

    file.close();
}
