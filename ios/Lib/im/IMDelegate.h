//
//  IMDelegate.h
//  Runner
//
//  Created by Dsen on 2024/1/31.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol IMDelegate <NSObject>

-(void)im_onDisconnect:(NSInteger)reason;
-(void)im_onIMConnectSuccess;
-(void)im_onIMConnectClose;

-(void)im_onSetPropertyResult:(NSInteger)requestId
                   withResult:(NSInteger)result;


-(void)im_onLoginSuccess:(NSString *)msg;
-(void)im_onLoginFailed:(NSInteger)reason loginType:(NSInteger)loginType report:(NSString *)msg;

-(void)im_onMessage: (NSUInteger) userId
        withUserName:(NSString*) name
            withType:(NSInteger) type
       withTimeStamp:(NSUInteger) timestamp
         withMessage:(NSString*) message
            withInfo:(NSString*) info
         withOffline:(Boolean) isOffline
               msgId:(UInt64)msgId
          riskStatus:(UInt64)riskStatus;

-(void)im_onSysMessage:(NSInteger) type withMessage:(NSString*) message;

-(void)im_onRequestResult:(NSUInteger) type
          withRequestId:(NSUInteger) requestId
               withreason:(NSUInteger) reason;

-(void)im_onConnected;
-(void)im_onClose;
-(void)im_onNearbyUserReply:(NSUInteger) result
                withUsers:(NSArray*) users
            withRequestId:(NSInteger) requestId;

-(void)im_onUpdateReply:(NSUInteger)result
        withRequestId:(NSInteger)requestId;

-(void)im_onCleanReply:(NSUInteger) result
       withRequestId:(NSInteger) requestId;

@end

NS_ASSUME_NONNULL_END
