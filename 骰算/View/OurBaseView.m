//
//  OurBaseView.m
//  FingerInteract
//
//  Created by 陈江彬 on 11/19/15.
//  Copyright © 2015 Ocustom. All rights reserved.
//

#import "OurBaseView.h"

@implementation OurBaseView

DEF_SINGLETON(OurBaseView);

#pragma mark-
#pragma mark 初始化
- (id)initWithFrame:(CGRect)frame selectIndex:(int)selectIndex
{
    self = [super initWithFrame:frame];
    if (self)
    {
        
    }
    return self;
}


#pragma mark ----
#pragma mark UIButton
- (UIButton*)createButtonWithTitle:(NSString *)titleT backgroundImage:(UIImage *)backgroundImage iconImage:(UIImage *)iconImage highlightImage:(UIImage *)highLightImage tag:(NSInteger)tagN
{
    UIButton *button = [[UIButton alloc] init];
    [button setTitle:titleT forState:UIControlStateNormal];
    [button setBackgroundImage:backgroundImage forState:UIControlStateNormal];
    [button setImage:iconImage forState:UIControlStateNormal];
    [button setImage:highLightImage forState:UIControlStateHighlighted];
    button.tag = tagN;
    [button addTarget:self action:@selector(viewButtonAction:) forControlEvents:UIControlEventTouchUpInside];
    return button;
}

- (UIButton *)createButtonWithTitle:(NSString *)titleT titleColor:(UIColor *)titleColr titleFont:(UIFont *)titleFont tag:(NSInteger)tagN
{
    UIButton *button = [[UIButton alloc] init];
    [button setTitle:titleT forState:UIControlStateNormal];
    [button setTitleColor:titleColr forState:UIControlStateNormal];
    button.titleLabel.font = titleFont;
    button.tag = tagN;
    [button addTarget:self action:@selector(viewButtonAction:) forControlEvents:UIControlEventTouchUpInside];
    return button;
}

#pragma mark- 按钮事件
- (void)viewButtonAction:(UIButton *)sender
{
    
}

#pragma mark- UILabel
- (UILabel *)createLabelWithText:(NSString *)text font:(UIFont *)font textColor:(UIColor *)textColor textAlignment:(NSTextAlignment)textAlignment
{
    UILabel *label = [[UILabel alloc] init];
    label.backgroundColor = [UIColor clearColor];
    label.text = text;
    label.font = font;
    label.textAlignment = textAlignment;
    label.textColor = textColor;
    return label;
}

#pragma mark- 创建UITextField
- (UITextField *)createTextFieldWithText:(NSString *)text font:(UIFont*)font textColor:(UIColor *)textColor textAlignment:(NSTextAlignment)textAlignment
{
    UITextField *field = [[UITextField alloc] init];
    field.backgroundColor = [UIColor clearColor];
    field.text = text;
    field.font = font;
    field.textAlignment = textAlignment;
    field.textColor = textColor;
    field.font = font;
    return field;
}

#pragma mark-
#pragma mark 内存
- (void)dealloc
{
}


@end
