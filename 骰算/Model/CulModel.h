//
//  CulModel.h
//  骰算
//
//  Created by taic_cai on 2016/12/26.
//  Copyright © 2016年 taic_cai. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "NSObject+LKModel.h"

@interface CulModel : NSObject
@property (nonatomic, strong) NSString *name;           //名字
@property (nonatomic, strong) NSString *birthDay;       //生日
@property (nonatomic, assign) NSInteger IQ;             //iq值
@property (nonatomic, assign) NSInteger EQ;             //eq值
@property (nonatomic, assign) NSInteger attraction;     //吸引力

@property (nonatomic, strong) NSString *content;  //内容

@property (nonatomic, strong) UIImage *img;

@end
