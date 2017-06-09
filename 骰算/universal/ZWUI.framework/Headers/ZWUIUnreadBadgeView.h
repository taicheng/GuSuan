//
//  ZWUIUnreadBadgeView.h
//  ZWUI
//
//  Created by taic_cai on 2016/11/15.
//  Copyright © 2016年 taic_cai. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ZWUIUnreadBadgeProtocol.h"

@interface ZWUIUnreadBadgeView : UIView<ZWUIUnreadBadgeProtocol>
@property(nonatomic,strong) UIView *backgroundView;//圆角背景视图
@property(nonatomic,strong) UILabel *countLabel;//显示数量的文本

/**
 *  与外层容器的内边距,配合self.autoresizingMask属性,进行布局.默认为右上角布局,self.autoresizingMask = UIViewAutoresizingFlexibleLeftMargin|UIViewAutoresizingFlexibleBottomMargin
	默认值为(0,0,0,0)
 *w
 *  @return 边距
 */
+ (UIEdgeInsets)contentInsets;

/**
 *  返回未读数对应的字符串.默认的显示规则为
 count:(,0]=>0
 count:(0,99]=>count
 count:(99,)=>99+
 *
 *  @param count 未读数
 *
 *  @return 对应的字符串
 */
+ (NSString *)stringWithUnreadCount:(NSInteger)count;
@end
