#ifndef __NMODE_GUI_H__
#define __NMODE_GUI_H__

#include <QApplication>
#include <QDesktopWidget>
#include <QLabel>
#include <QSpinBox>
#include <QCheckBox>
#include <QPushButton>

class NGui : public QWidget
{
    Q_OBJECT

public:
    NGui();

protected:
    // void resizeEvent(QResizeEvent *event) override;

private slots:
    // void newScreenshot();
    // void saveScreenshot();
    // void shootScreen();
    // void updateCheckBox();

private:
    // void updateScreenshotLabel();

    QPixmap originalPixmap;

    QLabel *screenshotLabel;
    QSpinBox *delaySpinBox;
    QCheckBox *hideThisWindowCheckBox;
    QPushButton *newScreenshotButton;
};

#endif // __NMODE_GUI_H__

