//
//  MBProgressHUD+ZWUI.h
//  ZWUI
//
//  Created by taic_cai on 16/8/24.
//  Copyright © 2016年 taic_cai. All rights reserved.
//

#import "MBProgressHUD.h"

@interface MBProgressHUD(ZWUI)

#pragma mark - show to view

//显示提示信息
+ (MBProgressHUD *)showTipHubWithMsg:(NSString *)msg addedTo:(UIView *)view;
//显示成功信息
+ (MBProgressHUD *)showSuccessHubWithMsg:(NSString *)msg addedTo:(UIView *)view;
//显示失败信息
+ (MBProgressHUD *)showErrorHubWithMsg:(NSString *)msg addedTo:(UIView *)view;
//显示进行中的信息，头部是类似菊花转的动画，底部为文字，可为空
+ (MBProgressHUD *)showLoadingHubWithMsg:(NSString *)msg addedTo:(UIView *)view;
+ (MBProgressHUD *)showLoadingHubAddedTo:(UIView *)view;


#pragma mark - Show To Window
//顯示提示信息,只顯示文字說明.當文字信息太長時,msg顯示簡單文字,具體提示信息放在detailsLabelText中進行顯示
+ (MBProgressHUD *)showWindowTipHUDWithMsg:(NSString *)msg;
//顯示成功信息,頭部是打勾的成功圖片,底部為文字說明
+ (MBProgressHUD *)showWindowSuccessHUDWithMsg:(NSString *)msg;
//顯示失敗信息,頭部是!的失敗圖片,底部為失敗的文字說明.當文字信息太長時,msg顯示簡單文字,具體錯誤信息放在detailsLabelText中進行顯示
+ (MBProgressHUD *)showWindowErrorHUDWithMsg:(NSString *)msg;
//顯示進行中的信息,頭部是菊花動畫,底部為文字說明,可為空
+ (MBProgressHUD *)showWindowLoadingHUD;	//無默認文字
+ (MBProgressHUD *)showWindowLoadingHUDWithMsg:(NSString *)msg;
//顯示處理進度的信息,頭部是處理進度動畫,底部為進度說明文字,可為空
+ (MBProgressHUD *)showWindowProgressingHUDWithMsg:(NSString *)msg;


@end

@interface UIView(MBProgressHUD_ZWUI)
/**
 *  返回子视图中的hud
 *
 *  @return @[MBProgressHUD]
 */
- (NSArray *)subviewsOfMBProgressHUD;
/**
 *  隐藏子视图中的所有hud
 *
 *  @param animated 是否动画
 */
- (void)hideAllMBProgressHUD:(BOOL)animated;
@end