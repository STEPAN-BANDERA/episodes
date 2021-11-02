/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "chartview.h"
#include <QtGui/QMouseEvent>
#include <QtCharts>

ChartView::ChartView(QWidget *parent) :
    QChartView(parent),
    m_isTouching(false)
{
    setRubberBand(QChartView::RectangleRubberBand);
}

void ChartView::SetQchart(QChart *qchart)
{
    this->setChart(qchart);
}

bool ChartView::viewportEvent(QEvent *event)
{
    if (event->type() == QEvent::TouchBegin) {
        // By default touch events are converted to mouse events. So
        // after this event we will get a mouse event also but we want
        // to handle touch events as gestures only. So we need this safeguard
        // to block mouse events that are actually generated from touch.
        m_isTouching = true;

        // Turn off animations when handling gestures they
        // will only slow us down.
        chart()->setAnimationOptions(QChart::NoAnimation);
    }
    return QChartView::viewportEvent(event);
}

void ChartView::mousePressEvent(QMouseEvent *event)
{

//    auto const widgetPos = event->localPos();
//    auto const scenePos = mapToScene(QPoint(static_cast<int>(widgetPos.x()), static_cast<int>(widgetPos.y())));
//    auto const chartItemPos = chart()->mapFromScene(scenePos);
//    auto const valueGivenSeries = chart()->mapToValue(chartItemPos);
//    qDebug() << "widgetPos:" << widgetPos;
//    qDebug() << "scenePos:" << scenePos;
//    qDebug() << "chartItemPos:" << chartItemPos;
//    qDebug() << "valSeries:" << valueGivenSeries;


    if (m_isTouching)
        return;
    QChartView::mousePressEvent(event);
}

void ChartView::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isTouching)
        return;
    QChartView::mouseMoveEvent(event);
}

void ChartView::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_isTouching)
        m_isTouching = false;

    // Because we disabled animations when touch event was detected
    // we must put them back on.
    chart()->setAnimationOptions(QChart::SeriesAnimations);

    QChartView::mouseReleaseEvent(event);
}

auto ChartView::seriesRect(QChart *chart, QAbstractSeries *series) {
   auto inScene = chart->plotArea();
   auto inChart = chart->mapFromScene(inScene);
   auto inChartRect = inChart.boundingRect();
   auto inItem1 = chart->mapToValue(inChartRect.topLeft(), series);
   auto inItem2 = chart->mapToValue(inChartRect.bottomRight(), series);
   return QRectF(inItem1, inItem2).normalized();
}

auto ChartView::pointsInRect(QXYSeries *series, const QRectF &rect) {
   QVector<QPointF> result;
   auto const points = series->pointsVector();
   std::copy_if(points.begin(), points.end(), std::back_inserter(result),
                [rect](auto &p) { return rect.contains(p); });
   return result;
}

void ChartView::keyPressEvent(QKeyEvent *event)
{



    QAbstractSeries* series = this->chart()->series()[0];
    QLineSeries* lineSeries = qobject_cast<QLineSeries*>(series);

    auto rect = seriesRect(this->chart(), lineSeries);
    auto const points = pointsInRect(lineSeries, rect);
    foreach (auto var, points) {
        qDebug() << qSetRealNumberPrecision(16) << var.rx() << " " << var.ry();
    }
    qDebug() << points.size();

    if (event->key() == Qt::Key_Plus) {
            chart()->zoomIn();
        }


//    qDebug() << event->type();
//    auto b = chart()->series();
//    qDebug() << "b size" << b.size();
//    auto c = b[0];
//    auto d = dynamic_cast<QPieSeries*>(c);
//    auto a = d->slices(); //[0]->slices();
//    qDebug() << "a size" << a.size();
//    foreach (const auto &var, a) {
//       qDebug() << var;
//    }
//    //a[0]->chart();
//    if (event->key() == Qt::Key_Plus) {
//        chart()->zoomIn();
//       // auto a = chart->series();
//    }
//    else if (event->key() == Qt::Key_Minus) {
//        chart()->zoomOut();
//    }
////![1]
//    case Qt::Key_Left:
//        chart()->scroll(-10, 0);
//        break;
//    case Qt::Key_Right:
//        chart()->scroll(10, 0);
//        break;
//    case Qt::Key_Up:
//        chart()->scroll(0, 10);
//        break;
//    case Qt::Key_Down:
//        chart()->scroll(0, -10);
//        break;
//    else {
//        QGraphicsView::keyPressEvent(event);
//    }
}
