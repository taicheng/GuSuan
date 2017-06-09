//
//  SSTabBarViewController.m
//  骰算
//
//  Created by taic_cai on 2016/12/26.
//  Copyright © 2016年 taic_cai. All rights reserved.
//

#import "SSTabBarViewController.h"
#import "SSCodeViewController.h"
#import "MainViewController.h"
#import "ResultViewController.h"

@interface SSTabBarViewController ()<UITabBarControllerDelegate>
@property (nonatomic, strong) SSCodeViewController *codeVC;
@property (nonatomic, strong) MainViewController *mainVC;
@end

@implementation SSTabBarViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    self.view.backgroundColor = [UIColor whiteColor];
    self.edgesForExtendedLayout = UIRectEdgeNone;
    self.tabBar.translucent = NO;
    self.tabBar.tintColor = [UIColor colorWithRed:0 green:0.5 blue:1 alpha:1];
    self.delegate = self;
    self.viewControllers = @[
                             self.mainVC,
                             self.codeVC,
                             ];
    self.title = self.selectedViewController.title;
    [self tabBarController:self didSelectViewController:[self mainVC]];
    self.selectedIndex = [self.viewControllers indexOfObject:self.mainVC];
}
- (SSCodeViewController *)codeVC {
    if (!_codeVC) {
        _codeVC = [[SSCodeViewController alloc] init];
    }
    return _codeVC;
}
- (MainViewController *)mainVC {
    if (!_mainVC) {
        _mainVC = [[MainViewController alloc] init];
    }
    @weakify(self);
    _mainVC.whenDone = ^(CulModel *model) {
        @normalize(self);
        ResultViewController *resultVC = [[ResultViewController alloc] init];
        resultVC.model = model;
        resultVC.whenDismiss = ^(void){
            @normalize(self);
            self.mainVC.EQTField.text = nil;
            self.mainVC.IQTField.text = nil;
            self.mainVC.attractionTField.text = nil;
            self.mainVC.birthField.text = nil;
            self.mainVC.nameField.text = nil;
        };
        [self presentViewController:resultVC animated:YES
                                              completion:^{
                                                  
                                              }];
    };
    return _mainVC;
}
#pragma mark - delegate:UITabBarControllerDelegate
- (void)tabBarController:(UITabBarController *)tabBarController didSelectViewController:(UIViewController *)viewController{
    self.title = viewController.title;
    UIBarButtonItem *item = viewController.navigationItem.rightBarButtonItem;
    self.navigationItem.rightBarButtonItem = item;
}

@end
