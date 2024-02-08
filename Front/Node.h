//
// Created by Данил Подлягин on 08.02.2024.
//
#pragma once
#include "header.h"

class Node: public QGraphicsItem {
public:
    Node();
    Node(int x, int y, double radius, Neurons cur): x_(x), y_(y), radius_(radius), cur_(cur) {}

protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
    QRectF boundingRect() const override;

private:
    double radius_;
    int x_, y_;
    Neurons cur_;
};

