#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "QFileDialog"
#include "QMessageBox"
#include "QTextEdit"
#include <QFileDialog>
#include <QFont>
#include <QColorDialog>
#include <QColor>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mSaveAsDialog( new SaveAsDialog( ) ),
    mPreferencesDialog( new PreferencesDialog( ) ),
    mAboutDialog( new AboutDialog( ) ),
    mTextEditorHasChanged( false )
{    
    ui->setupUi(this);
    setCentralWidget( ui->textEdit );
    mFullScreenOnStartUp = getFullScreenFromFile( );
    if( mFullScreenOnStartUp )
        on_actionFull_Screen_triggered();
    mPreferencesDialog->enableFullScreenOnstartUp( mFullScreenOnStartUp );

    QWidget::setWindowTitle( "Divitto's Editor" );

    connect( ui->textEdit, SIGNAL(textChanged()), this, SLOT(setTextEditorChanged() ) );

    connect( mSaveAsDialog, SIGNAL(saveSignal()), this, SLOT(on_actionSave_triggered() ) );
    connect( mSaveAsDialog, SIGNAL(saveFileNameSignal(QString)), this, SLOT(currentFile(QString) ) );

    connect( mPreferencesDialog, SIGNAL( enableWordWrapHasChanged(bool) ), this, SLOT( setWordWrap(bool) ) );
    connect( mPreferencesDialog, SIGNAL( changeFullScreenOnStartUpSignal(bool)), this, SLOT( setFullScreenOnStartUp(bool) ) );
    connect( mPreferencesDialog, SIGNAL( changeFontSignal() ), this, SLOT( on_actionchangeFont_triggered() ) );
    connect( mPreferencesDialog, SIGNAL( changeBackgroundColorSignal() ), this, SLOT( on_actionchangeBackgroundColor_triggered() ) );
    connect( mPreferencesDialog, SIGNAL( changeHighlighterSignal() ), this, SLOT( on_actionHighlighter_triggered() ) );
    connect( mPreferencesDialog, SIGNAL( changeTextColorSignal() ), this, SLOT( on_actionTextColorChanged_triggered() ) );



}

MainWindow::~MainWindow()
{
    delete mSaveAsDialog;
    delete mPreferencesDialog;
    delete mAboutDialog;
    delete ui;
}

bool MainWindow::getFullScreenFromFile( void )
{
    QFile* file = new QFile( "config.txt" );
    if( file->exists() && file->open( QFile::ReadOnly ) ) {
        if( file->readAll().toStdString() == "true" ) {
            file->close();
            delete file;
            return true;
        }else if( file->readAll().toStdString() == "false" ) {
            file->close();
            delete file;
            return false;
        }
    }else
        std::cout << "ERROR Reading config.txt" << std::endl;
    delete file;
    return false;
}

void MainWindow::on_actionNew_triggered()
{
    if( !this->mTextEditorHasChanged || QMessageBox::question(nullptr, "Are you SURE?", "You have unsaved data!\nAre you <b>SURE</b> you want to close the current file?", QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes ) {
        createNewDocument();
        this->mTextEditorHasChanged = false;
    }
}

void MainWindow::on_actionOpen_triggered()
{
    if( !this->mTextEditorHasChanged || QMessageBox::question(nullptr, "Are you SURE?",
                                            "You have unsaved data!\nAre you SURE you want to close the current file?", QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes) {
        QFile* newFile = new QFile( QFileDialog::getOpenFileName( nullptr, "Open File" ), nullptr );
        if( newFile->exists( ) && newFile->open( QFile::ReadOnly ) ) {
            ui->textEdit->setText( newFile->readAll( ) );
            this->mCurrentFile = newFile->fileName();
            this->mTextEditorHasChanged = false;
        }
        delete newFile;
    }
}

void MainWindow::on_actionSave_triggered()
{
    if( ui->textEdit->toPlainText() != "" || !this->mTextEditorHasChanged ) {
        if( this->mCurrentFile == "" )
            on_actionSave_As_triggered();
        else {
            QFile* file = new QFile( this->mCurrentFile );
            if( file->exists() && file->open( QFile::WriteOnly ) ) {
                file->write( ui->textEdit->toPlainText( ).toStdString().c_str() );
                this->mTextEditorHasChanged = false;
                QMessageBox( QString("Hurray!"), QString("Save has completed!"), QMessageBox::NoIcon, QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton ).exec();
            }
            file->close();
        }
    }else
        QMessageBox( QString("Oops!"), QString("There is nothing to be saved!"), QMessageBox::NoIcon, QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton ).exec();
}

void MainWindow::on_actionSave_As_triggered()
{
    mSaveAsDialog->show();
}

void MainWindow::createNewDocument()
{
    ui->textEdit->setText( "" );
    this->mCurrentFile = "";
}

void MainWindow::setWordWrap( bool mode ) {
    if( mode )
        ui->textEdit->setLineWrapMode( QTextEdit::WidgetWidth );
    else
        ui->textEdit->setLineWrapMode( QTextEdit::NoWrap );
}

void MainWindow::setFullScreenOnStartUp(bool mode)
{
    this->mFullScreenOnStartUp = mode;
    QFile* config = new QFile( "config.txt" );
    if( config->exists() && config->open( QFile::WriteOnly ) ) {
        if( mode ) config->write( "true" );
        else config->write( "false" );
        config->close();
    }
    delete config;
}

void MainWindow::on_actionClose_triggered()
{
    if( this->mTextEditorHasChanged ) {
        if( QMessageBox::question(nullptr, "Are you SURE?", "You have unsaved data! are you SURE you want to quit?", QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes)
            this->close();
    }else
        this->close();
}

void MainWindow::on_actionPreferences_triggered()
{
    this->mPreferencesDialog->show();
}

void MainWindow::on_actionchangeFont_triggered()
{
    bool flag;
    QFont font = QFontDialog::getFont( &flag, nullptr );
    if( flag )
        ui->textEdit->setFont( font );
}

void MainWindow::on_actionchangeBackgroundColor_triggered()
{
    QPalette p = ui->textEdit->palette();
    p.setColor( QPalette::Base, QColorDialog::getColor( ) );
    ui->textEdit->setPalette( p );
}

void MainWindow::on_actionHighlighter_triggered()
{
    ui->textEdit->setTextBackgroundColor( QColorDialog::getColor( ) );
}

void MainWindow::on_actionTextColorChanged_triggered()
{
    ui->textEdit->setTextColor( QColorDialog::getColor( ) );
}

void MainWindow::on_actionFull_Screen_triggered()
{
    QWidget::showMaximized();
}


void MainWindow::on_actionAbout_triggered()
{
    mAboutDialog->exec();
}

void MainWindow::on_actionHelp_triggered()
{
    QMessageBox::information( this, "Help", "For help, tips, and other information\nplease visit us at\n\ndivittounlimited.com" );
}
