#include "header.h"

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
    void gotoEditor();

private:
    QWidget* window_;

    QLabel* begin_;
    QPushButton* load_button_;
    QPushButton* create_button_;

    QLabel* editor_;
    QLabel* pokapohui1_;

    QLabel* simulation_;
    QLabel* pokapohui2_;

    std::string number_;
    QLabel* logtext_;
    QTabWidget* maintab_;
};