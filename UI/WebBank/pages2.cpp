#include "wdelegate.h"
#include "pages.h"
#include "wmsgbox.h"
#include "wuimanip.h"
#include <QHeaderView>
#include <QListWidget>
#include <QToolButton>
#include <QTime>
#include <QDebug>
#include <QCryptographicHash>
#include <QFileDialog>
#include <QDir>
#include <QAxObject>
#include <QLinearGradient>
#include "qcustomplot.h"

PlotPage::PlotPage(QWidget *parent) : WPage(parent)
{
    //components new
    mainTitle->setText(tr("Account Statistics"));
    returnBtn = new QPushButton(tr("Return"), this);
    histogramPlot = new QCustomPlot(this);
    piePlot = new QCustomPlot(this);

    //set object name
    returnBtn->setObjectName("CHPReturn");

    //set position and size
    mainTitle->setGeometry(QRect(24, 6, 708, 60));
    histogramPlot->setGeometry(QRect(24, 72, 500, 400));
    piePlot->setGeometry(QRect(570, 72, 140, 400));
    returnBtn->setGeometry(QRect(600, 500, 96, 36));

    initPlot();

    //set connections
    connect(returnBtn, SIGNAL(clicked(bool)), parent->parent(), SLOT(showMyAccountPage()));
}

