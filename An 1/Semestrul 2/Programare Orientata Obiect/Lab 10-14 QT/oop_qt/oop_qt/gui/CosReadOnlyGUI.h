#pragma once
#include<QWidget>
#include<QPainter>
#include "../service/locatar_service.h"
using namespace std;
class HistogramGUI :public QWidget, public Observer {
private:
    locatar_service& cos;
public:
    HistogramGUI(locatar_service& cos) :cos{ cos } {
        cos.addObserver(this);
    }
    void update()override {
        repaint();
    }
    void paintEvent(QPaintEvent* ev)override {
        QPainter p{ this };
        int i = 0;
        srand(time(NULL));
        for (const auto& u : cos.get_notifications()) {
            i++;
            int x = rand()%300;
            int y = rand() % 300;
            p.drawRect(x, y, 20, u);
            p.drawImage(x, y, QImage("C:\\Users\\emanu\\CLionProjects\\oop_qt\\cipricraciun.jpg"));
        }
    }
    ~HistogramGUI() {
        cos.removeObserver(this);
    }

};