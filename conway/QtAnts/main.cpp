#include <QtWidgets>

#define FRAMERATE 20
#define CELLSIZE 10

class AntSimWindow : public QWidget
{
private:
    QImage frame, nextframe;
    QTimer timer;

    void resizeEvent(QResizeEvent *event) override
    {
        resizeFrame(event->size());
    }

    void resizeFrame(const QSize& size)
    {
        QImage new_frame = QImage(size.width() / CELLSIZE, size.height() / CELLSIZE, QImage::Format_Mono);
        new_frame.fill(0);
        QPainter p(&new_frame);
        p.drawImage(QPoint(0, 0), frame);
        frame = new_frame;
        nextframe = new_frame;
    }

    void keyPressEvent(QKeyEvent *event) override
    {
        if(event->key() == Qt::Key::Key_Space)
        {
            if(timer.isActive()) timer.stop();
            else timer.start(1000/FRAMERATE);
        }
        else
            QWidget::keyPressEvent(event);
    }

    void mousePressEvent(QMouseEvent *event) override
    {
        paintCell(event);
    }

    void mouseMoveEvent(QMouseEvent *event) override
    {
        paintCell(event);
    }

    void paintCell(QMouseEvent *event)
    {
        if(event->buttons() & Qt::LeftButton)
        {
            frame.setPixel(event->x() / CELLSIZE, event->y() / CELLSIZE, 1);
            nextframe.setPixel(event->x() / CELLSIZE, event->y() / CELLSIZE, 1);
            repaint();
        }
        else if(event->buttons() & Qt::RightButton)
        {
            frame.setPixel(event->x() / CELLSIZE, event->y() / CELLSIZE, 0);
            nextframe.setPixel(event->x() / CELLSIZE, event->y() / CELLSIZE, 0);
            repaint();
        }
    }

    void paintEvent(QPaintEvent *event) override
    {
        QPainter p(this);
        p.drawImage(rect(), frame);
    }

    void tick()
    {
        for(int y = 0; y < frame.height(); y++)
            for(int x = 0; x < frame.width(); x++)
            {

            }

        frame = nextframe;
        repaint();
    }


public:
    explicit AntSimWindow(QWidget *parent = nullptr) : QWidget(parent), timer(this)
    {
        setWindowTitle("Game of Life");
        setMouseTracking(true);
        resize(800, 600);
        connect(&timer, &QTimer::timeout, this, &AntSimWindow::tick);
        timer.start(1000/FRAMERATE);
    }
};


int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    AntSimWindow window;
    //window.resize(800, 600);
    window.show();

    return app.exec();
}