void PlotPage::initPlot()
{
    QVector<QString> histogramLabels(4);
    QVector<double> histogramValues(4);
    double sum = 0;

    int accountNum = WUIManip::getAccountNum();
    for (int i = 0; i < accountNum; ++i)
    {
        QVector<QString> recordInfo = WUIManip::getAccountRecord(i);

        for (int i = 0; i < recordInfo.size() / 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                QString info = recordInfo[3 * i + 2];
                if (info == "Water" || info == "Gas" || info == "Electricity")
                {
                    histogramValues[3] += recordInfo[3 * i].toFloat();
                }
                else if (info == "Transfer to Others")
                {
                    histogramValues[0] += recordInfo[3 * i].toFloat();
                }
                else if (info == "Transfer to Current")
                {
                    histogramValues[1] += recordInfo[3 * i].toFloat();
                }
                else if (info == "Transfer to Fixed")
                {
                    histogramValues[2] += recordInfo[3 * i].toFloat();
                }
            }
        }
    }
    for (int i = 0; i < 4; ++i)
    {
        sum += histogramValues[i];
    }

    histogramLabels[0] = tr("To Others");
    histogramLabels[1] = tr("To Current");
    histogramLabels[2] = tr("To Fixed");
    histogramLabels[3] = tr("Payment");

    bars = new QCPBars(histogramPlot->xAxis, histogramPlot->yAxis);
    QVector<double> index(4);
    for (int i = 0; i < 4; ++i)
    {
        index[i] = i;
    }
    bars->setData(index, histogramValues);

    histogramPlot->xAxis->setAutoTicks(false);
    histogramPlot->xAxis->setAutoTickLabels(false);
    histogramPlot->xAxis->setAutoTickStep(false);

    histogramPlot->addPlottable(bars);
    histogramPlot->rescaleAxes();

    for (int i = 0; i < 4; ++i)
    {
        coor.append(i * 1.0);
    }

    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor("#EEE"));
    plotGradient.setColorAt(1, QColor("#EEE"));
    histogramPlot->setBackground(plotGradient);

    QPen pen;
    pen.setWidthF(2);
    pen.setColor(QColor(3, 155, 229, 154));
    bars->setPen(pen);
    bars->setBrush(QBrush(QColor(3, 155, 229, 154)));

    histogramPlot->xAxis->setSubTickCount(0);
    histogramPlot->xAxis->setTickLength(0, 4);
    histogramPlot->xAxis->grid()->setVisible(false);
    histogramPlot->xAxis->setRange(-1, 4);
    histogramPlot->yAxis->grid()->setSubGridVisible(false);
    histogramPlot->xAxis->setTickVector(coor);
    histogramPlot->xAxis->setTickVectorLabels(histogramLabels);

    histogramPlot->replot();

    //Plot Pie Graph
    QVector<QString> pieLabel(1);
    pieLabel[0] = tr("Percentage");

    for (int i = 0; i < 4; i++)
    {
        QCPBars *pieBar = new QCPBars(piePlot->xAxis, piePlot->yAxis);
        piePlotBars.append(pieBar);
        piePlot->addPlottable(piePlotBars[i]);
    }

    piePlotBars[0]->setName(tr("To Others"));
    piePlotBars[1]->setName(tr("To Current"));
    piePlotBars[2]->setName(tr("To Fixed"));
    piePlotBars[3]->setName(tr("Payment"));

    piePlot->setBackground(plotGradient);
    piePlotBars[0]->setPen(pen);
    piePlotBars[0]->setBrush(QBrush(QColor(3, 155, 229, 222)));
    piePlotBars[1]->setPen(pen);
    piePlotBars[1]->setBrush(QBrush(QColor(79, 195, 247, 222)));
    piePlotBars[2]->setPen(pen);
    piePlotBars[2]->setBrush(QBrush(QColor(2, 136, 209, 222)));
    piePlotBars[3]->setPen(pen);
    piePlotBars[3]->setBrush(QBrush(QColor(1, 87, 155, 222)));

    piePlotBars[2]->moveAbove(piePlotBars[3]);
    piePlotBars[1]->moveAbove(piePlotBars[2]);
    piePlotBars[0]->moveAbove(piePlotBars[1]);

    piePlot->xAxis->setAutoTicks(false);
    piePlot->xAxis->setAutoTickLabels(false);
    piePlot->xAxis->setSubTickCount(0);
    piePlot->xAxis->setTickLength(0, 4);
    piePlot->xAxis->grid()->setVisible(false);
    piePlot->xAxis->setRange(-2, 2);
    piePlot->yAxis->grid()->setSubGridVisible(false);

    QVector<double> pieKeys;
    QVector<double> pieValue1;
    QVector<double> pieValue2;
    QVector<double> pieValue3;
    QVector<double> pieValue4;
    pieValue1 << histogramValues[0] / sum;
    pieValue2 << histogramValues[1] / sum;
    pieValue3 << histogramValues[2] / sum;
    pieValue4 << histogramValues[3] / sum;

    pieKeys << 0.0;
    piePlot->xAxis->setTickVector(pieKeys);
    piePlot->xAxis->setTickVectorLabels(pieLabel);
    piePlot->yAxis->setVisible(false);

    piePlotBars[0]->setData(pieKeys, pieValue1);
    piePlotBars[1]->setData(pieKeys, pieValue2);
    piePlotBars[2]->setData(pieKeys, pieValue3);
    piePlotBars[3]->setData(pieKeys, pieValue4);
    piePlot->rescaleAxes();

    piePlot->replot();
}

