#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include "NetworkObserver.h"

#include <vector>
#include <string>

class NetworkManager
{
public:
    NetworkManager();

    void connect();
    void sendString(const std::string & message);

    enum class ConnectionStatus{Disconnect, Prohibited, Connected};
    ConnectionStatus getNetworkStatus();

private:


    ConnectionStatus connectionStatus_;
    std::vector<NetworkObserver> networkObservers_;
};

#endif // NETWORKMANAGER_H
