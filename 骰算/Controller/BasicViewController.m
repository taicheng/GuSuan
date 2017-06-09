//
//  BasicViewController.m
//  骰算
//
//  Created by taic_cai on 2016/12/26.
//  Copyright © 2016年 taic_cai. All rights reserved.
//

#import "BasicViewController.h"

@interface BasicViewController ()

@end

@implementation BasicViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
}

#pragma mark- 创建按钮 带图片
- (UIButton*)createButtonWithTitle:(NSString *)titleT backgroundImage:(UIImage *)backgroundImage iconImage:(UIImage *)iconImage highlightImage:(UIImage *)highLightImage tag:(NSInteger)tagN
{
    UIButton *button = [[UIButton alloc] init];
    [button setTitle:titleT forState:UIControlStateNormal];
    [button setBackgroundImage:backgroundImage forState:UIControlStateNormal];
    [button setImage:iconImage forState:UIControlStateNormal];
    [button setImage:highLightImage forState:UIControlStateHighlighted];
    button.tag = tagN;
    [button addTarget:self action:@selector(buttonAction:) forControlEvents:UIControlEventTouchUpInside];
    return button;
}
#pragma mark- 创建按钮 纯文字
- (UIButton *)createButtonWithTitle:(NSString *)titleT titleColor:(UIColor *)titleColr titleFont:(UIFont *)titleFont tag:(NSInteger)tagN
{
    UIButton *button = [[UIButton alloc] init];
    [button setTitle:titleT forState:UIControlStateNormal];
    [button setTitleColor:titleColr forState:UIControlStateNormal];
    button.titleLabel.font = titleFont;
    button.tag = tagN;
    [button addTarget:self action:@selector(buttonAction:) forControlEvents:UIControlEventTouchUpInside];
    return button;
}

- (void)setTopViewWithTitle:(NSString *)title leftBtn:(UIView *)leftBtn rightBtnArray:(NSArray *)rightBtnArray rightBtnTagsArray:(NSArray *)tagsArray hidden:(BOOL)hidden
{
    if (!hidden)
    {
        if (_baseTitleView)
        {
            [_baseTitleView removeFromSuperview];
            RELEASEOBJECT(_baseTitleView);
        }
        
        _baseTitleView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, kScreenWidth, 66)];
        _baseTitleView.userInteractionEnabled = YES;
        _baseTitleView.backgroundColor = [UIColor whiteColor];
        [self.view addSubview:_baseTitleView];
        float rightBtnsWith = 0;//计算右侧按钮的宽度
        if (rightBtnArray)
        {
            for (int i=0; i<rightBtnArray.count; i++) {
                UIButton *btnRight = rightBtnArray[i];
                btnRight.tag = [tagsArray[i] intValue];
                rightBtnsWith+= btnRight.width;
                [_baseTitleView addSubview:btnRight];
            }
        }
        //标题
        _baseTitleLabel = [self createLabelWithText:title font:[UIFont boldSystemFontOfSize:15*ScreenMultiple] textColor:[UIColor blackColor] textAlignment:NSTextAlignmentCenter];
        @try {
            CGRect frame ;
            if (rightBtnsWith>1) {
                frame = CGRectMake(kScreenWidth/2-(kScreenWidth-rightBtnsWith*2)/2, StatusBarHeight, kScreenWidth-rightBtnsWith*2, NaviBarHeight);
                
            }else {
                frame = CGRectMake(0, StatusBarHeight, kScreenWidth, NaviBarHeight);
            }
            [_baseTitleLabel setFrame:frame];
        } @catch (NSException *exception) {
        } @finally {
            
        }
        [_baseTitleView addSubview:_baseTitleLabel];
        //分割线
        _lineBottom = [[UILabel alloc] initWithFrame:CGRectMake(0,StatusBarHeight+NaviBarHeight-1 , kScreenWidth, 1)];
        _lineBottom.backgroundColor = UIColorWithRGB(223, 224, 224, 1);
        [_baseTitleView addSubview:_lineBottom];
        if (leftBtn)
        {
            [_baseTitleView addSubview:leftBtn];
        }
        else
        {
            _leftBtn = [[OurButtonView alloc] initWithFrame:CGRectMake(-6*ScreenMultiple, StatusBarHeight, 50*ScreenMultiple, NaviBarHeight) imageSize:CGSizeMake(22.0*ScreenMultiple, 22.0*ScreenMultiple) iconImage:[UIImage imageNamed:@"back"] highlightImage:[UIImage imageNamed:@"back"] btnTag:25837];
            __weak BasicViewController *weakSelf = self;
            _leftBtn.block = ^(NSInteger btnTag){
                [weakSelf buttonAction:weakSelf.leftBtn.backBtn];
            };
            [_baseTitleView addSubview:_leftBtn];
        }
    }
}
#pragma mark- 创建UILabel
- (UILabel *)createLabelWithText:(NSString *)text font:(UIFont*)font textColor:(UIColor *)textColor textAlignment:(NSTextAlignment)textAlignment
{
    UILabel *label = [[UILabel alloc] init];
    label.backgroundColor = [UIColor clearColor];
    label.text = text;
    label.font = font;
    label.textAlignment = textAlignment;
    label.textColor = textColor;
    label.font = font;
    return label;
}
- (void)buttonAction:(UIButton *)sender {
}

- (void)showViewTipHubWithMsg:(NSString *)msg {
    if (!msg.length) {
        return;
    }
    MBProgressHUD *hub = [MBProgressHUD showTipHubWithMsg:msg addedTo:self.view];
    hub.userInteractionEnabled = NO;
    [hub hideAnimated:YES afterDelay:2.5f];
}

@end
