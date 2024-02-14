#include "App.h"

App::App(int width, int height)
{
    base_font_ = QFont("Rockwell", 20);
    window_ = new QMainWindow();
    window_->setFixedSize(width, height);
    window_->setStyleSheet("QMainWindow {"
                           "background: #000000 }");
    window_->setFont(base_font_);

    base_line_ = new QLabel(window_);
    base_line_->resize(2, 600);
    base_line_->move(220, 0);
    base_line_->setStyleSheet("QLabel { background: #404040;"
                              "border-radius:2px;"
                              "}");

    begin_button_ = new QPushButton(window_);
    begin_button_->move(10, 30);
    begin_button_->resize(200, 60);
    begin_button_->setStyleSheet("QPushButton { color: #ffffff;"
                                 "background: #404040;"
                                 "border-radius: 5px; }");
    begin_button_->setFont(base_font_);
    begin_button_->setText("НАЧАЛО");
    connect(begin_button_, SIGNAL(released()), this, SLOT(gotoBegin()));

    editor_button_ = new QPushButton(window_);
    editor_button_->move(10, 100);
    editor_button_->resize(200, 60);
    editor_button_->setStyleSheet("QPushButton { color: #ffffff;"
                                  "background: #404040;"
                                  "border-radius: 5px; }");
    editor_button_->setFont(base_font_);
    editor_button_->setText("РЕДАКТОР");
    connect(editor_button_, SIGNAL(released()), this, SLOT(gotoEditor()));

    simulation_button_ = new QPushButton(window_);
    simulation_button_->move(10, 170);
    simulation_button_->resize(200, 60);
    simulation_button_->setStyleSheet("QPushButton { color: #ffffff;"
                                  "background: #404040;"
                                  "border-radius: 5px; }");
    simulation_button_->setFont(base_font_);
    simulation_button_->setText("СИМУЛЯЦИЯ");
    connect(simulation_button_, SIGNAL(released()), this, SLOT(gotoSimulator()));

    // РАБОТА С НАЧАЛЬНОЙ СТРАНИЦЕЙ

    logo_font_ = QFont("Rockwell", 50);

    begin_ = new QLabel(window_);
    begin_->move(225, 10);
    begin_->resize(760, 570);
    begin_->setStyleSheet("QLabel {"
                          "background: #000000 }");

    create_button_ = new QPushButton(begin_);
    create_button_->move(30, 55);
    create_button_->resize(200, 60);
    create_button_->setStyleSheet("QPushButton { color: #ffffff;"
                                  "background: #404040;"
                                  "border-radius: 5px; }");
    create_button_->setFont(QFont("Rockwell", 25));
    create_button_->setText("СОЗДАТЬ");
    connect(create_button_, SIGNAL(released()), this, SLOT(clearEditScene()));

    logtext_ = new QLabel(begin_);
    logtext_->resize(460, 460);
    logtext_->move(250, 20);
    QPixmap logo_;
    logo_.load("../src/front/img/logo.jpg");
    logtext_->setPixmap(logo_);

    name_text_ = new QLabel(begin_);
    name_text_->resize(760, 100);
    name_text_->move(30, 470);
    name_text_->setFont(logo_font_);
    name_text_->setText("Neural Network Constructor");
    name_text_->setStyleSheet("QLabel {"
                              "background: #000000; "
                              "}");


    // РАБОТА СО СТРАНИЦЕЙ РЕДАКЦИИ
    neuro_font_ = QFont("Rockwell", 20);

    editor_ = new QLabel(window_);
    editor_->move(225, 10);
    editor_->resize(760, 570);
    editor_->setStyleSheet("QLabel {"
                           "background: #404040 }");

    in_neuron_ = new QPushButton(editor_);
    in_neuron_->resize(60, 60);
    in_neuron_->move(30, 10);
    in_neuron_->setStyleSheet("QPushButton {background: #60dc65;"
                              "border-radius: 30px;"
                              "color: #ffffff;}");
    in_neuron_->setText("IN");
    in_neuron_->setFont(neuro_font_);
    connect(in_neuron_, SIGNAL(released()), this, SLOT(drawInNeuron()));

    FCL_neuron_ = new QPushButton(editor_);
    FCL_neuron_->resize(60, 60);
    FCL_neuron_->move(30, 80);
    FCL_neuron_->setStyleSheet("QPushButton {background: #4bdfda;"
                               "border-radius: 30px;"
                               "color: #ffffff }");
    FCL_neuron_->setFont(neuro_font_);
    FCL_neuron_->setText("FCL");
    connect(FCL_neuron_, SIGNAL(released()), this, SLOT(drawFCLNeuron()));

    out_neuron_ = new QPushButton(editor_);
    out_neuron_->resize(60, 60);
    out_neuron_->move(30, 150);
    out_neuron_->setStyleSheet("QPushButton {background: #e93f3f;"
                               "border-radius: 30px; }");
    out_neuron_->setFont(neuro_font_);
    out_neuron_->setText("OUT");
    connect(out_neuron_, SIGNAL(released()), this, SLOT(drawOutNeuron()));

    set_neuron_count_btn_ = new QPushButton(editor_);
    set_neuron_count_btn_->resize(110, 40);
    set_neuron_count_btn_->move(5, 230);
    set_neuron_count_btn_->setStyleSheet("QPushButton {background: #505050;"
                                      "}");
    set_neuron_count_btn_->setFont(QFont("Rockwell", 15));
    set_neuron_count_btn_->setText("НЕЙРОНЫ");
    connect(set_neuron_count_btn_, SIGNAL(released()), this, SLOT(setCount()));

    neurons_counter_settings = new QMainWindow;
    neurons_counter_settings->resize(200, 100);

    neurons_counter_tablet_ = new QLineEdit(neurons_counter_settings);
    neurons_counter_tablet_->resize(180, 30);
    neurons_counter_tablet_->move(10, 10);
    neurons_counter_tablet_->setPlaceholderText("Количество нейронов");

    go_from_neurons_settings = new QPushButton(neurons_counter_settings);
    go_from_neurons_settings->resize(85, 40);
    go_from_neurons_settings->move(10, 50);
    go_from_neurons_settings->setFont(QFont("Rockwell", 10));
    go_from_neurons_settings->setText("ОТМЕНИТЬ");

    save_neurons_settings = new QPushButton(neurons_counter_settings);
    save_neurons_settings->resize(85, 40);
    save_neurons_settings->move(105, 50);
    save_neurons_settings->setFont(QFont("Rockwell", 10));
    save_neurons_settings->setText("СОХРАНИТЬ");
    connect(save_neurons_settings, SIGNAL(released()), this, SLOT(setupNeurons()));


    delete_neuron_btn_ = new QPushButton(editor_);
    delete_neuron_btn_->resize(110, 40);
    delete_neuron_btn_->move(5, 280);
    delete_neuron_btn_->setStyleSheet("QPushButton {background: #505050;"
                                      "}");
    delete_neuron_btn_->setFont(QFont("Rockwell", 15));
    delete_neuron_btn_->setText("УДАЛИТЬ");
    delete_neuron_btn_->setEnabled(false);
    connect(delete_neuron_btn_, SIGNAL(released()), this, SLOT(deleteNeuron()));

    add_edge_btn_ = new QPushButton(editor_);
    add_edge_btn_->resize(110, 40);
    add_edge_btn_->move(5, 330);
    add_edge_btn_->setStyleSheet("QPushButton {background: #505050;"
                                      "}");
    add_edge_btn_->setFont(QFont("Rockwell", 12));
    add_edge_btn_->setText("СОЗДАТЬ РЕБРО");
    connect(add_edge_btn_, SIGNAL(released()), this, SLOT(connectNodes()));


    edit_tablet_ = new GraphWidget(editor_);
    edit_tablet_->resize(650, 570);
    edit_tablet_->move(120, 0);
    edit_tablet_->setStyleSheet("QGraphicsView {"
                                "background: #d5d5d5; }");

    connect(edit_tablet_, SIGNAL(mousePressedSignal(QMouseEvent *)), this, SLOT(graphWidgetClicked(QMouseEvent *)));

    edit_scene_ = new QGraphicsScene();
    edit_scene_->setBackgroundBrush(QColor(64, 64, 64));
    edit_tablet_->setScene(edit_scene_);

    func_text = new QLabel(editor_);
    func_text->resize(110, 40);
    func_text->move(5, 370);
    func_text->setFont(QFont("Rockwell", 15));
    func_text->setText("ФУНКЦИИ");

    relu_func_btn_ = new QPushButton(editor_);
    relu_func_btn_->resize(90, 30);
    relu_func_btn_->move(25, 410);
    relu_func_btn_->setStyleSheet("QPushButton {"
                                 "background: #505050; }");
    relu_func_btn_->setFont(QFont("Rockwell", 15));
    relu_func_btn_->setText("ReLu");
    connect(relu_func_btn_, SIGNAL(released()), this, SLOT(setupReLuFunc()));


    sigmoid_func_btn_ = new QPushButton(editor_);
    sigmoid_func_btn_->resize(90, 30);
    sigmoid_func_btn_->move(25, 445);
    sigmoid_func_btn_->setStyleSheet("QPushButton {"
                                  "background: #505050; }");
    sigmoid_func_btn_->setFont(QFont("Rockwell", 15));
    sigmoid_func_btn_->setText("Sigmoid");
    connect(sigmoid_func_btn_, SIGNAL(released()), this, SLOT(setupSigmoidFunc()));

    hiptan_func_btn_ = new QPushButton(editor_);
    hiptan_func_btn_->resize(90, 30);
    hiptan_func_btn_->move(25, 480);
    hiptan_func_btn_->setStyleSheet("QPushButton {"
                                     "background: #505050; }");
    hiptan_func_btn_->setFont(QFont("Rockwell", 15));
    hiptan_func_btn_->setText("Tanh");
    connect(hiptan_func_btn_, SIGNAL(released()), this, SLOT(setupHiptanFunc()));

    settings_btn_ = new QPushButton(editor_);
    settings_btn_->resize(110, 40);
    settings_btn_->move(5, 525);
    settings_btn_->setStyleSheet("QPushButton {"
                                         "background: #505050; }");
    settings_btn_->setFont(QFont("Rockwell", 15));
    settings_btn_->setText("НАСТРОЙКИ");
    connect(settings_btn_, SIGNAL(released()), this, SLOT(chooseSettings()));//

    settings_window_ = new QMainWindow();
    settings_window_->resize(220, 180);

    epoch_count_tablet_ = new QLineEdit(settings_window_);
    epoch_count_tablet_->resize(200, 30);
    epoch_count_tablet_->move(10, 10);
    epoch_count_tablet_->setPlaceholderText("Количество эпох");

    learn_rate_count_tablet_ = new QLineEdit(settings_window_);
    learn_rate_count_tablet_->resize(200, 30);
    learn_rate_count_tablet_->move(10, 50);
    learn_rate_count_tablet_->setPlaceholderText("Скорость обучения");

    test_data_btn_ = new QPushButton(settings_window_);
    test_data_btn_->resize(200, 30);
    test_data_btn_->move(10, 80);
    test_data_btn_->setText("Тестовые данные");
    connect(test_data_btn_, SIGNAL(released()), this, SLOT(loadTestData()));

    train_data_btn_ = new QPushButton(settings_window_);
    train_data_btn_->resize(200, 30);
    train_data_btn_->move(10, 110);
    train_data_btn_->setText("Тренировочные данные");
    connect(train_data_btn_, SIGNAL(released()), this, SLOT(loadTrainData()));

    save_settings_btn_ = new QPushButton(settings_window_);
    save_settings_btn_->resize(95, 30);
    save_settings_btn_->move(115, 140);
    save_settings_btn_->setFont(QFont("Rockwell", 12));
    save_settings_btn_->setText("СОХРАНИТЬ");
    connect(save_settings_btn_, SIGNAL(released()), this, SLOT(saveSettings()));

    go_from_settings_btn_ = new QPushButton(settings_window_);
    go_from_settings_btn_->resize(95, 30);
    go_from_settings_btn_->move(10, 140);
    go_from_settings_btn_->setFont(QFont("Rockwell", 12));
    go_from_settings_btn_->setText("ОТМЕНИТЬ");
    connect(go_from_settings_btn_, SIGNAL(released()), this, SLOT(closeSettings()));

    start_simulating_btn_ = new QPushButton(editor_);
    start_simulating_btn_->resize(200, 80);
    start_simulating_btn_->move(560, 500);
    start_simulating_btn_->setStyleSheet("QPushButton {"
                                "background: #202020; }");
    start_simulating_btn_->setFont(QFont("Rockwell", 25));
    start_simulating_btn_->setText("ЗАПУСК");
    connect(start_simulating_btn_, SIGNAL(released()), this, SLOT(start_simulating()));

    // РАБОТА СО СТРАНИЦЕЙ СИМУЛЯЦИИ

    simulation_ = new QLabel(window_);
    simulation_->move(225, 10);
    simulation_->resize(120, 570);
    simulation_->setStyleSheet("QLabel {"
                               "background: #404040 }");
    simulation_->setFont(neuro_font_);

    epoch_count_ = new QLabel(simulation_);
    sim_font_ = QFont("Rockwell", 25);
    epoch_count_->setFont(sim_font_);
    epoch_count_->resize(120, 80);
    epoch_count_->move(1, 10);
    epoch_count_->setText("F");

    epochs_counter_back_ = new QPushButton(simulation_);
    epochs_counter_back_->setFont(QFont("Rockwell", 12));
    epochs_counter_back_->setText("<");
    epochs_counter_back_->resize(30, 30);
    epochs_counter_back_->move(1, 100);
    epochs_counter_back_->setStyleSheet("QPushButton { color: #ffffff;"
                                      "background: #505050;"
                                      "border-radius: 5px; }");

    connect(epochs_counter_back_, SIGNAL(released()), this, SLOT(minusEpochCounter()));

    choose_epoch_counter_ = new QPushButton(simulation_);
    choose_epoch_counter_->setFont(QFont("Rockwell", 12));
    choose_epoch_counter_->setText("эпоха");
    choose_epoch_counter_->resize(50, 30);
    choose_epoch_counter_->move(35, 100);
    choose_epoch_counter_->setStyleSheet("QPushButton { color: #ffffff;"
                                        "background: #505050;"
                                        "border-radius: 5px; }");
    connect(choose_epoch_counter_, SIGNAL(released()), this, SLOT(changeCounterTablet()));

    epochs_counter_up_ = new QPushButton(simulation_);
    epochs_counter_up_->setFont(QFont("Rockwell", 12));
    epochs_counter_up_->setText(">");
    epochs_counter_up_->resize(30, 30);
    epochs_counter_up_->move(89, 100);
    epochs_counter_up_->setStyleSheet("QPushButton { color: #ffffff;"
                                         "background: #505050;"
                                         "border-radius: 5px; }");
    connect(epochs_counter_up_, SIGNAL(released()), this, SLOT(plusEpochCounter()));


    epochs_counter_settings_ = new QMainWindow();
    epochs_counter_settings_->resize(150, 60);

    epochs_counter_tablet_ = new QLineEdit(epochs_counter_settings_);
    epochs_counter_tablet_->resize(130, 20);
    epochs_counter_tablet_->move(10, 5);
    epochs_counter_tablet_->setPlaceholderText("Количество эпох");

    save_epo_settings_btn_ = new QPushButton(epochs_counter_settings_);
    save_epo_settings_btn_->resize(100, 30);
    save_epo_settings_btn_->move(25, 30);
    save_epo_settings_btn_->setFont(QFont("Rockwell", 12));
    save_epo_settings_btn_->setText("СОХРАНИТЬ");
    connect(save_epo_settings_btn_, SIGNAL(released()), this, SLOT(saveEpoSettings()));

    gotoBegin();
}

