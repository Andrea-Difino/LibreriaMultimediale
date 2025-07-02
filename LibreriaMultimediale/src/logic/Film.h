//
// Created by ANDREA on 17/12/2024.
//

#ifndef FILM_H
#define FILM_H
#include "Item.h"
#include <vector>

class Film : public Item {
    public:
        explicit Film(const std::string &title,const std::string& des,const std::string &g, unsigned int year, unsigned int time, const std::string& img_path);
        ~Film() override = default;

        std::string getGenre() const;
        unsigned int getTime() const;
        unsigned int getHours() const;
        unsigned int getMinutes() const;
        unsigned int getSeconds() const;

        void setGenre(const std::string &g);
        void setTime(unsigned int seconds);

        void accept(VisitorInterface *visitor) override;

        std::string getExtendedLength() const;

        void displayInfo() const override;

        static std::vector<std::string> tipology;
    private:
        std::string genre;
        unsigned int time;
};


#endif //FILM_H
