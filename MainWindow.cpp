#include "MainWindow.h"

IOCContainer gContainer;
int IOCContainer::s_nextTypeId = 13830;

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    this->setGeometry(100, 100, 1000, 600);

    btnChangeDirectory = new QPushButton("Change Directory");
    btnPrintChart = new QPushButton("Print Chart");

    chkbxBlackWhiteChart = new QCheckBox("B/w Chart");

    comboboxChartType = new QComboBox();
    comboboxChartType->addItem("Bar");
    comboboxChartType->addItem("Pie");

    wrapperLayout = new QHBoxLayout(this);
    fileExplorerLayout = new QVBoxLayout();
    chartLayout = new QVBoxLayout();
    chartWidgetLayout = new QHBoxLayout();

    fileSplitter = new QSplitter();
    chartSplitter = new QSplitter();


    wrapperLayout->addLayout(fileExplorerLayout);
    wrapperLayout->addLayout(chartLayout);

    chartLayout->addLayout(chartWidgetLayout);

    fileExplorerLayout->addWidget(fileSplitter, 1);
    chartLayout->addWidget(chartSplitter);

    chartWidgetLayout->addWidget(comboboxChartType);
    chartWidgetLayout->addWidget(chkbxBlackWhiteChart);
    chartWidgetLayout->addWidget(btnPrintChart);


    fileModel = new QFileSystemModel(this);
    fileModel->setFilter(QDir::NoDotAndDotDot | QDir::AllEntries);

    directoryPath = QDir::currentPath();
    pathLabel = new QLabel();

    pathLabel->setText(directoryPath);
    QModelIndex pathIndex = fileModel->setRootPath(directoryPath);

    tableFileView = new QTableView();
    tableFileView->setModel(fileModel);
    tableFileView->setRootIndex(pathIndex);

    tableFileView->setSelectionMode(QAbstractItemView::SingleSelection);

    chartView = new QChartView();
    chartView->setRenderHint(QPainter::Antialiasing);

    fileSplitter->addWidget(tableFileView);
    chartSplitter->addWidget(chartView);
    fileExplorerLayout->addWidget(btnChangeDirectory, 0, Qt::AlignBottom);
    fileExplorerLayout->addWidget(pathLabel, 0, Qt::AlignBottom);

    connect(btnChangeDirectory, &QPushButton::clicked,
            this, &MainWindow::changeDirectory);

    connect(tableFileView->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &MainWindow::fileSelection);

    connect(comboboxChartType, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::changeChartType);

    connect(chkbxBlackWhiteChart, &QCheckBox::toggled,
            this, &MainWindow::colorSwap);

    connect(btnPrintChart, &QPushButton::clicked,
            this, &MainWindow::printChart);
}

void MainWindow::changeDirectory() {
    QFileDialog dialogWindow(this);
    dialogWindow.setFileMode(QFileDialog::Directory);

    if (dialogWindow.exec()) {
        directoryPath = dialogWindow.selectedFiles().first();
        pathLabel->setText(directoryPath);
    }
    tableFileView->setRootIndex(fileModel->setRootPath(directoryPath));
}

void MainWindow::fileSelection(const QItemSelection &selected, const QItemSelection &deselected) {
    Q_UNUSED(deselected);

    QModelIndexList indexes = selected.indexes();
    if (indexes.count() < 1) {
        exceptionCall("Selection Error", "No items has been Selected");
        return;
    }

    filePath = fileModel->filePath(indexes.first());

    if (filePath.endsWith(".json")) {
        gContainer.RegisterInstance<IDataLoader, JSONDataLoader>();
    } else if (filePath.endsWith(".sqlite")) {
        gContainer.RegisterInstance<IDataLoader, SQLDataLoader>();
    } else {
        exceptionCall("Wrong file format", "Please select .json or .sqlite file");
        if (isChartActive) {
            auto chart = gContainer.GetObject<IChart>();
            chart->getChart()->setTitle("");
            chart->clearChart();
            isChartActive = false;
        }
        return;
    }
    if (comboboxChartType->currentText() == "Pie") {
        gContainer.RegisterInstance<IChart, PieChart>();
        isChartActive = true;
    }
    else if (comboboxChartType->currentText() == "Bar") {
        gContainer.RegisterInstance<IChart, BarChart>();
        isChartActive = true;
    }
    if (isChartActive) {
        drawChart();
    }
}

void MainWindow::changeChartType() {
    if (comboboxChartType->currentText() == "Pie") {
        gContainer.RegisterInstance<IChart, PieChart>();
    } else if (comboboxChartType->currentText() == "Bar") {
        gContainer.RegisterInstance<IChart, BarChart>();
    } if (isChartActive) {
        drawChart();
    }
}

void MainWindow::colorSwap() {
    if (isChartActive) drawChart();
}

void MainWindow::printChart() {
    if(isChartActive){
        QString fileName = QFileDialog::getSaveFileName(this,
                                                        tr("Save the file as PDF"),
                                                        QDir::currentPath(),
                                                        tr("(PDF Files)*.pdf"));

        if (fileName.isEmpty()) {
            return;
        }

        QPdfWriter writer(fileName);
        writer.setPageSize(QPagedPaintDevice::A4);

        QPainter painter(&writer);
        chartView->render(&painter);
        painter.end();
    } else {
        exceptionCall("Pdf error", "No chart to print");
    }
}

void MainWindow::drawChart() {
    auto chart = gContainer.GetObject<IChart>();
    auto dataLoader = gContainer.GetObject<IDataLoader>();

    QList<DataStorage> items = dataLoader->loadData(filePath);
    chart->createChart(items, chkbxBlackWhiteChart->isChecked());

    chartView->setChart(chart->getChart());
}

void MainWindow::exceptionCall(QString title, QString message) {
    QMessageBox *messageBox = new QMessageBox();
    messageBox->setWindowTitle(title);
    messageBox->setText(message);
    messageBox->exec();
}

