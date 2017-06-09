//
//  ZWAPIMessage_Basic.h
//  ZWAPI
//
//  Created by taic_cai on 16/8/16.
//  Copyright © 2016年 taic_cai. All rights reserved.
//

#import "ZWMessage.h"
#import "NSError+ZWAPI.h"

@interface ZWAPIMessage_Basic : ZWMessage<ZWMessageExecutorProtocol>
/**
 *  子类重写,用于实例消息状态的变化
 */
- (void)routine;

/**
 *  如果消息队列中,没有正在执行的消息,则创建新消息,否则返回该消息,从而保证消息队列中,只有一个正在发送处理中的该类型消息
 *
 *  @return 消息
 */
+ (id)createSingleAPI;

#pragma mark - interval of api sending
/**
 *  两次api之间的发送间隔.0代表没有间隔.如果发送api时,与上次的请求时间间隔少于此值,请求发送失败,失败code为kZWAPIErrorCodeIntervalLimit
	该机制的一个应用场景就是发送手机验证码请求.这种请求要求两次请求之间,要有一定的时间间隔.
 *	默认为返回0,没有间隔.
 *  @return 间隔,单位为秒
 */
+ (NSTimeInterval)intervalOfAPISending;

/**
 *  清除上一次请求发送时间记录
 */
+ (void)clearAPILastSendTick;

/**
 *  在intervalOfAPISending的发送间隔限定下,是否能够发送请求
 *
 *  @return 是否可以发送请求
 */
+ (BOOL)canSendAPIWithIntervalLimit;

/**
 *  在intervalOfAPISending的限定下,距离下次api的发送还剩多少时间,单位为秒.0代表可以发送
 *
 *  @return 时间
 */
+ (NSTimeInterval)timeRemainingForSendAPI;

@end
