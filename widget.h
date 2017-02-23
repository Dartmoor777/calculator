#ifndef WIDGET_H
#define WIDGET_H
#include <QtMath>
#include <QtWidgets>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    QString calculate(QString first, QString action, QString second);

private:
    Ui::Widget *ui;
    QList<QString> revertList;
public slots:
    void but_add(QString);
private slots:
    void on_pushButton_erase_clicked();
    void on_pushButton_eq_clicked();
    void on_pushButton_revert_clicked();
};

#endif // WIDGET_H
