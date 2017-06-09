//
//  SSResultView.m
//  骰算
//
//  Created by taic_cai on 2016/12/26.
//  Copyright © 2016年 taic_cai. All rights reserved.
//

#import "SSResultView.h"
#import <CoreText/CoreText.h>

@interface SSResultView ()
@property (nonatomic, strong) UILabel *nameLabel;
@property (nonatomic, strong) UILabel *EQLabel;
@property (nonatomic, strong) UILabel *IQLabel;
@property (nonatomic, strong) UILabel *attractLabel;

@property (nonatomic, strong) UILabel *contentView;

@property (nonatomic, strong) UIImageView *imageView;
@property (nonatomic, strong) UIButton    *longBtn;
@property (nonatomic, strong) UILabel     *noteLabel;
@end
@implementation SSResultView

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        UIFont *fontD = [self customFontWithPath:nil size:20*ScreenMultiple];
        self.backgroundColor = [UIColor blackColor];
        self.nameLabel = [[UILabel alloc] init];
        self.nameLabel.textColor = [UIColor whiteColor];
        self.nameLabel.backgroundColor = [UIColor clearColor];
        self.nameLabel.font = [self customFontWithPath:nil size:52*ScreenMultiple];
        [self addSubview:self.nameLabel];
        
        UIColor *textColor = [UIColor orangeColor];
        UIFont *font1 = [self customFontWithPath:nil size:23*ScreenMultiple];
        self.EQLabel = [self createLabelWithText:nil font:font1 textColor:textColor textAlignment:NSTextAlignmentCenter];
        self.EQLabel.backgroundColor = [UIColor clearColor];
        [self addSubview:self.EQLabel];
        
        self.IQLabel = [self createLabelWithText:nil font:font1 textColor:textColor textAlignment:1];
        [self addSubview:self.IQLabel];
        self.attractLabel = [self createLabelWithText:nil font:font1 textColor:textColor textAlignment:1];
        [self addSubview:self.attractLabel];
        
        NSArray *familyNames = [[NSArray alloc] initWithArray:[UIFont familyNames]];
        NSArray *fontNames;
        NSInteger indFamily, indFont;
        for (indFamily=0; indFamily<[familyNames count]; ++indFamily)
        {
            NSLog(@"Family name: %@", [familyNames objectAtIndex:indFamily]);
            fontNames = [[NSArray alloc] initWithArray:
                         [UIFont fontNamesForFamilyName:
                          [familyNames objectAtIndex:indFamily]]];
            for (indFont=0; indFont<[fontNames count]; ++indFont)
            {
                NSLog(@"    Font name: %@", [fontNames objectAtIndex:indFont]);
            }
        }
        
        
        self.contentView = [self createLabelWithText:nil font:fontD textColor:[UIColor whiteColor] textAlignment:NSTextAlignmentLeft];
        self.contentView.numberOfLines = 0;
        [self addSubview:self.contentView];
        
        self.imageView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"icon_loadingSquare.png"]];
        [self addSubview:self.imageView];
        
        self.noteLabel = [self createLabelWithText:@"长按识别二维码\n为自己的2017年代言" font:[UIFont systemFontOfSize:15*ScreenMultiple] textColor:[UIColor whiteColor] textAlignment:NSTextAlignmentLeft];
        self.noteLabel.numberOfLines = 0;
        
        [self addSubview:self.noteLabel];
    }
    return self;
}

- (void)setModel:(CulModel *)model {
    self.nameLabel.text = model.name;
    self.EQLabel.text = [NSString stringWithFormat:@"情商 %ld",(long)model.EQ];
    self.IQLabel.text = [NSString stringWithFormat:@"智商 %ld",(long)model.IQ];
    self.attractLabel.text = [NSString stringWithFormat:@"吸引力 %ld",(long)model.attraction];
    
    self.contentView.text = model.content;
    self.imageView.image = model.img?model.img:[UIImage imageNamed:@"icon_loadingSquare.png"];
}

