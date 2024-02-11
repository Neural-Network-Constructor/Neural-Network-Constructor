#include "App.h"
#include "widget.h"

App::App(int width, int height)
{
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
    begin_button_->setText("НАЧАЛО");
    connect(begin_button_, SIGNAL(released()), this, SLOT(gotoBegin()));

    editor_button_ = new QPushButton(window_);
    editor_button_->move(10, 100);
    editor_button_->resize(200, 60);
    editor_button_->setStyleSheet("QPushButton { color: #ffffff;"
                                  "background: #404040;"
                                  "border-radius: 5px; }");
    editor_button_->setText("РЕДАКТОР");
    connect(editor_button_, SIGNAL(released()), this, SLOT(gotoEditor()));

    simulation_button_ = new QPushButton(window_);
    simulation_button_->move(10, 170);
    simulation_button_->resize(200, 60);
    simulation_button_->setStyleSheet("QPushButton { color: #ffffff;"
                                  "background: #404040;"
                                  "border-radius: 5px; }");
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
    create_button_->move(10, 30);
    create_button_->resize(200, 60);
    create_button_->setStyleSheet("QPushButton { color: #ffffff;"
                                  "background: #404040;"
                                  "border-radius: 5px; }");
    create_button_->setText("СОЗДАТЬ");
    connect(create_button_, SIGNAL(released()), this, SLOT(gotoEditor()));

    load_button_ = new QPushButton(begin_);
    load_button_->move(10, 110);
    load_button_->resize(200, 60);
    load_button_->setStyleSheet("QPushButton { color: #ffffff;"
                                "background: #404040;"
                                "border-radius: 5px; }");

    load_button_->setText("ОТКРЫТЬ");
    connect(load_button_, SIGNAL(released()), this, SLOT(loadNNCFromFile()));

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
    neuro_font_ = QFont("Rockwell", 30);

    editor_ = new QLabel(window_);
    editor_->move(225, 10);
    editor_->resize(760, 570);
    editor_->setStyleSheet("QLabel {"
                           "background: #404040 }");

    in_neuron_ = new QPushButton(editor_);
    in_neuron_->resize(100, 100);
    in_neuron_->move(10, 10);
    in_neuron_->setStyleSheet("QPushButton {background: #60dc65;"
                              "border-radius: 50px;"
                              "color: #ffffff;}");
    in_neuron_->setText("IN");
    in_neuron_->setFont(neuro_font_);
    connect(in_neuron_, SIGNAL(released()), this, SLOT(drawInNeuron()));

    FCL_neuron_ = new QPushButton(editor_);
    FCL_neuron_->resize(100, 100);
    FCL_neuron_->move(10, 120);
    FCL_neuron_->setStyleSheet("QPushButton {background: #4bdfda;"
                               "border-radius: 50px;"
                               "color: #ffffff }");
    FCL_neuron_->setFont(neuro_font_);
    FCL_neuron_->setText("FCL");
    connect(FCL_neuron_, SIGNAL(released()), this, SLOT(drawFCLNeuron()));

    out_neuron_ = new QPushButton(editor_);
    out_neuron_->resize(100, 100);
    out_neuron_->move(10, 230);
    out_neuron_->setStyleSheet("QPushButton {background: #e93f3f;"
                               "border-radius: 50px; }");
    out_neuron_->setFont(neuro_font_);
    out_neuron_->setText("OUT");
    connect(out_neuron_, SIGNAL(released()), this, SLOT(drawOutNeuron()));

    delete_neuron_btn_ = new QPushButton(editor_);
    delete_neuron_btn_->resize(110, 40);
    delete_neuron_btn_->move(5, 340);
    delete_neuron_btn_->setStyleSheet("QPushButton {background: #505050;"
                                      "}");
    delete_neuron_btn_->setText("УДАЛИТЬ");
    delete_neuron_btn_->setEnabled(false);
    connect(delete_neuron_btn_, SIGNAL(released()), this, SLOT(deleteNeuron()));

    add_edge_btn_ = new QPushButton(editor_);
    add_edge_btn_->resize(110, 40);
    add_edge_btn_->move(5, 390);
    add_edge_btn_->setStyleSheet("QPushButton {background: #505050;"
                                      "}");
    add_edge_btn_->setText("СОЗДАТЬ РЕБРО");
    connect(add_edge_btn_, SIGNAL(released()), this, SLOT(connectNodes()));
//    connect(edit_tablet_, &GraphWidget::mousePressedSignal, this, &App::graphWidgetClicked);


    edit_tablet_ = new GraphWidget(editor_);
    edit_tablet_->resize(650, 570);
    edit_tablet_->move(120, 0);
    edit_tablet_->setStyleSheet("QGraphicsView {"
                                "background: #d5d5d5; }");

    connect(edit_tablet_, SIGNAL(mousePressedSignal(QMouseEvent *)), this, SLOT(graphWidgetClicked(QMouseEvent *)));

    edit_scene_ = new QGraphicsScene();
    edit_scene_->setBackgroundBrush(QColor(64, 64, 64));
    edit_tablet_->setScene(edit_scene_);
    for (int i = -10000; i <= 10000; i += 25)
    {
        edit_scene_->addLine(i, -10000, i, 10000);
    }
    for (int i = -10000; i <= 10000; i += 25)
    {
        edit_scene_->addLine(-10000, i, 10000, i);
    }

    settings_btn_ = new QPushButton(editor_);
    settings_btn_->resize(110, 40);
    settings_btn_->move(5, 440);
    settings_btn_->setStyleSheet("QPushButton {"
                                         "background: #505050; }");
    settings_btn_->setText("НАСТРОЙКИ");
    connect(settings_btn_, SIGNAL(released()), this, SLOT(chooseSettings()));//

    settings_window_ = new QMainWindow();
    settings_window_->resize(220, 120);

    epoch_count_tablet_ = new QLineEdit(settings_window_);
    epoch_count_tablet_->resize(200, 30);
    epoch_count_tablet_->move(10, 10);
    epoch_count_tablet_->setPlaceholderText("Количество эпох");

    csv_file_btn_ = new QPushButton(settings_window_);
    csv_file_btn_->resize(200, 30);
    csv_file_btn_->move(10, 50);
    csv_file_btn_->setText("Выберите *.csv файл");
    connect(csv_file_btn_, SIGNAL(released()), this, SLOT(loadCSVFromFile()));

    save_settings_btn_ = new QPushButton(settings_window_);
    save_settings_btn_->resize(95, 30);
    save_settings_btn_->move(115, 80);
    save_settings_btn_->setText("СОХРАНИТЬ");
    connect(save_settings_btn_, SIGNAL(released()), this, SLOT(closeSettings()));

    go_from_settings_btn_ = new QPushButton(settings_window_);
    go_from_settings_btn_->resize(95, 30);
    go_from_settings_btn_->move(10, 80);
    go_from_settings_btn_->setText("ОТМЕНИТЬ");
    connect(go_from_settings_btn_, SIGNAL(released()), this, SLOT(closeSettings()));



    start_simulating_btn_ = new QPushButton(editor_);
    start_simulating_btn_->resize(110, 40);
    start_simulating_btn_->move(5, 490);
    start_simulating_btn_->setStyleSheet("QPushButton {"
                                "background: #505050; }");
    start_simulating_btn_->setText("ЗАПУСК");
    connect(start_simulating_btn_, SIGNAL(released()), this, SLOT(start_simulating()));

    // РАБОТА СО СТРАНИЦЕЙ СИМУЛЯЦИИ

    simulation_ = new QLabel(window_);
    simulation_->move(225, 10);
    simulation_->resize(120, 570);
    simulation_->setStyleSheet("QLabel {"
                               "background: #404040 }");


    gotoBegin();
}

