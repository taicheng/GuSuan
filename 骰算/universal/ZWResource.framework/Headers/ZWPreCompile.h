//
//  Header.h
//  ZWResource
//
//  Created by taic_cai on 16/8/24.
//  Copyright © 2016年 taic_cai. All rights reserved.
//

#ifndef ZWPRECOMPILE_h
#define ZWPRECOMPILE_h
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


/**
 *  对于block外部与内部间的变量传递,定义block外的weak弱引用与block内的strong强引用,防止因block而引起的循环引用内存泄露
 *	范例:
 - (void)test{
	NSObject *obj;
	@weakify(self);
	@weakify(obj);
	void(^testBlock)() = ^(){
 @normalize(self);
 @normalize(obj);
 ...
	};
 }
 *  @param objc_arc 对象
 *
 */
#undef weakify
#define weakify( x )	autoreleasepool{} __weak __typeof__(x) __weak_##x##__ = x;

#undef	normalize
#define normalize( x )	try{} @finally{} __typeof__(x) x = __weak_##x##__;
#undef	normalizeAndNoNil
#define normalizeAndNoNil( x )	try{} @finally{} __typeof__(x) x = __weak_##x##__;if(x==nil)return;


/**
 *  进行log输出(仅在debug模式下才起作用)
 *	使用范例:
	ZWLog(@"test:%@=%@",@"name",@"hello");
	ZWError(@"%@:%@",@"name",@"errorinfo");
 */
#define ZWLog(format,args...) NSLog([NSString stringWithFormat:@"%%@ [%%@] %%d\n================================================={\n\t%@\n}=================================================\n\n",format],[[NSString stringWithUTF8String:__FILE__] lastPathComponent] ,NSStringFromSelector(_cmd) ,__LINE__,##args)
#define ZWError(format,args...) NSLog([NSString stringWithFormat:@"%%@ [%%@] %%d\n-----------------------ERROR----------------------\n================================================={\n\t%@\n}=================================================\n\n",format],[[NSString stringWithUTF8String:__FILE__] lastPathComponent] ,NSStringFromSelector(_cmd) ,__LINE__,##args)
//eg:ZWLogSelector(_cmd,param1,param2);
#define ZWLogSelector(selector,args...) {\
NSArray *pices = [NSStringFromSelector(selector) componentsSeparatedByString:@":"];\
NSMutableArray *formats = [[NSMutableArray alloc] initWithCapacity:pices.count];\
for (NSString *p in pices) {\
if(p.length){\
NSString *p2 = [NSString stringWithFormat:@"%@:%%@",p];\
[formats addObject:p2];\
}\
}\
NSString *format = [formats componentsJoinedByString:@","];\
ZWLog(format, args);\
}


#endif /* ZWPRECOMPILE_h */
