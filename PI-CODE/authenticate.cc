// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2020-2021 Intel Corporation. All Rights Reserved.

#include "../../include/RealSenseID/FaceAuthenticator.h"
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <iostream>
#include <chrono>
#include <thread>
#include <future>




char ipOmni[50] ;
int  portOmni=0 ;
char readerOmni[50] ;
char usbPort[200]; 


int sendTcp(const char* pUser);
 


void addLog( char *pErr) ;

void addLog( char *pErr)
{
    std::cout << pErr  << std::endl;
}


class MyAuthClbk : public RealSenseID::AuthenticationCallback
{
public:
    void OnResult(const RealSenseID::AuthenticateStatus status, const char* user_id) override
    {
        addLog("got call back call");
        if (status == RealSenseID::AuthenticateStatus::Success)
          {
                std::cout << "Authenticated " << user_id << std::endl;
               auto futureFunction= std::async(sendTcp,user_id);

          } 
           if (status == RealSenseID::AuthenticateStatus::MaskDetectedInHighSecurity)
           {
                std::cout << "Authenticated " << user_id << std::endl;
                auto futureFunction= std::async(sendTcp,user_id);
           }

       
    }

    void OnHint(const RealSenseID::AuthenticateStatus hint) override
    {
        std::cout << "OnHint " << hint << std::endl;
    }

    void OnFaceDetected(const std::vector<RealSenseID::FaceRect>& faces, const unsigned int ts) override
    {
        for (auto& face : faces)
        {
            printf("** Detected face %u,%u %ux%u (timestamp %u)\n", face.x, face.y, face.w, face.h, ts);
        }
    }
};

// As seen on http://www.di.uniba.it/~reti/LabProRete/Interazione(TCP)Client-Server_Portabile.pdf
#if defined WIN32
#include <winsock.h>
#else
#define closesocket close
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif
#include <stdio.h>
#include <map>
#include <string>
using namespace  std;

#define BUFFERSIZE 512
#define PROTOPORT  5193            // Default port number
#pragma comment(lib, "ws2_32.lib") // Winsock Library
void ClearWinSock()
{
#if defined WIN32
    WSACleanup();
#endif
}


std::string buildJson(std::map<std::string, std::string>&  map)
{
    std::string json = "{";
    int index = 0;
    for (std::map<string, string>::iterator it = map.begin(); it != map.end(); ++it)
    {
        index++;
        string prop = it->first.c_str();
        string val = it->second.c_str();
        // json += "\r\n";
        json += '"';
        json += prop;
        json += '"';
        json += ":";
        json += '"';
        json += val;
        json += '"';
        if (index < map.size())
            json += ',';
    }
    //	json += "\r\n";
    json += "}";
   

    return json;
}
void ErrorHandler(char* errorMessage)
{
    printf(errorMessage);
}



int sendTcp(const char* pUser)
{

        addLog(" send tcp 1");
try
{
  //  char* ip = "192.168.0.64";
//int port = 8093;
//char* reader = "11";

#if defined WIN32
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0)
    {
        addLog("error at WSASturtup\n");
        return 0;
    }
#endif

        addLog(" send tcp 2");
    // Socket creation
    int Csocket;
    Csocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (Csocket < 0)
    {
		addLog("socket creation failed");
        ErrorHandler("socket creation failed.\n");
        closesocket(Csocket);
        ClearWinSock();
        return 0;
    }

        addLog(" send tcp 333");
    // Server address construction
    struct sockaddr_in sad;
     addLog(" send tcp 3.1");
    memset(&sad, 0, sizeof(sad));
    sad.sin_family = AF_INET;
    sad.sin_addr.s_addr = inet_addr(ipOmni); // server IP
    sad.sin_port = htons(portOmni);                       // Server port
    // Connection to the server
     addLog(" going to connect...");
    if (connect(Csocket, (struct sockaddr*)&sad, sizeof(sad)) < 0)
    {
		addLog("Failed to connect.\n");
        ErrorHandler("Failed to connect.\n");
        closesocket(Csocket);
        ClearWinSock();
        return 0;
    }
 addLog(" send tcp 4");
   //@ char* inputString = "prova"; // String to send

    std::map<std::string, std::string> map;
    map["cmd"] = "Vision";
    map["badgeName"] = pUser;
    map["readerNeuron"] = readerOmni;
    string json = buildJson(map);
 
 addLog(" send tcp 3");
    char* inputString = const_cast<char*>(json.c_str());

    int stringLen = strlen(inputString);
 addLog(" send tcp 5");
    if (send(Csocket, inputString, stringLen, 0) != stringLen)
    {
		addLog("send() sent a different number of bytes than expected");
        ErrorHandler("send() sent a different number of bytes than expected");
        closesocket(Csocket);
        ClearWinSock();
        return 0;
    }
 addLog(" send tcp 6");
    closesocket(Csocket);
    ClearWinSock();
	addLog("tcp sent succsfully");
    return 1;

    int bytesRcvd;
    int totalBytesRcvd = 0;
    char buf[BUFFERSIZE]; // buffer for data from the server
    printf("Received: "); // Setup to print the echoed string

    while (totalBytesRcvd < stringLen)
    {
        if ((bytesRcvd = recv(Csocket, buf, BUFFERSIZE - 1, 0)) <= 0)
        {
            ErrorHandler("recv() failed or connection closed prematurely");
            closesocket(Csocket);
            ClearWinSock();
            return 0;
        }
        totalBytesRcvd += bytesRcvd; // Keep tally of total bytes
        buf[bytesRcvd] = '\0';       // Add \0 so printf knows where to stop
        printf("%s", buf);           // Print the echo buffer
    }
    // Closing connection
    closesocket(Csocket);
    ClearWinSock();
    printf("\n");
    system("pause");
    return (0);
	}
	catch(...)
	{
		addLog("excpetion in tcpsend");
	}
	
}




int main(int argc, char *argv[])
{
while(true)
{
    try{
	
	std::cout << "argc " << argc << std::endl;
     
    if(argc==5)
    {
        strcpy(ipOmni , argv[1])  ;
        portOmni=atol(argv[2]) ;
        strcpy(readerOmni,argv[3] );
		strcpy(usbPort,argv[4] );

        std::cout << "ipOmni " << ipOmni << std::endl;
        std::cout << "portOmni " << portOmni << std::endl;
        std::cout << "readerOmni " << readerOmni << std::endl;
		std::cout << "usbPort " << usbPort << std::endl;
       
    }
   

    //sendTcp("uri");
    RealSenseID::FaceAuthenticator authenticator;

   // auto status = authenticator.Connect({"/dev/ttyACM0"});
    auto status = authenticator.Connect({usbPort});

    if (status != RealSenseID::Status::Ok)
    {
        std::cout << "Failed connecting with status " << status << std::endl;
        return 1;
    }
    while(true)
    {
        MyAuthClbk auth_clbk;
        authenticator.Authenticate(auth_clbk);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
	}
	catch(...)
	{
	}
}
   
}
//printfERROR