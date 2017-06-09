//
//  ZWAPIJSONMessage.h
//  ZWAPI
//
//  Created by taic_cai on 16/8/16.
//  Copyright © 2016年 taic_cai. All rights reserved.
//

#import "ZWAPIMessage.h"

@interface ZWAPIJSONMessage : ZWAPIMessage
@property(nonatomic,strong) NSDictionary *result;
@property(nonatomic,strong) NSArray *resultList;
@end
