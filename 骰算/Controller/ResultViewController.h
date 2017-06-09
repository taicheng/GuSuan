//
//  ResultViewController.h
//  骰算
//
//  Created by taic_cai on 2016/12/26.
//  Copyright © 2016年 taic_cai. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "BasicViewController.h"
#import "CulModel.h"

typedef void(^ResultViewControllerBlock) (void);

@interface ResultViewController : BasicViewController
@property (nonatomic, strong) CulModel *model;
@property (nonatomic, copy) ResultViewControllerBlock whenDismiss;
@end
