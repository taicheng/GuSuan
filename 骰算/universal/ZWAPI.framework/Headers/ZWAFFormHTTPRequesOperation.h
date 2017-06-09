//
//  ZWAFFormHTTPRequesOperation.h
//  ZWAPI
//
//  Created by taic_cai on 16/8/16.
//  Copyright © 2016年 taic_cai. All rights reserved.
//

#import "ZWFormHttpRequestOperation.h"
#import "AFNetworking.h"

@interface ZWAFFormHTTPRequesOperation : ZWFormHttpRequestOperation{
    NSURLSessionTask  *_requestSession;
}
@property (nonatomic, strong)   NSData           *responseDataSession;
@property (nonatomic, strong)   NSError          *responseError;
@property (nonatomic, readonly) NSURLSessionTask *requestSessionOfAFHTTP;

@end
