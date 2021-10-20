#include "songdialog.h"
#include "ui_songdialog.h"
#include <QFileDialog>
#include <QRandomGenerator>
#include <iostream>
#include "songlistdialog.h"

QString GetRandomString();

SongDialog::SongDialog(QWidget* parent): QDialog(parent), m_ui(new Ui::SongDialog())
{
	m_ui->setupUi(this);
	connect(m_ui->btnPreview, &QPushButton::clicked, this, &SongDialog::choosePreview);
	QDir dir;
	if (!dir.exists(m_imageDir))
		dir.mkpath(m_imageDir);
}

SongDialog::~SongDialog()
{
    delete m_ui;
}

song SongDialog::sendData()
{
    return input;
}

void SongDialog::choosePreview()
{
	const auto filename = QFileDialog::getOpenFileName(this, tr("Выберите изображение"),
		QString(), "(*.jpeg *.jpg *png *gif)");
	if (filename.isEmpty())
		return;
    std::cout<<"name of chosen: "<<filename.toStdString()<<std::endl;
	const QString copyName = copiedPreview(filename);
    input.setImgPath(fullImagePath(copyName));
	showPreview(copyName);
}

QString SongDialog::copiedPreview(const QString& filePath) const
{
	const QImage image(filePath);
	const auto smaller = image.scaled(m_ui->labelPreview->width(), m_ui->labelPreview->height(),
		Qt::AspectRatioMode::KeepAspectRatioByExpanding);

    //QString name = "1.png";
    QString name = GetRandomString();
	if (!smaller.save(fullImagePath(name), "PNG"))
		return QString();

    std::cout<<"name of copied: "<<name.toStdString()<<std::endl;
    std::cout<<"full path of copied: "<<fullImagePath(name).toStdString()<<std::endl;

	return  name;
}

void SongDialog::showPreview(const QString& relativePath) const
{
	if (relativePath.isEmpty())
		return;
	const auto fn = fullImagePath(relativePath);
	if (!QFile::exists(fn))
		return;

	const QPixmap pixmap(fn);	
	m_ui->labelPreview->setPixmap(pixmap);
}

QString SongDialog::fullImagePath(const QString& relativePath) const
{
	QDir dir;
	dir.cd(m_imageDir);
    std::cout<<"relative path "<<relativePath.toStdString()<<std::endl;
    std::cout<<"relative absolute path "<<dir.absoluteFilePath(relativePath).toStdString()<<std::endl;
    return dir.absoluteFilePath(relativePath);
}

void SongDialog::getSong(song changeble)
{
    m_ui->authorLineEdit->setText(changeble.getAuthor());
    m_ui->nameLineEdit->setText(changeble.getName());
    m_ui->lengthLineEdit->setText(changeble.getLength());
    m_ui->horizontalSlider->setValue(changeble.getRating());
}

void SongDialog::on_buttonBox_accepted() //if pressed button OK
{
    std::cout<<"Pressed button OK"<<std::endl;

    QString name = m_ui->nameLineEdit->text();
    QString author = m_ui->authorLineEdit->text();
    QString length = m_ui->lengthLineEdit->text();
    int rating = m_ui->horizontalSlider->value();

    if(name!="" && author!="" && length!="")
    {
        input.setName(name);
        input.setAuthor(author);
        input.setLength(length);
        input.setRating(rating);

    }

    this->close();
}

void SongDialog::on_buttonBox_rejected() //if pressed button Отмена
{
    this->close();
}

QString GetRandomString()
{
   const QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
   const int randomStringLength = 14; // assuming you want random strings of 14 characters

   QString randomString;
   for(int i=0; i<randomStringLength; ++i)
   {
       //int index = qrand() % possibleCharacters.length();
       int index = QRandomGenerator::global()->generate() % possibleCharacters.length();
       QChar nextChar = possibleCharacters.at(index);
       randomString.append(nextChar);
   }
   return randomString;
}
