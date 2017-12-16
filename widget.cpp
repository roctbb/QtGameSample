#include "widget.h"
#include "ui_widget.h"
#include <QtGui>
#include <QFile>
#include <QTextStream>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setGeometry(this->x(), this->y(), 600,600);
    QFile file(":/files/game.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream fs(&file);
        for (int i=0; i<wblocks; i++)
            for (int j=0; j<hblocks; j++)
                fs >> game_map[i][j];
    }
    else {
        for (int i=0; i<wblocks; i++)
            for (int j=0; j<hblocks; j++)
                game_map[i][j]=0;
    }
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *e)
{
    QImage grass(":/files/images/grass.jpg");
    QImage block(":/files/images/brick.jpg");
    QImage player(":/files/images/player.png");

    QPainter painter(this);

    int wsize = this->width()/wblocks;
    int hsize = this->height()/hblocks;

    for (int i=0; i<wblocks; i++)
        for (int j=0; j<hblocks; j++)
            if (game_map[i][j]==0)
                painter.drawImage(i*wsize, j*hsize, grass.scaled(wsize, hsize));
            else
                painter.drawImage(i*wsize, j*hsize, block.scaled(wsize, hsize));
    painter.drawImage(player_x*wsize, player_y*hsize, player.scaled(wsize, hsize));
}

void Widget::keyPressEvent(QKeyEvent *e)
{
    if (e->key()==Qt::Key_D)
        if (game_map[player_x+1][player_y]!=1)
            player_x++;
    if (e->key()==Qt::Key_A)
        if (game_map[player_x-1][player_y]!=1)
            player_x--;
    if (e->key()==Qt::Key_W)
        if (game_map[player_x][player_y-1]!=1)
            player_y--;
    if (e->key()==Qt::Key_S)
        if (game_map[player_x][player_y+1]!=1)
            player_y++;
    this->repaint();
}
