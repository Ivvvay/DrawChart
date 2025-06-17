#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QComboBox>
#include <QCheckBox>
#include <QLabel>
#include <QPushButton>
#include <QSplitter>
#include <QTableView>
#include <QFileDialog>
#include <QFileSystemModel>
#include <QtCharts/QChartView>
#include <QMessageBox>
#include <QPdfWriter>
#include "Charts.h"
#include "IOCContainer.h"


class MainWindow : public QWidget
{
    Q_OBJECT

private slots:
    void changeDirectory();
    void fileSelection(const QItemSelection &selected, const QItemSelection &deselected);
    void changeChartType();
    void printChart();
    void colorSwap();
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() {}

private:
    QString directoryPath;
    QString filePath;

    QFileSystemModel* fileModel;
    QTableView* tableFileView;

    QChartView* chartView;

    QLabel* pathLabel;

    QPushButton* btnPrintChart;
    QPushButton* btnChangeDirectory;

    QCheckBox* chkbxBlackWhiteChart;

    QComboBox* comboboxChartType;

    QHBoxLayout* wrapperLayout;
    QVBoxLayout* fileExplorerLayout;
    QVBoxLayout* chartLayout;
    QHBoxLayout* chartWidgetLayout;

    QSplitter* fileSplitter;
    QSplitter* chartSplitter;

    bool isChartActive = false;

    void exceptionCall(QString title, QString message);
    void drawChart();
};
#endif // MAINWINDOW_H
