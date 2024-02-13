#include "header.h"
#include "Node.h"
#include "graphwidget.h"
#pragma once

class App : public QMainWindow {
    Q_OBJECT

public:
    App(int width, int height); // конструктор
    ~App() override; // деструктор

    void render() { // создание окна программы
        window_->show();
    }

private slots:
    void loadNNCFromFile();// загрузка из файла
    void gotoBegin(); // возвращение к стартовому экрану
    void gotoEditor(); // возвращение к редактору
    void gotoSimulator(); // возвращение к симуляции
    void getUpdate();

    void drawInNeuron(); // рисование входного нейрона
    void drawFCLNeuron(); // рисование основного нейрона
    void drawOutNeuron(); // рисование выходного нейрона
    void deleteNeuron(); // удаление нейрона
    void graphWidgetClicked(QMouseEvent *event); // создание ребра
    void connectNodes();
    void chooseSettings();
    void loadCSVFromFile();
    void closeSettings();
    void saveSettings();
    void start_simulating();
    void dfs(Node* u);
    void minusEpochCounter();
    void plusEpochCounter();
    void changeCounterTablet();
    void changeEpochCounter(int n);
    void saveEpoSettings();
    void setupReLuFunc();
    void setupSigmoidFunc();
    void clearEditScene();
    void setupHiptanFunc();

private:
    std::map <Node*, std::pair<std::vector<Node*>, bool> > graph_;
    std::map <Node*, int> used_;
    Node* node, *root_, *leaf_, *last_;
    bool is_exist_edge_to_leaf_ = false;
    int connProcess;
    int epochs_ = -1, cur_epochs = 1;
    std::vector<Node*> nodes_;
    QFont base_font_;
    QWidget* window_;
    QLabel* base_line_;
    QFont logo_font_;
    QFont sim_font_;
    QPushButton* begin_button_;
    QPushButton* editor_button_;
    QPushButton* simulation_button_;


    QLabel* begin_;
    QPushButton* load_button_;
    QPushButton* create_button_;
    QLabel* name_text_;
    QFont neuro_font_;

    QLabel* editor_;
    QPushButton* in_neuron_;
    QPushButton* FCL_neuron_;
    QPushButton* out_neuron_;
    QPushButton* delete_neuron_btn_;
    QPushButton* add_edge_btn_;
    QLabel* func_text;
    QPushButton* relu_func_btn_;
    QPushButton* sigmoid_func_btn_;
    QPushButton* hiptan_func_btn_;
    QPushButton* settings_btn_;
    QWidget* settings_window_;
    QLineEdit* epoch_count_tablet_;
    QLabel* csv_file_text_;
    QPushButton* csv_file_btn_;
    QPushButton* save_settings_btn_;
    QPushButton* go_from_settings_btn_;

    QPushButton* start_simulating_btn_;

    GraphWidget* edit_tablet_;
    QGraphicsScene* edit_scene_;
    QPainter* painter_;

    QWidget* creating_tablet_;
    QLineEdit* x_coord_;
    QLineEdit* y_coord_;
    QPushButton* neuron_painter_;


    QLabel* simulation_;
    QLabel* epoch_count_;
    QPushButton* epochs_counter_back_;
    QPushButton* choose_epoch_counter_;
    QPushButton* epochs_counter_up_;
    QMainWindow* epochs_counter_settings_;
    QLineEdit* epochs_counter_tablet_;
    QPushButton* save_epo_settings_btn_;


    QTabBar* tabbar_;
    QLabel* logtext_;
    QTabWidget* maintab_;
};
