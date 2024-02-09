#ifndef EDGE_H
#define EDGE_H

#include "header.h"
class Node;

class Edge : public QGraphicsItem
{
public:
    Edge(Node *sourceNode, Node *destNode); // конструктор
    ~Edge() override; // деструктор
    Node *sourceNode() const; // исходная вершина
    Node *destNode() const; // целевая вершина

    void adjust(); //

    enum { Type = UserType + 2 };
    int type() const override { return Type; }

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    Node *source, *dest;

    QPointF sourcePoint;
    QPointF destPoint;
    qreal arrowSize;
};

#endif // EDGE_H