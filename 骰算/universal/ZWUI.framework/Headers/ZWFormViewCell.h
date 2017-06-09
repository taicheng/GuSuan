//
//  ZWFormViewCell.h
//  ZWUI
//
//  Created by taic_cai on 16/9/2.
//  Copyright © 2016年 taic_cai. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "UITableViewCell+ZWTableViewCell.h"

//单元格的默认高度
#define kZWFormViewCellDefaultHeight 44
#define kZWFormViewCellMargin UIEdgeInsetsMake(14, 15, 14, 15);
#define kZWFormViewCellAccessoryWidth 34

@class ZWFormElement;
@interface ZWFormViewCell : UITableViewCell<ZWTableViewCellProtocol>
/**
 *  返回内容的边距,默认是UIEdgeInsetsMake(14, 15, 14, 15)
 *
 *  @return 边距
 */
+ (UIEdgeInsets)contentMarginInsets;
@property (nonatomic,readonly) CGFloat rightContentMargin;//根据是否有accessoryView,得出适合的右边距
@property (nonatomic,strong) ZWFormElement *element;//表單數據
@property (nonatomic,strong) UIImageView *elementIconImageView;//图标
@property (nonatomic,strong) UILabel *elementTitleLabel;//说明文本
@end
