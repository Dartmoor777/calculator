#include "advancedlineedit.h"

AdvancedLineEdit::AdvancedLineEdit(QWidget *parent) : QLineEdit(){

}

//void AdvancedLineEdit::keyPressEvent(QKeyEvent *event){
//    event->accept();
//    insert(event->key());
//    event->
//    if(event->key() == Qt::Key_BracketRight){
//        int curPosition = cursorPosition();
//        QString str = text();
//        if( (curPosition) > str.size() || (curPosition == 0))
//            return;
//        if ( (str[curPosition] == ')')
//             || (str[curPosition] == '|') ){
//            setCursorPosition(curPosition+1);
//            event->ignore();
//        }
//    }
//}
