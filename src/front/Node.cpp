#include "Node.h"

Node::Node() {

}


void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setPen(Qt::NoPen);
    if (cur_ == Neurons::In) {
        painter->setBrush(QColor(96, 220, 101));
    }
    else if (cur_ == Neurons::FCN) {
        painter->setBrush(QColor(75, 223, 218));
    }
    else {
        painter->setBrush(QColor(233, 63, 63));
    }
    painter->drawEllipse(int(x_ - radius_/2), int (y_ - radius_/2), int(radius_), int(radius_));
}


QRectF Node::boundingRect() const {
    return {x_ - radius_/2, y_ - radius_/2, radius_, radius_};
}
