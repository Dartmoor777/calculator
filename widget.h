#ifndef WIDGET_H
#define WIDGET_H
#include <QtMath>
#include <math.h>
#include <QtWidgets>

namespace Ui {
class Widget;
}

constexpr double pi = 3.1415926535897;
constexpr double e = 2.7182818284;

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    QString calculate(QString first, QString action, QString second = "");

private:
    Ui::Widget *ui;
//    QLinkedList<QString> revertList;
    QString evaluation(QString, QRegExp);
    QLinkedList<QString> split(QString str);
    bool eventFilter(QObject *watched, QEvent *event);
public slots:
    void but_add(QString);
    void onConversionListChange();
private slots:
    void on_pushButton_erase_clicked();
    void on_pushButton_eq_clicked();
    void on_pushButton_revert_clicked();
    void on_lineEdit_textChanged(const QString &arg1);
    void on_listWidget_itemClicked(QListWidgetItem *item);
    void on_saveButton_3_clicked();
    void on_saveButton_2_clicked();
    void on_delAllButton_clicked();
    void on_saveButton_clicked();
    void on_delButton_clicked();
    void on_pasteButton_clicked();
};

#endif // WIDGET_H
