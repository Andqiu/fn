//
//  IMClient.h
//  Runner
//
//  Created by Dsen on 2024/1/31.
//

#import <Foundation/Foundation.h>
#import "IMClientHandler.h"

NS_ASSUME_NONNULL_BEGIN

@interface IMClient : NSObject

+(instancetype)shared;

@property (nonatomic, strong) IMClientHandler *handler;


- (int)start;
- (void)stop;

-(void)loginWithType:(NSInteger)type
                  ip:(NSString *)ip
             account:(NSString *)account
                 pwd:(NSString *)pwd;

-(void)loginOut;

-(NSString *)getUserInfo;

@end

NS_ASSUME_NONNULL_END
