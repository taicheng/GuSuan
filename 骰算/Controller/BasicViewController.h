//
//  BasicViewController.h
//  骰算
//
//  Created by taic_cai on 2016/12/26.
//  Copyright © 2016年 taic_cai. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "OurBaseView.h"
#import "OurButtonView.h"
#import <ZWUI/ZWUI.h>

@interface BasicViewController : UIViewController
/**
 *  标题视图
 */
@property (nonatomic, strong) UIView *baseTitleView;

/**
 *  标题
 */
@property (nonatomic, strong) UILabel *baseTitleLabel;
/**
 *  左边按钮
 */
@property (nonatomic, strong) OurButtonView *leftBtn;
/**
 * 导航栏底部分割线
 */
@property (nonatomic, strong) UILabel *lineBottom;

- (void)setTopViewWithTitle:(NSString *)title leftBtn:(UIView *)leftBtn rightBtnArray:(NSArray *)rightBtnArray rightBtnTagsArray:(NSArray *)tagsArray hidden:(BOOL)hidden;


- (void)showViewTipHubWithMsg:(NSString *)msg;
@end
