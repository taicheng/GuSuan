//
//  ZWCollectionCellModel.h
//  ZWUI
//
//  Created by taic_cai on 16/8/15.
//  Copyright © 2016年 taic_cai. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
@class ZWCollectionSectionModel,ZWCollectionModel;
@interface ZWCollectionCellModel : NSObject{
@protected
    __weak ZWCollectionSectionModel *_sectionModel;
}
@property(nonatomic,readonly) ZWCollectionModel *collectionModel;//集合模型对象
@property(nonatomic,strong) id userInfo;//自定義的擴展對象
@property(nonatomic,assign) BOOL selected;
@property(nonatomic,readonly) NSInteger indexInSectionModel;
@property(nonatomic,readonly) NSIndexPath *indexPathInModel;
@property(nonatomic,readonly) NSIndexPath *indexPathOfPreCell;//上一个单元格的indexpath
@property(nonatomic,readonly) NSIndexPath *indexPathOfNextCell;//下一个单元格的indexpath
//弱引用上層的分組對象
- (void)setSectionModel:(ZWCollectionSectionModel *)sectionModel;
- (ZWCollectionSectionModel *)sectionModel;

- (NSComparisonResult)compare:(ZWCollectionCellModel *)otherObject;
@end
