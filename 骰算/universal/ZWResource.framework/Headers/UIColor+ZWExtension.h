//
//  UIColor+ZWExtension.h
//  ZWResource
//
//  Created by taic_cai on 16/9/1.
//  Copyright © 2016年 taic_cai. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

@interface UIColor(ZWExtension)

@property(nonatomic,readonly) NSString *hexColorString;//返回16进制的颜色字符串,格式为#AARRBBGG

+ (UIColor *) colorWithHexString:(NSString *)hexString; //以十六进制字符串设置颜色
- (NSString *)descriptionOfColorString;   //自身描述
@end
