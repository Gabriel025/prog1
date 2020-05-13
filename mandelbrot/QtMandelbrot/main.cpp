#include <QtWidgets>
#include <complex>

typedef std::complex<double> complexd;

inline double lerpd(double a, double b, double t)
{
    return a * (1 - t) + b * t;
}


#define RECALC_DELAY 100

class MandelbrotWindow : public QWidget
{
private:
    QImage frame;
    complexd center, half_width;

    QTimer recalc_timer;
    QThread recalc_thread;
    QMutex frame_lock;


    void resizeEvent(QResizeEvent *event) override
    {
        resizeFrame(event->size());
    }

    void resizeFrame(const QSize& size)
    {
        QImage new_frame = QImage(size.width(), size.height(), QImage::Format_Grayscale8);
        new_frame.fill(0);
        QPainter p(&new_frame);
        p.drawImage(QPoint(0, 0), frame);
        frame = new_frame;
    }

    void keyPressEvent(QKeyEvent *event) override
    {
        QWidget::keyPressEvent(event);
    }

    void mousePressEvent(QMouseEvent *event) override
    {
        //paintCell(event);
    }

    void wheelEvent(QWheelEvent *event) override
    {
        event->delta();
    }

    void paintEvent(QPaintEvent *event) override
    {
        QPainter p(this);
        p.drawImage(rect(), frame);
    }

    void recalculate()
    {
        for(int y = 0; y < frame.height(); y++)
            for(int x = 0; x < frame.width(); x++)
            {
                int n = nLiveNeighbors(x, y);

                if(frame.pixelIndex(x, y) == 1 && (n < 2 || n > 3))
                    nextframe.setPixel(x, y, 0);
                if(frame.pixelIndex(x, y) == 0 && n == 3)
                    nextframe.setPixel(x, y, 1);
            }

        frame = nextframe;
        repaint();
    }

    unsigned char mandelbrot_iter(complexd c, unsigned int max_iter)
    {
        complexd z = c;
        unsigned char result = 0;

        for(unsigned int i = 1; i <= max_iter; i++)
        {
            double re2 = z.real() * z.real();
            double im2 = z.imag() * z.imag();
            if(re2 + im2 > 4)
            {
                result = 1 + i * 254 / max_iter;
                break;
            }

            //(a+bi)^2 + c + di = a*a-b*b+c + (2*a*b+d)*i
            z.imag(2 * z.real() * z.imag() + c.imag());
            z.real(re2 - im2 + c.real());
        }

        return result;
    }

    complexd screen_coords_to_complex(QPoint point, complexd top_left, complexd bottom_right)
    {
        complexd result;
        result.real(lerpd(top_left.real(), bottom_right.real(), (double)point.first / img_size.first));
        result.imag(lerpd(top_left.imag(), bottom_right.imag(), (double)point.second / img_size.second));

        return result;
    }

public:
    explicit MandelbrotWindow(QWidget *parent = nullptr) : QWidget(parent), recalc_timer(this), recalc_thread(this)
    {
        setWindowTitle("Mandelbrot set");
        resize(800, 600);

        recalc_timer.setSingleShot(true);
        recalc_timer.setInterval(RECALC_DELAY);
        connect(&recalc_timer, &QTimer::timeout, &recalc_thread, &QThread::start);
        //connect(&recalc_thread, &QThread::finished, this, ...);
    }
};


int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    MandelbrotWindow window;
    //window.resize(800, 600);
    window.show();

    return app.exec();
}