App::~App()
{
    delete window_;
}

void App::getUpdate() {
    window_->update();
    edit_scene_->update();
    edit_tablet_->update();
    editor_->update();
    editor_button_->update();
    for (auto e : nodes_) {
        e->update();
    }
}


void App::gotoBegin()
{
    begin_button_->setStyleSheet("QPushButton { color: #ffffff;"
                                 "background: #202020;"
                                 "border-radius: 5px; }");
    editor_button_->setStyleSheet("QPushButton { color: #ffffff;"
                                  "background: #404040;"
                                  "border-radius: 5px; }");
    simulation_button_->setStyleSheet("QPushButton { color: #ffffff;"
                                      "background: #404040;"
                                      "border-radius: 5px; }");

    begin_->show();
    editor_->hide();
    simulation_->hide();
}

void App::gotoEditor()
{
    for (int i = -10000; i <= 10000; i += 25)
    {
        edit_scene_->addLine(i, -10000, i, 10000);
    }
    for (int i = -10000; i <= 10000; i += 25)
    {
        edit_scene_->addLine(-10000, i, 10000, i);
    }
    if (!nodes_.empty()) {
        for (auto e : nodes_) {
            e->setFlag(QGraphicsItem::ItemIsMovable, true);
        }
    }
    begin_button_->setStyleSheet("QPushButton { color: #ffffff;"
                                 "background: #404040;"
                                 "border-radius: 5px; }");
    editor_button_->setStyleSheet("QPushButton { color: #ffffff;"
                                  "background: #202020;"
                                  "border-radius: 5px; }");
    simulation_button_->setStyleSheet("QPushButton { color: #ffffff;"
                                      "background: #404040;"
                                      "border-radius: 5px; }");
    begin_->hide();
    editor_->show();
    simulation_->hide();
    start_simulating_btn_->show();
}

