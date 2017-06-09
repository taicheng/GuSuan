//
//  SSResultView.h
//  骰算
//
//  Created by taic_cai on 2016/12/26.
//  Copyright © 2016年 taic_cai. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "OurBaseView.h"
#import "CulModel.h"

@interface SSResultView : OurBaseView

@property (nonatomic, strong) CulModel *model;
- (CGFloat)getAutoHeight;
@end
