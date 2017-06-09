//
//  ZWFormElement.h
//  ZWUI
//
//  Created by taic_cai on 16/9/2.
//  Copyright © 2016年 taic_cai. All rights reserved.
//
#import "ZWTableViewCellModel.h"

@class ZWFormElement;

typedef void(^ZWFormElementB)(ZWFormElement *el);
typedef void(^ZWFormElementC)(ZWFormElement *el,id value);

@interface ZWFormElement : ZWTableViewCellModel
@property (nonatomic,strong) UIImage           *icon;//說明圖片
@property (nonatomic,strong) NSString          *title;//左側的文本
@property (nonatomic,strong) NSString		   *detail;//內文

@property (nonatomic,strong) NSString          *name;//表單中的name屬
@property (nonatomic,assign) BOOL              required;//是否是必填
@property (nonatomic,assign) BOOL			   canFocus;//是否可以獲得輸入焦點,默認是YES
@property (nonatomic,strong) id                value;//值對象

#pragma mark - action
@property (nonatomic,copy  ) ZWFormElementB    whenDone;//完成時執行的action
@property (nonatomic,copy  ) ZWFormElementB    whenCancel;//取消時執行的action
@property (nonatomic,copy  ) ZWFormElementC    whenChange;//value改變時執行的action
@property (nonatomic,readonly) NSString        *valueString;//返回value对应的字符串

- (id)initWithTitle:(NSString *)title name:(NSString *)name; //根據json字符串初始化

#pragma mark HTTP相關操作,子類重寫
- (BOOL)validWithError:(NSError **)error;	//合法性驗證
- (NSDictionary *)keyAndValues;	//返回對應的key=>value,用於js中的表單提交時,數據回調
@end