App::~App()
{
    delete window_;
}

void App::loadNNCFromFile()
{
    QString file = QFileDialog::getOpenFileName(nullptr, "Выберите nnc файл", "", "*.nnc");
    QFile in(file);
    if (!in.open(QIODevice::ReadOnly))
        return;
    QString data = in.readLine();
    in.close();
    if (data.isEmpty())
        return;
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
}

void App::gotoSimulator()
{
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
}

void App::drawInNeuron()
{
    in_neuron_->setStyleSheet("QPushButton {background: #606060;"
                              "border-radius: 50px;"
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
                              "border-radius: 50px;"
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
                                      "border-radius: 50px;"
                                      "color: #ffffff;}");
            in_neuron_->setEnabled(true);
        } else if (node->getType() == Neurons::Out) {
            out_neuron_->setStyleSheet("QPushButton {background: #e93f3f;"
                                       "border-radius: 50px;"
                                       "color: #ffffff;}");
            out_neuron_->setEnabled(true);
        }
        graph_[node].first.clear();
        graph_[node].second = false;
        delete edit_scene_->selectedItems().takeFirst();
        delete_neuron_btn_->setEnabled(false);
    }

}

void App::graphWidgetClicked(QMouseEvent *event)
{
    auto selectedItems = edit_scene_->selectedItems();
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
                        (node->getType() == Neurons::Out && is_exist_edge_to_leaf_)) {

                    } else {
                        Edge *e = new Edge(nSourse, node);
                        edit_scene_->addItem(e);
                        graph_[nSourse].first.push_back(node);
                        graph_[nSourse].second = true;
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

void App::chooseSettings() {
    settings_window_->show();
}

void App::loadCSVFromFile()
{
    QString file = QFileDialog::getOpenFileName(nullptr, "Выберите csv файл", "", "*.csv");
    QFile in(file);
    if (!in.open(QIODevice::ReadOnly))
        return;
    QString data = in.readLine();
    in.close();
    if (data.isEmpty())
        return;
}

void App::closeSettings() {
    settings_window_->hide();
}

void App::start_simulating() {
    std::cout << "In ";
    dfs(root_);
    used_.clear();

}

void App::dfs(Node* u) {
    used_[u] = 1;
    if (!graph_[u].second)
        return;
    for (auto e : graph_[u].first) {
        if (!used_[e]) {
            if (e->getType() == Neurons::In) {
                std::cout << "In ";
            } else if (e->getType() == Neurons::FCL) {
                std::cout << "FCL ";
            } else {
                std::cout << "Out ";
            }
            dfs(e);
        }
    }
}