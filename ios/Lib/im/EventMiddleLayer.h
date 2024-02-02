//
//  LoginEvenMiddle.h
//  first
//
//  Created by jum on 28/9/14.
//  Copyright (c) 2014年 hsing. All rights reserved.
//

#ifndef __LOGIN_EVENT_MIDDLE_H__
#define __LOGIN_EVENT_MIDDLE_H__

#include <string>
#include "locate.h"

class CLoginEventMiddle
{
public:
    ~CLoginEventMiddle();
    static CLoginEventMiddle& getInstance();
    
    void OnLoginSuccess(const std::string &reportdata);
    void OnLoginFailed(unsigned int reason, int loginType, const std::string &reportdata);
    void OnDisconnect(unsigned int reason);
    void OnSetPropertyResult(UInt32 requestId, UInt32 result);
private:
    CLoginEventMiddle();
};

class CIMEventMiddle
{
public:
    ~CIMEventMiddle();
    static CIMEventMiddle& getInstance();
    
    void onIMCreated();
    void onIMConnectSuccess();
    void onIMConnectClose();
    void onMessage(UInt32 userId,
                   const std::string &name,
                   UInt8 type,
                   UInt32 timestamp,
                   const std::string &body,
                   const std::string &info,
                   bool isOffline,
                   UInt64 msgId,
                   UInt64 riskStatus);
    
    void onSysMessage(int type,const std::string& body);
    
    void onRequestResult(UInt32 type, UInt32 requestId, UInt32 reason);
private:
    CIMEventMiddle();
};

class CLocateEventMiddile
{
public:
    ~CLocateEventMiddile();
    static CLocateEventMiddile& getInstance();
    
    void OnConnected();
    void OnClose();
    void OnNearbyUserReply(UInt32 result, const locate::ClientHandler::UserList &users, int requestId);
    void OnUpdateReply(UInt32 result,int requestId);
    void OnCleanReply(UInt32 result, int requestId);
private:
    CLocateEventMiddile();
};

#endif

