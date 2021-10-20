#ifndef SONGLIST_H
#define SONGLIST_H

#include <QString>
#include <QList>
#include <QPixmap>
#include <iostream>

class song
{
private:
    QString name;
    QString author;
    QString length;
    int rating;
    QString imgPath;
public:
    song();
    void setName(QString name){this->name=name;};
    void setAuthor(QString author){this->author=author;};
    void setLength(QString length){this->length=length;};
    void setRating(int rating){this->rating=rating;};
    void setImgPath(QString path){this->imgPath=path;};
    QString getName(){return name;};
    QString getAuthor(){return author;};
    QString getLength(){return length;};
    QString getImgPath(){return imgPath;};
    int getRating(){return rating;};
    void show();
    ~song();
};

class songList
{
private:
    int songsCount;
    QList<song> songs;
public:
    songList();
    song getItem(int i){return songs.at(i);};
    void insert(song data);
    void removeItem(int id);
    int getSongsCount(){return songsCount;};
    std::string getName(int i){return songs[i].getName().toStdString();};
    std::string getAuthor(int i){return songs[i].getAuthor().toStdString();};
    std::string getLength(int i){return songs[i].getLength().toStdString();};
    std::string getImgPath(int i){return songs[i].getImgPath().toStdString();};
    int getRating(int i){return songs[i].getRating();};
    void sort();
    static bool sortComparator(const song &v1, const song &v2)
    {
        song b1=v1;
        song b2=v2;
        return b1.getRating()>b2.getRating();
    }
    ~songList();
};

#endif // SONGLIST_H
