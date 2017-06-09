//
//  NSError+ZWAPI.h
//  ZWAPI
//
//  Created by taic_cai on 16/8/16.
//  Copyright © 2016年 taic_cai. All rights reserved.
//

#import <Foundation/Foundation.h>

extern NSString *const kZWAPIErrorDomain;

NS_ENUM(NSInteger)
{
    kZWAPIErrorCodeNoUrl=2000,//没有url值
    kZWAPIErrorCodeIntervalLimit=2001,//两次发送时间间隔限制
};
@interface NSError (ZWAPI)
+ (NSError *)errorWithZWAPICode:(NSInteger)code errorMsg:(NSString *)msg;

/**
 *  是否是网络异常的错误.条件为:
 self.domain=NSURLErrorDomain && self.code in @[
 @(NSURLErrorTimedOut),//超时
 @(NSURLErrorCannotFindHost),//查找不到对方的host
 @(NSURLErrorCannotConnectToHost),//连接不上对方的host
 @(NSURLErrorNetworkConnectionLost),//网络连接断掉
 @(NSURLErrorDNSLookupFailed),//dns查找失败
 @(NSURLErrorNotConnectedToInternet),//无网络连接
 ]
 *
 *  @return 是否是网络异常的错误
 */
- (BOOL)isNetworkAnomaly;

/**
 *  是否是请求发送太频繁错误,判断依据是code==kZWAPIErrorCodeIntervalLimit,domain==kZWAPIErrorDomain
 *
 *  @return	是否是请求发送太频繁错误
 */
- (BOOL)isApiSendIntervalLimitError;
@end
