//
//  test.m
//  Runner
//
//  Created by Dsen on 2024/1/31.
//

#import "IMClientHandler.h"
#import "Runner-Swift.h"

@interface IMClientHandler ()
@property (nonatomic, strong,readonly) FlutterMethodChannel *channel;

@end

@implementation IMClientHandler

- (instancetype)init {
    self = [super init];
    if(self){

    }
    return self;
}

-(FlutterMethodChannel *)channel {
    AppDelegate *deletate = (AppDelegate *)[UIApplication sharedApplication].delegate;
    return deletate.imChannel;
}

///MARK: - 登录代理回调
- (void)im_onCleanReply:(NSUInteger)result withRequestId:(NSInteger)requestId {
    
}

- (void)im_onClose {
    
}

- (void)im_onConnected {
    
}

- (void)im_onDisconnect:(NSInteger)reason {
    
}

- (void)im_onIMConnectClose {
    
}

- (void)im_onIMConnectSuccess {
    
}

- (void)im_onLoginFailed:(NSInteger)reason loginType:(NSInteger)loginType report:(nonnull NSString *)msg {
    [self.channel invokeMethod:@"im_onLoginFailed" arguments:@{@"loginType":@(loginType),@"msg":msg,@"code":@(reason)}];
}

- (void)im_onLoginSuccess:(nonnull NSString *)msg {
    [self.channel invokeMethod:@"im_onLoginSuccess" arguments:@{@"msg":msg}];

}

- (void)im_onMessage:(NSUInteger)userId withUserName:(nonnull NSString *)name withType:(NSInteger)type withTimeStamp:(NSUInteger)timestamp withMessage:(nonnull NSString *)message withInfo:(nonnull NSString *)info withOffline:(Boolean)isOffline msgId:(UInt64)msgId riskStatus:(UInt64)riskStatus {
    [self.channel invokeMethod:@"im_onMessage" arguments:@{@"userId":@(userId),
                                                           @"name":name ?: @"",
                                                           @"type":@(type),
                                                           @"timestamp":@(timestamp),
                                                           @"message":message ?: @"",
                                                           @"info":info ?: @"",
                                                           @"isOffline":@(isOffline),
                                                           @"msgId":@(msgId),
                                                           @"riskStatus":@(riskStatus),
                                                         }];

}

- (void)im_onNearbyUserReply:(NSUInteger)result withUsers:(nonnull NSArray *)users withRequestId:(NSInteger)requestId {
    
}

- (void)im_onRequestResult:(NSUInteger)type withRequestId:(NSUInteger)requestId withreason:(NSUInteger)reason {
    
}

- (void)im_onSetPropertyResult:(NSInteger)requestId withResult:(NSInteger)result {
    
}

- (void)im_onSysMessage:(NSInteger)type withMessage:(nonnull NSString *)message {
    
}

- (void)im_onUpdateReply:(NSUInteger)result withRequestId:(NSInteger)requestId {
    
}

@end
