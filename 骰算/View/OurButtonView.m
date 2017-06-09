//
//  OurButtonView.m
//  FingerInteract
//
//  Created by 陈江彬 on 11/23/15.
//  Copyright © 2015 Ocustom. All rights reserved.
//

#import "OurButtonView.h"

@interface OurButtonView()
{
    NSString *observeKeyPath;
    BOOL haveRegistKVO;
}

@property (nonatomic, strong) UIImage *normalImage;
@property (nonatomic, strong) UIImage *highLightImage;

@end


@implementation OurButtonView

#pragma mark- 初始化
- (id)initWithFrame:(CGRect)frame imageSize:(CGSize)imageSize iconImage:(UIImage *)iconImage highlightImage:(UIImage *)highImage btnTag:(NSInteger)btnTag
{
    self = [super initWithFrame:frame];
    if (self)
    {
        haveRegistKVO = YES;
        observeKeyPath = @"highlighted";
        
        _normalImage = iconImage;
        _highLightImage = highImage;
        
        self.backBtn = [self createButtonWithTitle:nil backgroundImage:nil iconImage:nil highlightImage:nil tag:btnTag];
        [self.backBtn setFrame:CGRectMake(0, 0, frame.size.width, frame.size.height)];
        [self addSubview:self.backBtn];
        [self.backBtn addObserver:self forKeyPath:observeKeyPath options:NSKeyValueObservingOptionNew|NSKeyValueObservingOptionOld context:NULL];
        
        _iconImageView = [[UIImageView alloc] initWithFrame:CGRectMake((frame.size.width-imageSize.width)/2, (frame.size.height-imageSize.height)/2, imageSize.width, imageSize.height)];
        _iconImageView.image = _normalImage;
        [self addSubview:_iconImageView];
    }
    return self;
}

- (void)setIsDisabled:(BOOL)isDisabled
{
    _isDisabled = isDisabled;
    
    _backBtn.userInteractionEnabled = !isDisabled;
    
    if (_isDisabled)
    {
        _iconImageView.image = _disableImage;
    }
    else
    {
        _iconImageView.image = _normalImage;
    }
}

-(void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary *)change context:(void *)context
{
    if([keyPath isEqualToString:observeKeyPath])
    {
        if (self.backBtn.highlighted)
        {
            _iconImageView.image = _highLightImage;
        }
        else
        {
            [self performSelector:@selector(changeImageViewImage) withObject:nil afterDelay:0.1f];
        }
    }
}

- (void)changeImageViewImage
{
    _iconImageView.image = _normalImage;
}

- (void)viewButtonAction:(UIButton *)sender
{
    if (_block)
    {
        _block(sender.tag);
    }
}

- (void)removeViewObserve
{
    haveRegistKVO = NO;
    [_backBtn removeObserver:self forKeyPath:observeKeyPath];
}

- (void)setNormalImage:(UIImage *)normalImage1 highLightImage:(UIImage *)highLightImage1
{
    _iconImageView.image = normalImage1;
    _normalImage = normalImage1;
    _highLightImage = highLightImage1;
}

- (void)dealloc
{
    if (haveRegistKVO)
    {
        [self removeViewObserve];
    }
}




@end
