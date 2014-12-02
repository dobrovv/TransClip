#include "TCPopup.h"

#include <QApplication>
#include <QCursor>
#include <QACtion>
#include <QMouseEvent>
#include <QDesktopWidget>
#include <QTimer>
#include <QDebug>

#ifdef Q_OS_WIN
    #include <windows.h>
#endif

static Qt::WindowFlags popupWindowFlags = Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint;

TCPopup::TCPopup(QWidget *parent) :
    QMainWindow(parent)
{
    staysOnTop = false;

    if ( staysOnTop ) {
        setWindowFlags( Qt::Dialog );
    } else {
        setWindowFlags( popupWindowFlags );
    }

    escapeAction = new QAction(this);
    escapeAction->setShortcut( QKeySequence( "Esc" ) );
    addAction( escapeAction );
    connect( escapeAction, SIGNAL( triggered() ),
             this, SLOT( hidePopup() ) );

    hideTimer = new QTimer(this);
    hideTimer->setSingleShot( true );
    hideTimer->setInterval( 400 );
    connect( hideTimer, SIGNAL( timeout() ),
             this, SLOT( hideTimerExpired() ) );

    mouseGrabPollTimer = new QTimer(this);
    mouseGrabPollTimer->setSingleShot( false );
    mouseGrabPollTimer->setInterval( 10 );
    connect( mouseGrabPollTimer, SIGNAL( timeout() ),
             this, SLOT( mouseGrabPoll() ));

}

TCPopup::~TCPopup()
{

}

void TCPopup::showPopup( bool giveFocus )
{
    if ( !isVisible() )
    {
        // Need to show the window

        if ( !staysOnTop )
        {
            // Decide where should the window land

            QPoint currentPos = QCursor::pos();

            QRect desktop = QApplication::desktop()->screenGeometry();

            QSize windowSize = geometry().size();

            int x, y;

            /// Try the to-the-right placement
            if ( currentPos.x() + 4 + windowSize.width() <= desktop.topRight().x() )
                x = currentPos.x() + 4;
            else
                /// Try the to-the-left placement
                if ( currentPos.x() - 4 - windowSize.width() >= desktop.x() )
                    x = currentPos.x() - 4 - windowSize.width();
                else
                    // Center it
                    x = desktop.x() + ( desktop.width() - windowSize.width() ) / 2;

            /// Try the to-the-bottom placement
            if ( currentPos.y() + 15 + windowSize.height() <= desktop.bottomLeft().y() )
                y = currentPos.y() + 15;
            else
                /// Try the to-the-top placement
                if ( currentPos.y() - 15 - windowSize.height() >= desktop.y() )
                    y = currentPos.y() - 15 - windowSize.height();
                else
                    // Center it
                    y = desktop.y() + ( desktop.height() - windowSize.height() ) / 2;

            move( x, y );
        }

        show();

        if ( giveFocus )
        {
            activateWindow();
            raise();
        }

        if ( !staysOnTop )
        {
            mouseEnteredOnce = false;
            // Need to monitor the mouse so we know when to hide the window
            interceptMouse();
        }

        // This produced some funky mouse grip-related bugs so we commented it out
        //QApplication::processEvents(); // Make window appear immediately no matter what
    }
    else if ( staysOnTop )
    {
        // Pinned-down window isn't always on top, so we need to raise it
        show();
        activateWindow();
        raise();
    }

    if ( staysOnTop )
        setWindowTitle( "TransClip" );

#ifdef Q_OS_WIN
    /* To much pain in the ass with all this Qt hacks, just put it on top please!!! */

    HWND hwndPopup = reinterpret_cast<HWND>(winId());
    SetWindowPos( hwndPopup, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE );
#endif

}

void TCPopup::hidePopup()
{
    uninterceptMouse();
    hideTimer->stop();
    unsetCursor();
    hide();
}

void TCPopup::interceptMouse()
{
    if ( !mouseIntercepted )
    {
        // We used to grab the mouse -- but this doesn't always work reliably
        // (e.g. doesn't work at all in Windows 7 for some reason). Therefore
        // we use a polling timer now.

        //    grabMouse();
        mouseGrabPollTimer->start();

        qApp->installEventFilter( this );

        mouseIntercepted = true;
    }
}

void TCPopup::uninterceptMouse()
{
    if ( mouseIntercepted )
    {
        qApp->removeEventFilter( this );
        mouseGrabPollTimer->stop();
        //    releaseMouse();

        mouseIntercepted = false;
    }
}

