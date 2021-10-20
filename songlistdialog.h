#pragma once
#include <QDialog>
#include "songdialog.h"
#include "songlist.h"
#include <QStandardItemModel>
#include <QStandardItem>

namespace Ui 
{
class SongListDialog;
}


class SongListDialog : public QDialog 
{
Q_OBJECT

public:
	SongListDialog(QWidget *parent = nullptr);
    QString fullPath(const QString& relativePath) const;
	~SongListDialog();
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
public slots:
	void on_btnCreate_clicked();
    void on_btnSave_clicked();
    void on_btnEdit_clicked();

private slots:

    void on_tableView_clicked(const QModelIndex &index);

    void on_btnSort_clicked();

private:
	Ui::SongListDialog* m_ui = nullptr;
    QStandardItemModel *model;
    songList list;
    const QString fileDir = "../src";
    const QString fileName="data.txt";
    int chosenRow;
    void readDataFromFile(std::string path);
    void setTableHeader();
    void showList();
};
