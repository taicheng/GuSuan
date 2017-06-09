//
//  ZWFormHttpRequestOperationDelegate.h
//  ZWAPI
//
//  Created by taic_cai on 16/8/16.
//  Copyright © 2016年 taic_cai. All rights reserved.
//

#import <Foundation/Foundation.h>

@class ZWFormHttpRequestOperation;

@protocol ZWFormHttpRequestOperationDelegate <NSObject>
@optional
- (void)operationStart:(ZWFormHttpRequestOperation *)op;//开始请求
- (void)operationComplete:(ZWFormHttpRequestOperation *)op withSuccess:(BOOL)success error:(NSError *)error;//完成
- (void)operationSuccess:(ZWFormHttpRequestOperation *)op;//成功
- (void)operationFail:(ZWFormHttpRequestOperation *)op withError:(NSError *)error;//失败
- (void)operationCancel:(ZWFormHttpRequestOperation *)op;//取消
- (void)operationUploadProgress:(ZWFormHttpRequestOperation *)op withBytesWritten:(int64_t)bytesWritten totalBytesWritten:(int64_t)totalBytesWritten totalBytesExpectedToWrite:(int64_t)totalBytesExpectedToWrite;//上传进度改变
- (void)operationDownloadProgress:(ZWFormHttpRequestOperation *)op withBytesRead:(int64_t)bytesRead totalBytesRead:(int64_t)totalBytesRead totalBytesExpectedToRead:(int64_t)totalBytesExpectedToRead;//下载进度改变
@end
