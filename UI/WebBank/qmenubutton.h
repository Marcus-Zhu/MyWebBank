#ifndef QMENUBUTTON_H
#define QMENUBUTTON_H
#include <QPushButton>
class QMenu;

class QMenuButton : public QPushButton
{
    Q_OBJECT
public:
    enum btnType {userBtn = 1, settingBtn = 2};
    QMenuButton(QWidget *parent = 0, btnType t = userBtn);
    QMenu *menu;
private slots:
    void popMenu();
};

#endif // QMENUBUTTON_H
