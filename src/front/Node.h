#pragma once

#include "header.h"
#include "Edge.h"

class GraphWidget;
class QGraphicsSceneMouseEvent;

class Node : public QGraphicsItem
{
    friend Edge::Edge(Node *sourceNode, Node *destNode);
    friend Edge::~Edge();
public:
    Node(Neurons type); // конструктор
    ~Node() override; // деструктор
    QList<Edge *> edges() const; // массив рёбер

    enum { Type = UserType + 1 };
    int type() const override { return Type; }
    const Neurons getType() const {return _type; }
    static const int RADIUS = 30; // базовый радиус
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, // рисование вершины
               QWidget *widget) override;

    bool mark() const; // проверка на выделенность
    void addEdge(Edge *edge); // добавление ребра
    void setMark(bool mark); // установка выделенности

protected:
    QVariant itemChange(GraphicsItemChange change, // смена фокуса на вершине
                        const QVariant &value) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override; // нажатие клавиши мыши
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override; // удержание клавиши мыши
    void removeEdge(Edge *edge); // удаление ребра
private:
    QList<Edge *> edgeList; // массив ребёр, связанных с ним
    bool _mark; // метка выделенности
    Neurons _type; // тип нейрона
};



