//
// Created by ANDREA on 17/12/2024.
//

#ifndef VISORINTERFACE_H
#define VISORINTERFACE_H

class Book;
class Film;
class Music;

class VisitorInterface {
    public:
        virtual void visit(Book* libro) = 0;
        virtual void visit(Film* film) = 0;
        virtual void visit(Music* dvd) = 0;
        virtual ~VisitorInterface() = default;
};




#endif //VISORINTERFACE_H
