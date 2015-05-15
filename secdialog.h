#ifndef SECDIALOG_H
#define SECDIALOG_H

#include <QDialog>
#include <QFileSystemModel>

namespace Ui {
class SecDialog;
}

class SecDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SecDialog(QWidget *parent = 0);
    ~SecDialog();

private slots:
    void on_treeView_clicked(const QModelIndex &index);

    void on_listView_clicked(const QModelIndex &index);

    void on_ok_button_clicked();

private:
    Ui::SecDialog *ui;
    QString sPath;
    QFileSystemModel *dirmodel;
    QFileSystemModel *filemodel;
};

#endif // SECDIALOG_H
