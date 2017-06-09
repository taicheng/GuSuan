//
//  MainViewController.m
//  骰算
//
//  Created by taic_cai on 2016/12/23.
//  Copyright © 2016年 taic_cai. All rights reserved.
//

#import "MainViewController.h"

#import "JXAlertview.h"
#import "CulModel.h"
#import "NSObject+LKDBHelper.h"

@interface MainViewController ()<UITextFieldDelegate,CustomAlertDelegete>

@end

@implementation MainViewController

- (id)init {
    if (self = [super init]) {
        self.title = @"首页";
        self.tabBarItem.title = self.title;
        self.tabBarItem.image = [UIImage imageNamed:@"2More.png"];
    }
    return self;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    [self setupForSubViews];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(notifyAction:) name:@"SSCodeViewControllerImage" object:nil];
}
- (void)notifyAction:(NSNotification *)noty {
    UIImage *img = noty.object;
    self.img = img;
}
- (void)setupForSubViews {
    self.nameLabel =  [[UILabel alloc] init];
    self.nameLabel.font = [UIFont systemFontOfSize:14*ScreenMultiple];
    self.nameLabel.text = @"姓名:";
    [self.nameLabel sizeToFit];
    self.nameLabel.origin = CGPointMake(15*ScreenMultiple, 100*ScreenMultiple);
    [self.view addSubview:self.nameLabel];
    
    self.nameField = [[UITextField alloc] init];
    [self.nameField addTarget:self action:@selector(__nameChange:) forControlEvents:UIControlEventEditingChanged];
    self.nameField.borderStyle = UITextBorderStyleRoundedRect;
    self.nameField.layer.masksToBounds = YES;
    self.nameField.layer.borderColor = [UIColor blackColor].CGColor;
    self.nameField.layer.borderWidth = 1*ScreenMultiple;
    self.nameField.size = CGSizeMake(200*ScreenMultiple, 30*ScreenMultiple);
    self.nameField.left = self.nameLabel.right + 10*ScreenMultiple;
    self.nameField.centerY = self.nameLabel.centerY;
    self.nameField.layer.cornerRadius = 5*ScreenMultiple;
    [self.view addSubview:self.nameField];
    
    self.addTxtForShearPlate = [[UIButton alloc] init];
    [self.addTxtForShearPlate setTitle:@"粘贴剪切版中的文字" forState:UIControlStateNormal];
    [self.addTxtForShearPlate addTarget:self action:@selector(pasteTextFrom:) forControlEvents:UIControlEventTouchUpInside];
    self.addTxtForShearPlate.titleLabel.font = [UIFont systemFontOfSize:10*ScreenMultiple];
    CGSize fitsize1 = [self.addTxtForShearPlate sizeThatFits:kScreenSize];
    self.addTxtForShearPlate.left = self.nameField.left;
    self.addTxtForShearPlate.top = self.nameField.bottom + 8*ScreenMultiple;
    self.addTxtForShearPlate.size = CGSizeMake(fitsize1.width + 20*ScreenMultiple, fitsize1.height);
    [self.addTxtForShearPlate setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
    self.addTxtForShearPlate.layer.masksToBounds = YES;
    self.addTxtForShearPlate.layer.borderWidth = 0.5*ScreenMultiple;
    self.addTxtForShearPlate.layer.borderColor = [UIColor blackColor].CGColor;
    self.addTxtForShearPlate.layer.cornerRadius = 5*ScreenMultiple;
    [self.view addSubview:self.addTxtForShearPlate];
    
    
    self.birthLabel = [[UILabel alloc] init];
    self.birthLabel.font = [UIFont systemFontOfSize:14*ScreenMultiple];
    self.birthLabel.text = @"生日:";
    self.birthLabel.size = self.nameLabel.size;
    self.birthLabel.left = self.nameLabel.left;
    self.birthLabel.top = self.addTxtForShearPlate.bottom + 20*ScreenMultiple;
    [self.view addSubview:self.birthLabel];
    
    self.birthField = [[UITextField alloc] init];
    self.birthField.delegate = self;
    self.birthField.borderStyle = UITextBorderStyleRoundedRect;
    self.birthField.layer.masksToBounds = YES;
    self.birthField.layer.borderColor = [UIColor blackColor].CGColor;
    self.birthField.layer.borderWidth = 1*ScreenMultiple;
    self.birthField.layer.cornerRadius = 5*ScreenMultiple;
    self.birthField.size = CGSizeMake(200*ScreenMultiple, 30*ScreenMultiple);
    self.birthField.left = self.nameField.left;
    self.birthField.centerY = self.birthLabel.centerY;
    [self.view addSubview:self.birthField];
    self.Dpicker = [[CustomDatePicker alloc] initWithFrame:CGRectMake(0, 20*ScreenMultiple, self.view.frame.size.width-20*ScreenMultiple, 200*ScreenMultiple)];
    
    self.indexLabel = [[UILabel alloc] init];
    self.indexLabel.text = @"指定\n指数:";
    self.indexLabel.numberOfLines = 0;
    self.indexLabel.font = [UIFont systemFontOfSize:14*ScreenMultiple];
    CGSize fitsize2 = [self.indexLabel sizeThatFits:CGSizeMake(self.birthLabel.size.width, self.view.size.height)];
    self.indexLabel.size = fitsize2;
    self.indexLabel.left = self.nameLabel.left;
    self.indexLabel.top = self.birthField.bottom + 50*ScreenMultiple;
    [self.view addSubview:self.indexLabel];
    
    self.EQTField = [[UITextField alloc] init];
    [self.EQTField addTarget:self action:@selector(__EQChange:) forControlEvents:UIControlEventEditingChanged];
    self.EQTField.borderStyle = UITextBorderStyleRoundedRect;
    self.EQTField.keyboardType =  UIKeyboardTypeNumberPad;
    self.EQTField.size = CGSizeMake(60*ScreenMultiple, 30*ScreenMultiple);
    self.EQTField.left = self.birthField.left;
    self.EQTField.centerY = self.indexLabel.centerY;
    [self.view addSubview:self.EQTField];
    self.EQ = [[UILabel alloc] init];
    self.EQ.text = @"情商";
    self.EQ.font = [UIFont systemFontOfSize:14*ScreenMultiple];
    [self.EQ sizeToFit];
    self.EQ.bottom = self.EQTField.top - 5*ScreenMultiple;
    self.EQ.centerX = self.EQTField.centerX;
    [self.view addSubview:self.EQ];
    
    self.IQTField = [[UITextField alloc] init];
    [self.IQTField addTarget:self action:@selector(__IQChange:) forControlEvents:UIControlEventEditingChanged];
    self.IQTField.borderStyle = UITextBorderStyleRoundedRect;
    self.IQTField.frame = self.EQTField.frame;
    self.IQTField.keyboardType =  UIKeyboardTypeNumberPad;
    self.IQTField.left = self.EQTField.right + 10*ScreenMultiple;
    [self.view addSubview:self.IQTField];
    self.IQ = [[UILabel alloc] init];
    self.IQ.text = @"智商";
    self.IQ.font = [UIFont systemFontOfSize:14*ScreenMultiple];
    [self.IQ sizeToFit];
    self.IQ.bottom = self.IQTField.top - 5*ScreenMultiple;
    self.IQ.centerX = self.IQTField.centerX;
    [self.view addSubview:self.IQ];
    
    self.attractionTField = [[UITextField alloc] init];
    self.attractionTField.borderStyle = UITextBorderStyleRoundedRect;
    self.attractionTField.keyboardType =  UIKeyboardTypeNumberPad;
    [self.attractionTField addTarget:self action:@selector(__attraction:) forControlEvents:UIControlEventEditingChanged];
    self.attractionTField.frame = self.EQTField.frame;
    self.attractionTField.left = self.IQTField.right + 10*ScreenMultiple;
    [self.view addSubview:self.attractionTField];
    self.attraction = [[UILabel alloc] init];
    self.attraction.font = [UIFont systemFontOfSize:14*ScreenMultiple];;
    self.attraction.text = @"吸引力";
    [self.attraction sizeToFit];
    self.attraction.bottom = self.attractionTField.top - 5*ScreenMultiple;
    self.attraction.centerX = self.attractionTField.centerX;
    [self.view addSubview:self.attraction];
    
    self.resultBtn = [[UIButton alloc] init];
    [self.resultBtn setTitle:@"生成" forState:UIControlStateNormal];
    [self.resultBtn addTarget:self action:@selector(__productForResult:) forControlEvents:UIControlEventTouchUpInside];
    [self.resultBtn setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
    self.resultBtn.titleLabel.font = [UIFont systemFontOfSize:14*ScreenMultiple];
    self.resultBtn.size = CGSizeMake(200*ScreenMultiple, 30*ScreenMultiple);
    self.resultBtn.left = self.nameField.left;
    self.resultBtn.top = self.indexLabel.bottom + 40*ScreenMultiple;
    self.resultBtn.backgroundColor = [UIColor lightGrayColor];
    self.resultBtn.layer.masksToBounds = YES;
    self.resultBtn.layer.cornerRadius = 5*ScreenMultiple;
    [self.view addSubview:self.resultBtn];
    
}

- (void)__nameChange:(id)sender {
    
}
- (void)pasteTextFrom:(id)sender {
    UIPasteboard *pb = [UIPasteboard generalPasteboard];
    self.nameField.text = pb.string;
}
- (void)__EQChange:(id)sender {
    
}
- (void)__IQChange:(id)sender {
    
}
- (void)__attraction:(id)sender {
    
}
- (void)__productForResult:(id)sender {
    if (!self.nameField.text.length) {
        UIAlertController *alert = [UIAlertController alertControllerWithTitle:nil message:@"名字未填写完整！" preferredStyle:UIAlertControllerStyleAlert];
        UIAlertAction *cancleAction = [UIAlertAction actionWithTitle:@"知道了" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
            [alert dismissViewControllerAnimated:YES completion:nil];
        }];
        [alert addAction:cancleAction];
        [self presentViewController:alert animated:YES completion:nil];
        return;
    }
    CulModel *model = [[CulModel searchWithWhere:[NSString stringWithFormat:@"name is \"%@\"",self.nameField.text] orderBy:nil offset:0 count:1] firstObject];
    NSData *dataimge = [[NSUserDefaults standardUserDefaults] objectForKey:@"SSCodeVCUserDefaultImage"];
    self.img = [UIImage imageWithData:dataimge];
    if (!model) {
        NSArray *ord = [self autoIndex];
        model = [[CulModel alloc] init];
        model.name = self.nameField.text;
        model.birthDay = self.birthField.text;
        model.EQ = self.EQTField.text.length?[self.EQTField.text integerValue]:[[ord firstObject] intValue];
        model.IQ = self.IQTField.text.length?[self.IQTField.text integerValue]:[ord[1] intValue];
        model.attraction = self.attractionTField.text.length?[self.attractionTField.text integerValue]:[[ord lastObject] intValue];
        model.img = self.img;
        model.content = [self getContentWithAuto];
        [CulModel insertToDB:model];
    }else {
        model.img = self.img;
        [CulModel updateToDB:model where:nil];
    }
    self.EQTField.text = [NSString stringWithFormat:@"%@",@(model.EQ)];
    self.IQTField.text = [NSString stringWithFormat:@"%@",@(model.IQ)];
    self.attractionTField.text = [NSString stringWithFormat:@"%@",@(model.attraction)];
    if (self.whenDone) {
        self.whenDone(model);
    }
}
- (NSInteger)randIndex {
    NSInteger index = 100 + arc4random() % 80;
    return index;
}

- (NSArray *)autoIndex {
    NSInteger index =  450 + arc4random() % 20;
    NSInteger index1 = 120 + arc4random() % 60;
    NSInteger index2 = 120 + arc4random() % 60;
    NSInteger index3 = index - index2 - index1;
    NSArray *array1 = @[@(index1), @(index2), @(index3)];
    NSMutableArray *results = [[NSMutableArray alloc] initWithArray:array1];
    NSUInteger i = results.count;
    while(--i > 0) {
        int j = rand() % (i+1);
        [results exchangeObjectAtIndex:i withObjectAtIndex:j];
    }
    return results;
}
//- (NSInteger)randIndex {
//    CulModel *model = [[CulModel searchWithWhere:nil orderBy:nil offset:0 count:0] lastObject];
//    NSInteger result = 1;
//    NSInteger index = 1+ arc4random() % 3;
//    if (index==1) {
//        result = model.EQ;
//    }else if (index == 2) {
//        result =model.IQ;
//    }else {
//        result = model.attraction;
//    }
//    if (result <= 0) {
//        return 130;
//    }
//    return result +1;
//}
#pragma mark - uitextfielddelegate
-(BOOL)textFieldShouldBeginEditing:(UITextField *)textField
{
    [self.view endEditing:YES];
    JXAlertview *alert = [[JXAlertview alloc] initWithFrame:CGRectMake(10*ScreenMultiple, (self.view.frame.size.height-260*ScreenMultiple)/2, self.view.frame.size.width-20*ScreenMultiple, 260*ScreenMultiple)];
    //alert.image = [UIImage imageNamed:@"dikuang"];
    alert.delegate = self;
    [alert initwithtitle:@"请选择日期" andmessage:@"" andcancelbtn:@"取消" andotherbtn:@"确定"];
    
    //我把Dpicker添加到一个弹出框上展现出来 当然大家还是可以以任何其他动画形式展现
    [alert addSubview:self.Dpicker];
    [alert show];
    return NO;
}
-(void)btnindex:(int)index :(int)tag
{
    if (index == 2) {
        self.birthField.text = [NSString stringWithFormat:@"%d-%d-%d",self.Dpicker.year,self.Dpicker.month,self.Dpicker.day];
        [self.birthField resignFirstResponder];
    }
}

- (NSString *)getContentWithAuto {
    NSArray *array1 = @[@"你只看到我的冒险，却没看到我之前准备到凌晨四点；",
                        @"你只看到我的笑脸，却没看到我每天熬夜到几点；",
                        @"你只听到我的欢声笑语，却没看到我的独自沉默；",
                        @"你只看到我还没有很出息，却没看到我从未放弃；",
                        @"你只看到我工资的额度，却没看到我加班的次数；",
                        @"你只看到我的世故，却没看到我善良的成熟；",
                        @"你只看到我的勇敢面对，却没看我也曾因为害怕而惭愧；",
                        @"你只看到我的一手好牌，却没看到我也曾打过一手烂牌；",
                        @"你只看到我的笑而不语，却没看到我的痛而不言；"
                        ];
    NSInteger auto1 = arc4random()%array1.count;
    NSString *str1 = array1[auto1];
    
    NSArray *array2 = @[@"你有你的看法，我有我的观念；",
                        @"你有你的评价，我有我的理念；",
                        @"你有你的无奈，我有我的坚持；",
                        @"你有你的理由，我有我的想法；",
                        @"你有你的道理，我有我的性格；",
                        @"你有你的背景，我有我的实力；",
                        @"你有你的现实，我有我的梦想；",
                        @"你有你的顾 虑，我有我的诚意；",
                        @"你有你的放肆，我有我的克制；",
                        @"你有你的决定，我有我的选择；",
                        @"你有你的圆滑，我有我的原则；",
                        @"你有你的世故，我有我的成熟；",
                        ];
    NSInteger auto2 = arc4random()%array2.count;
    NSString *str2 = array2[auto2];
    
    NSArray *array3 = @[@"你嘲笑我认真做事，我可怜你不可一世；",
                        @"你嘲笑我一无所有不配去爱，我可怜你不懂付出只会等待；",
                        @"你嘲笑我一无是处，我可怜你没有气度；",
                        @"你嘲笑我不会示弱只会逞强，我可怜你经历太少不懂坚强；",
                        @"你嘲笑我工作辛苦收入还少，我可怜你游手好闲只会啃老；",
                        @"你嘲笑我事事上心没有安全感，我可怜你假装豁达其实是懒；",
                        @"你嘲笑我这么恋家因为缺爱，我可怜你未曾经历所以不懂爱；",
                        @"你嘲笑我嘴硬心软太感性，我可怜你不懂人情心太硬；",
                        @"你嘲笑我排队让座心眼实，我可怜你只为自己太自私；",
                        @"你嘲笑我没有心机太耿直，我可怜你机关算尽后悔迟；",
                        @"你嘲笑我常常折腾不稳定，我可怜你一眼到头没活力；",
                        @"你嘲笑我那么努力还是一事无成，我可怜你还没开始就过完这一生；",
                        @"你嘲笑我谦虚谨慎没有气场，我可怜你心高气傲朋友太少；",
                        @"你嘲笑我毕业多年没赚到钱，我可怜你只顾赚钱学业搁浅；",
                        @"你嘲笑我带着憧憬自我鼓励，我可怜你怨天尤人自暴自弃；",
                        ];
    NSInteger auto3 = arc4random()%array3.count;
    NSString *str3 = array3[auto3];
    
    NSArray *array4 = @[@"梦想注定是孤独的旅行，那又怎样，就算遍体鳞伤，也要追求到底。",
                        @"人生注定是孤独的旅行，那又怎样，就算受尽质疑，也要活得漂亮。",
                        @"优秀注定是孤独的属性，那又怎样，就算没人能懂，也要坚持自我。",
                        @"梦想总是被不断质疑，那又怎样，就算四周黑暗，也要点起自己的灯。",
                        @"人生本就是坎坷的路程，那又怎样，就算跌倒受伤，也要继续前行。",
                        @"人生注定是物质与精神的角逐，那又怎样，就算两败俱伤，也要永不停息。",
                        @"人生总是很难赢过所有人，那又怎样，就算从没赢过别人，也要赢过自己。",
                        @"人生总会受到打击，那又怎样，就算恋人离你而去，也要为了更好的明天拼命努力。",
                        ];
    NSInteger auto4 = arc4random()%array4.count;
    NSString *str4 = array4[auto4];
    NSString *str5 = [NSString stringWithFormat:@"我是%@，2017年，我为自己代言。",self.nameField.text];
    NSString *resultStr = [NSString stringWithFormat:@"%@%@%@%@\n%@",str1,str2,str3,str4,str5];
    return resultStr;
}
@end
