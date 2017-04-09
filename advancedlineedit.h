#ifndef ADVANCEDLINEEDIT_H
#define ADVANCEDLINEEDIT_H

#include <QtWidgets>
#include <QObject>

class AdvancedLineEdit : public QLineEdit
{
public:
    explicit AdvancedLineEdit(QWidget *parent = 0);
//    ~AdvancedLineEdit(){};
private:
    void keyPressEvent(QKeyEvent *);
//    void keyPressEvent(QKeyEvent *event);
};

#endif // ADVANCEDLINEEDIT_H
