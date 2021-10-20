#include "songlist.h"

songList::songList()
{
    this->songsCount=0;
}

void songList::insert(song data)
{
    songsCount++;
    songs.append(data);
}

void songList::removeItem(int id)
{
    songsCount--;
    songs.removeAt(id);
}

songList::~songList()
{

}

song::song()
{
    this->name="";
    this->author="";
    this->length="";
    this->rating=0;
    this->imgPath="\n";
}

void song::show()
{
    std::cout<<"Name: "<<name.toStdString()<<std::endl;
    std::cout<<"Author: "<<author.toStdString()<<std::endl;
    std::cout<<"Length: "<<length.toStdString()<<std::endl;
    std::cout<<"Rating: "<<rating<<std::endl;
}

void songList::sort()
{
    qSort(songs.begin(), songs.end(), sortComparator);
}

song::~song()
{

}
