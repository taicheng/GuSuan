//
//  NSDictionary+ZWExtension.h
//  ZWResource
//
//  Created by taic_cai on 16/8/30.
//  Copyright © 2016年 taic_cai. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface NSDictionary(ZWExtension)

- (id)objectAtPath:(NSString *)path;
- (id)objectAtPath:(NSString *)path otherwise:(NSObject *)other;

- (NSArray *)arrayAtPath:(NSString *)path;
- (NSArray *)arrayAtPath:(NSString *)path otherwise:(NSArray *)other;

- (NSDictionary *)dictionaryAtPath:(NSString *)path;
- (NSDictionary *)dictionaryAtPath:(NSString *)path otherwise:(NSDictionary *)other;

- (id)jsonValueAtPath:(NSString *)path;//限制在NSArray和NSDictionary之间
- (id)jsonValueAtPath:(NSString *)path otherwise:(id)other;

- (NSString *)stringAtPath:(NSString *)path;
- (NSString *)stringAtPath:(NSString *)path otherwise:(NSString *)other;

- (NSNumber *)numberAtPath:(NSString *)path;
- (NSNumber *)numberAtPath:(NSString *)path otherwise:(NSNumber *)other;

- (BOOL)boolAtPath:(NSString *)path;
- (BOOL)boolAtPath:(NSString *)path otherwise:(BOOL)other;

- (NSInteger)integerAtPath:(NSString *)path;
- (NSInteger)integerAtPath:(NSString *)path otherwise:(NSInteger)other;

- (CGFloat)floatAtPath:(NSString *)path;
- (CGFloat)floatAtPath:(NSString *)path otherwise:(CGFloat)other;

- (CGFloat)CGFloatAtPath:(NSString *)path;
- (CGFloat)CGFloatAtPath:(NSString *)path otherwise:(CGFloat)other;

- (double)doubleAtPath:(NSString *)path;
- (double)doubleAtPath:(NSString *)path otherwise:(CGFloat)other;

- (NSTimeInterval)NSTimeIntervalAtPath:(NSString *)path;
- (NSTimeInterval)NSTimeIntervalAtPath:(NSString *)path otherwise:(CGFloat)other;

/**
 *  递归方式返回可变的字典
 *
 *  @return NSMutableDictionary
 */
- (NSMutableDictionary *)mutableDictionary;

/**
 *  返回json格式的字符串
 *
 *  @return 字符串
 */
- (NSString *)jsonString;

/**
 *  返回json格式的二进制数据
 *
 *  @return NSData对象
 */
- (NSData *)jsonData;


#define kZWDateFormatNormal @"YYYY-MM-dd HH:mm:ss"
- (NSDate *)dateAtPath:(NSString *)path dateFormat:(NSString *)dateFormat;//日期格式,如:YYYY-MM-dd HH:mm:ss.如果obj值为时间戳,则以1970/01/01为基准
- (NSDate *)dateSinceReferenceDateAtPath:(NSString *)path dateFormat:(NSString *)dateFormat;//日期格式,如:YYYY-MM-dd HH:mm:ss.如果obj值为时间戳,则以SinceReferenceDate为基准
- (NSDate *)dateAtPath:(NSString *)path dateFormat:(NSString *)dateFormat otherwise:(NSDate *)other;
- (NSDate *)dateSinceReferenceDateAtPath:(NSString *)path dateFormat:(NSString *)dateFormat otherwise:(NSDate *)other;
//时间起点为1970年
- (NSDate *)dateSince1970AtPath:(NSString *)path dateFormat:(NSString *)dateFormat;
- (NSDate *)dateSince1970AtPath:(NSString *)path dateFormat:(NSString *)dateFormat otherwise:(NSDate *)other;
//时间起点为1970年,时间戳单位为毫秒
- (NSDate *)dateSince1970MillisecondAtPath:(NSString *)path dateFormat:(NSString *)dateFormat;
- (NSDate *)dateSince1970MillisecondAtPath:(NSString *)path dateFormat:(NSString *)dateFormat otherwise:(NSDate *)other;

/**
 *  返回json格式的字符串
 *
 *  @param compact 是否要压缩字符串,YES:将输出没有分行的字符串,NO:将输出分好行的字符串,便于阅读
 *
 *  @return 字符串
 */
- (NSString *)jsonStringWithCompacted:(BOOL)compact;

/**
 *  返回json格式的二进制数据
 *
 *  @param compact 是否输出紧凑的数据
 *
 *  @return NSData对象
 */
- (NSData *)jsonDataWithCompacted:(BOOL)compact;
@end
