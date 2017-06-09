//
//  NSString+ZWExtension.h
//  ZWResource
//
//  Created by taic_cai on 16/8/30.
//  Copyright © 2016年 taic_cai. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface NSString(ZWExtension)
@property (nonatomic, readonly) NSString *md5;//返回小寫的md5值
@property (nonatomic, readonly) NSString *MD5;//返回大写的md5值
/**
 *  对json格式的字符串进行处理,返回其对应的NSDictionary或者NSArray等对象
 *
 *  @return json對象
 */
- (id)jsonValue;

/**
 *  string為NSDictionary的json格式
 *
 *  @return json對應的NSDictionary
 */
- (NSDictionary *)jsonDictionary;

/**
 *  string為NSArray的json格式
 *
 *  @return json對應的NSArray
 */
- (NSArray *)jsonArray;

- (NSNumber *)numberValue;


/**
 *  搜索指定字符串的所有位置
 *
 *  @param searchString 指定的字符串
 *
 *  @return NSRange包装类的列表
 */
- (NSArray<NSValue *> *)rangesOfString:(NSString *)searchString;

/*
 *  @param font 字体格式
 *  @param size 约束大小
 *  @return 字符串在约束大小的条件下对应的合适大小
 */
- (CGSize)fdd_sizeWithFont:(UIFont *)font constrainedToSize:(CGSize)size;

@end

@interface NSString(ZWCheck)


/**
 * @return 是否邮件格式
 */
- (BOOL)isStringForEmailFormat;

/**
 * @return 是否中国手机格式
 */
- (BOOL)isStringForChinaMobileFormat;


/**
 * @return 去掉空白字符后是否为空字符
 */
- (BOOL)isNilByReduceWhitespaceCharacter;
/**
 * @return 是否包含空白字符
 */
- (BOOL)haswhitespaceCharacterSet;
@end
