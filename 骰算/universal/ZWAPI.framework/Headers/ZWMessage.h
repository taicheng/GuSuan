//
//  ZWMessage.h
//  ZWAPI
//
//  Created by taic_cai on 16/8/16.
//  Copyright © 2016年 taic_cai. All rights reserved.
//

/**
 ----------------------------------------------------------------------
 消息状态变更的处理逻辑如下:
 1.执行executor对象的preExecuteMessage方法,如果返回NO,状态变更处理结束.这种情况一般用在preExecuteMessage中,状态又进行了变更,此时后续的处理已经不需要了.
 2.执行executor对象的executeMessage方法.如果在执行过程中,又变更了消息状态(如调用self.failed=YES),此时该新状态是存储在nextState中的,并不会立刻改变当前的state.
 3.执行executor对象的postExecuteMessage方法.
 4.在executor对象的处理逻辑结束后,如果状态发生改变了,那直接返回,停止后面的逻辑.
 5.对self.state,调用相应的whenXXX(self);block方法.
 遍历self.responders,调用其对应的preRespondMessage,respondMessage,postRespondMessage等方法.如果preExecuteMessage返回了NO,则该responder的respondMessage与postRespondMessage方法不会执行,但是不会影响其他的responder
 ----------------------------------------------------------------------
 消息进度变化的处理逻辑如下:(前提:消息要处理wating状态时,才可能进行进度的改变)
 1.执行executor对象的executeMessageProgress:方法
 2.执行self.whenProgressed(self);语句
 3.遍历self.responders,调用方法respondMessageProgress:
 ----------------------------------------------------------------------
 对于单例的消息,它可以在消息完成后,再次处于发送中的状态,从而达到消息复用的目的.
 对于一个消息,被其他多个消息依赖的情况,当它完成之后,被从messagequeue中移除,但它还被依赖消息持有着,等待被依赖消息的释放.
 消息状态的变化,是延迟的,在messagequeue的定时器中执行.
 */

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "ZWMessageExecutorProtocol.h"
#import "ZWMessageResponderProtocol.h"

@class ZWMessage,ZWMessageQueue;
typedef void(^ZWMessageBlock)(void);//回调
typedef void(^ZWMessageBlockM)(ZWMessage *msg);//回调

typedef enum {
    ZWMessageStateCreated,//消息被创建
    ZWMessageStateSending,//消息正在发送
    ZWMessageStateWaiting,//消息正在等待回应
    ZWMessageStateSucceed,//消息处理成功(本地或网络)
    ZWMessageStateFailed,//消息处理失败(本地或网络)
    ZWMessageStateCancelled//消息被取消了
}ZWMessageState;//消息状态

@interface ZWMessage : NSObject<ZWMessageResponderProtocol>{
@protected
    NSMutableArray *_waitingMessages;
    NSMutableArray *_responders;
    NSTimer *_timer;
    ZWMessageState _state;
    NSError *_error;
    NSRecursiveLock *_lock;
    NSMutableArray *_dependMessages;
    NSMutableArray *_monitorMessages;
    NSMutableArray *_unMonitorMessages;
}
@property(nonatomic,strong) NSString *name;//消息名称
@property(nonatomic,assign) ZWMessageQueue *messageQueue;//弱引用消息队列
@property(nonatomic,readonly) BOOL timeout;//是否超时了
@property(nonatomic,assign) NSTimeInterval timeoutSeconds;//超时时间,默认是0,不设置超时时间
@property(nonatomic,assign) BOOL emitted;//标记消息是否已经被发送过了

@property(nonatomic,assign) id<ZWMessageExecutorProtocol>executor;//消息处理器,负责消息状态变化时的响应

@property(nonatomic,strong) NSMutableDictionary *input;//消息处理的输入参数
@property(nonatomic,strong) NSMutableDictionary *output;//消息处理的输出结果

@property(nonatomic,readonly) NSError *error;//错误信息
@property(nonatomic,readonly) NSString *errorMsg;//错误文字信息
@property(nonatomic,assign) ZWMessageState state;//消息状态,设置新的状态,会在下一个循环周期时才更新
@property(nonatomic,assign) ZWMessageState stateToResumeAfterWaittingOther;//在等待其他api执行结束后,要恢复的状态.在执行waitMessage:动作时,stateToResumeAfterWaitOther=self.state

