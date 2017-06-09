//
//  ZWTableViewCellModel.h
//  ZWUI
//
//  Created by taic_cai on 16/8/16.
//  Copyright © 2016年 taic_cai. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "ZWCollection_Header.h"

@class ZWTableViewModel,ZWTableViewSectionModel,ZWTableViewCellModel;
@protocol ZWTableViewCellProtocol;


typedef void(^ZWTableViewCellModelBlockC)(ZWTableViewCellModel *cellModel);	//點擊該數據時觸發的動作
typedef void(^ZWTableViewCellModelBlockP)(ZWTableViewCellModel *cellModel,BOOL selected);	//被触控事件选中是触发
typedef BOOL(^ZWTableViewCellModelBlockD)(ZWTableViewCellModel *cellModel);	//刪除數據時觸發的動作
typedef BOOL(^ZWTableViewCellModelBlockM)(ZWTableViewCellModel *src,
                                          ZWTableViewCellModel *dst);	//移動數據時觸發的動作
typedef void(^ZWTableViewCellModelBlockS)(ZWTableViewCellModel *cellModel,
                                          UITableViewCell<ZWTableViewCellProtocol> *cellView);	//繪製該數據時觸發的動作

@interface ZWTableViewCellModel : ZWCollectionCellModel{
@protected
    BOOL _selected;
    NSString *_reuseIdentity;
}
@property(nonatomic,assign) Class<ZWTableViewCellProtocol> cellClass;			//對應的cell類,實例化時默認設置為UITableViewCell
@property(nonatomic,strong) UITableViewCell<ZWTableViewCellProtocol> *staticTableViewCell;//静态的单元格,会替换cellClass的动态实例化.静态单元格的使用情景之一:表单的多行文本输入,随着输入,行数会自动变化,如果采用cellClass机制,reload cell时会导致cell被重新实例化或者cell被移出再移入tableView,从而cell失去焦点.

@property(nonatomic,strong) NSString *indexTitle;//自動進行分組時,使用的索引值
@property(nonatomic,assign) BOOL canEdit;//是否可以被編輯
@property(nonatomic,assign) BOOL canMove;//是否可以被移動
@property(nonatomic, copy)  NSArray<UITableViewRowAction *> *actionArray;  //侧滑时的选项数组

@property(nonatomic,copy) ZWTableViewCellModelBlockC whenClick;//点击触发
@property(nonatomic,copy) ZWTableViewCellModelBlockP whenSelected;//被触控事件选中时触发
@property(nonatomic,copy) ZWTableViewCellModelBlockC whenClickAccessory;//操作按鈕被點擊時的action
@property(nonatomic,copy) ZWTableViewCellModelBlockD whenDelete;//删除触发
@property(nonatomic,copy) ZWTableViewCellModelBlockM whenMove;//移動位置觸發

@property(nonatomic,copy) ZWTableViewCellModelBlockS whenShow;//設置cell繪製的block,在cell被顯示時進行自定義畫面的處理.一般是用於cellClass=UITableViewCell時,對UITableViewCell的內容進行定制.如需要更複雜的控制,請創建UITableViewCell的子類來實現.

@property(nonatomic,readonly) ZWTableViewModel *tableViewModel;//弱引用外部的tableViewModel
@property(nonatomic,assign) UITableViewCell *tableViewCell;//弱引用對應的cell視圖
@property(nonatomic,assign) UITableView *tableView;//弱引用外部的tableview
@property(nonatomic,assign) UITableViewCellAccessoryType accessoryType;//操作按鈕的類型,對應於cell.accessoryType值
@property(nonatomic,assign) UITableViewCellStyle cellStyle;//cell視圖的style值,對應於cell.cellStyle
@property(nonatomic,strong) NSString *reuseIdentity;//用於列表重用單元格視圖時的標誌符,默認為NSStringFromCGClass(self.class)

- (ZWTableViewSectionModel *)sectionModel;

/**
 *	tableview在生成UITableViewCell时,手動繪製cell的內容,默認是調用whenShow的block
 */
- (void)displayCell:(UITableViewCell<ZWTableViewCellProtocol> *)cell;

/**
 *	刷新视图
 */
- (void)refresh;
- (void)refreshWithAnimated:(BOOL)animated;
/**
 取消选中某一个Cell
 */
- (void)deselectCellWithAnimated:(BOOL)animated;
@end

@interface ZWTableViewCellModel(NS_DEPRECATED_IOS)
- (ZWTableViewSectionModel *)tableSectionModel;
@end