void PlotPage::setPlot()
{
    QVector<double> histogramValues(4);
    double sum = 0;

    int accountNum = WUIManip::getAccountNum();
    for (int i = 0; i < accountNum; ++i)
    {
        QVector<QString> recordInfo = WUIManip::getAccountRecord(i);

        for (int i = 0; i < recordInfo.size() / 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                QString info = recordInfo[3 * i + 2];
                if (info == "Water" || info == "Gas" || info == "Electricity")
                {
                    histogramValues[3] += recordInfo[3 * i].toFloat();
                }
                else if (info == "Transfer to Others")
                {
                    histogramValues[0] += recordInfo[3 * i].toFloat();
                }
                else if (info == "Transfer to Current")
                {
                    histogramValues[1] += recordInfo[3 * i].toFloat();
                }
                else if (info == "Transfer to Fixed")
                {
                    histogramValues[2] += recordInfo[3 * i].toFloat();
                }
            }
        }
    }
    for (int i = 0; i < 4; ++i)
    {
        sum += histogramValues[i];
    }

    delete bars;
    bars = new QCPBars(histogramPlot->xAxis, histogramPlot->yAxis);
    QVector<double> index(4);
    for (int i = 0; i < 4; ++i)
    {
        index[i] = i;
    }
    bars->setData(index, histogramValues);

    QPen pen;
    pen.setWidthF(2);
    pen.setColor(QColor(3, 155, 229, 154));
    bars->setPen(pen);
    bars->setBrush(QBrush(QColor(3, 155, 229, 154)));

    histogramPlot->xAxis->setSubTickCount(0);
    histogramPlot->xAxis->setTickLength(0, 4);
    histogramPlot->xAxis->grid()->setVisible(false);
    histogramPlot->xAxis->setRange(-1, 4);
    histogramPlot->xAxis->setTickVector(coor);
    histogramPlot->yAxis->grid()->setSubGridVisible(false);

    histogramPlot->rescaleAxes();
    histogramPlot->replot();

    QVector<double> pieValue1;
    QVector<double> pieValue2;
    QVector<double> pieValue3;
    QVector<double> pieValue4;
    pieValue1 << histogramValues[0] / sum;
    pieValue2 << histogramValues[1] / sum;
    pieValue3 << histogramValues[2] / sum;
    pieValue4 << histogramValues[3] / sum;

    piePlot->yAxis->setVisible(false);

    QVector<double> pieKeys;
    pieKeys << 0.0;
    piePlotBars[0]->setData(pieKeys, pieValue1);
    piePlotBars[1]->setData(pieKeys, pieValue2);
    piePlotBars[2]->setData(pieKeys, pieValue3);
    piePlotBars[3]->setData(pieKeys, pieValue4);
    piePlot->rescaleAxes();

    piePlot->replot();
}

void PlotPage::updateLanguage()
{
    //update language in this page
    mainTitle->setText(tr("Account Statistics"));
    returnBtn->setText(tr("Return"));
    //    setPlot();
}

CurrencyPage::CurrencyPage(QWidget *parent) : WPage(parent)
{
    //components new
    mainTitle->setText(tr("Currency Information"));
    label1 = new QLabel(tr("CNY to USD"), this);
    label2 = new QLabel(tr("CNY to EUR"), this);
    label3 = new QLabel(tr("CNY to KRW"), this);
    label4 = new QLabel(tr("CNY to JPY"), this);
    edit1 = new QLineEdit(this);
    edit2 = new QLineEdit(this);
    edit3 = new QLineEdit(this);
    edit4 = new QLineEdit(this);

    //set object name
    label1->setObjectName("CCPLabel1");
    label2->setObjectName("CCPLabel2");
    label3->setObjectName("CCPLabel3");
    label4->setObjectName("CCPLabel4");
    edit1->setObjectName("CCPEdit1");
    edit2->setObjectName("CCPEdit2");
    edit3->setObjectName("CCPEdit3");
    edit4->setObjectName("CCPEdit4");

    edit1->setEnabled(false);
    edit2->setEnabled(false);
    edit3->setEnabled(false);
    edit4->setEnabled(false);

    //set position and size
    mainTitle->setGeometry(QRect(24, 6, 708, 60));
    label1->setGeometry(QRect(24, 92, 200, 24));
    label2->setGeometry(QRect(24, 140, 200, 24));
    label3->setGeometry(QRect(24, 188, 200, 24));
    label4->setGeometry(QRect(24, 236, 200, 24));
    edit1->setGeometry(QRect(288, 88, 400, 32));
    edit2->setGeometry(QRect(288, 136, 400, 32));
    edit3->setGeometry(QRect(288, 184, 400, 32));
    edit4->setGeometry(QRect(288, 232, 400, 32));
}

void CurrencyPage::setCurrency()
{
    edit1->setText("");
    edit2->setText("");
    edit3->setText("");
    edit4->setText("");
    QString *currency = WUIManip::getCurrency();
    edit1->setText(currency[0]);
    edit2->setText(currency[1]);
    edit3->setText(currency[2]);
    edit4->setText(currency[3]);
    WMsgBox::information(tr("Currency Information Acquired!"));
}

void CurrencyPage::updateLanguage()
{

}
