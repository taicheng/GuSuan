//
//  ZWUIUnreadBadgeProtocol.h
//  ZWUI
//
//  Created by taic_cai on 2016/11/15.
//  Copyright © 2016年 taic_cai. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
@protocol ZWUIUnreadBadgeProtocol <NSObject>
/**
 *  设置未读角标.一般情况下,当未读数为0时,应该隐藏掉未读角标视图.
 *
 *  @param count    未读数
 *  @param view		要显示未读消息的视图
 *  @param animated 是否动画
 */
- (void)setUnreadCount:(NSInteger)count toView:(UIView *)view animated:(BOOL)animated;
@end