void App::gotoSimulator()
{
    if (epochs_ != -1) {
        begin_button_->setStyleSheet("QPushButton { color: #ffffff;"
                                     "background: #404040;"
                                     "border-radius: 5px; }");
        editor_button_->setStyleSheet("QPushButton { color: #ffffff;"
                                      "background: #404040;"
                                      "border-radius: 5px; }");
        simulation_button_->setStyleSheet("QPushButton { color: #ffffff;"
                                          "background: #202020;"
                                          "border-radius: 5px; }");
        begin_->hide();
        editor_->show();
        simulation_->show();
        start_simulating_btn_->hide();
    }
}

void App::drawInNeuron()
{
    in_neuron_->setStyleSheet("QPushButton {background: #606060;"
                              "border-radius: 30px;"
                              "color: #ffffff;}");
    in_neuron_->setEnabled(false);
    nodes_.push_back(new Node(Neurons::In));
    edit_scene_->addItem(nodes_.back());
    root_ = nodes_.back();
}

void App::drawFCLNeuron()
{
    nodes_.push_back(new Node(Neurons::FCL));
    edit_scene_->addItem(nodes_.back());
}

void App::drawOutNeuron()
{
    out_neuron_->setStyleSheet("QPushButton {background: #606060;"
                              "border-radius: 30px;"
                              "color: #ffffff;}");
    out_neuron_->setEnabled(false);
    nodes_.push_back(new Node(Neurons::Out));
    edit_scene_->addItem(nodes_.back());
    leaf_ = nodes_.back();
}

