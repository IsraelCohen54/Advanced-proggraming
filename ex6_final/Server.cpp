#include "Server.h"
#include <unistd.h>
#include <thread>
using namespace std;

Server::Server(int port)throw (const char*) {
    fd = socket(AF_INET,SOCK_STREAM,0);
    if(fd<0)
        throw ("socket failed");
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);
    if(bind(fd, (struct sockaddr*)&server, sizeof(server))<0)
        throw ("bind failure");
    if(listen(fd,3) < 0)
        throw ("listen failure");
}
void Server::start(ClientHandler& ch)throw(const char*){
    //cout<<"t was created!"<<endl;
    t = new thread([&ch,this](){
        while(run) {
            //cout<<"waiting for a new client\n";
            socklen_t clientSize = sizeof(client);
            //cout<<"waiting before"<<endl;
            int aClient = accept(fd, (struct sockaddr *) &client, &clientSize);
            //cout<<"waiting after\n"<<endl;
            if (aClient < 0)
                throw ("accept failure");
            //cout<<"client connected!\n"<<endl;
            ch.handle(aClient);
            //cout<<"close it1"<<endl;
            //this_thread::sleep_for (chrono::seconds(1));
            close(aClient);
            //cout<<"goes to sleep for 1 sec"<<endl;
            this_thread::sleep_for (chrono::milliseconds(200));
            //std::this_thread::sleep_for (std::chrono::seconds(1));
        }
        //cout<<"close it2"<<endl;
        //this_thread::sleep_for (chrono::seconds(1));
        } 
    );
}

void Server::stop(){
    run = false;
    
    //change_f(true);
    //if (t!=NULL)
        //delete t;
       // this->stop();
	t->join(); // do not delete this!
    //this_thread::sleep_for (chrono::seconds(1));
    close(fd);
}

Server::~Server() {
}