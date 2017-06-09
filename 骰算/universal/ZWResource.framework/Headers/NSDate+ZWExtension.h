//
//  NSDate+ZWExtension.h
//  ZWResource
//
//  Created by taic_cai on 2016/10/24.
//  Copyright © 2016年 taic_cai. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface NSDate (ZWExtension)

/**
 *  当前日前往前一天的时间
 *
 *  @return 日期
 */
- (NSDate *)yesterday;

/**
 *  当前日前往后一天的时间
 *
 *  @return 日期
 */
- (NSDate *)tomorrow;

/**
 *  返回当前时间所在月的第一天
 *
 *  @return 0:0开始的日期
 */
- (NSDate *)monthOfFirstDay;

/**
 *  返回当前时间所在月的最后一天
 *
 *  @return 0:0开始的日期
 */
- (NSDate *)monthOfLastDay;

/**
 *  当前时刻与指定的时刻是否在同一天
 *
 *  @param date 另一时刻
 *
 *  @return 是否在同一天内
 */
- (BOOL)isSameDayWithDate:(NSDate *)date;

/**
 *  判断是否比指定的日期要早
 *
 *  @param date 指定的日期
 *
 *  @return 是否比指定日期早
 */
- (BOOL)isEarlierDate:(NSDate *)date;

/**
 *  判断是否比指定的日期要晚
 *
 *  @param date 指定的日期
 *
 *  @return 是否比指定日期晚
 */
- (BOOL)isLaterDate:(NSDate *)date;

/**
 *  判断日期是否过期
 *
 *  @return	如果比当前时间点要晚时,返回YES,其余返回NO
 */
- (BOOL)isExpire;

/**
 *  现在这个时刻是否是今天
 *
 *  @return 是否是今天
 */
- (BOOL)isToday;

/**
 *  现在这个时刻是否是昨天
 *
 *  @return 是否是昨天
 */
- (BOOL)isYesterday;

/**
 *  现在这个时刻是否是明天
 *
 *  @return 是否是明天
 */

- (BOOL)isTomorrow;

/**
 *  返回距离现在这天的00:00刻,指定time秒数的时间点
 *
 *  @param time 当前时间所在的天到00:00这个时间点的秒数
 *
 *  @return 时间
 */
- (NSDate *)dateWithZeroSeconds:(NSInteger)time;

/**
 *  返回与00:00的秒数
 *
 *  @return 秒数
 */
- (NSInteger)secordsWithZeroTime;

/**
 *  当前时间与date之间间隔的天数
 *
 *  @param date 要计算的日期
 *
 *  @return 两个时间点对应的天数之差
 */
- (NSInteger)dayIntervalSinceDate:(NSDate *)dateFormat;

/**
 *  返回日期字符串
 *
 *  @param dateFormat 日期的显示格式，如YYYY-MM-dd HH:mm:ss
 *
 *  @return 字符串
 */
- (NSString *)stringWithDateFormat:(NSString *)dateFormat;

/**
 *  从字符串中实例出日期
 *
 *  @param dateString 字符串，如1999-9-10
 *  @param dateFormat 日期字符串的格式
 *
 *  @return 日期对象
 */
+ (NSDate *)dateWithString:(NSString *)dateString dateFormat:(NSString *)dateFormat;


@end
