//
//  ZWUICollectionViewCellModel.h
//  ZWUI
//
//  Created by taic_cai on 16/8/15.
//  Copyright © 2016年 taic_cai. All rights reserved.
//

#import "ZWCollectionCellModel.h"
#import "ZWUICollectionViewCellProtocol.h"

@class ZWUICollectionViewCellModel,ZWUICollectionViewSectionModel,ZWUICollectionViewModel;
typedef void(^ZWUICollectionViewCellModelBlockC)(ZWUICollectionViewCellModel *cellModel);
typedef void(^ZWUICollectionViewCellModelBlockS)(ZWUICollectionViewCellModel *cellModel,BOOL selected);

@interface ZWUICollectionViewCellModel : ZWCollectionCellModel
@property(nonatomic,assign) Class<ZWUICollectionViewCellProtocol> cellClass;
@property(nonatomic,strong) UICollectionViewCell<ZWUICollectionViewCellProtocol> *staticCollectionViewCell;//静态的单元格视图,此时不会使用cellClass去实现化单元格了
@property(nonatomic,strong) NSString *reuseIdentity;//用於列表重用單元格視圖時的標誌符,默認為NSStringFromCGClass(self.class)
@property(nonatomic,assign) UICollectionViewCell<ZWUICollectionViewCellProtocol> *collectionViewCell;//弱引用单元格视图
@property(nonatomic,assign) UICollectionView *collectionView;
@property(nonatomic,copy) ZWUICollectionViewCellModelBlockC whenClick;//点击时被触发
@property(nonatomic,copy) ZWUICollectionViewCellModelBlockS whenSelected;//被触控事件选中时触发
- (ZWUICollectionViewSectionModel *)sectionModel;
- (ZWUICollectionViewModel *)collectionModel;
/**
 *  根据模型显示视图
 *
 *  @param cell 视图对象
 */
- (void)displayCell:(UICollectionViewCell<ZWUICollectionViewCellProtocol> *)cell;

/**
 *  刷新视图
 */
- (void)refresh;
@end
