//
//  ZWTableViewCellProtocol.h
//  ZWUI
//
//  Created by taic_cai on 16/8/16.
//  Copyright © 2016年 taic_cai. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ZWTableViewCellModel.h"

#ifndef DEF_ZWTableViewCellModel
#define DEF_ZWTableViewCellModel(clazz,property) \
- (ZWTableViewCellModel *)cellModel{\
return self.property;\
}\
- (void)setCellModel:(ZWTableViewCellModel *)cellModel{\
self.property = (clazz *)cellModel;\
}
#endif

@protocol ZWTableViewCellProtocol <NSObject>
/**
 *  根據cellmodel,計算出cell視圖的高度
 *
 *  @param tableView 外層tableview
 *  @param cellModel 單元格數據
 *
 *  @return 高度值
 */
+ (CGFloat)heightWithTableView:(UITableView *)tableView cellModel:(ZWTableViewCellModel *)cellModel;
@property(nonatomic,strong) ZWTableViewCellModel *cellModel;//cell的數據模型對象
@optional
//选中/取消选中单元格
- (void)tableView:(UITableView *)tableView didSelectCell:(BOOL)selected;
@end
