#pragma once
#include <QDialog>
#include "songlistdialog.h"
#include "songlist.h"

namespace Ui 
{	
class SongDialog;
}

class SongDialog : public QDialog
{
	Q_OBJECT
public:
	SongDialog(QWidget* parent = nullptr);
	~SongDialog();
    song sendData();
    void getSong(song changeble);
private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
	void choosePreview();

	QString copiedPreview(const QString& filePath) const;
	void showPreview(const QString& relativePath) const;
	QString fullImagePath(const QString& relativePath) const;
	
	Ui::SongDialog* m_ui = nullptr;
    const QString m_imageDir = "../images";
    song input;
    song songToChange;
};

