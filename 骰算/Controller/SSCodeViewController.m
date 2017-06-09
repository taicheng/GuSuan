//
//  SSCodeViewController.m
//  骰算
//
//  Created by taic_cai on 2016/12/26.
//  Copyright © 2016年 taic_cai. All rights reserved.
//

#import "SSCodeViewController.h"
#import "SCMakeImage.h"
#import "CulModel.h"
#import <CoreText/CoreText.h>
#import "LKDBHelper.h"

@interface SSCodeViewController ()
@property (nonatomic,strong)  UIButton     *uploadBtn;
@property (nonatomic, strong) SCMakeImage *scMakeImage;

@property (nonatomic, strong) UIButton     *deleteBtn;
@end

@implementation SSCodeViewController

- (id)init {
    if (self = [super init]) {
        self.title = @"二维码";
        self.tabBarItem.title = self.title;
        self.tabBarItem.image = [UIImage imageNamed:@"7picture.png"];
    }
    return self;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    NSData *dataimge = [[NSUserDefaults standardUserDefaults] objectForKey:@"SSCodeVCUserDefaultImage"];
    UIImage *img = [UIImage imageWithData:dataimge];
    if (img) {
        self.imgV = [[UIImageView alloc] initWithImage:img];
    }else {
        self.imgV = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"icon_loadingSquare.png"]];
    }
    self.imgV.size = CGSizeMake(200*ScreenMultiple, 200*ScreenMultiple);
    self.imgV.center = self.view.center;
    self.imgV.centerY -= 100;
    self.imgV.layer.masksToBounds = YES;
    self.imgV.layer.borderColor = [UIColor grayColor].CGColor;
    self.imgV.layer.borderWidth = 1*ScreenMultiple;
    [self.view addSubview:self.imgV];
    
    self.uploadBtn = [[UIButton alloc] init];
    [self.uploadBtn setTitle:@"上传" forState:UIControlStateNormal];
    [self.uploadBtn addTarget:self action:@selector(uploadImg:) forControlEvents:UIControlEventTouchUpInside];
    self.uploadBtn.backgroundColor = [UIColor  lightGrayColor];
    self.uploadBtn.layer.masksToBounds = YES;
    self.uploadBtn.layer.cornerRadius = 6*ScreenMultiple;
    [self.uploadBtn setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
    self.uploadBtn.size = CGSizeMake(200*ScreenMultiple, 35*ScreenMultiple);
    self.uploadBtn.top = self.imgV.bottom + 40*ScreenMultiple;
    self.uploadBtn.centerX = self.view.centerX;
    [self.view addSubview:self.uploadBtn];
    
    self.deleteBtn = [[UIButton alloc] init];
    [self.deleteBtn setTitle:@"清空数据" forState:UIControlStateNormal];
    [self.deleteBtn addTarget:self action:@selector(__actionForDeleteData) forControlEvents:UIControlEventTouchUpInside];
    self.deleteBtn.backgroundColor = [UIColor  lightGrayColor];
    self.deleteBtn.layer.masksToBounds = YES;
    self.deleteBtn.layer.cornerRadius = 6*ScreenMultiple;
    [self.deleteBtn setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
    self.deleteBtn.size = CGSizeMake(200*ScreenMultiple, 35*ScreenMultiple);
    self.deleteBtn.top = self.uploadBtn.bottom + 30*ScreenMultiple;
    self.deleteBtn.centerX = self.view.centerX;
    [self.view addSubview:self.deleteBtn];
    
//    CGFloat spacer = 15*ScreenMultiple;
//    UIButton *btn1 = [[UIButton alloc] init];
//    [btn1 setTitle:@"下载字体" forState:UIControlStateNormal];
//    [btn1 addTarget:self action:@selector(__actionforDownloadFont) forControlEvents:UIControlEventTouchUpInside];
//    btn1.backgroundColor = [UIColor  lightGrayColor];
//    [btn1 sizeToFit];
//    btn1.left = spacer;
//    btn1.top = self.deleteBtn.bottom + 20*ScreenMultiple;
//    [self.view addSubview:btn1];
}

- (BOOL)__actionforDownloadFont {
    UIFont *font = [UIFont fontWithName:@"Varsity" size:12];
    NSMutableDictionary *fontAttrs = [NSMutableDictionary dictionaryWithObjectsAndKeys:@"STHeitiSC-Light", kCTFontNameAttribute, nil];
    CTFontDescriptorRef desc = CTFontDescriptorCreateWithAttributes((__bridge CFDictionaryRef)fontAttrs);
    NSMutableArray *descArray = [NSMutableArray new];
    [descArray addObject:(__bridge id)desc];
    CFRelease(desc);
    //封装成一个CF的字体对象
    
    //将对象传入，进行下载
    CTFontDescriptorMatchFontDescriptorsWithProgressHandler((__bridge CFArrayRef)descArray, NULL, ^bool(CTFontDescriptorMatchingState state, CFDictionaryRef  _Nonnull progressParameter) {
        NSDictionary *progressDic = (__bridge NSDictionary *)progressParameter;
        NSLog(@"state: %u",state);
        NSLog(@"progress: %@",progressDic);
        UIFont *font = [UIFont fontWithName:@"Varsity" size:12];
        return YES;
    });
    return YES;
}

- (void)uploadImg:(id)sender {
    self.scMakeImage = [[SCMakeImage alloc] init];
    self.scMakeImage.pushFromViewController = self;
    @weakify(self);
    self.scMakeImage.makeImageBlock = ^(UIImage *image) {
        @normalize(self);
        NSData *dataimge = UIImagePNGRepresentation(image);
        [[NSNotificationCenter defaultCenter] postNotificationName:@"SSCodeViewControllerImage" object:image];
        [[NSUserDefaults standardUserDefaults] setObject:dataimge forKey:@"SSCodeVCUserDefaultImage"];
        [[NSUserDefaults standardUserDefaults] synchronize];
        self.imgV.image = image;
    };
    [self.scMakeImage selectFromPhotoAlbum];
}

- (void)__actionForDeleteData {
    UIAlertController *alert = [UIAlertController alertControllerWithTitle:nil message:@"确认清空数据？" preferredStyle:UIAlertControllerStyleAlert];
    @weakify(self);
    @weakify(alert);
    UIAlertAction *cancleAction = [UIAlertAction actionWithTitle:@"取消" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
        @normalize(alert);
        [alert dismissViewControllerAnimated:YES completion:nil];
    }];
    UIAlertAction *checkAction = [UIAlertAction actionWithTitle:@"确定" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
        @normalize(alert);
        [LKDBHelper clearTableData:[CulModel class]];
        [alert dismissViewControllerAnimated:YES completion:^{
            @normalize(self);
            [self showViewTipHubWithMsg:@"清空数据成功！"];
        }];
    }];
    [alert addAction:cancleAction];
    [alert addAction:checkAction];
    [self presentViewController:alert animated:YES completion:nil];

}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
