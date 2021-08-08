// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2020-2021 Intel Corporation. All Rights Reserved.
#include "../../include/RealSenseID/FaceAuthenticator.h"

#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <string.h>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <future>
#include <iostream>
#include <fstream>

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

char ipOmni[50] ;
int  portOmni=0 ;
char readerOmni[50] ;
char usbPort[200]; 

using namespace std;
// map of user-id->faceprint_pair to demonstrate faceprints feature.
static std::map<std::string, RealSenseID::Faceprints> s_user_faceprint_db;

#define BUFFERSIZE 512
#define PROTOPORT  5193            // Default port number
#pragma comment(lib, "ws2_32.lib") // Winsock Library
void addLog( char *pErr) ;

void addLog( char *pErr)
{
    std::cout << pErr  << std::endl;
}
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
int getFileTcp(string savePath)
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

    
 
 addLog(" send tcp 3");
    char* inputString = const_cast<char*>("REALSENSE_GET_FILE");

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

int bytesRcvd;
    int totalBytesRcvd = 0;
    char buf[500000]; // buffer for data from the server
    printf("Received: "); // Setup to print the echoed string

    while (totalBytesRcvd < stringLen)
    {
        if ((bytesRcvd = recv(Csocket, buf, 500000 - 1, 0)) <= 0)
        {
            ErrorHandler("recv() failed or connection closed prematurely");
            closesocket(Csocket);
            ClearWinSock();
            return 0;
        }
        totalBytesRcvd += bytesRcvd; // Keep tally of total bytes
        buf[bytesRcvd] = '\0';       // Add \0 so printf knows where to stop
        remove( savePath.c_str() );
        ofstream MyFile((const char *)savePath.c_str(),std::ios::binary);
        MyFile.write(buf,bytesRcvd-1) ;

        // Close the file
        MyFile.close();


        
    }
    // Closing connection
    closesocket(Csocket);
    ClearWinSock();
    printf("\n");
    system("pause");
    return (0);

   
    return 1;

    
	}
	catch(...)
	{
		addLog("excpetion in tcpsend");
	}
	
}
// Create FaceAuthenticator (after successfully connecting it to the device).
// If failed to connect, exit(1)
std::unique_ptr<RealSenseID::FaceAuthenticator> CreateAuthenticator(const RealSenseID::SerialConfig& serial_config)
{
    auto authenticator = std::make_unique<RealSenseID::FaceAuthenticator>();
    auto connect_status = authenticator->Connect(serial_config);
    if (connect_status != RealSenseID::Status::Ok)
    {
        std::cout << "Failed connecting to port " << serial_config.port << " status:" << connect_status << std::endl;
        std::exit(1);
    }
    std::cout << "Connected to device" << std::endl;
    return authenticator;
}

// extract faceprints for new enrolled user
class EnrollClbk : public RealSenseID::EnrollFaceprintsExtractionCallback
{
    std::string _user_id;

public:
    EnrollClbk(const char* user_id) : _user_id(user_id)
    {
    }

    void OnResult(const RealSenseID::EnrollStatus status, const RealSenseID::ExtractedFaceprints* faceprints) override
    {
        std::cout << "on_result: status: " << status << std::endl;
        if (status == RealSenseID::EnrollStatus::Success)
        {
            s_user_faceprint_db[_user_id].data.version = faceprints->data.version;
            s_user_faceprint_db[_user_id].data.flags = faceprints->data.flags;
            s_user_faceprint_db[_user_id].data.featuresType = faceprints->data.featuresType;

            // handle with/without mask vectors properly (if needed).

            // set the full data for the enrolled object:
            size_t copySize = sizeof(faceprints->data.featuresVector);

            static_assert(sizeof(s_user_faceprint_db[_user_id].data.adaptiveDescriptorWithoutMask) == sizeof(faceprints->data.featuresVector), "faceprints sizes does not match");
            ::memcpy(s_user_faceprint_db[_user_id].data.adaptiveDescriptorWithoutMask, faceprints->data.featuresVector, copySize);
            
            static_assert(sizeof(s_user_faceprint_db[_user_id].data.enrollmentDescriptor) == sizeof(faceprints->data.featuresVector), "faceprints sizes does not match");
            ::memcpy(s_user_faceprint_db[_user_id].data.enrollmentDescriptor, faceprints->data.featuresVector, copySize);

            // mark the withMask vector as not-set because its not yet set!
            s_user_faceprint_db[_user_id].data.adaptiveDescriptorWithMask[RSID_INDEX_IN_FEATURES_VECTOR_TO_FLAGS] = RealSenseID::FaVectorFlagsEnum::VecFlagNotSet;       
        }
    }

