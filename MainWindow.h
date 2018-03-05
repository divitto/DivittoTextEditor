#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <iostream>



#include "SaveAsDialog.h"
#include "PreferencesDialog.h"
#include "AboutDialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //## Interface

    QString currentFile( void ) const;
    bool getTextEditorHasChanged( void ) const;
    bool getFullScreenFromFile( void );
private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_As_triggered();

    void setTextEditorChanged( void );
    void currentFile( QString fileName );
    void createNewDocument();
    void setWordWrap( bool mode );
    void setFullScreenOnStartUp( bool mode );

    void on_actionClose_triggered();

    void on_actionPreferences_triggered();

    void on_actionchangeFont_triggered();
    void on_actionchangeBackgroundColor_triggered();
    void on_actionHighlighter_triggered();
    void on_actionTextColorChanged_triggered();
    void on_actionFull_Screen_triggered();

    void on_actionAbout_triggered();

    void on_actionHelp_triggered();

private:
    Ui::MainWindow *ui;

    // Dialogs
    SaveAsDialog*     mSaveAsDialog;
    PreferencesDialog* mPreferencesDialog;
    AboutDialog* mAboutDialog;

    // Attributes
    QString mCurrentFile;
    bool mTextEditorHasChanged;
    bool mFullScreenOnStartUp;

};

inline void MainWindow::currentFile( QString fileName ) { this->mCurrentFile = fileName; }
inline QString MainWindow::currentFile( void ) const { return mCurrentFile; }
inline void MainWindow::setTextEditorChanged( void ) { this->mTextEditorHasChanged = true; }
inline bool MainWindow::getTextEditorHasChanged( void ) const { return mTextEditorHasChanged; }
#endif // MAINWINDOW_H
