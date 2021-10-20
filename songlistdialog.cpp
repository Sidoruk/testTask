#include "songlistdialog.h"
#include "songdialog.h"
#include "ui_songlistdialog.h"
#include <iostream>
#include <fstream>
#include <QFileDialog>


void SongListDialog::readDataFromFile(std::string path)
{
    std::ifstream file;
    file.open(path);
    if(file.is_open())
    {
        std::cout<<"File opened successfully to read\n\n";
        int countOfElements;
        file>>countOfElements;
        std::cout<<"File contains "<<countOfElements<<" elements\n";
        std::string str;
        song item;
        int rate;

        for(int i=0; i<countOfElements; i++){
            file>>str;  //read name
            item.setName(QString::fromStdString(str));
            file>>str;  //read author
            item.setAuthor(QString::fromStdString(str));
            file>>str; //read length
            item.setLength(QString::fromStdString(str));
            file>>rate;  //read rating
            item.setRating(rate);
            file>>str;  //read absolute path to image
            item.setImgPath(QString::fromStdString(str));

            list.insert(item);
        }
    }
    else
    {
        std::cout<<"Error while opening file to read\n\n";
    }
    file.close();
}

QVariant SongListDialog::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
            switch (section) {
            case 0:
                return QString("Preview");
            case 1:
                return QString("Name");
            case 2:
                return QString("Author");
            case 3:
                return QString("Length");
            }
        }
        return QVariant();
}

void SongListDialog::setTableHeader()
{
    model=new QStandardItemModel(m_ui->tableView);

    showList();

    m_ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    m_ui->tableView->setModel(model);
    model->setHeaderData(0, Qt::Horizontal, "Preview", Qt::EditRole);
    model->setHeaderData(1, Qt::Horizontal, "Name", Qt::EditRole);
    model->setHeaderData(2, Qt::Horizontal, "Author", Qt::EditRole);
    model->setHeaderData(3, Qt::Horizontal, "Length", Qt::EditRole);
}

QString SongListDialog::fullPath(const QString& relativePath) const
{
    QDir dir;
    dir.cd(fileDir);
    return dir.absoluteFilePath(relativePath);
}

void SongListDialog::showList()
{
    model->clear();
    QString imgPath;

    QPixmap pixmap;
    for(int i=0; i<list.getSongsCount(); i++)
    {
        imgPath=QString::fromStdString(list.getImgPath(i));
        pixmap.load(imgPath);
        QIcon image(pixmap);
        QStandardItem *it=new QStandardItem;
        it->setIcon(image);
        it->setToolTip(QString::number(list.getRating(i)));

        model->setItem(i, 0, it);

        QStandardItem *itmName=new QStandardItem;
        itmName->setText(QString::fromStdString(list.getName(i)));
        itmName->setToolTip(QString::number(list.getRating(i)));
        model->setItem(i, 1, itmName);

        QStandardItem *itmAuthor=new QStandardItem;
        itmAuthor->setText(QString::fromStdString(list.getAuthor(i)));
        itmAuthor->setToolTip(QString::number(list.getRating(i)));
        model->setItem(i, 2, itmAuthor);

        QStandardItem *itmLen=new QStandardItem;
        itmLen->setText(QString::fromStdString(list.getLength(i)));
        itmLen->setToolTip(QString::number(list.getRating(i)));
        model->setItem(i, 3, itmLen);
    }
}

SongListDialog::SongListDialog(QWidget *parent): QDialog(parent)
{
    QDir dir;
    if (!dir.exists(fileDir))
        dir.mkpath(fileDir);

    readDataFromFile(fullPath(fileName).toStdString());
    m_ui = new Ui::SongListDialog();
    m_ui->setupUi(this);
    setTableHeader();
}

SongListDialog::~SongListDialog()
{
	delete m_ui;
}

void SongListDialog::on_btnCreate_clicked()
{
	SongDialog dlg;
    dlg.setModal(true);
    if(dlg.exec())
    {
        song acceptedSong=dlg.sendData();
        std::cout<<"Accepted song:"<<std::endl;
        acceptedSong.show();
        list.insert(acceptedSong);
        std::cout<<"Size of list="<<list.getSongsCount()<<std::endl;

        showList();
    }
}

void SongListDialog::on_btnSave_clicked()
{
    std::ofstream saveFile;
    saveFile.open(fullPath(fileName).toStdString());
    if(saveFile.is_open())
    {
        std::cout<<"File for saving was opened successfully\n\n";
        saveFile<<list.getSongsCount()<<std::endl;
        for(int i=0; i<list.getSongsCount(); i++)
        {
            saveFile<<list.getName(i)<<std::endl;
            saveFile<<list.getAuthor(i)<<std::endl;
            saveFile<<list.getLength(i)<<std::endl;
            saveFile<<list.getRating(i)<<std::endl;
            saveFile<<list.getImgPath(i)<<std::endl;
        }
    }
    else
    {
        std::cout<<"Error while opening file for saving\n"<<std::endl;
    }
    saveFile.close();
}

void SongListDialog::on_btnEdit_clicked()
{
    SongDialog dlg;
    dlg.setModal(true);

    dlg.getSong(list.getItem(chosenRow));
    if(dlg.exec())
    {
        song acceptedSong=dlg.sendData();
        std::cout<<"Accepted song:"<<std::endl;
        acceptedSong.show();
        list.insert(acceptedSong);
        list.removeItem(chosenRow);
        std::cout<<"Size of list="<<list.getSongsCount()<<std::endl<<std::endl;

        showList();
    }
}

void SongListDialog::on_tableView_clicked(const QModelIndex &index)
{
    QModelIndex id=m_ui->tableView->model()->index(index.row(), 0, index.parent());
    if(id.isValid())
    {
        chosenRow=id.row();
        std::cout<<"Chosen row number: "<<chosenRow<<std::endl;
    }
}

void SongListDialog::on_btnSort_clicked()
{
    list.sort();
    showList();
}


