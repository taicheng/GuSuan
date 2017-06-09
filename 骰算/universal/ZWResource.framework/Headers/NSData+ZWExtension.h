//
//  NSData+ZWExtension.h
//  ZWResource
//
//  Created by taic_cai on 16/8/30.
//  Copyright © 2016年 taic_cai. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSData(ZWExtension)

@property (nonatomic, readonly) NSData *	MD5;//返回对应的md5数据
@property (nonatomic, readonly) NSString *	MD5String;//返回大写的md5字符串
@property (nonatomic, readonly) NSString *  md5String;//返回小写的md5字符串

@end
