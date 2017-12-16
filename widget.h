#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtGui>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

    int game_map[12][12];
    int wblocks = 12;
    int hblocks = 12;

    int player_x = 6;
    int player_y = 6;
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
protected:
    void paintEvent(QPaintEvent * e);
    void keyPressEvent(QKeyEvent * e);
};

#endif // WIDGET_H
