//
//  OurBaseView.h
//  FingerInteract
//
//  Created by 陈江彬 on 11/19/15.
//  Copyright © 2015 Ocustom. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface OurBaseView : UIView

AS_SINGLETON(OurBaseView);

/**Interface
 * @brief:创建按钮
 *
 */
- (UIButton*)createButtonWithTitle:(NSString *)titleT backgroundImage:(UIImage *)backgroundImage iconImage:(UIImage *)iconImage highlightImage:(UIImage *)highLightImage tag:(NSInteger)tagN;

/**
 *  创建按钮
 */
- (UIButton *)createButtonWithTitle:(NSString *)titleT titleColor:(UIColor *)titleColr titleFont:(UIFont *)titleFont tag:(NSInteger)tagN;


/**Interface
 * @brief:创建Label
 *
 */
- (UILabel *)createLabelWithText:(NSString *)text font:(UIFont *)font textColor:(UIColor *)textColor textAlignment:(NSTextAlignment)textAlignment;


- (UITextField *)createTextFieldWithText:(NSString *)text font:(UIFont*)font textColor:(UIColor *)textColor textAlignment:(NSTextAlignment)textAlignment;
@end
