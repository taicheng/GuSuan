//
//  MacroDefine.m
//  骰算
//
//  Created by taic_cai on 2016/12/26.
//  Copyright © 2016年 taic_cai. All rights reserved.
//

#import "MacroDefine.h"

@implementation MacroDefine
DEF_SINGLETON(MacroDefine);
#pragma mark- 适配iPhone6，6plus的不同分辨率
- (float)screenMultiple {
    return kScreenHeight/667;
    
}

@end
