#include <QApplication>
// 主窗口类，用于向其中添加工具篮和小部件
#include <QtWidgets/QMainWindow>

// 包含用于显示图表的窗口小部件的头文件
#include <QtCharts/QChartView>
// 包含用于绘制条形图的头文件
#include <QtCharts/QBarSeries>
// 包含表示条形图中一个数据集的头文件
#include <QtCharts/QBarSet>
// 包含用于显示图例的头文件
#include <QtCharts/QLegend>
// 包含用于在图表轴上添加类别的头文件
#include <QtCharts/QBarCategoryAxis>
// 包含用于创建水平堆叠条形图的头文件
#include <QtCharts/QHorizontalStackedBarSeries>
// 包含用于创建折线图的头文件
#include <QtCharts/QLineSeries>
// 包含用于修改图表轴上名称的头文件
#include <QtCharts/QCategoryAxis>
// 包含用于创建饼图的头文件
#include <QtCharts/QPieSeries>
// 包含用于表示饼图中一个部分的头文件
#include <QtCharts/QPieSlice>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 设置4个数据集
    QBarSet *set0 = new QBarSet("Ziying Cheng");
    QBarSet *set1 = new QBarSet("Haoyu Kang");
    QBarSet *set2 = new QBarSet("Zehao Li");
    QBarSet *set3 = new QBarSet("Weijie Cai");

    // 每个数据集中有六个数据集，对应着六年内的次数
    *set0 << 30 << 10 << 20 << 720 << 720 << 1000;
    *set1 << 250 << 315 << 282 << 307 << 303 << 330;
    *set2 << 294 << 246 << 257 << 319 << 300 << 325;
    *set3 << 248 << 244 << 265 << 281 << 278 << 313;

    // 创建柱状图对象
    QBarSeries *series = new QBarSeries();
    // 将数据集与各自的柱状图进行绑定
    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->append(set3);

    // 创建图表对象
    QChart *chart = new QChart();

    // 将柱状图添加到图表中
    chart->addSeries(series);
    chart->setTitle("年均开导次数");// 设置图标标题
    chart->setAnimationOptions(QChart::AllAnimations);// 使能图表动画
    QStringList categories; // 创建刻度标签类别
    categories << "2013" << "2014" << "2015" << "2016" << "2017" << "2018"; // 添加刻度标签

    QBarCategoryAxis *axis = new QBarCategoryAxis(); //创建柱状图标签（刻度）轴对象
    axis->append(categories);// 绑定轴和类别
    chart->createDefaultAxes(); //创建默认的坐标轴

    chart->setAxisX(axis, series);// 将横坐标轴与柱状系列关联，
    // series是次数
    // cate是年份

    // 设置图示可见和图示位置
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    // 创建图标显示对象
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);// 设定渲染为抗锯齿

    QPalette pal = qApp->palette(); // 获取调色盘，给对象调色

    // 设置窗口的颜色和文字颜色
    pal.setColor(QPalette::Window, QRgb(0xffffff));
    pal.setColor(QPalette::WindowText, QRgb(0x404044));

    qApp->setPalette(pal);// 应用程序按照调色盘的配置设置颜色；

    QMainWindow window;

    // 设置窗口位置与尺寸
    window.setCentralWidget(chartView);
    window.resize(420, 300);
    window.show();
    return a.exec();
}
