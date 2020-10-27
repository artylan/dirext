#ifndef PROGRESSDIALOG_H
#define PROGRESSDIALOG_H

#include <QDialog>

namespace Ui {
class ProgressDialog;
}

class ProgressDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProgressDialog(QWidget *parent = nullptr);
    ~ProgressDialog();

    void setProgress(int progress);
    bool isCanceled();
    int getProgress();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::ProgressDialog *ui;
    bool canceled;
    int progress;

private slots:
    void on_pushButton_clicked();

};

#endif // PROGRESSDIALOG_H
