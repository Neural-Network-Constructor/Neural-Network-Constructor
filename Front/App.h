#include "header.h"
#include "Node.h"
#pragma once

class App : public QMainWindow {
    Q_OBJECT

public:
    App(int width, int height);
    ~App() override;

    void render() {
        window_->show();
    }

private slots:
    void loadFromFile();
    void gotoBegin();
    void gotoEditor();
    void gotoSimulator();

    void createInNeuron();
    void createFNNNeuron();
    void createOutNeuron();

    void drawInNeuron();
    void drawFNNNeuron();
    void drawOutNeuron();

private:
    std::vector<Node*> nodes_;
    QWidget* window_;
    QLabel* base_line_;
    QPushButton* begin_button_;
    QPushButton* editor_button_;
    QPushButton* simulation_button_;


    QLabel* begin_;
    QPushButton* load_button_;
    QPushButton* create_button_;

    QLabel* editor_;
    QPushButton* in_neuron_;
    QPushButton* fnn_neuron_;
    QPushButton* out_neuron_;
    QGraphicsView* edit_tablet_;
    QGraphicsScene* edit_scene_;
    QPainter* painter_;

    QWidget* creating_tablet_;
    QLineEdit* x_coord_;
    QLineEdit* y_coord_;
    QPushButton* neuron_painter_;


    QLabel* simulation_;
    QLabel* pokapohui2_;


    QTabBar* tabbar_;
    QLabel* logtext_;
    QTabWidget* maintab_;
};