#ifndef SAVEASDIALOG_H
#define SAVEASDIALOG_H

#include <QDialog>

namespace Ui {
class SaveAsDialog;
}

class SaveAsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SaveAsDialog(QWidget *parent = 0);
    ~SaveAsDialog();
signals:
    void saveSignal( );
    void saveFileNameSignal( QString fileName );

private slots:
    void on_browseButton_clicked();

    void on_saveButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::SaveAsDialog *ui;
};

#endif // SAVEASDIALOG_H
