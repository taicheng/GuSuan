//
//  ZWTableViewSectionView.h
//  ZWUI
//
//  Created by taic_cai on 16/8/16.
//  Copyright © 2016年 taic_cai. All rights reserved.
//


#import <UIKit/UIKit.h>
#import "ZWTableViewSectionViewProtocol.h"
#define kZWTableViewSectionViewDefaultHeight 22
@interface ZWTableViewSectionView : UIView<ZWTableViewSectionViewProtocol>
@property(nonatomic,strong) UILabel *textLabel;
@end
