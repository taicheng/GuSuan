//
//  ZWUICollectionViewTitleSupplementarySectionModel.h
//  ZWUI
//
//  Created by taic_cai on 16/8/15.
//  Copyright © 2016年 taic_cai. All rights reserved.
//

#import "ZWUICollectionViewSectionModel.h"
#import "ZWUICollectionViewSupplementaryElementProtocol.h"
@interface ZWUICollectionViewTitleSupplementarySectionModel : ZWUICollectionViewSectionModel
@property(nonatomic,assign) BOOL showHead;//是否显示head,默认为NO
@property(nonatomic,strong) NSString *headTitle;
@property(nonatomic,assign) Class<ZWUICollectionViewSupplementaryElementProtocol> headClass;

@property(nonatomic,assign) BOOL showFoot;//是否显示foot,默认为NO
@property(nonatomic,strong) NSString *footTitle;
@property(nonatomic,assign) Class<ZWUICollectionViewSupplementaryElementProtocol> footClass;
@end
