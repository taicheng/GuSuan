//
//  SCMakeImage.h
//  StudyClound
//
//  Created by 陈江彬 on 7/7/15.
//  Copyright (c) 2015 StudyClound. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AssetsLibrary/AssetsLibrary.h>

typedef void (^SCMakeImageBlock)(UIImage *);


//用于图片上传到网络的时候，进行裁剪的最大尺寸，根据iPhone6 plus计算而来（568*ScreenMultiple）
#define MaxImageCropHeight 738


@interface SCMakeImage : NSObject

/**
 *  裁剪的图片宽度
 */
@property (nonatomic, assign) float cropImageWidth;
/**
 *  裁剪的图片高度
 */
@property (nonatomic, assign) float cropImageHeight;

@property (nonatomic, assign) BOOL shouldCropImage;

/**
 *  从哪个页面推过来
 */
@property (nonatomic, weak) UIViewController *pushFromViewController;

@property (nonatomic, copy) SCMakeImageBlock makeImageBlock;

- (void)selectFromPhotoAlbum;

- (void)selectFromCarmer;




#pragma mark- 压缩手机里的图片
- (UIImage *)decreaseImageWithAsset:(ALAsset *)asset maxPixelSize:(int)size;

#pragma mark- 压缩普通的图片
- (UIImage *)decreaseImageWithOriginImage:(UIImage *)originImage maxPixelSize:(int)size;

#pragma mark- 缩小图片质量
- (UIImage *)lowerQualityWithOriginImage:(UIImage *)originImage;

- (NSData *)lowerImageQualityWithOriginImage:(UIImage *)originImage;

#pragma mark- 获取图片的中心视图（正方形图片）
- (UIImage *)getImageCenterWithOriginImage:(UIImage *)image;





@end











