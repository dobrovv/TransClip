#ifndef TCPOPUP_H
#define TCPOPUP_H

#include <QMainWindow>
#include <QDialog>
#include <QClipboard>

class TCPopup : public QMainWindow
{
    Q_OBJECT

public:
    explicit TCPopup(QWidget *parent = 0);
    ~TCPopup();

    inline bool popupStaysOnTop() {return staysOnTop;}

signals:

public slots:

    void showPopup(bool giveFocus = true );

    // Hides the popup window, effectively closing it.
    void hidePopup();

    void setStaysOnTop(bool onTop = true );

private:

    // Grabs mouse and installs global event filter to track it thoroughly.
    void interceptMouse();
    // Ungrabs mouse and uninstalls global event filter.
    void uninterceptMouse();

    bool staysOnTop;

    QString pendingInputText, inputText;

    bool mouseEnteredOnce;
    bool mouseIntercepted;

    QPoint startPos; // For window moving

    QTimer *hideTimer; // When mouse leaves the window, a grace period is
    // given for it to return back. If it doesn't before
    // this timer expires, the window gets hidden.
    //QTimer altModeExpirationTimer, altModePollingTimer; // Timers for alt mode

    QTimer *mouseGrabPollTimer;

    QAction *escapeAction;

    virtual bool eventFilter( QObject * watched, QEvent * event );

    /// Called from event filter or from mouseGrabPoll to handle mouse event
    /// while it is being intercepted.
    void reactOnMouseMove( QPoint const & p );

    virtual void mousePressEvent( QMouseEvent * );
    virtual void mouseMoveEvent( QMouseEvent * );
    virtual void mouseReleaseEvent( QMouseEvent * );
    virtual void leaveEvent( QEvent * event );
    virtual void enterEvent( QEvent * event );
    virtual void showEvent( QShowEvent * );

private slots:

    void hideTimerExpired();

    /// Called repeatedly once the popup is initially engaged and we monitor the
    /// mouse as it may move away from the window. This simulates mouse grab, in
    /// essense, but seems more reliable. Once the mouse enters the window, the
    /// polling stops.
    void mouseGrabPoll();

    void escapePressed();

};

#endif // TCPOPUP_H