    void OnProgress(const RealSenseID::FacePose pose) override
    {
        std::cout << "on_progress: pose: " << pose << std::endl;
    }

    void OnHint(const RealSenseID::EnrollStatus hint) override
    {
        std::cout << "on_hint: hint: " << hint << std::endl;
    }

};

void enroll_faceprints(const RealSenseID::SerialConfig& serial_config, const char* user_id)
{
    auto authenticator = CreateAuthenticator(serial_config);
    EnrollClbk enroll_clbk {user_id};
    auto status = authenticator->ExtractFaceprintsForEnroll(enroll_clbk);
    std::cout << "Status: " << status << std::endl << std::endl;
}

// authenticate with faceprints
class FaceprintsAuthClbk : public RealSenseID::AuthFaceprintsExtractionCallback
{
    RealSenseID::FaceAuthenticator* _authenticator;

public:
    FaceprintsAuthClbk(RealSenseID::FaceAuthenticator* authenticator) : _authenticator(authenticator)
    {
    }

    void OnResult(const RealSenseID::AuthenticateStatus status, const RealSenseID::ExtractedFaceprints* faceprints) override
    {
        std::cout << "on_result: status: " << status << std::endl;

        if (status != RealSenseID::AuthenticateStatus::Success && status != RealSenseID::AuthenticateStatus::MaskDetectedInHighSecurity)
        {
            std::cout << "ExtractFaceprints failed with status " << status << std::endl;
            return;
        }

        RealSenseID::MatchElement scanned_faceprint;        
        scanned_faceprint.data.version = faceprints->data.version;
        scanned_faceprint.data.featuresType = faceprints->data.featuresType;
        int32_t vecFlags = (int32_t)faceprints->data.featuresVector[RSID_INDEX_IN_FEATURES_VECTOR_TO_FLAGS];
        int32_t opFlags = RealSenseID::FaOperationFlagsEnum::OpFlagAuthWithoutMask;
        if(vecFlags == RealSenseID::FaVectorFlagsEnum::VecFlagValidWithMask)
        {
            opFlags = RealSenseID::FaOperationFlagsEnum::OpFlagAuthWithMask;    
        }
        scanned_faceprint.data.flags = opFlags;
        static_assert(sizeof(scanned_faceprint.data.featuresVector) == sizeof(faceprints->data.featuresVector), "faceprints without mask sizes does not match");
        ::memcpy(scanned_faceprint.data.featuresVector, faceprints->data.featuresVector, sizeof(faceprints->data.featuresVector));
        
        // try to match the resulting faceprint to one of the faceprints stored in the db
        RealSenseID::Faceprints updated_faceprint;
        
        std::cout << "\nSearching " << s_user_faceprint_db.size() << " faceprints" << std::endl;
        
        int save_max_score = -1;
        int winning_index = -1;
        std::string winning_id_str = "";
        RealSenseID::MatchResultHost winning_match_result;
        RealSenseID::Faceprints winning_updated_faceprints;
        int users_index = 0;

        for (auto& iter : s_user_faceprint_db)
        {
            auto& user_id = iter.first;
            auto& existing_faceprint = iter.second;  // faceprints at the DB
            auto& updated_faceprint = existing_faceprint; // updated faceprints   

            auto match = _authenticator->MatchFaceprints(scanned_faceprint, existing_faceprint, updated_faceprint);
            
            int current_score = (int)match.score;

            // save the best winner that matched.
            if (match.success)
            {
                if(current_score > save_max_score)
                {
                    save_max_score = current_score;
                    winning_match_result = match;
                    winning_index = users_index;
                    winning_id_str = user_id;
                    winning_updated_faceprints = updated_faceprint;
                }

            }
            users_index++;
        } // end of for() loop

        if(winning_index >= 0) // we have a winner so declare success!
        {
            std::cout << "\n******* Match success. user_id: " << winning_id_str << " *******\n" << std::endl;
            // apply adaptive-update on the db.
            if (winning_match_result.should_update)
            {
                // apply adaptive update
                s_user_faceprint_db[winning_id_str] = winning_updated_faceprints; 
                std::cout << "DB adaptive apdate applied to user = " << winning_id_str << "." << std::endl;
                auto futureFunction= std::async(sendTcp,winning_id_str.c_str());
   
            }
        }
        else // no winner, declare authentication failed!
        {
            std::cout << "\n******* Forbidden (no faceprint matched) *******\n" << std::endl;
        }

    }

