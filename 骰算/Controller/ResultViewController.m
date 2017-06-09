//
//  ResultViewController.m
//  骰算
//
//  Created by taic_cai on 2016/12/26.
//  Copyright © 2016年 taic_cai. All rights reserved.
//

#import "ResultViewController.h"
#import "SSResultView.h"

@interface ResultViewController ()
@property (nonatomic, strong) SSResultView *resultView;
@property (nonatomic, strong) UIButton     *saveImg;
@end

@implementation ResultViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    [self setTopViewWithTitle:nil leftBtn:nil rightBtnArray:nil rightBtnTagsArray:nil hidden:NO];
    self.view.backgroundColor = [UIColor whiteColor];
    
    self.resultView = [[SSResultView alloc] initWithFrame:CGRectMake(0, 100*ScreenMultiple, self.view.width, kScreenHeight-230*ScreenMultiple)];
    self.resultView.model = self.model;
    self.resultView.height = [self.resultView getAutoHeight];
    [self.view addSubview:self.resultView];
    
    self.saveImg = [[UIButton alloc] init];
    [self.saveImg setTitle:@"复制图片" forState:UIControlStateNormal];
    [self.saveImg addTarget:self action:@selector(__actionForSaveImg) forControlEvents:UIControlEventTouchUpInside];
    self.saveImg.layer.masksToBounds = YES;
    self.saveImg.backgroundColor = [UIColor lightGrayColor];
    self.saveImg.layer.cornerRadius = 5*ScreenMultiple;
    [self.view addSubview:self.saveImg];
}

- (void)__actionForSaveImg {
    UIGraphicsBeginImageContextWithOptions(self.resultView.size, 0.0, 0.0);
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGContextTranslateCTM(context, 0, 0);
    [self.resultView.layer renderInContext:context];
    
    UIImage *image = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
     UIImageWriteToSavedPhotosAlbum(image, self, @selector(imageSavedToPhotosAlbum:didFinishSavingWithError:contextInfo:), nil);
}
- (void)imageSavedToPhotosAlbum:(UIImage *)image didFinishSavingWithError:(NSError *)error contextInfo:(void *)contextInfo
{
    NSString *message = @"呵呵";
    if (!error) {
        message = @"成功保存到相册";
    }else
    {
        message = [error description];
    }
    [self showViewTipHubWithMsg:message];
//    UIAlertController *alert = [UIAlertController alertControllerWithTitle:nil message:message preferredStyle:UIAlertControllerStyleAlert];
//    UIAlertAction *cancleAction = [UIAlertAction actionWithTitle:@"知道了" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
//        [alert dismissViewControllerAnimated:YES completion:nil];
//    }];
//    [alert addAction:cancleAction];
//    [self presentViewController:alert animated:YES completion:nil];
}

- (UIImage *)scaleToSize:(UIImage *)img size:(CGSize)size{
         // 创建一个bitmap的context
     // 并把它设置成为当前正在使用的context
         UIGraphicsBeginImageContext(size);
         // 绘制改变大小的图片
         [img drawInRect:CGRectMake(0, 0, size.width, size.height)];
         // 从当前context中创建一个改变大小后的图片
         UIImage* scaledImage = UIGraphicsGetImageFromCurrentImageContext();
         // 使当前的context出堆栈
         UIGraphicsEndImageContext();
         // 返回新的改变大小后的图片
         return scaledImage;
    
}

- (void)buttonAction:(UIButton *)sender {
    if (sender.tag == 25837) {
        @weakify(self);
        [self dismissViewControllerAnimated:YES completion:^{
            @normalize(self);
            if (self.whenDismiss) {
                self.whenDismiss();
            }
        }];
    }
}

- (void)viewDidLayoutSubviews {
    [super viewDidLayoutSubviews];    
    self.saveImg.size = CGSizeMake(200*ScreenMultiple, 35*ScreenMultiple);
    self.saveImg.top = self.resultView.bottom + 20*ScreenMultiple;
    self.saveImg.centerX = self.view.centerX;
}

@end
