#include "Edge.h"
#include "Node.h"
#include "graphwidget.h"

#include "header.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>

Node::Node(Neurons type) : _type(type)
{
    setFlag(ItemIsSelectable);
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(1);
}

Node::~Node()
{
    while (!edgeList.isEmpty())
        delete edgeList.takeFirst();
}

void Node::addEdge(Edge *edge)
{
    edgeList << edge;
    edge->adjust();
}

void Node::removeEdge(Edge *edge)
{
    edgeList.removeOne(edge);
}

bool Node::mark() const
{
    return _mark;
}

void Node::setMark(bool mark)
{
    _mark = mark;
    update();
}

QList<Edge *> Node::edges() const
{
    return edgeList;
}

QRectF Node::boundingRect() const
{
    return shape().boundingRect();
}

QPainterPath Node::shape() const
{
    QPainterPath path;
    path.addEllipse(-RADIUS, -RADIUS, 2 * RADIUS, 2 * RADIUS);
    return path;
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    std::string text1 = "", text2 = "";
    if (this->_type == Neurons::FCL) {
        if (this->_func == ActivationFunc::ReLu) {
            text1 = "ReLu";
            text2 = std::to_string(this->neurons_count_);
        } else if (this->_func == ActivationFunc::Sigmoid) {
            text1 = "Sigmoid";
            text2 = std::to_string(this->neurons_count_);
        } else {
            text1 = "Tanh";
            text2 = std::to_string(this->neurons_count_);
        }
    } else if (this->_type == Neurons::In) {
        text1= "IN";
        text2 = std::to_string(this->neurons_count_);
    } else {
        text1 = "OUT";
    }
    if (this->_type == Neurons::In) {
        painter->setBrush((option->state & QStyle::State_Selected ? QColor(188,240,190) : QColor(96, 220, 101)));
    }
    else if (this->_type == Neurons::FCL) {
        painter->setBrush((option->state & QStyle::State_Selected ? QColor(168, 248, 245) : QColor(75, 223, 218)));
    }
    else if (this->_type == Neurons::Out) {
        painter->setBrush((option->state & QStyle::State_Selected ? QColor(247,182,182) : QColor(233, 63, 63)));
    }
    if (is_in_dfs_) {
        painter->setBrush(QColor(244, 32, 249));
    }
    painter->setPen(QPen(_mark ? Qt::white : Qt::black, 2));
    painter->drawEllipse(-RADIUS, -RADIUS, 2 * RADIUS, 2 * RADIUS);
    painter->drawText(-24,  -4, QString::fromStdString(text1));
    painter->drawText(-24, 14, QString::fromStdString(text2));
}



QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
        case ItemPositionHasChanged:
                    foreach (Edge *edge, edgeList)
                    edge->adjust();
            break;
        default:
            break;
    };

    return QGraphicsItem::itemChange(change, value);
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mousePressEvent(event);
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

void Node::setIsInDfs(bool check) {
    is_in_dfs_ = check;
    update();
}

void Node::setSimulateMod() {

}

void Node::setFunc(ActivationFunc func) {
    this->_func = func;
}
ActivationFunc Node::getFunc() {
    return this->_func;
}

void Node::setNeuronsCount(int n) {
    this->neurons_count_ = n;
}

int Node::getNeuronsCount() {
    return this->neurons_count_;
}
