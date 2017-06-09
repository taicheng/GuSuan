//
//  UIView+ZWUIUnreadBadge.h
//  ZWUI
//
//  Created by taic_cai on 2016/11/15.
//  Copyright © 2016年 taic_cai. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ZWUIUnreadBadgeProtocol.h"
@interface UIView (ZWUIUnreadBadge)
@property(nonatomic,assign) Class unreadBadgeClass;
+ (Class)unreadBadgeClass;//未读角标显示类,默认为HVUIUnreadBadgeView
@property(nonatomic,readonly) UIView<ZWUIUnreadBadgeProtocol> *unreadBadgeView;

/**
 *  设置未读数
 *
 *  @param count    未读数
 *  @param animated 是否动画
 */
- (void)setUnreadCount:(NSInteger)count animated:(BOOL)animated;
@end
