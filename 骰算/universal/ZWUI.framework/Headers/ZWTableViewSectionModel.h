//
//  ZWTableViewSectionModel.h
//  ZWUI
//
//  Created by taic_cai on 16/8/16.
//  Copyright © 2016年 taic_cai. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "ZWCollection_Header.h"

@class ZWTableViewModel,ZWTableViewCellModel,ZWTableViewSectionModel;
@protocol ZWTableViewSectionViewProtocol;

typedef void(^ZWTableViewSectionModelS)(ZWTableViewSectionModel *sectionModel,UIView *view);	//繪製該數據時觸發的動作

@interface ZWTableViewSectionModel : ZWCollectionSectionModel{
}
@property(nonatomic,strong) NSString *indexTitle;//本組的索引字符串
@property(nonatomic,assign) Class<ZWTableViewSectionViewProtocol> headViewClass;//默認是UIView
@property(nonatomic,assign) Class<ZWTableViewSectionViewProtocol> footViewClass;//默認是UIView

@property(nonatomic,assign) BOOL showHeadView;//是否顯示頭部視圖,默認為否
@property(nonatomic,assign) BOOL showFootView;//是否顯示尾部視圖,默認為否
@property(nonatomic,assign) BOOL showDefaultHeadView;//是否使用系統默認的頭部,默認為NO
@property(nonatomic,assign) BOOL showDefaultFootView;//是否使用系統默認的尾部,默認為NO
@property(nonatomic,assign) CGFloat headViewHeight;//使用系統默認的視圖時,head視圖高度
@property(nonatomic,assign) CGFloat footViewHeight;//使用系統默認的視圖時,foot視圖高度
@property(nonatomic,strong) NSString *headTitle;//head區域的字符串
@property(nonatomic,strong) NSString *footTitle;//foot區域的字符串

@property(nonatomic,assign) UITableView *tableView;//弱引用外部的tableview
@property(nonatomic,assign) ZWTableViewModel *tableViewModel;

@property(nonatomic,copy) ZWTableViewSectionModelS whenShowHeadView;//顯示自定義head視圖的繪製block
@property(nonatomic,copy) ZWTableViewSectionModelS whenShowFootView;//顯示自定義foot視圖的繪製block

- (ZWTableViewCellModel *)cellModelAtIndex:(NSInteger)index;

/**
 *  初始化一个显示空白头部的分组
 *
 *  @param height 头部的高度
 *
 *  @return 分组
 */
- (id)initWithBlankHeadView:(CGFloat)height;

/**
 *  初始化一个显示空白尾部的分组
 *
 *  @param height 尾部的高度
 *
 *  @return 分组
 */
- (id)initWithBlankFootView:(CGFloat)height;

/**
 *  初始化一个显示空白头部/尾部的分组
 *
 *  @param headViewHeight 头部高度
 *  @param footViewHeight 尾部高度
 *
 *  @return 分组
 */
- (id)initWithBlankHeadView:(CGFloat)headViewHeight footView:(CGFloat)footViewHeight;

/**
 *  设置显示系统默认的头部视图
 *
 *  @param height 视图高度
 */
- (void)showDefaultHeadViewWithHeight:(CGFloat)height;
/**
 *  设置显示系统默认的尾部视图
 *
 *  @param height 视图高度
 */
- (void)showDefaultFootViewWithHeight:(CGFloat)height;

- (void)displayHeadView:(UIView<ZWTableViewSectionViewProtocol> *)view;
- (void)displayFootView:(UIView<ZWTableViewSectionViewProtocol> *)view;

- (void)refresh;//刷新整個section
@end



@interface ZWTableViewSectionModel(NS_DEPRECATED_IOS)//将要被废弃的接口
@property (nonatomic,strong) NSMutableArray   *cells;//本組底下的單元格對象

/**
 *	添加单元格
 */
- (void)addCellModel:(ZWTableViewCellModel *)cellModel atIndex:(NSInteger)index;

/**
 *	清空所有數據
 */
- (void)removeAllCells;
@end