void App::deleteNeuron() {
    if (!edit_scene_->selectedItems().empty()) {
        node = dynamic_cast<Node*>(edit_scene_->selectedItems().takeFirst());
        if (node->getType() == Neurons::In) {
            in_neuron_->setStyleSheet("QPushButton {background: #60dc65;"
                                      "border-radius: 30px;"
                                      "color: #ffffff;}");
            in_neuron_->setEnabled(true);
        } else if (node->getType() == Neurons::Out) {
            out_neuron_->setStyleSheet("QPushButton {background: #e93f3f;"
                                       "border-radius: 30px;"
                                       "color: #ffffff;}");
            out_neuron_->setEnabled(true);
        }
        if (node == last_ || node == leaf_) {
            is_exist_edge_to_leaf_ = false;
        }
        graph_[node].first.clear();
        graph_[node].second = true;
        nodes_.erase(std::find(nodes_.begin(), nodes_.end(),node));
        delete edit_scene_->selectedItems().takeFirst();
        delete_neuron_btn_->setEnabled(false);
    }
}

void App::graphWidgetClicked(QMouseEvent *event)
{
    auto selectedItems = edit_scene_->selectedItems();
    if (!simulation_->isHidden()) {
        if (selectedItems.size() == 0) {
            return;
        } else if (edit_tablet_->itemAt(event->pos())) {
            // Если нажатие произошло над элементом сцены.
            Node *node = dynamic_cast<Node *>(selectedItems.at(0));
            if (node) { // Если выделена вершина.
                // работа с бэком и получение информации от него
                auto it = node;
            }
        }
    }
    else {
        if (selectedItems.size() == 0) {
            // Если выделенных элементов нет.
            delete_neuron_btn_->setEnabled(false);
            return;
        } else if (edit_tablet_->itemAt(event->pos())) {
            // Если нажатие произошло над элементом сцены.
            delete_neuron_btn_->setEnabled(true);
            Node *node = dynamic_cast<Node *>(selectedItems.at(0));
            if (node) { // Если выделена вершина.
                if (connProcess == CONN::NEED_SOURCE) {
                    // Отмечаем источник.
                    node->setMark(true);
                    connProcess = CONN::NEED_DEST;
                } else if (connProcess == CONN::NEED_DEST) {
                    // Находим вершину назначения.
                    Node * nSourse = nullptr;
                            foreach (auto it, edit_scene_->items()) {
                            Node *nTemp = dynamic_cast<Node *>(it);
                            if (nTemp && nTemp->mark()) {
                                nSourse = nTemp;
                                break;
                            }
                        }
                    if (nSourse) {
                        // Если нашлась выделенная вершина.
                        if (nSourse->getType() ==  Neurons::Out ||
                            node->getType() == Neurons::In ||
                            (node->getType() == Neurons::Out && is_exist_edge_to_leaf_) ||
                            nSourse->getType() == Neurons::In && node->getType() == Neurons::Out) {

                        } else {
                            Edge *e = new Edge(nSourse, node);
                            edit_scene_->addItem(e);
                            graph_[nSourse].first.push_back(node);
                            graph_[nSourse].second = false;
                            if (node == leaf_ && !is_exist_edge_to_leaf_)
                                last_ = nSourse;
                            is_exist_edge_to_leaf_ = is_exist_edge_to_leaf_ || (node == leaf_);
                        }
                        nSourse->setMark(false);
                        connProcess = CONN::NONE;
                    } else {
                        qDebug() << "Error connProcess value";
                    }
                }
            }
        }
    }
}

