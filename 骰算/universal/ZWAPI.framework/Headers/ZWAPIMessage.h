//
//  ZWAPIMessage.h
//  ZWAPI
//
//  Created by taic_cai on 16/8/16.
//  Copyright © 2016年 taic_cai. All rights reserved.
//

#import "ZWMessage.h"
#import "ZWMessageExecutorProtocol.h"

#import "ZWFormHttpRequestOperationDelegate.h"
#import "ZWFormHttpRequestOperation.h"
#import "ZWAFFormHTTPRequesOperation.h"
#import "ZWAPIMessage_Basic.h"
@class ZWAPIMessage;

typedef ZWFormHttpRequestOperation *(^ZWAPIMessageN)(NSString *url);

@interface ZWAPIMessage : ZWAPIMessage_Basic<ZWFormHttpRequestOperationDelegate>{
@protected
    NSMutableArray *_requests;//由self产生的请求对象
}
@property(nonatomic,strong) Class httpClass;//http请求的类,默认为ZWAFFormHTTPRequesOperation
@property(nonatomic,readonly) ZWFormHttpRequestOperation *request;//请求对象
@property(nonatomic,readonly) ZWAPIMessageN HTTP;//生成POST的请求,并延迟0.01秒发送
@property(nonatomic,readonly) ZWAPIMessageN HTTP_GET;//生成get的http请求,并延迟0.01秒发送
@property(nonatomic,readonly) ZWAPIMessageN HTTP_POST;//生成get的http请求,并延迟0.01秒发送
@property(nonatomic,assign  ) CGFloat progressOfUpload;//消息的上传进度
@property(nonatomic,assign  ) CGFloat progressOfDownload;//消息的下载进度
@property(nonatomic,assign  ) CGFloat progressOfUploadAndDownload;//消息的处理进度(上传+下载)
@property(nonatomic,assign  ) CGFloat progressFactorOfDownload;//在计算进度时,下载进度所占的比例,进度=progressOfDownload*(progressFactorOfDownload)+progressOfUpload*(1-progressFactorOfDownload),默认为0

/**
 *  产生http请求对象
 *
 *  @param url    请求的url值
 *  @param method 请求的方法,get/post/...
 *
 *  @return ZWFormHttpRequestOperation对象
 */
- (ZWFormHttpRequestOperation *)addRequestWithUrl:(NSString *)url method:(NSString *)method;

/**
 *  对产生出来的http请求,进行统一的默认设置
 *	@override
 *  @param op 请求对象
 */
- (void)defaultConfigToRequest:(ZWFormHttpRequestOperation *)op;

#pragma mark - resend for network error
@property(nonatomic,assign) NSInteger resendTimesForNetworkFail;//当请求因为网络不好等原因而失败时,尝试重发请求的次数.默认为0,代表不尝试
@property(nonatomic,assign) NSInteger resendedTimes;//已重新发送请求的次数

/**
 *  是否是提交表单数据的请求,默认为NO.如果为YES,则intervalOfAPISending的值会返回1
 *
 *  @return 是否是提交数据的表单请求
 */
+ (BOOL)isSubmitFormAPI;

/**
 *  因网络异常而进行重发,请求的执行进度会保留在上一次的值,直到下次请求的进度超过它
 */
- (void)resendForNetworkError;

/**
 *  判断是否需要因为网络异常而进行重发请求
 *
 *  @return 请求是否需要重发
 */
- (BOOL)shouldResendForNetworkError;

/**
 *  因为网络异常而导致失败时的回调
 */
- (void)didFailWithNetworkError;
@end