- (void)layoutSubviews {
    [super layoutSubviews];
    CGFloat spacer = 15*ScreenMultiple;
    
    [self.nameLabel sizeToFit];
    self.nameLabel.top = 44*ScreenMultiple;
    self.nameLabel.centerX = self.centerX;
    
    [self.EQLabel sizeToFit];
    self.EQLabel.top = self.nameLabel.bottom + 10*ScreenMultiple;
    self.EQLabel.left = spacer;
    
    [self.attractLabel sizeToFit];
    self.attractLabel.right = self.width - spacer;
    self.attractLabel.top = self.EQLabel.top;
    
    [self.IQLabel sizeToFit];
    self.IQLabel.top = self.EQLabel.top;
    self.IQLabel.centerX = self.EQLabel.right + (self.width - self.EQLabel.right - self.attractLabel.width - spacer)/2;
    
    CGSize fitsize = [self.contentView sizeThatFits:CGSizeMake(self.width- spacer*2, kScreenHeight)];
    self.contentView.size = fitsize;
    self.contentView.left = spacer;
    self.contentView.top = self.EQLabel.bottom + 20*ScreenMultiple;
    
    self.imageView.size = CGSizeMake(72*ScreenMultiple, 72*ScreenMultiple);
    self.imageView.top = self.contentView.bottom + 30*ScreenMultiple;
    
    [self.noteLabel sizeToFit];
    self.noteLabel.centerY = self.imageView.centerY;
    self.imageView.left = (self.width - (self.imageView.width + self.noteLabel.width + 20*ScreenMultiple))/2;
    self.noteLabel.left = self.imageView.right + 20*ScreenMultiple;
}

- (CGFloat)getAutoHeight {
    CGFloat spacer = 15*ScreenMultiple;
    
    [self.nameLabel sizeToFit];
    self.nameLabel.top = 20*ScreenMultiple;
    self.nameLabel.centerX = self.centerX;
    
    [self.EQLabel sizeToFit];
    self.EQLabel.top = self.nameLabel.bottom + 10*ScreenMultiple;
    self.EQLabel.left = spacer;
    
    [self.IQLabel sizeToFit];
    self.IQLabel.top = self.EQLabel.top;
    self.IQLabel.centerX = self.centerX;
    
    [self.attractLabel sizeToFit];
    self.attractLabel.right = self.width - spacer;
    self.attractLabel.top = self.EQLabel.top;
    
    CGSize fitsize = [self.contentView sizeThatFits:CGSizeMake(self.width- spacer*2, kScreenHeight)];
    self.contentView.size = fitsize;
    self.contentView.left = spacer;
    self.contentView.top = self.EQLabel.bottom + 20*ScreenMultiple;
    
    self.imageView.size = CGSizeMake(72*ScreenMultiple, 72*ScreenMultiple);
    self.imageView.left = spacer;
    self.imageView.top = self.contentView.bottom + 30*ScreenMultiple;
    
    [self.noteLabel sizeToFit];
    self.noteLabel.left = self.imageView.right + 40*ScreenMultiple;
    self.noteLabel.centerY = self.imageView.centerY;
    return self.noteLabel.bottom + 70*ScreenMultiple;
}
-(UIFont*)customFontWithPath:(NSString*)path size:(CGFloat)size
{
//    NSString *databasePath = [NSHomeDirectory() stringByAppendingPathComponent:@"Documents/Font"];
//    NSString *filthPath = [databasePath stringByAppendingPathComponent:[NSString stringWithFormat:@"HYy2gj.ttf"]];
    path = [[NSBundle mainBundle] pathForResource:@"TTYouErJ" ofType:@".ttf"];//字体，目前是放在app里面
    
    NSURL *fontUrl = [NSURL fileURLWithPath:path];
    CGDataProviderRef fontDataProvider = CGDataProviderCreateWithURL((__bridge CFURLRef)fontUrl);
    CGFontRef fontRef = CGFontCreateWithDataProvider(fontDataProvider);
    CGDataProviderRelease(fontDataProvider);
    CTFontManagerRegisterGraphicsFont(fontRef, NULL);
    NSString *fontName = CFBridgingRelease(CGFontCopyPostScriptName(fontRef));
    UIFont *font = [UIFont fontWithName:fontName size:size];
    CGFontRelease(fontRef);
    return font;
}
@end
