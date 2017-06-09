//
//  CulModel.m
//  骰算
//
//  Created by taic_cai on 2016/12/26.
//  Copyright © 2016年 taic_cai. All rights reserved.
//

#import "CulModel.h"

@implementation CulModel

+(NSString*)getPrimaryKey {
    return @"name";
}

+ (NSString *)getTableName {
    return @"CulModel";
}

@end
