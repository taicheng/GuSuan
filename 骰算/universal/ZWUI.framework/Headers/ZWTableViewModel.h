//
//  ZWTableViewModel.h
//  ZWUI
//
//  Created by taic_cai on 16/8/16.
//  Copyright © 2016年 taic_cai. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ZWCollection_Header.h"

#import "ZWTableViewSectionModel.h"
#import "ZWTableViewCellModel.h"
#import "ZWTableViewSectionViewProtocol.h"
#import "ZWTableViewCellProtocol.h"
#import "UITableViewCell+ZWTableViewCell.h"

#define TableViewDefaultSectionIndexTitle @"#"

@interface ZWTableViewModel : ZWCollectionModel<UITableViewDataSource,UITableViewDelegate>{
@protected
    ZWTableViewSectionModel *_defaultIndexTitleSectionModel;	//存儲section的indexTitle沒有值的情況
}
@property(nonatomic,assign) id<UITableViewDataSource> forwardDataSource;//遞用鏈傳遞
@property(nonatomic,assign) id<UITableViewDelegate  > forwardDelegate;//遞用鏈傳遞

@property(nonatomic,assign) UITableView *tableView;//弱引用
@property(nonatomic,assign) BOOL showSectionIndexTitle;//是否顯示分組索引,默認為NO
@property(nonatomic,strong) NSString *defaultSectionIndexTitle;//當sectionModel.indexTitle沒有值時,採用此默認值,默認為#

@property(nonatomic,readwrite,getter=isEditting) BOOL editting;//是否处在编辑状态中

#pragma mark - empty
@property(nonatomic,assign) Class emptyBackgroundViewClass;//没有单元格数据时的背景视图类
@property(nonatomic,strong) UIView *emptyBackgroundView;//没有单元格数据时的背景视图
typedef void(^ZWTableViewModelC)(ZWTableViewModel *model);
@property(nonatomic,copy) ZWTableViewModelC whenReloadBackgroundView;
- (void)reloadTableViewBackgroundView;//刷新tableview的backgroundView

/**
 *  使用tableview初始化,会设置tableview的datasource与delegate为self
 *
 *  @param tableView 列表对象
 *
 *  @return 列表的数据模型
 */
- (id)initWithTableView:(UITableView *)tableView;

- (ZWTableViewCellModel *)cellModelAtIndexPath:(NSIndexPath *)indexpath;
- (ZWTableViewSectionModel *)sectionModelAtIndex:(NSInteger)index;
- (ZWTableViewCellModel *)cellModelForSelectedCellModel;

- (ZWTableViewModel *)forwardDataSourceTo:(id<UITableViewDataSource>)dataSource;
- (ZWTableViewModel *)forwardDelegateTo:(id<UITableViewDelegate>)delegate;

/**
 *  将tableView的dataSource和delegate设置为self.如果forwardDelegate要监听scrollViewDidScroll:事件,则必须在设置collectionView的delegate之前设置forwardDelegate,因为scrollView是在设置delegate时,去获取delegate是否实现scrollViewDidScroll:方法,后续就不会再获取了.
 *
 *  @param tableView 视图
 */
- (void)setTableViewDataSourceAndDelegate:(UITableView *)tableView;


/**
 *	添加上自動分組的單元格數據,分組的索引值為cellModel.indexTitle值,僅當showSectionIndexTitle為YES時才會出現右側的分組索引條
 *	@return 返回被歸進的分組中,其中分組默認設置為顯示系統自帶的title,title值為分組的索引值,
 */
- (ZWTableViewSectionModel *)addAutoIndexedCellModel:(ZWTableViewCellModel *)cellModel;

/**
 *	按照字符串順序對分組進行排序
 */
- (void)sort;

/**
 *  刷新列表视图,会保持列表视图的选中状态
 */
- (void)reloadTableViewData;
- (void)reloadTableViewDataWithAnimated:(BOOL)animated;
/**
 *  动画的方式添加/删除单元格
 *
 *  @param cellModel  单元格数据
 *  @param animated   是否动画
 */
- (void)addCellModel:(ZWTableViewCellModel *)cellModel animated:(BOOL)animated;

- (void)insertCellModel:(ZWTableViewCellModel *)cellModel atIndexPath:(NSIndexPath *)indexPath animated:(BOOL)animated;
- (void)insertCellModel:(ZWTableViewCellModel *)cellModel afterIndexPath:(NSIndexPath *)indexPath animated:(BOOL)animated;
- (void)insertCellModel:(ZWTableViewCellModel *)cellModel beforeIndexPath:(NSIndexPath *)indexPath animated:(BOOL)animated;

- (void)insertCellModels:(NSArray *)cellModels afterIndexPath:(NSIndexPath *)indexPath animated:(BOOL)animated;
- (void)insertCellModels:(NSArray *)cellModels beforeIndexPath:(NSIndexPath *)indexPath animated:(BOOL)animated;

- (void)removeCellModel:(ZWTableViewCellModel *)cellModel animated:(BOOL)animated;
- (void)removeCellModels:(NSArray *)cellModels animated:(BOOL)animated;
- (void)removeCellModelsAtIndexPaths:(NSArray *)indexpaths animated:(BOOL)animated;
@end


@interface ZWTableViewModel(NS_DEPRECATED_IOS)//将要被废弃的接口
- (void)setSectionModels:(NSMutableArray *)sectionModels;
- (NSMutableArray *)sectionModels;
/**
 *  返回选中/未选中的单元格列表
 *
 *  @param selected 是否选中
 *
 *  @return 列表数据
 */
- (NSArray *)cellsOfSelected:(BOOL)selected;

- (void)removeEmptySections;
/**
 *	返回指定的ZWTableViewSectionModel對象
 */
- (ZWTableViewSectionModel *)sectionModelAtSection:(NSUInteger)section;

- (NSIndexPath *)indexPathWithCellModel:(ZWTableViewCellModel *)cellModel;
- (NSIndexSet *)indexSetWithSectionModel:(ZWTableViewSectionModel *)sectionModel;

/**
 *	添加单元格数据到最后一个分组中,如果没有分组,建立分组
 */
- (ZWTableViewSectionModel *)addListedCellModel:(ZWTableViewCellModel *)cellModel;

/**
 *	移除掉自動分組的單元格數據
 */
- (void)removeAutoIndexedCellModel:(ZWTableViewCellModel *)cellModel;
/**
 *  返回选中/未选中的单元格列表
 *
 *  @param selected 是否选中
 *
 *  @return 列表数据
 */
- (NSArray *)cellModelsOfSelected:(BOOL)selected;
@end