@property(nonatomic,copy) ZWMessageBlockM whenUpdate;//状态变化时的回调
@property(nonatomic,copy) ZWMessageBlockM whenSending;//发送后的回调
@property(nonatomic,copy) ZWMessageBlockM whenWaiting;//进入等待后的回调
@property(nonatomic,copy) ZWMessageBlockM whenSucceed;//处理成功后的回调
@property(nonatomic,copy) ZWMessageBlockM whenFailed;//处理失败后的回调
@property(nonatomic,copy) ZWMessageBlockM whenCancelled;//被取消后的回调
@property(nonatomic,copy) ZWMessageBlockM whenDoned;//succeed,failed,cancel时回调
@property(nonatomic,copy) ZWMessageBlockM whenProgressed;//进度变化时的回调

@property (nonatomic,assign  ) BOOL    progressUpdated;//是否有新的进度,只有在wait时候才会更新进度
@property (nonatomic,assign  ) CGFloat progress;//消息的处理进度
@property (nonatomic,assign  ) BOOL    created;//是否在创建状态
@property (nonatomic,assign  ) BOOL    sending;//是否在发送中状态
@property (nonatomic,assign  ) BOOL    waiting;//是否在等待状态
@property (nonatomic,assign  ) BOOL    succeed;//是否在成功状态
@property (nonatomic,assign  ) BOOL    failed;//是否在失败状态
@property (nonatomic,assign  ) BOOL    cancelled;//是否在取消状态
@property (nonatomic,readonly) BOOL    finished;//是否处于完成状态,完成状态为succeed,failed,cancelled

@property(nonatomic,copy) NSArray *responders;//消息响应者(可设置多个),这里弱引用响应者
//responders消息响应者的添加,移除,查询操作
- (void)addResponder:(id<ZWMessageResponderProtocol>)responder;//add和remove要配对
- (void)removeResponder:(id<ZWMessageResponderProtocol>)responder;
- (void)removeAllResponders;
- (BOOL)hasResponder:(id<ZWMessageResponderProtocol>)responder;

@property(nonatomic,readonly) NSArray *waitingMessages;//正在等待执行的消息
//等待其他消息的执行结果,此时会进入wait状态,被等待的消息执行完后,如果全部成功,则进入succeed状态,否则进入failed状态.当取消本消息时,需要手动移除依赖关系.返回是否操作成功,当msg已经完成时,不会进行任务操作,直接返回NO
- (BOOL)waitMessage:(ZWMessage *)msg;
- (BOOL)waitMessage:(ZWMessage *)msg stateToResumeAfterWaittingOther:(ZWMessageState)stateToResumeAfterWaittingOther;
- (NSArray<ZWMessage *> *)waitingMessagesWithClass:(Class)clazz;//返回正在等待执行的指定消息类
- (ZWMessage *)waitingMessageWithClass:(Class)clazz;//返回正在等待执行的指定消息类
- (BOOL)hasWaitingMessageWithClass:(Class)clazz;//是否有等待指定的消息类

//设置不监听msg的进度
- (void)unMonitorMessageProgress:(ZWMessage *)msg;

@property(nonatomic,readonly) NSArray *monitorMessages;//正在监控进度的消息
//监控消息的执行过程,会影响自己的进度.当消息完成时,进度都+=1,其他情况会+=msg.progress.当所有被监听消息执行完时,如果没有其他等待消息,则会修改自己的状态
- (void)monitorMessage:(ZWMessage *)msg;

@property(nonatomic,readonly) NSArray *dependMessages;
//以队列的方式依赖消息.如依赖消息A,B,C,那消息执行顺序是A(succeed)=>B(succeed)=>C(succeed)=>self(succeed)
//自己会进入waiting状态.返回是否操作成功,当msg已经完成时,不会进行任务操作,直接返回NO
- (BOOL)dependMessageInQueue:(ZWMessage *)msg;

//取消所有依赖的消息(如果该消息还被其他消息所依赖,此时不取消这条消息),这里只是移除依赖关系,但self还会持有依赖的消息
- (void)cancelAllOtherMessages;
- (NSArray *)allOtherMessages;//等待或依赖,监控的其他api集合
- (NSArray *)waitingOrDependingMessages;//等待或依赖的其他api集合
- (void)removeOtherMessage:(ZWMessage *)msg;
- (void)removeOtherMessages:(NSArray *)msgs;//从依赖的其他消息中,移除指定的消息.这里只是移除关系,并不会更新进度,取消其他消息

//由消息队列调用,执行状态变更
- (void)runloop;

//发送消息到默认的消息队列中
- (void)send;
- (void)resend;//将消息重新发送
//取消消息,会马上移除掉等待的其他消息
- (void)cancel;
//返回状态对应的字符串
- (NSString *)stateString:(ZWMessageState)state;
- (NSString *)stateString;

/**
 *  设置失败信息
 *
 *  @param domain 失败的domain
 *  @param code   code值
 *  @param msg    文件描述
 */
- (void)setErrorWithDomain:(NSString *)domain code:(NSInteger)code msg:(NSString *)msg;
@end
