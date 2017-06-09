//
//  OurButtonView.h
//  FingerInteract
//
//  Created by 陈江彬 on 11/23/15.
//  Copyright © 2015 Ocustom. All rights reserved.
//

#import "OurBaseView.h"

typedef void (^OurButtonViewBlock)(NSInteger btnTag);

@interface OurButtonView : OurBaseView

@property (nonatomic, strong) UIButton *backBtn;
@property (nonatomic, strong) UIImageView *iconImageView;

@property (nonatomic, assign) BOOL isDisabled;//是否可以点击
@property (nonatomic, strong) UIImage *disableImage;

@property (nonatomic, copy) OurButtonViewBlock block;

/**
 *  创建button
 */
- (id)initWithFrame:(CGRect)frame imageSize:(CGSize)imageSize iconImage:(UIImage *)iconImage highlightImage:(UIImage *)highImage btnTag:(NSInteger)btnTag;

- (void)setImageWithUrl:(NSString *)urlStr;

- (void)removeViewObserve;

- (void)setNormalImage:(UIImage *)normalImage highLightImage:(UIImage *)highLightImage;

@end