void App::connectNodes()
{
    if(edit_scene_->selectedItems().size() == 0) {
        connProcess = CONN::NEED_SOURCE;
    } else if (edit_scene_->selectedItems().size() == 1
               && (node = dynamic_cast<Node *>
    (edit_scene_->selectedItems().at(0)))) {
        node->setMark(true);
        edit_scene_->clearSelection();
        connProcess = CONN::NEED_DEST;
    }

}

void App::setupReLuFunc() {
    if(edit_scene_->selectedItems().size() == 0) {
        return;
    } else if (edit_scene_->selectedItems().size() == 1
               && (node = dynamic_cast<Node *> (edit_scene_->selectedItems().at(0)))) {
        if (node->getType() == Neurons::FCL) {
            node->setFunc(ActivationFunc::ReLu);
        }
        node->update();
    }
}

void App::setupSigmoidFunc() {
    if(edit_scene_->selectedItems().size() == 0) {
        return;
    } else if (edit_scene_->selectedItems().size() == 1
               && (node = dynamic_cast<Node *> (edit_scene_->selectedItems().at(0)))) {
        if (node->getType() == Neurons::FCL) {
            node->setFunc(ActivationFunc::Sigmoid);
        }
        node->update();
    }
}

void App::setupHiptanFunc() {
    if(edit_scene_->selectedItems().size() == 0) {
        return;
    } else if (edit_scene_->selectedItems().size() == 1
               && (node = dynamic_cast<Node *> (edit_scene_->selectedItems().at(0)))) {
        if (node->getType() == Neurons::FCL) {
            node->setFunc(ActivationFunc::Hiptan);
        }
        node->update();
    }
}

