#include "App.h"

App::App(int width, int height) {
    number_ = "";

    window_ = new QMainWindow();
    window_->setFixedSize(width, height);
    window_->setStyleSheet("QMainWindow {"
                           "background: #000000 }");

// РАБОТА С НАЧАЛЬНОЙ СТРАНИЦЕЙ

    begin_ = new QLabel(window_);
    begin_->setStyleSheet("QLabel {"
                          "background: #000000 }");
    create_button_ = new QPushButton(begin_);
    create_button_->move(10, 30);
    create_button_->resize(200, 60);
    create_button_->setStyleSheet("QPushButton { color: #ffffff;"
                                  "background: #404040;"
                                  "border-radius: 5px; }");
    create_button_->setText("СОЗДАТЬ");
    connect(create_button_, SIGNAL (released()), this, SLOT (gotoEditor()));

    load_button_ = new QPushButton(begin_);
    load_button_->move(10, 110);
    load_button_->resize(200, 60);
    load_button_->setStyleSheet("QPushButton { color: #ffffff;"
                                "background: #404040;"
                                "border-radius: 5px; }");
    load_button_->setText("ОТКРЫТЬ");
    connect(load_button_, SIGNAL (released()), this, SLOT (loadFromFile()));

    logtext_ = new QLabel(begin_);
    logtext_->resize(460, 460);
    logtext_->move(250, 6);
    QPixmap logo_;
    logo_.load("/Users/noname/Documents/Programming/Applied/NNC/logo.jpg");
    logtext_->setPixmap(logo_);

// РАБОТА СО СТРАНИЦЕЙ РЕДАКЦИИ (ГАЗЕТ БлЯтЪ)

    editor_ = new QLabel(window_);
    editor_->setStyleSheet("QLabel {"
                          "background: #000000 }");
    pokapohui1_ = new QLabel(editor_);
    pokapohui1_->resize(300, 400);
    pokapohui1_->move(250, 70);
    pokapohui1_->setText("ПРОСТИТЕ,ПОКА НЕ ЕБУ, КАК ЭТО ДЕЛАТЬ");


// РАБОТА СО СТРАНИЦЕЙ СИМУЛЯЦИИ (ОРГАЗМА БЛЯТЬ)

    simulation_ = new QLabel(window_);
    simulation_->setStyleSheet("QLabel {"
                          "background: #000000 }");

    pokapohui2_ = new QLabel(simulation_);
    pokapohui2_->resize(300, 400);
    pokapohui2_->move(250, 70);
    pokapohui2_->setText("БЭКЕНДЕРЫ НЕ СДЕЛАЛИ, ЖДЁМС");

// ОРГИЯ С ГЛАВНОЙ ЧАСТЬЮ ФРОНТА

    maintab_ = new QTabWidget(window_);
    maintab_->setStyleSheet("QTabWidget { background: #fff;"
                            "border: none; }");
    maintab_->setTabPosition(QTabWidget::North);
    maintab_->resize(760, 570);
    maintab_->move(20, 10);
    maintab_->addTab(begin_, "НАЧАЛО");
    maintab_->addTab(editor_, "РЕДАКТОР");
    maintab_->addTab(simulation_, "СИМУЛЯЦИЯ");


}

App::~App() {
    delete simulation_;
    delete editor_;
    delete begin_;
    delete load_button_;
    delete create_button_;
    delete window_;
    delete logtext_;
}

void App::loadFromFile() {
    QString file = QFileDialog::getOpenFileName(nullptr, "Выберите md файл", "", "*.md");
    QFile in(file);
    if (!in.open(QIODevice::ReadOnly)) return;
    QString data = in.readLine();
    in.close();
    if (data.isEmpty()) return;
}

void App::gotoEditor() {
    maintab_->setCurrentWidget(editor_);
}
