#ifndef WLOGIN_H
#define WLOGIN_H

#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QDialog>
#include <QMouseEvent>

class WLogin : public QDialog
{
    Q_OBJECT
public:
    explicit WLogin(QWidget *parent = 0);

protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

public slots:
    void openWindow();
    void checkLogin();
    void checkReg();
    void changeToReg();
    void changeToLogin();

private:
    QLabel *bgLabel;
    QLineEdit *userName;
    QLineEdit *password;
    QLineEdit *passwordConfirm;
    QLineEdit *idCard;
    QLineEdit *cardNum;
    QLineEdit *mobile;
    QLineEdit *email;
    QLineEdit *address;
    QLineEdit *zipcode;
    QLabel *notice;
    QPushButton *closeBtn;
    QPushButton *regBtn;
    QPushButton *loginBtn;
    QPushButton *registerBtn;
    QPushButton *backBtn;
    bool isPressed;
    QPoint movePoint;
};

#endif // WLOGIN_H