void App::chooseSettings() {
    settings_window_->show();
}

void App::loadTestData() {
    QString file = QFileDialog::getOpenFileName(nullptr, "Выберите csv файл", "", "*.csv");
    test_data = file.toStdString();
}

void App::loadTrainData() {
    QString file = QFileDialog::getOpenFileName(nullptr, "Выберите csv файл", "", "*.csv");
    train_data = file.toStdString();
}

void App::closeSettings() {
    settings_window_->hide();
}

void App::saveSettings() {
    epochs_ = epoch_count_tablet_->text().toInt();
    learning_rate = learn_rate_count_tablet_->text().toDouble();
    start_simulating_btn_->setStyleSheet("QPushButton {"
                                         "background: #505050 }");
    //магия с *.csv файл
    settings_window_->hide();
}

void App::start_simulating() {
    if (!out_neuron_->isEnabled() && !in_neuron_->isEnabled() && epochs_ > 0 && is_exist_edge_to_leaf_ && learning_rate > 0) {
        std::string string_epochs_ = "эпоха\n1/\n"+std::to_string(epochs_);
        epoch_count_->setText(QString::fromStdString(string_epochs_));
        cur_epochs = 1;
        for (auto e : nodes_) {
            e->setMark(false);
            e->setFlag(QGraphicsItem::ItemIsMovable, false);
            e->setSelected(false);
        }
        for (auto e : graph_) {
            if (!e.second.second) {
                for (auto elem : e.second.first) {
                    vgraph_[(void*)e.first].first.push_back((void*)elem);
                }
                if (e.first == last_) {
                    vgraph_[(void*)e.first].second = true;
                }
            }
        }
        for (auto e : graph_) {
            if (!e.second.second) {
                if (e.first->getType() == Neurons::FCL) {
                    if (e.first->getFunc() == ActivationFunc::ReLu) {
                        activations[(void*)e.first] = 1;
                    } else if (e.first->getFunc() == ActivationFunc::Sigmoid) {
                        activations[(void*)e.first] = 2;
                    } else {
                        activations[(void*)e.first] = 3;
                    }
                }
                values_nums[(void*)e.first] = e.first->getNeuronsCount();
                is_input[(void*)e.first] = (e.first->getType() == Neurons::In);
            }
        }
        // вот тут создам ебанину
        gotoSimulator();
    }
}

