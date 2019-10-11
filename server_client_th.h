#ifndef __CLIENT_TH_H__
#define __CLIENT_TH_H__

#include "common_thread.h"
#include "common_socket.h"
#include "server_ftp.h"
#include <string>
#include <vector>
#include <atomic>

class ClientTh: public Thread {
    private:
    std::atomic<bool> keep_talking;
    std::atomic<bool> is_running;
    Client me;
    Socket *peer;
    FTP *ftp;

    void receiveCommand(std::vector<char> &command);
    void sendResponse(std::string &response);
    std::string handleCommand(std::string &cmd, bool *should_stop_after_send);

    public:
    ClientTh(Socket *peer, FTP *ftp);
    virtual void run() override;
    void stop();
    bool isDead();
    ~ClientTh();
};

#endif
