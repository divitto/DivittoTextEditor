#include "PreferencesDialog.h"
#include "ui_PreferencesDialog.h"
#include <QFile>

PreferencesDialog::PreferencesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreferencesDialog)
{
    ui->setupUi(this);
    connect( ui->fullScreenOnStartUpCheckBox, SIGNAL( stateChanged( int ) ), this, SLOT( on_fullScreenOnStartUpCheckBox_stateChanged(int) ) );
}

PreferencesDialog::~PreferencesDialog()
{
    delete ui;
}

void PreferencesDialog::enableFullScreenOnstartUp( bool mode )
{
    ui->fullScreenOnStartUpCheckBox->setChecked( mode );
}

void PreferencesDialog::on_acceptButton_clicked()
{
    if( ui->wordWrapCheckBox->isChecked() )
        emit enableWordWrapHasChanged( true );
    else
        emit enableWordWrapHasChanged( false );
    if( ui->fullScreenOnStartUpCheckBox->isChecked() )
        emit changeFullScreenOnStartUpSignal( true );
    else
        emit changeFullScreenOnStartUpSignal( false );
    this->close();
}

void PreferencesDialog::on_changeFontButton_clicked()
{
    emit changeFontSignal( );
}

void PreferencesDialog::on_backgroundColorButton_clicked()
{
    emit changeBackgroundColorSignal( );
}

void PreferencesDialog::on_changeHighlighterButton_clicked()
{
    emit changeHighlighterSignal( );
}

void PreferencesDialog::on_forgroundColorButton_clicked()
{
    emit changeTextColorSignal( );
}

void PreferencesDialog::on_fullScreenOnStartUpCheckBox_stateChanged( int mode )
{
    QFile* config = new QFile( "config.txt" );
    if( config->exists() && config->open( QFile::WriteOnly ) ) {
        if( mode ) config->write( "true" );
        else config->write( "false" );
        config->close();
    }
    delete config;
}
