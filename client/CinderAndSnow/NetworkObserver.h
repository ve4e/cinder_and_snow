#ifndef NETWORKOBSERVER_H
#define NETWORKOBSERVER_H

class NetworkObserver
{
public:
    NetworkObserver();

    virtual void handleConnectionStatusChange() = 0;

    virtual ~NetworkObserver();
};

#endif // NETWORKOBSERVER_H
