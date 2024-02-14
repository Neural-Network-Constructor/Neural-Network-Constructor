#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>

class Node;

class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    GraphWidget(QWidget *parent = nullptr); // конструктор

    //    void itemMoved();

public slots:
    void shuffle(); // рандомный разброс рёбер
    void zoomIn();  // приближение
    void zoomOut(); // отдаление

protected:
    void keyPressEvent(QKeyEvent *event) override; // нажатие кнопки
#if QT_CONFIG(wheelevent)
    void wheelEvent(QWheelEvent *event) override; // скроллинг колёсика мыши
#endif
    void mousePressEvent(QMouseEvent *event) override; // нажатие кнопки мыши
    void scaleView(qreal scaleFactor);                 // изменение масштаба
signals:
    void mousePressedSignal(QMouseEvent *event);
};

#endif