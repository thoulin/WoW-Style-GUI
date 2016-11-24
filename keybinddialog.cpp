#include "keybindialog.hpp"



KeybindDialog::KeybindDialog(QWidget *parent)
    : QFrame(parent)
{
    setGeometry(150,150,150,150);
    setObjectName("keybindDialog");
    setStyleSheet("border: 2px solid black;"
                  "background-color: white;");
    info = new QLabel(this);
    info->resize(150,150);
    info->setText("Press a Key Combination!");
    info->setAlignment(Qt::AlignCenter);
    num = -1;
    count = 0;
    grabKeyboard();
    show();
}

//possibly use QKeySequenceEdit in the future but probably not
void KeybindDialog::keyReleaseEvent(QKeyEvent *event){
    QKeySequence keybind;
    if(event->modifiers() & Qt::ControlModifier &&
       event->modifiers() & Qt::ShiftModifier &&
       event->modifiers() & Qt::AltModifier){
        qDebug() << "Shift Control Alt Detected";
        keyPress.append("Shift+Ctrl+Alt+");
        qDebug() << QKeySequence(keyPress + QKeySequence(event->key()).toString());
        parseKey(keyPress + QKeySequence(event->key()).toString());
        return;
    }

    else if(event->modifiers() & Qt::ShiftModifier &&
            event->modifiers() & Qt::ControlModifier){
        qDebug() << "Shift Control Detected";
        keyPress.append("Shift+Ctrl+");
        qDebug() << QKeySequence(keyPress + QKeySequence(event->key()).toString());
        parseKey(keyPress + QKeySequence(event->key()).toString());
        return;
    }

    else if(event->modifiers() & Qt::ShiftModifier &&
            event->modifiers() & Qt::AltModifier){
        qDebug() << "Shift Alt Detected";
        keyPress.append("Shift+Alt+");
        qDebug() << QKeySequence(keyPress + QKeySequence(event->key()).toString());
        parseKey(keyPress + QKeySequence(event->key()).toString());
        return;
    }

    else if(event->modifiers() & Qt::AltModifier &&
            event->modifiers() & Qt::ControlModifier){
        qDebug() << "Control Alt Detected";
        keyPress.append("Ctrl+Alt+");
        qDebug() << QKeySequence(keyPress + QKeySequence(event->key()).toString());
        parseKey(keyPress + QKeySequence(event->key()).toString());
        return;
    }

    else if(event->modifiers() & Qt::ShiftModifier){
        qDebug() << "Shift Detected";
        keyPress.append("Shift+");
        qDebug() << QKeySequence(keyPress + QKeySequence(event->key()).toString());
        parseKey(keyPress + QKeySequence(event->key()).toString());
        return;
    }

    else if(event->modifiers() & Qt::ControlModifier){
        qDebug() << "Control Detected";
        keyPress.append("Ctrl+");
        qDebug() << QKeySequence(keyPress + QKeySequence(event->key()).toString());
        parseKey(keyPress + QKeySequence(event->key()).toString());
        return;
    }

    else if(event->modifiers() & Qt::AltModifier){
        qDebug() << "Alt Detected";
        keyPress.append("Alt+");
        qDebug() << QKeySequence(keyPress + QKeySequence(event->key()).toString());
        parseKey(keyPress + QKeySequence(event->key()).toString());
        return;
    }

    else{
        if(event->key() == Qt::Key_unknown){
            qDebug() << "Unknown Key";
            delete(this);
            return;
        }
        else if (event->key() == Qt::Key_Alt ||
                 event->key() == Qt::Key_Control ||
                 event->key() == Qt::Key_Shift){
            if (count > 2){
                qDebug() << "Bad combo";
                delete(this);
                return;
            }
            switch (event->key()){
                case Qt::Key_Alt:
                    keyPress.append("Alt+");
                    break;
                case Qt::Key_Control:
                    keyPress.append("Ctrl+");
                    break;
                case Qt::Key_Shift:
                    keyPress.append("Shift+");
                    break;
                default:
                    break;
            }
            count++;
            return;
        }
        if(event->key() == Qt::Key_Escape){
            qDebug() << "Cannot bind escape!";
            event->ignore();
            delete(this);
            return;
        }
        qDebug() << "Just a Key Detected";
        qDebug() << QKeySequence(event->key()).toString();
        parseKey(keyPress + QKeySequence(event->key()).toString());
        return;
    }
}

void KeybindDialog::parseKey(QString key){
    int size;
    //qDebug() << "Before Split:" << key;
    QStringList query = key.split('+');
    size = query.size();
    query.removeDuplicates();
    if (size != query.size()){
        qDebug() << "Bad Input";
        delete(this);
        return;
    }
    else{
        //qDebug() << key;
        emit newBind(QKeySequence(key),num);
        delete(this);
        return;
    }
}

void KeybindDialog::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_Escape){
        event->ignore();
    }
}

void KeybindDialog::reject(){

}
