//
//  ZWTableViewSectionAdjustsView.h
//  ZWUI
//
//  Created by taic_cai on 16/8/16.
//  Copyright © 2016年 taic_cai. All rights reserved.
//

#import "ZWTableViewSectionView.h"

@interface ZWTableViewSectionAdjustsView : ZWTableViewSectionView
+ (instancetype)shareInstance;//此单例用于动态高度的计算
+ (UIEdgeInsets)contentMargin;//返回UIEdgeInsetsMake(8, 16, 8, 16)
/**
 *  只显示头部,分组高度自适应
 *
 *  @param title 标题
 *
 *  @return 分组
 */
+ (ZWTableViewSectionModel *)sectionModelWithHeadTitle:(NSString *)title;
/**
 *  只显示尾部,分组高度自适应
 *
 *  @param title 标题
 *
 *  @return 分组
 */
+ (ZWTableViewSectionModel *)sectionModelWithFootTitle:(NSString *)title;

/**
 *  分组高度自适应
 *
 *  @param headTitle 头部标题
 *  @param footTitle 尾部标题
 *
 *  @return 分组
 */
+ (ZWTableViewSectionModel *)sectionModelWithHeadTitle:(NSString *)headTitle footTitle:(NSString *)footTitle;
@end