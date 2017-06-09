//
//  MainViewController.h
//  骰算
//  首页
//  Created by taic_cai on 2016/12/23.
//  Copyright © 2016年 taic_cai. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CustomDatePicker.h"

@class CulModel;
typedef void(^MainViewControllerBlock) (CulModel *model);

@interface MainViewController : UIViewController
@property (nonatomic, copy) MainViewControllerBlock whenDone;

@property (nonatomic, strong) UILabel *nameLabel;
@property (nonatomic, strong) UITextField *nameField;
@property (nonatomic, strong) UIButton    *addTxtForShearPlate;

@property (nonatomic, strong) UILabel *birthLabel;
@property (nonatomic, strong) UITextField *birthField;
@property (nonatomic, strong) CustomDatePicker *Dpicker;

@property (nonatomic, strong) UILabel *indexLabel;
@property (nonatomic, strong) UILabel *EQ;
@property (nonatomic, strong) UITextField *EQTField;

@property (nonatomic, strong) UILabel *IQ;
@property (nonatomic, strong) UITextField *IQTField;

@property (nonatomic, strong) UILabel *attraction;
@property (nonatomic, strong) UITextField *attractionTField;

@property (nonatomic, strong) UIButton *resultBtn;

@property (nonatomic, strong) UIImage *img;
@end
