//
//  ZWMessageExecutorProtocol.h
//  ZWAPI
//
//  Created by taic_cai on 16/8/16.
//  Copyright © 2016年 taic_cai. All rights reserved.
//

#import <Foundation/Foundation.h>

@class ZWMessage;

@protocol ZWMessageExecutorProtocol <NSObject>

@optional

/**
 *  处理消息的前置逻辑
 *
 *  @param msg 消息对象
 *
 *  @return 如果返回NO,停止消息的后续处理
 */
- (BOOL)preExecuteMessage:(ZWMessage *)msg;

/**
 *  处理消息
 *
 *  @param msg 消息对象
 */
- (void)executeMessage:(ZWMessage *)msg;

/**
 *  处理消息的后置逻辑
 *
 *  @param msg 消息对象
 */
- (void)postExecuteMessage:(ZWMessage *)msg;

/**
 *  处理消息的处理进度变化,进度在msg.progress属性中
 *
 *  @param msg 消息对象
 */
- (void)executeMessageProgress:(ZWMessage *)msg;

@end