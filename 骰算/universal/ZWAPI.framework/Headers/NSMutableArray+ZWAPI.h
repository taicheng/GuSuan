//
//  NSMutableArray+ZWAPI.h
//  ZWAPI
//
//  Created by taic_cai on 16/8/16.
//  Copyright © 2016年 taic_cai. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSMutableArray (ZWAPI)
/**
 *  构造一个不会retain其中元素的数组
 *
 *  @return 可变数组
 */
+ (NSMutableArray *)noRetainArrayForZWAPI;
@end
