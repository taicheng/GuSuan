//
//  FIUIImageCache.h
//  ZWUI
//
//  Created by taic_cai on 16/8/24.
//  Copyright © 2016年 taic_cai. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <ZWResource/ZWResource.h>

@interface FIUIImageCache : NSObject{
    NSMutableDictionary *_caches;
}

AS_SINGLETON(FIUIImageCache);

- (void)setImage:(UIImage *)image forName:(NSString *)name;

- (UIImage *)imageForName:(NSString *)name;

@end