void App::dfs(Node* u) {
    if (graph_[u].second)
        return;
    for (int i = 0; i < 1e9; ++i) {}
    used_[u] = 1;
    if (u->getType() == Neurons::In) {
        std::cout << "In ";
    } else if (u->getType() == Neurons::FCL) {
        std::cout << "FCL ";
    } else {
        std::cout << "Out ";
    }
    for (auto e : graph_[u].first) {
        if (!used_[e]) {
            dfs(e);
            for (int i = 0; i < 1e9; ++i) {}
        }
    }
}
void App::minusEpochCounter() {
    changeEpochCounter(-1);
}

void App::changeCounterTablet() {
    epochs_counter_settings_->show();
}

void App::plusEpochCounter() {
    changeEpochCounter(1);
}

void App::changeEpochCounter(int n) {
    cur_epochs = std::max(cur_epochs + n, 1);
    if (cur_epochs > epochs_)
        cur_epochs = epochs_;
    std::string string_epochs_ = "эпоха\n" + std::to_string(cur_epochs) + "/\n"+std::to_string(epochs_);
    epoch_count_->setText(QString::fromStdString(string_epochs_));
    epoch_count_->update();
    simulation_->update();
}

void App::saveEpoSettings() {
    cur_epochs = epochs_counter_tablet_->text().toInt();
    cur_epochs = std::max(cur_epochs, 1);
    if (cur_epochs > epochs_)
        cur_epochs = epochs_;
    changeEpochCounter(0);
    epochs_counter_settings_->hide();
}

void App::clearEditScene() {
    gotoEditor();
}

void App::setCount() {
    neurons_counter_settings->show();
}

void App::goFromNeuronsSettings() {
    neurons_counter_tablet_->clear();
    neurons_counter_settings->hide();
}

void App::setupNeurons() {
    if(edit_scene_->selectedItems().size() == 0) {
        return;
    } else if (edit_scene_->selectedItems().size() == 1
               && (node = dynamic_cast<Node *> (edit_scene_->selectedItems().at(0)))) {
        node->setNeuronsCount(neurons_counter_tablet_->text().toInt());
        neurons_counter_tablet_->clear();
        node->update();
    }
    neurons_counter_settings->hide();
}
