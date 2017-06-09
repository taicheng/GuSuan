//
//  MacroDefine.h
//  骰算
//
//  Created by taic_cai on 2016/12/26.
//  Copyright © 2016年 taic_cai. All rights reserved.
//

#import <Foundation/Foundation.h>

#undef	AS_SINGLETON
#define AS_SINGLETON( ... ) \
- (instancetype)sharedInstance; \
+ (instancetype)sharedInstance;

#undef	DEF_SINGLETON
#define DEF_SINGLETON( ... ) \
- (instancetype)sharedInstance{ \
return [[self class] sharedInstance]; \
} \
+ (instancetype)sharedInstance{ \
static dispatch_once_t once; \
static id __singleton__; \
dispatch_once( &once, ^{ __singleton__ = [[self alloc] init]; } ); \
return __singleton__; \
}

#undef weakify
#define weakify( x )	autoreleasepool{} __weak __typeof__(x) __weak_##x##__ = x;
#undef	normalize
#define normalize( x )	try{} @finally{} __typeof__(x) x = __weak_##x##__;
#undef	normalizeAndNoNil
#define normalizeAndNoNil( x )	try{} @finally{} __typeof__(x) x = __weak_##x##__;if(x==nil)return;

#define RELEASEOBJECT(object) if(object){object = nil;}

//状态栏高度
#define StatusBarHeight [UIApplication sharedApplication].statusBarFrame.size.height

//导航栏高度
#define NaviBarHeight 44

#define UIColorWithRGB(r, g, b, a) [UIColor colorWithRed:r/255.0f green:g/255.0f blue:b/255.0f alpha:a]

#define kScreenSize           [[UIScreen mainScreen] bounds].size
#define kScreenWidth          [[UIScreen mainScreen] bounds].size.width
#define kScreenHeight         [[UIScreen mainScreen] bounds].size.height
#define ScreenMultiple        [[MacroDefine sharedInstance] screenMultiple]

@interface MacroDefine : NSObject
AS_SINGLETON(MacroDefine);
- (float)screenMultiple;
@end
