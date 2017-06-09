//
//  ZWCollectionSectionModel.h
//  ZWUI
//
//  Created by taic_cai on 16/8/15.
//  Copyright © 2016年 taic_cai. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
@class ZWCollectionModel,ZWCollectionCellModel;
@interface ZWCollectionSectionModel : NSObject{
@protected
    NSMutableArray *_cellModels;
    __weak ZWCollectionModel *_collectionModel;
}
@property(nonatomic,readonly) NSArray *cellModels;//含有的單元格
@property(nonatomic,strong) id userInfo;//自定義的擴展對象
@property(nonatomic,readonly) NSInteger numberOfCells;//单元格数量
@property(nonatomic,readonly) NSInteger indexInModel;
//弱引用外層的數據
- (void)setCollectionModel:(ZWCollectionModel *)collectionModel;
- (ZWCollectionModel *)collectionModel;

/**
 *  加到單元格到分組中
 *
 *  @param cellModel 單元格數據
 */
- (void)addCellModel:(ZWCollectionCellModel *)cellModel;
- (void)addCellModels:(NSArray<ZWCollectionCellModel *> *)cellModels;
- (void)insertCellModel:(ZWCollectionCellModel *)cellModel atIndex:(NSInteger)index;
- (void)insertCellModels:(NSArray *)cellModels afterIndex:(NSInteger)index;
- (void)insertCellModels:(NSArray *)cellModels beforeIndex:(NSInteger)index;

/**
 *  將cell從所有的分組中移除
 *
 *  @param cellModel 單元格對象
 */
- (void)removeCellModel:(ZWCollectionCellModel *)cellModel;

/**
 *  移除index位置的单元格
 *
 *  @param index 索引位置
 */
- (void)removeCellModelAtIndex:(NSInteger)index;

/**
 *  移除多个单元格
 *
 *  @param indexes 索引位置集合
 */
- (void)removeCellModelsAtIndexes:(NSIndexSet *)indexes;

/**
 *	清空所有數據
 */
- (void)removeAllCellModels;

/**
 *  返回指定索引下的单元格数据
 *
 *  @param index 索引
 *
 *  @return 单元格数据
 */
- (ZWCollectionCellModel *)cellModelAtIndex:(NSInteger)index;

/**
 *  返回指定单元格数据对应的索引
 *
 *  @param cellModel 单元格数据
 *
 *  @return 索引号
 */
- (NSInteger)indexOfCellModel:(ZWCollectionCellModel *)cellModel;

- (NSIndexPath *)indexPathForSelectedCellModel;
- (ZWCollectionCellModel *)cellModelForSelectedCellModel;
- (NSArray *)indexPathsForSelectedCellModels;
- (NSArray *)cellModelsForSelectedCellModels;

- (NSComparisonResult)compare:(ZWCollectionSectionModel *)otherObject;
@end


@interface ZWCollectionSectionModel(NS_DEPRECATED_IOS)//将要被废弃的接口
@property (nonatomic,strong) NSMutableArray    *cells;//含有的單元格
@end