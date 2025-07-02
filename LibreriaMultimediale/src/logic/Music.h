//
// Created by ANDREA on 17/12/2024.
//

#ifndef MUSICA_H
#define MUSICA_H
#include <string>
#include "Item.h"


class Music : public Item {
public:
    Music(const std::string &tit,const std::string &des,const std::string &sing,unsigned int y,unsigned int time, const std::string& img_path);
    ~Music() override;

    void setSinger(std::string sing);
    void setTime(unsigned int seconds);

    unsigned int getTime() const;
    std::string getSinger() const;
    unsigned int getHours() const;
    unsigned int getMinutes() const;
    unsigned int getSeconds() const;
    std::string getExtendedLength() const;

    void accept(VisitorInterface *visitor) override;
    void displayInfo() const override;
private:
    std::string singer;
    unsigned int time;
};


#endif //MUSICA_H
