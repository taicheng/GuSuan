//
//  ZWFormFilePart.h
//  ZWAPI
//
//  Created by taic_cai on 16/8/16.
//  Copyright © 2016年 taic_cai. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface ZWFormFilePart : NSObject
@property(nonatomic,strong) NSURL *url;//文件在本地磁盘中的路径url
@property(nonatomic,strong) NSData *data;//文件的二进制数据
@property(nonatomic,strong) NSString *name;//表单name属性值
@property(nonatomic,strong) NSString *fileName;//文件路径名
@property(nonatomic,strong) NSString *mimeType;//表单中的mimeType值

- (id)initWithFileURL:(NSURL *)url name:(NSString *)name fileName:(NSString *)fileName mimeType:(NSString *)mimeType;
- (id)initWithFileURL:(NSURL *)url name:(NSString *)name;
- (id)initWithFileData:(NSData *)data name:(NSString *)name fileName:(NSString *)fileName mimeType:(NSString *)mimeType;
- (id)initWithJPG:(UIImage *)image name:(NSString *)name;
- (id)initWithPNG:(UIImage *)image name:(NSString *)name;
/**
 *  根据url获取文件名称
 *
 *  @param url 文件对应的url对象
 *
 *  @return 文件名
 */
+ (NSString *)fileNameWithURL:(NSURL *)url;

/**
 *  根据url指定的文件的后缀,获取上传文件时,表项的mimeType值
 *
 *  @param extension 文件名后缀
 *
 *  @return mimeType值
 */
+ (NSString *)mimeTypeWithPathExtension:(NSString *)extension;
@end
