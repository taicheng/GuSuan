//
//  ZWUICollectionViewCellProtocol.h
//  ZWUI
//
//  Created by taic_cai on 16/8/15.
//  Copyright © 2016年 taic_cai. All rights reserved.
//

#import <Foundation/Foundation.h>

#ifndef DEF_ZWCollectionViewCellModel
#define DEF_ZWCollectionViewCellModel(clazz,property) \
- (ZWUICollectionViewCellModel *)collectionCellModel{\
return self.property;\
}\
- (void)setCollectionCellModel:(ZWUICollectionViewCellModel *)collectionCellModel{\
self.property = (clazz *)collectionCellModel;\
}
#endif

@class ZWUICollectionViewCellModel;

@protocol ZWUICollectionViewCellProtocol <NSObject>
@property(nonatomic,strong) ZWUICollectionViewCellModel *collectionCellModel;//数据模型
@optional
/**
 *  返回单元格的尺寸信息
 *
 *  @param collectionView      集合视图
 *  @param collectionCellModel 数据对象
 *
 *  @return 尺寸信息
 */
+ (CGSize)sizeWithCollectionView:(UICollectionView *)collectionView collectionCellModel:(ZWUICollectionViewCellModel *)collectionCellModel;
//选中/取消选中单元格
- (void)collectionView:(UICollectionView *)collectionView didSelectCell:(BOOL)selected;
@end
