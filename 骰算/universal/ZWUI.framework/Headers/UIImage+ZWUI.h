//
//  UIImage+ZWUI.h
//  ZWUI
//
//  Created by taic_cai on 16/8/24.
//  Copyright © 2016年 taic_cai. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "FIUIImageCache.h"

@interface UIImage(ZWUI)

//查找bundle中的图片
+ (UIImage *)imageWithName:(NSString *)name bundle:(NSBundle *)bundle;

/**
 *  根据颜色创建图片
 *
 *  @param color 要创建图片的颜色
 *
 *  @return 返回创建好的图片
 */
+ (UIImage *)imageWithColor:(UIColor *)color;
@end
