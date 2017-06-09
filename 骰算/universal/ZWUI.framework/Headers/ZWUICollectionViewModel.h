//
//  ZWUICollectionViewModel.h
//  ZWUI
//
//  Created by taic_cai on 16/8/15.
//  Copyright © 2016年 taic_cai. All rights reserved.
//


#import "ZWCollection_Header.h"
#import "ZWUICollectionViewSectionModel.h"
#import "ZWUICollectionViewCellModel.h"
#import "ZWUICollectionViewCellProtocol.h"

@interface ZWUICollectionViewModel : ZWCollectionModel<UICollectionViewDataSource,UICollectionViewDelegate,UICollectionViewDelegateFlowLayout>
@property(nonatomic,assign) id<UICollectionViewDataSource> forwardDataSource;//遞用鏈傳遞
@property(nonatomic,assign) id<UICollectionViewDelegate,UICollectionViewDelegateFlowLayout> forwardDelegate;//遞用鏈傳遞
@property(nonatomic,readwrite,getter=isEditting) BOOL editting;//是否处在编辑状态中
@property(nonatomic,assign) UICollectionView *collectionView;//弱引用外部的collectionView

#pragma mark - empty
@property(nonatomic,assign) Class emptyBackgroundViewClass;//没有单元格数据时的背景视图类
@property(nonatomic,strong) UIView *emptyBackgroundView;//没有单元格数据时的背景视图
typedef void(^ZWUICollectionViewModelC)(ZWUICollectionViewModel *model);
@property(nonatomic,copy) ZWUICollectionViewModelC whenReloadBackgroundView;
- (void)reloadCollectionViewBackgroundView;//刷新tableview的backgroundView

- (id)initWithCollectionView:(UICollectionView *)collectionView;

- (ZWUICollectionViewCellModel *)cellModelAtIndexPath:(NSIndexPath *)indexpath;
- (ZWUICollectionViewSectionModel *)sectionModelAtIndex:(NSInteger)index;
- (ZWUICollectionViewCellModel *)cellModelForSelectedCellModel;

/**
 *  将collectionView的dataSource和delegate设置为self.如果forwardDelegate要监听scrollViewDidScroll:事件,则必须在设置collectionView的delegate之前设置forwardDelegate,因为scrollView是在设置delegate时,去获取delegate是否实现scrollViewDidScroll:方法,后续就不会再获取了.
 *
 *  @param collectionView 集合视图
 */
- (void)setCollectionViewDataSourceAndDelegate:(UICollectionView *)collectionView;

/**
 *  刷新集合视图,会保持集合视图的cell选中状态
 */
- (void)reloadCollectionViewData;

/**
 *  动画的方式添加/删除单元格
 *
 *  @param cellModel  单元格数据
 *  @param animated   是否动画
 *  @param completion 动画结束后的回调
 */
- (void)addCellModel:(ZWCollectionCellModel *)cellModel animated:(BOOL)animated completion:(void (^)(BOOL finished))completion;
- (void)removeCellModel:(ZWCollectionCellModel *)cellModel animated:(BOOL)animated completion:(void (^)(BOOL finished))completion;
- (void)removeCellModels:(NSArray<ZWCollectionCellModel *> *)cellModels animated:(BOOL)animated completion:(void (^)(BOOL finished))completion;
@end


@interface ZWUICollectionViewModel(NS_DEPRECATED_IOS)//将要被废弃的接口
/**
 *  往前近的一个分组添加单元格,如果没有分组,创建分组
 *
 *  @param cellModel 单元格
 *
 *  @return 被添加单元格的分组
 */
- (ZWUICollectionViewSectionModel *)addListedCellModel:(ZWUICollectionViewCellModel *)cellModel;
/**
 *  选中单元格,其他单元格置于未选中状态
 *
 *  @param cellModel 单元格对象
 */
- (void)selectSingleCellModel:(ZWUICollectionViewCellModel *)cellModel;

/**
 *  选中的单元格数据
 *
 *  @return 单元格数据对象
 */
- (ZWUICollectionViewCellModel *)selectedCellModel;

/**
 *  选中的多个单元格数据
 *
 *  @return @[ZWUICollectionViewCellModel]
 */
- (NSArray *)selectedCellModels;
@end
