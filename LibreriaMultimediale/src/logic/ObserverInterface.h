//
// Created by adifi on 24/02/2025.
//

#ifndef OBSERVERINTERFACE_H
#define OBSERVERINTERFACE_H

class ObserverInterface {
    public:
        virtual ~ObserverInterface() = default;
        virtual void addW_notification(QWidget* widget) = 0;
        virtual void removeW_notification() = 0;
};



#endif //OBSERVERINTERFACE_H
