//
//  LoginEvenMiddle.m
//  first
//
//  Created by jum on 28/9/14.
//  Copyright (c) 2014年 hsing. All rights reserved.
//
#include "platform.hpp"
#import "EventMiddleLayer.h"
#include "chat_clienthandler_impl.h"
#import "IMClient.h"
////////////////////////////////////CLoginEventMiddle/////////////////////////////////////

CLoginEventMiddle::CLoginEventMiddle()
{
    
}

CLoginEventMiddle::~CLoginEventMiddle()
{
    
}

CLoginEventMiddle& CLoginEventMiddle::getInstance()
{
    static CLoginEventMiddle s_event;
    return s_event;
}

void CLoginEventMiddle::OnLoginSuccess(const std::string &reportdata)
{
    [[IMClient shared].handler im_onLoginSuccess:[NSString stringWithFormat:@"%s",reportdata.c_str()]];
}

void CLoginEventMiddle::OnLoginFailed(unsigned int reason, int loginType,const std::string &reportdata)
{
    [[IMClient shared].handler im_onLoginFailed:reason loginType:loginType report:[NSString stringWithFormat:@"%s",reportdata.c_str()]];
}

void CLoginEventMiddle::OnDisconnect(unsigned int reason)
{
    [[IMClient shared].handler im_onDisconnect:reason];
}

void CLoginEventMiddle::OnSetPropertyResult(UInt32 requestId, UInt32 result)
{
    [[IMClient shared].handler im_onSetPropertyResult:requestId withResult: result];
}

///////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////CIMEventMiddle/////////////////////////////////////

CIMEventMiddle::CIMEventMiddle(){}

CIMEventMiddle::~CIMEventMiddle(){}
CIMEventMiddle& CIMEventMiddle::getInstance()
{
    static CIMEventMiddle s_imEvent;
    return s_imEvent;
}

void CIMEventMiddle::onIMCreated()
{
//    UInt64 msgId = [[ECIMMsgIdTable km_sharedInstance] currentMaxOfflineMsgId];
//    rtalk_wrap::CChatClientHandlerImpl::GetInstance().SetOffMsgId(msgId);
}

void CIMEventMiddle::onIMConnectSuccess()
{
    [[IMClient shared].handler im_onIMConnectSuccess];
}

void CIMEventMiddle::onIMConnectClose()
{
    [[IMClient shared].handler im_onIMConnectClose];
}

void CIMEventMiddle::onMessage(UInt32 userId,
                               const std::string &name,
                               UInt8 type,
                               UInt32 timestamp,
                               const std::string &body,
                               const std::string &info,
                               bool isOffline,
                               UInt64 msgId,
                               UInt64 riskStatus)
{
    [[IMClient shared].handler im_onMessage:userId
                                         withUserName:[NSString stringWithUTF8String:name.c_str()]
                                             withType:type
                                        withTimeStamp:timestamp
                                          withMessage:[NSString stringWithUTF8String:body.c_str()]
                                             withInfo:[NSString stringWithUTF8String:info.c_str()]
                                          withOffline:isOffline
                                                msgId:msgId
                                           riskStatus:riskStatus];
}

void CIMEventMiddle::onSysMessage(int type,const std::string& body)
{
    [[IMClient shared].handler im_onSysMessage:type
                                             withMessage:[NSString stringWithUTF8String:body.c_str()]];
}


void CIMEventMiddle::onRequestResult(UInt32 type, UInt32 requestId, UInt32 reason)
{
    [[IMClient shared].handler im_onRequestResult:type
                                              withRequestId:requestId
                                                 withreason:reason];

}

//////////////////////////////////////////////////////////////////////////////////////////

CLocateEventMiddile::CLocateEventMiddile(){}
CLocateEventMiddile::~CLocateEventMiddile(){}

CLocateEventMiddile& CLocateEventMiddile::getInstance()
{
    static CLocateEventMiddile s_locate;
    return s_locate;
}

void CLocateEventMiddile::OnConnected()
{
    [[IMClient shared].handler im_onClose];
}

void CLocateEventMiddile::OnClose()
{
    [[IMClient shared].handler im_onClose];
}

void CLocateEventMiddile::OnNearbyUserReply(UInt32 result, const locate::ClientHandler::UserList &users, int requestId)
{
    NSArray* locateUsers = nil;
    
    int userSize = (int)users.size();
    if(userSize > 0)
    {
        std::list<locatep::UserInfo>::const_iterator it = users.begin();
        NSMutableArray* uu = [[NSMutableArray alloc] init];
        
     
        for(;it != users.end(); it++)
        {
//            NearlyUserInfo* info = [[NearlyUserInfo alloc] init];
//
//            info.uid = it->GetUserId();
//            info.distance = it->GetDistance();
//            info.sex = it->GetSex();       //性别
//
//            [uu addObject:info];
        }
        
        locateUsers = uu;
    }

    [[IMClient shared].handler im_onNearbyUserReply:result withUsers:locateUsers withRequestId:requestId];
}

void CLocateEventMiddile::OnUpdateReply(UInt32 result,int requestId)
{
    [[IMClient shared].handler im_onUpdateReply:result withRequestId:requestId];
}

void CLocateEventMiddile::OnCleanReply(UInt32 result, int requestId)
{
    [[IMClient shared].handler im_onCleanReply:result withRequestId:requestId];
}


///////////////////////////////////CLocateEventMiddile////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////









