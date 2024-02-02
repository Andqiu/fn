//
//  IMClient.m
//  Runner
//
//  Created by Dsen on 2024/1/31.
//

#import "IMClient.h"
#include "platform.hpp"
#include "rtalk/rtalk.h"
#include "os_def.h"
#include "rtalk_clienthandler_impl.h"
#include "chat_clienthandler_impl.h"
#include "locate_clienthandler_impl.h"

@interface IMClient (){
    NSRecursiveLock *_mLock;
    bool     _mEnd;
    bool     _mIsRuning;
    
    CFTimeInterval _arcReportTime;
    NSThread *_mKeepliveThread;

}

@end

@implementation IMClient

+(instancetype)shared {
    static IMClient *client = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        client = [IMClient new];
    });
    return client;
}

-(id)init{
    if(self=[super init]){
        _handler = [IMClientHandler new];
        _mLock = [[NSRecursiveLock alloc] init];
    }
    return self;
}

- (int)start{
    _arcReportTime = CACurrentMediaTime();
    _mIsRuning = true;
    _mKeepliveThread = [[NSThread alloc] initWithTarget:self selector:@selector(run) object:nil];
    [_mKeepliveThread start];
    return 0;
}

- (void)stop {
    _mIsRuning = false;
    int count = 0;

    while(_mKeepliveThread != nil
          && ![_mKeepliveThread isFinished]
          && count < 30)
    {
        [NSThread sleepForTimeInterval:0.10];
        count++;
    }

    _mKeepliveThread = nil;
    
    rtalk_wrap::CRtalkClientHandlerImpl::GetInstance().Stop();
}

- (void)run{
    [[NSThread currentThread] setName:@"keep live"];
    _mEnd = NO;
    while (_mIsRuning){
        @autoreleasepool {
            [NSThread sleepForTimeInterval:0.01];
            [self keepLive];
        }
    }
    _mEnd = YES;
    [[NSThread currentThread] setName:@""];
}

- (void)keepLive {
    [_mLock lock];
    double startTime = timeGetTime();
    if (_mIsRuning) {
        rtalk_wrap::CRtalkClientHandlerImpl::GetInstance().Keeplive();
    }
    double dif = timeGetTime() - startTime;
    
    if (dif > 1.0) {
        NSLog(@"too long time %lf" ,dif);
    }
        
    [_mLock unlock];
}

-(void)loginWithType:(NSInteger)type
                  ip:(NSString *)ip
             account:(NSString *)account
                 pwd:(NSString *)pwd {
    
    NSString *simCode = @"";
    NSString* version = @"IOS,version=8.10.5(50001),system=15.3.1,app=hsing,bundleId=com.km.gz.huange";
    NSString *deviceId = @"D041EC74-8A01-44D6-B8A9-D7F25A54487E";
    NSString *lang = @"zh-Hant";
    NSString *isad = @"0";
    NSString *sysLang = @"zh-Hans-CN";
    
    NSString *pushFlag = @"1";
    NSString *appleKey = @"";

    entryp::Login::Params params;
    if (pushFlag.length) {
        params["pushFlag"] = pushFlag.UTF8String;
    }
    if (deviceId) {
        params["deviceId"] = deviceId.UTF8String;
    }
    if (lang.length) {
        params["lang"] = lang.UTF8String;
    }
    if (sysLang.length) {
        params["sysLang"] = sysLang.UTF8String;
    }
    if (appleKey.length) {
        params["apple_key"] = appleKey.UTF8String;
    }
    if (simCode.length) {
        params["simCode"] = simCode.UTF8String;
    }
    if (isad.length) {
        params["_is_ad"] = isad.UTF8String;
    }
    
    [[IMClient shared] start];
    rtalk_wrap::CRtalkClientHandlerImpl::GetInstance().Login((UInt32)type,
                                                        [ip UTF8String],
                                                        [account UTF8String],
                                                        [pwd UTF8String],
                                                        [version UTF8String],
                                                        params,
                                                        10000);
}

-(void)loginOut {
    rtalk_wrap::CRtalkClientHandlerImpl::GetInstance().Logout();
    [[IMClient shared] stop];

}

-(NSString *)getUserInfo {
    std::string str =  rtalk_wrap::CRtalkClientHandlerImpl::GetInstance().GetPersonInfo();
    NSString *info = [NSString stringWithUTF8String:str.c_str()];
    return info;
}


@end
