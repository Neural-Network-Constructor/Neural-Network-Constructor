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
    Node(int type);
    ~Node() override;
    QList<Edge *> edges() const;

    enum { Type = UserType + 1 };
    int type() const override { return Type; }
    static const int RADIUS = 30;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    bool mark() const;
    void addEdge(Edge *edge);
    void setMark(bool mark);

protected:
    QVariant itemChange(GraphicsItemChange change,
                        const QVariant &value) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void removeEdge(Edge *edge);
private:
    QList<Edge *> edgeList;
    bool _mark;
    int _type;
};



