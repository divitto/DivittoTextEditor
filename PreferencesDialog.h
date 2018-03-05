#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H

#include <QDialog>
#include <QFontDialog>
#include<iostream>

namespace Ui {
class PreferencesDialog;
}

class PreferencesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PreferencesDialog(QWidget *parent = 0);
    ~PreferencesDialog();
    // Interface
    void enableFullScreenOnstartUp( bool mode );

signals:
    void enableWordWrapHasChanged( bool mode );
    void changeFontSignal( void );
    void changeBackgroundColorSignal( void );
    void changeHighlighterSignal( void );
    void changeTextColorSignal( void );
    void changeFullScreenOnStartUpSignal( bool mode );
private slots:
    void on_acceptButton_clicked();
    void on_changeFontButton_clicked();
    void on_backgroundColorButton_clicked();
    void on_changeHighlighterButton_clicked();
    void on_forgroundColorButton_clicked();
    void on_fullScreenOnStartUpCheckBox_stateChanged( int mode );

private:
    Ui::PreferencesDialog *ui;
};

#endif // PREFERENCESDIALOG_H
