//
//  ZWUICollectionViewSectionModel.h
//  ZWUI
//
//  Created by taic_cai on 16/8/15.
//  Copyright © 2016年 taic_cai. All rights reserved.
//

#import "ZWCollectionSectionModel.h"
#import "ZWUICollectionViewSupplementaryElementProtocol.h"

@class ZWUICollectionViewModel,ZWUICollectionViewCellModel;

@interface ZWUICollectionViewSectionModel : ZWCollectionSectionModel{
@protected
    NSMutableDictionary *_supplementaryElementCellClasses;
}
@property(nonatomic,assign) UICollectionView *collectionView;//弱引用集合视图
- (ZWUICollectionViewModel *)collectionModel;
- (ZWUICollectionViewCellModel *)cellModelAtIndex:(NSInteger)index;

/**
 *  刷新分组视图
 */
- (void)refresh;

/**
 *  设置集合分组的补充元素显示视图
 *
 *  @param aClass 视图类,必须为UICollectionReusableView的子类
 *  @param kind   补充元素对应的类型,用于区分不同的补充元素
 */
- (void)setSupplementaryElementViewClass:(Class<ZWUICollectionViewSupplementaryElementProtocol>)aClass forKind:(NSString *)kind;

/**
 *  移除指定类型的补充元素的显示视图类.被移走后,将不会显示视图
 *
 *  @param kind 补充元素对应的类型
 */
- (void)removeSupplementaryElementViewClassForKind:(NSString *)kind;

/**
 *  获取指定类型的补充元素的显示视图类
 *
 *  @param kind 补充元素对应的类型
 *
 *  @return UICollectionReusableView子类
 */
- (Class<ZWUICollectionViewSupplementaryElementProtocol>)supplementaryElementViewClassForKind:(NSString *)kind;

/**
 *  显示分组的补充元素视图
 *
 *  @param view 补充元素视图
 *  @param kind 补充元素对应的类型
 */
- (void)displaySupplementaryElementView:(UICollectionReusableView<ZWUICollectionViewSupplementaryElementProtocol> *)view forKind:(NSString *)kind;
@end