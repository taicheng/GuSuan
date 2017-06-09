//
//  ZWMessageQueue.h
//  ZWAPI
//
//  Created by taic_cai on 16/8/16.
//  Copyright © 2016年 taic_cai. All rights reserved.
//

/**
 *  该管理器会启动一个定时器,每隔一段时间,运行它持有的消息的runloop方法,以进行消息状态的转变.运行线程为主线程
 移除消息的时机点:
 当runloop之后,消息处于成功/失败/取消状态时,将消息放入待移除集合.下次运行时,如果消息状态还和上次一样,代表消息可以移除了.
 */
#import <Foundation/Foundation.h>
@class ZWMessage;
@interface ZWMessageQueue : NSObject{
    NSMutableArray *_messageQueue;
}
+ (instancetype)sharedInstance;
@property(nonatomic,readonly) NSArray *messages;

- (NSArray *)messages:(NSString *)msgName;//根据消息的name属性,获取消息列表
- (NSArray *)messagesWithClass:(Class)clazz;//根据消息的class类,获取消息列表
- (NSArray *)messagesByResponder:(id)responder;//获取响应者含有responder的消息列表

- (void)addMessages:(ZWMessage *)msg;
//发送消息
- (BOOL)sendMessage:(ZWMessage *)msg;

//取消消息@[ZWMessage]
- (void)cancelMessages:(NSArray *)msgs;
//取消所有的消息
- (void)cancelMessages;
//执行消息循环
- (void)runloop;
@end
