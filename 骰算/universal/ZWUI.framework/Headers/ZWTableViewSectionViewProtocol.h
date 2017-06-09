//
//  ZWTableViewSectionViewProtocol.h
//  ZWUI
//
//  Created by taic_cai on 16/8/16.
//  Copyright © 2016年 taic_cai. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ZWTableViewSectionModel.h"

typedef enum{
    ZWTableViewSectionViewKindOfHead=0,	//頭部
    ZWTableViewSectionViewKindOfFoot=1	//尾部
} ZWTableViewSectionViewKind;

@protocol ZWTableViewSectionViewProtocol <NSObject>
/**
 *  返回視圖的高度
 *
 *  @param tableView    外層的tableview
 *  @param sectionModel 分組數據模型
 *  @param kind         視圖的類型
 *
 *  @return 高度值
 */
+ (CGFloat)heightWithTableView:(UITableView *)tableView sectionModel:(ZWTableViewSectionModel *)sectionModel kind:(ZWTableViewSectionViewKind)kind;
/**
 *  設置分組模型與顯示類型
 *
 *  @param sectionModel 分組模型
 *  @param kind         類型
 */
- (void)setSectionModel:(ZWTableViewSectionModel *)sectionModel kind:(ZWTableViewSectionViewKind)kind;
@end
