//
//  ZWUICollectionViewTitleSupplementaryView.h
//  ZWUI
//
//  Created by taic_cai on 16/8/15.
//  Copyright © 2016年 taic_cai. All rights reserved.
//

#import "ZWUICollectionViewSupplementaryView.h"
#import "ZWUICollectionViewTitleSupplementarySectionModel.h"

@interface ZWUICollectionViewTitleSupplementaryView : ZWUICollectionViewSupplementaryView


@property(nonatomic,strong) ZWUICollectionViewTitleSupplementarySectionModel *titleSectionModel;
@property(nonatomic,strong) UILabel *textLabel;

+ (instancetype)shareInstance;//此单例用于动态高度的计算
+ (UIEdgeInsets)contentInsets;

@end