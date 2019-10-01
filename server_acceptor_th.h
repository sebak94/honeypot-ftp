#ifndef __ACCEPTOR_TH_H__
#define __ACCEPTOR_TH_H__

#include "common_thread.h"
#include "common_socket.h"
#include "server_ftp.h"

class AcceptorTh: public Thread {
    private:
    FTP *ftp;
    Socket skt;
    bool keep_accepting;

    public:
    AcceptorTh(const char *service, FTP *ftp);
    virtual void run() override;
    void stop();
    ~AcceptorTh();
};

#endif
