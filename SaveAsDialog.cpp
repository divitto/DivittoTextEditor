#include "SaveAsDialog.h"
#include "ui_SaveAsDialog.h"
#include "QFileDialog"
#include "QMessageBox"

SaveAsDialog::SaveAsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveAsDialog)
{
    ui->setupUi(this);
}

SaveAsDialog::~SaveAsDialog()
{
    delete ui;
}

void SaveAsDialog::on_browseButton_clicked()
{
    ui->fileNameEdit->setText( QFileDialog::getOpenFileName( ) );

}

void SaveAsDialog::on_saveButton_clicked()
{
    QFile* file = new QFile( ui->fileNameEdit->text() );
    if( file->exists() ) { // Prompt user here to make sure they do not over write a file that already exists!!!!!!
        if( QMessageBox::question(nullptr, "Are you SURE?", "Are you SURE you want to overwrite?",
                                  QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes ) {
            emit saveFileNameSignal( file->fileName() );
            emit saveSignal();
        }
    }else {
        emit saveFileNameSignal( file->fileName( ) );
        emit saveSignal();
    }
    delete file;
    this->close();
}

void SaveAsDialog::on_cancelButton_clicked()
{
    this->close( );
}