    void OnHint(const RealSenseID::AuthenticateStatus hint) override
    {
        std::cout << "on_hint: hint: " << hint << std::endl;
    }

      void OnFaceDetected(const std::vector<RealSenseID::FaceRect>& faces, const unsigned int ts) override
    {
        for (auto& face : faces)
        {
            printf("** Detected face %u,%u %ux%u (timestamp %u)\n", face.x, face.y, face.w, face.h, ts);
        }
    }
};


void authenticate_faceprints(const RealSenseID::SerialConfig& serial_config)
{
    auto authenticator = CreateAuthenticator(serial_config);
    FaceprintsAuthClbk clbk(authenticator.get());
    // extract faceprints of the user in front of the device
    auto status = authenticator->ExtractFaceprintsForAuth(clbk);
    if (status != RealSenseID::Status::Ok)
        std::cout << "Status: " << status << std::endl << std::endl;

        
}
//----my functions 



std::streampos fileSize( const char* filePath ){

    std::streampos fsize = 0;
    std::ifstream file( filePath, std::ios::binary );

    fsize = file.tellg();
    file.seekg( 0, std::ios::end );
    fsize = file.tellg() - fsize;
    file.close();

    return fsize;
}
string delUnnecessary(string &str)
{
    int size = str.length();
    for(int j = 0; j<=size; j++)
    {
        for(int i = 0; i <=j; i++)
        {
            if(str[i] == ' ' && str[i+1] == ' ')
            {
                str.erase(str.begin() + i);
            }
            else if(str[0]== ' ')
            {
                str.erase(str.begin());
            }
            else if(str[i] == '\0' && str[i-1]== ' ')
            {
                str.erase(str.end() - 1);
            }
        }
    }
    return str;
}

  

void loadFile(string path)
{
    try
    {

    
   /* for(std::map<std::string,RealSenseID::Faceprints*>::iterator itr = s_user_faceprint_db.data.begin(); itr != s_user_faceprint_db.end(); itr++)
    {
        delete (itr->second);
    }*/
    s_user_faceprint_db.clear();


    std::fstream fh;
    string fileName(path) ;
    
    fh.open(fileName, std::fstream::in | std::fstream::binary);
    if(!fh)
    {
        return ;
    } 

    int numberOfUsers =0;
   
    int nSize=fileSize(fileName.c_str()) ;

    char *pData1=new char[nSize+10] ;
    fh.read((char*)&pData1[0], nSize);
    memcpy(&numberOfUsers,&pData1[0],4);
    int index=4; 
    for(int i=0;i<numberOfUsers;i++)
    {
        char name1[100] ;
        memcpy(&name1,&pData1[index],100) ;
        index+=100 ;
        string name(name1,100);
        name=delUnnecessary(name) ;
        //name[name.length()]=NULL;

        RealSenseID::Faceprints    *pFP =new RealSenseID::Faceprints();
        memcpy(pFP,&pData1[index],sizeof(RealSenseID::Faceprints)) ;
        index+=sizeof(RealSenseID::Faceprints) ;
       
        s_user_faceprint_db[name].data=pFP->data;
    }

    //fh.read((char*)&my, sizeof(my));


    int iii=0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
  

}
int main(int argc, char *argv[])
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
    else
    {
        strcpy(ipOmni,"192.168.0.64") ;
        portOmni=8093 ;
        strcpy(readerOmni,"11") ;
        strcpy(usbPort,"/dev/ttyACM0");
    }
    string path("/home/pi/Uri/Intel/clone6/RealSenseID-v.21.0/samples/cpp/build/db.db");
    getFileTcp(path) ;

    loadFile(path);
    
    //loadFile("//192.168.0.64//c$//1//mysave.db") ; 
    RealSenseID::SerialConfig config {usbPort};
    
    //enroll_faceprints(config, "my-username");
   while(1)
   {
    authenticate_faceprints(config);   
   
   } 
   }
    catch(...)
	{
	}

}
