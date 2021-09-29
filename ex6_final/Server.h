#ifndef SERVER_H_
#define SERVER_H_

#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "commands.h"
#include "CLI.h"

using namespace std;
static volatile bool run = true;


//static pthread_mutex_t lock;

class SocketIO: public DefaultIO {
public:
    int serverFD;
    SocketIO(int serverFDD):serverFD(serverFDD){}

    virtual string read(){
        
        //pthread_mutex_lock(&lock);
        string serverInput="";
        char c=0;
        bool state=false;
        int counter=0;
        volatile char six='a';
        ::read(serverFD,&c,sizeof(char));
        while(c!='\n'){
            serverInput+=c;
            ::read(serverFD,&c,sizeof(char));
            //cout<<"c= "<<c;
            
            if(c=='6'&&six=='6'){
                counter+=1;
            }
            six = c;
            if (counter==5){
                serverInput="6";
                return serverInput; 
            }
        }
        //pthread_mutex_unlock(&lock);
        return serverInput;
    }
    virtual void write(string text){
        ::write(serverFD,text.c_str(),text.length());
        ::write(serverFD,"\n",1);
        char c=text[text.length()-1];
        //cout<<text[text.length()-1]<<endl;
        //if(!(text[text.length()-1]=='\n'))
         //   ::write(serverFD,"\n",1);
      //  ::write(serverFD,"\n",1);
    }
    virtual void write(float f){
    }
    virtual void read(float* f){
    }
    //void close(){
    //}
    ~SocketIO(){
      //  close();
    }
    

};
/*static void change_f(bool state){
    stopFlag=state;
}*/

// edit your ClientHandler interface here:
class ClientHandler{
    public:
    virtual void handle(int clientID)=0;
};

// you can add helper classes here and implement on the cpp file
// edit your AnomalyDetectionHandler class here
class AnomalyDetectionHandler:public ClientHandler{
	public:
    virtual void handle(int clientID){

        SocketIO sio (clientID);
        CLI cli (&sio);
        cli.start();
    }
};

// implement on Server.cpp
class Server {
public:
	thread* t; // the thread to run the start() method in
    struct sockaddr_in server;
    struct sockaddr_in client;
    int fd;
	Server(int port) throw (const char*);
	virtual ~Server();
	void start(ClientHandler& ch)throw(const char*);
	void stop();
};
#endif /* SERVER_H_ */
