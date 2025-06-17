#ifndef CHARTS_H
#define CHARTS_H

#include <QtCharts>
#include <QtCharts/QChart>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <DataLoader.h>

class IChart {
private:
    QChart* chart = new QChart();
public:
    virtual ~IChart() = default;
    QChart* getChart() { return chart; }
    void clearChart() { chart->removeAllSeries(); }
    virtual void createChart(QList<DataStorage>, bool isBWEnabled) = 0;
};

class BarChart: public IChart {
public:
    void createChart(QList<DataStorage>, bool isBWEnabled) override;
    ~BarChart() = default;
};

class PieChart: public IChart {
public:
    void createChart(QList<DataStorage>, bool isBWEnabled) override;
    ~PieChart() = default;
};
#endif // CHARTS_H
