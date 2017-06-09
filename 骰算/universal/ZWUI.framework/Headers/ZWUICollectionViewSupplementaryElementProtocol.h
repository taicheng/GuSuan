//
//  ZWUICollectionViewSupplementaryElementProtocol.h
//  ZWUI
//
//  Created by taic_cai on 16/8/15.
//  Copyright © 2016年 taic_cai. All rights reserved.
//
#import <Foundation/Foundation.h>

#ifndef DEF_ZWCollectionViewSectionModel
#define DEF_ZWCollectionViewSectionModel(clazz,property) \
- (ZWUICollectionViewSectionModel *)sectionModel{\
return self.property;\
}\
- (void)setCollectionSectionModel:(ZWUICollectionViewSectionModel *)sectionModel forKind:(NSString *)kind{\
self.property = (clazz *)sectionModel;\
}
#endif

@class ZWUICollectionViewSectionModel;
@protocol ZWUICollectionViewSupplementaryElementProtocol <NSObject>
/**
 *  设置补充视图所在的分组以及类型
 *
 *  @param sectionModel 分组数据
 *  @param kind         类型
 */
- (void)setCollectionSectionModel:(ZWUICollectionViewSectionModel *)sectionModel forKind:(NSString *)kind;

@optional
/**
 *  返回视图的尺寸,UICollectionViewDelegateFlowLayout使用
 *
 *  @param collectionView 集合
 *  @param sectionModel   分组
 *  @param kind           类型
 *
 *  @return 尺寸值
 */
+ (CGSize)referenceSizeWithCollectionView:(UICollectionView *)collectionView collectionSectionModel:(ZWUICollectionViewSectionModel *)sectionModel forKind:(NSString *)kind;
@end