bool TCPopup::eventFilter(QObject *watched, QEvent *event)
{
    /* if ( event->type() == QEvent::FocusIn && watched == ui.translateBox->translateLine() )
    {
        QFocusEvent * focusEvent = static_cast< QFocusEvent * >( event );

        // select all on mouse click
        if ( focusEvent->reason() == Qt::MouseFocusReason ) {
            QTimer::singleShot(0, this, SLOT(focusTranslateLine()));
        }
        return false;
    } */

    if ( mouseIntercepted )
    {
        // We're only interested in our events

        if ( event->type() == QEvent::MouseMove )
        {
            //    DPRINTF( "Object: %s\n", watched->objectName().toUtf8().data() );
            QMouseEvent * mouseEvent = ( QMouseEvent * ) event;
            reactOnMouseMove( mouseEvent->globalPos() );
        }
    }

    return QMainWindow::eventFilter( watched, event );
}

void TCPopup::reactOnMouseMove(const QPoint &p)
{
    if ( geometry().contains( p ) )
    {
        //        DPRINTF( "got inside\n" );

        hideTimer->stop();
        mouseEnteredOnce = true;
        uninterceptMouse();
    }
    else
    {
        //        DPRINTF( "outside\n" );
        // We're in grab mode and outside the window - calculate the
        // distance from it. We might want to hide it.

        // When the mouse has entered once, we don't allow it stayng outside,
        // but we give a grace period for it to return.
        int proximity = mouseEnteredOnce ? 0 : 60;

        // Note: watched == this ensures no other child objects popping out are
        // receiving this event, meaning there's basically nothing under the
        // cursor.
        if ( /*watched == this &&*/
             !frameGeometry().adjusted( -proximity, -proximity, proximity, proximity ).
             contains( p ) )
        {
            // We've way too far from the window -- hide the popup

            // If the mouse never entered the popup, hide the window instantly --
            // the user just moved the cursor further away from the window.

            if ( !mouseEnteredOnce )
                hidePopup();
            else
                hideTimer->start();
        }
    }
}

void TCPopup::mousePressEvent(QMouseEvent *ev)
{
    // With mouse grabs, the press can occur anywhere on the screen, which
    // might mean hiding the window.

    if ( !frameGeometry().contains( ev->globalPos() ) )
    {
        hidePopup();

        return;
    }

    if ( ev->button() == Qt::LeftButton )
    {
        startPos = ev->globalPos();
        setCursor( Qt::ClosedHandCursor );
    }

    QMainWindow::mousePressEvent( ev );
}

void TCPopup::mouseMoveEvent(QMouseEvent *event)
{
    if ( event->buttons() && cursor().shape() == Qt::ClosedHandCursor )
    {
        QPoint newPos = event->globalPos();

        QPoint delta = newPos - startPos;

        startPos = newPos;

        // Move the window

        move( pos() + delta );
    }

    QMainWindow::mouseMoveEvent( event );
}

void TCPopup::mouseReleaseEvent(QMouseEvent *ev)
{
    unsetCursor();
    QMainWindow::mouseReleaseEvent( ev );
}

void TCPopup::leaveEvent(QEvent *event)
{
    QMainWindow::leaveEvent( event );

    // We hide the popup when the mouse leaves it.

    // Combo-boxes seem to generate leave events for their parents when
    // unfolded, so we check coordinates as well.
    // If the dialog is pinned, we don't hide the popup.
    // If some mouse buttons are pressed, we don't hide the popup either,
    // since it indicates the move operation is underway.
    if ( !staysOnTop && !geometry().contains( QCursor::pos() ) &&
         QApplication::mouseButtons() == Qt::NoButton )
    {
        hideTimer->start();
    }
}

void TCPopup::enterEvent(QEvent *event)
{
    QMainWindow::enterEvent( event );

    if ( mouseEnteredOnce )
    {
        // We "enter" first time via our event filter. This seems to evade some
        // unexpected behavior under Windows.

        // If there was a countdown to hide the window, stop it.
        hideTimer->stop();
    }
}

void TCPopup::showEvent(QShowEvent *ev)
{
    QMainWindow::showEvent( ev );
}

void TCPopup::setStaysOnTop(bool onTop)
{
    staysOnTop = onTop;
    QByteArray geometry = saveGeometry();
    if ( onTop )
    {
        uninterceptMouse();
        setWindowFlags( Qt::Dialog );
        setWindowTitle( "TransClip" );
        hideTimer->stop();
    }
    else
    {
        setWindowFlags( popupWindowFlags );
        mouseEnteredOnce = true;
    }

    restoreGeometry(geometry);
    show();
}

void TCPopup::hideTimerExpired()
{
    if ( isVisible() )
        hidePopup();
}

void TCPopup::mouseGrabPoll()
{
    if ( mouseIntercepted )
        reactOnMouseMove( QCursor::pos() );
}

void TCPopup::escapePressed()
{
    hidePopup();
}
