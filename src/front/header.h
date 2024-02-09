#pragma once

#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>
#include <set>

#include <QMainWindow>
#include <QApplication>
#include <QLineEdit>
#include <QPainter>
#include <QPushButton>
#include <QLabel>
#include <QFileDialog>
#include <QFont>
#include <QFontDatabase>
#include <QMdiArea>
#include <QTabBar>
#include <QGraphicsView>
#include <QBrush>
#include <QColor>
#include <QGraphicsItem>

enum class Neurons
{
    In,
    FNN,
    Out
};