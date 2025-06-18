#include "Charts.h"

void BarChart::createChart(QList<DataStorage> list, bool isBWEnabled) {
    QChart* chart = getChart();
    QBarSeries *series = new QBarSeries(chart);
    int length = list.count();

    chart->setTitle("BarChart");

    for (int i = 0; i < length; i++) {
        QBarSet* set = new QBarSet(list.at(i).key);
        * set << list.at(i).value;

        if (isBWEnabled) {
            int bw = (rand() % 255 + rand() % 255 + rand() % 255) / 3;
            set->setBrush(QColor(bw, bw, bw));
        }
        series->append(set);
    }
    chart->removeAllSeries();

    chart->addSeries(series);
    chart->createDefaultAxes();
}

void PieChart::createChart(QList<DataStorage> list, bool isBWEnabled) {
    QChart* chart = getChart();
    QPieSeries * series = new QPieSeries(chart);
    int length = list.count();

    chart->setTitle("PieChart");

    for (int i = 0; i < length; i++) {
        QPieSlice* slice = series->append(list.at(i).key, list.at(i).value);

        if (isBWEnabled) {
            int bw = (rand() % 255 + rand() % 255 + rand() % 255) / 3;
            slice->setBrush(QColor(bw, bw, bw));
        }
    }
    chart->removeAllSeries();

    chart->addSeries(series);
}
