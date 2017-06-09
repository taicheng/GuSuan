//
//  ZWUICollectionViewSupplementaryView.h
//  ZWUI
//
//  Created by taic_cai on 16/8/15.
//  Copyright © 2016年 taic_cai. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ZWUICollectionViewSupplementaryElementProtocol.h"
#import "ZWUICollectionViewSectionModel.h"
@interface ZWUICollectionViewSupplementaryView : UICollectionReusableView<ZWUICollectionViewSupplementaryElementProtocol>
@property(nonatomic,strong) ZWUICollectionViewSectionModel *sectionModel;
@property(nonatomic,strong) NSString *kind;
@end
