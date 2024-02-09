#include "App.h"
#include "widget.h"

App::App(int width, int height)
{

    window_ = new QMainWindow();
    window_->setFixedSize(width, height);
    window_->setStyleSheet("QMainWindow {"
                           "background: #000000 }");

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

    editor_button_ = new QPushButton(window_);
    editor_button_->move(10, 170);
    editor_button_->resize(200, 60);
    editor_button_->setStyleSheet("QPushButton { color: #ffffff;"
                                  "background: #404040;"
                                  "border-radius: 5px; }");
    editor_button_->setText("СИМУЛЯЦИЯ");
    connect(editor_button_, SIGNAL(released()), this, SLOT(gotoSimulator()));

    // РАБОТА С НАЧАЛЬНОЙ СТРАНИЦЕЙ

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
    connect(load_button_, SIGNAL(released()), this, SLOT(loadFromFile()));

    logtext_ = new QLabel(begin_);
    logtext_->resize(460, 460);
    logtext_->move(250, 6);
    QPixmap logo_;
    logo_.load("../src/front/img/logo.jpg");
    logtext_->setPixmap(logo_);

    // РАБОТА СО СТРАНИЦЕЙ РЕДАКЦИИ

    editor_ = new QLabel(window_);
    editor_->move(225, 10);
    editor_->resize(760, 570);
    editor_->setStyleSheet("QLabel {"
                           "background: #404040 }");

    in_neuron_ = new QPushButton(editor_);
    in_neuron_->resize(100, 100);
    in_neuron_->move(10, 10);
    in_neuron_->setStyleSheet("QPushButton {background: #60dc65;"
                              "border-radius: 50px; }");
    connect(in_neuron_, SIGNAL(released()), this, SLOT(drawInNeuron()));

    fcn_neuron_ = new QPushButton(editor_);
    fcn_neuron_->resize(100, 100);
    fcn_neuron_->move(10, 120);
    fcn_neuron_->setStyleSheet("QPushButton {background: #4bdfda;"
                               "border-radius: 50px; }");
    connect(fcn_neuron_, SIGNAL(released()), this, SLOT(drawFCNNeuron()));

    out_neuron_ = new QPushButton(editor_);
    out_neuron_->resize(100, 100);
    out_neuron_->move(10, 230);
    out_neuron_->setStyleSheet("QPushButton {background: #e93f3f;"
                               "border-radius: 50px; }");
    connect(out_neuron_, SIGNAL(released()), this, SLOT(drawOutNeuron()));

    delete_neuron_btn_ = new QPushButton(editor_);
    delete_neuron_btn_->resize(100, 40);
    delete_neuron_btn_->move(10, 340);
    delete_neuron_btn_->setStyleSheet("QPushButton {background: #505050;"
                                      "}");
    delete_neuron_btn_->setText("УДАЛИТЬ");
    connect(delete_neuron_btn_, SIGNAL(released()), this, SLOT(deleteNeuron()));

    add_edge_btn_ = new QPushButton(editor_);
    add_edge_btn_->resize(100, 40);
    add_edge_btn_->move(10, 450);
    add_edge_btn_->setStyleSheet("QPushButton {background: #505050;"
                                      "}");
    add_edge_btn_->setText("СОЗДАТЬ РЕБРО");
    connect(add_edge_btn_, SIGNAL(released()), this, SLOT((graphWidgetClicked)));

    edit_tablet_ = new GraphWidget(editor_);
    edit_tablet_->resize(650, 570);
    edit_tablet_->move(120, 0);
    edit_tablet_->setStyleSheet("QGraphicsView {"
                                "background: #d5d5d5; }");

    edit_scene_ = new QGraphicsScene();
    edit_scene_->setBackgroundBrush(QColor(64, 64, 64));
    edit_tablet_->setScene(edit_scene_);
    for (int i = -1000; i <= 1000; i += 25)
    {
        edit_scene_->addLine(i, -1000, i, 1000);
    }
    for (int i = -1000; i <= 1000; i += 25)
    {
        edit_scene_->addLine(-1000, i, 1000, i);
    }

    // РАБОТА СО СТРАНИЦЕЙ СИМУЛЯЦИИ

    simulation_ = new QLabel(window_);
    simulation_->move(225, 10);
    simulation_->resize(760, 570);
    simulation_->setStyleSheet("QLabel {"
                               "background: #c401c0 }");

    pokapohui2_ = new QLabel(simulation_);
    pokapohui2_->resize(300, 400);
    pokapohui2_->move(250, 70);
    pokapohui2_->setText("БЭКЕНДЕРЫ НЕ СДЕЛАЛИ, ЖДЁМС");

    // ОРГИЯ С ГЛАВНОЙ ЧАСТЬЮ ФРОНТА
    gotoBegin();
}

App::~App()
{
    delete base_line_;
    delete simulation_;
    delete editor_;
    delete begin_;
    delete load_button_;
    delete create_button_;
    delete window_;
    delete logtext_;
}

void App::loadFromFile()
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
    begin_->show();
    editor_->hide();
    simulation_->hide();
}

void App::gotoEditor()
{
    begin_->hide();
    editor_->show();
    simulation_->hide();
}

void App::gotoSimulator()
{
    begin_->hide();
    editor_->hide();
    simulation_->show();
}

void App::drawInNeuron()
{
    nodes_.push_back(new Node(0));
    edit_scene_->addItem(nodes_.back());
}

void App::drawFCNNeuron()
{
    nodes_.push_back(new Node(1));
    edit_scene_->addItem(nodes_.back());
}

void App::drawOutNeuron()
{
    nodes_.push_back(new Node(2));
    edit_scene_->addItem(nodes_.back());
}

void App::deleteNeuron() {
    if (!edit_scene_->selectedItems().empty())
        delete edit_scene_->selectedItems().takeFirst();
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
                    Edge *e = new Edge(nSourse, node);
                    edit_scene_->addItem(e);
                    nSourse->setMark(false);
                    connProcess = CONN::NONE;
                } else {
                    qDebug() << "Error connProcess value";
                }
            }
        }
    }
}
