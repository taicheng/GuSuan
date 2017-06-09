//
//  SCMakeImage.m
//  StudyClound
//
//  Created by 陈江彬 on 7/7/15.
//  Copyright (c) 2015 StudyClound. All rights reserved.
//

#import "SCMakeImage.h"
#import "SCImageCropperViewController.h"
#import <MobileCoreServices/MobileCoreServices.h>
#import <ImageIO/ImageIO.h>
#import <AVFoundation/AVFoundation.h>

#define ORIGINAL_MAX_WIDTH 640.0f

typedef NS_ENUM(NSInteger, SCMakeImageAlertViewTag)
{
    SCMakeImageAlertView_PictureTag = 0,
    SCMakeImageAlertView_CameraTag,
};

@interface SCMakeImage()<UINavigationControllerDelegate,UIImagePickerControllerDelegate,VPImageCropperDelegate,UIAlertViewDelegate>

@property (nonatomic, strong) UIImagePickerController *imagePickerVC;
@property (nonatomic, assign) BOOL isTakePhoto;//是否拍照

@end


@implementation SCMakeImage

- (void)selectFromPhotoAlbum
{
    ALAuthorizationStatus status = [ALAssetsLibrary authorizationStatus];
    if (status==ALAuthorizationStatusRestricted|| status==ALAuthorizationStatusDenied)
    {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Sorry, you don’t have the access to photo album." message:@"Setting now?" delegate:self cancelButtonTitle:@"Cancel" otherButtonTitles:@"Setting",nil];
        alert.tag = SCMakeImageAlertView_PictureTag;
        alert.delegate = self;
        [alert show];
    }
    
    if ([self isPhotoLibraryAvailable])
    {
        UIImagePickerController *controller = [[UIImagePickerController alloc] init];
        controller.sourceType = UIImagePickerControllerSourceTypePhotoLibrary;
        NSMutableArray *mediaTypes = [[NSMutableArray alloc] init];
        [mediaTypes addObject:(__bridge NSString *)kUTTypeImage];
        controller.mediaTypes = mediaTypes;
        controller.delegate = self;
        [_pushFromViewController presentViewController:controller animated:YES completion:nil];
        
        _imagePickerVC = controller;
        _isTakePhoto = NO;
    }
}

- (void)selectFromCarmer
{
    AVAuthorizationStatus authStatus = [AVCaptureDevice authorizationStatusForMediaType:AVMediaTypeVideo];
    if (authStatus == AVAuthorizationStatusRestricted || authStatus ==AVAuthorizationStatusDenied)
    {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@" Sorry, you don’t have the access to camera." message:@"Setting now?" delegate:self cancelButtonTitle:@"Cancel" otherButtonTitles:@"Setting",nil];
        alert.tag = SCMakeImageAlertView_CameraTag;
        [alert show];
    }
    
    if ([self isCameraAvailable] && [self doesCameraSupportTakingPhotos])
    {
        UIImagePickerController *controller = [[UIImagePickerController alloc] init];
        controller.sourceType = UIImagePickerControllerSourceTypeCamera;
        if ([self isFrontCameraAvailable])
        {
            controller.cameraDevice = UIImagePickerControllerCameraDeviceFront;
        }
        NSMutableArray *mediaTypes = [[NSMutableArray alloc] init];
        [mediaTypes addObject:(__bridge NSString *)kUTTypeImage];
        controller.mediaTypes = mediaTypes;
        controller.delegate = self;
        [_pushFromViewController presentViewController:controller animated:YES completion:nil];
        
        _imagePickerVC = controller;
        _isTakePhoto = YES;
    }
}

#pragma mark- UIAlertViewDelegate
- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if (buttonIndex==0)
    {
        
    }
    else
    {
        NSURL *url = [NSURL URLWithString:@"prefs:root=Privacy"];
        
        if([[UIApplication sharedApplication] canOpenURL:url])
        {
            [[UIApplication sharedApplication] openURL:url];
        }
    }
}

#pragma mark- VPImageCropperDelegate
- (void)imageCropper:(SCImageCropperViewController *)cropperViewController didFinished:(UIImage *)editedImage
{
    if (_makeImageBlock)
    {
        _makeImageBlock([self decreaseImageWithOriginImage:editedImage maxPixelSize:MaxImageCropHeight]);
    }
    
    [_imagePickerVC dismissViewControllerAnimated:YES completion:nil];
}

- (void)imageCropperDidCancel:(SCImageCropperViewController *)cropperViewController
{
    if (_isTakePhoto)
    {
        [_imagePickerVC dismissViewControllerAnimated:YES completion:nil];
    }
    else
    {
        [cropperViewController.navigationController popViewControllerAnimated:YES];
    }
}

#pragma mark- UIImagePickerControllerDelegate
- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info
{
    UIImage *portraitImg = [info objectForKey:@"UIImagePickerControllerOriginalImage"];
    portraitImg = [self imageByScalingToMaxSize:portraitImg];
    
    if (_shouldCropImage)
    {
        //裁剪
        float cropWidth = kScreenWidth;
        float cropHeight = kScreenWidth;
        
        if (_cropImageHeight>0)
        {
            cropWidth = _cropImageWidth;
            cropHeight = _cropImageHeight;
        }
        
        SCImageCropperViewController *imgEditorVC = [[SCImageCropperViewController alloc] initWithImage:portraitImg cropFrame:CGRectMake(0, (kScreenHeight-cropHeight)/2, cropWidth, cropHeight) limitScaleRatio:3.0];
        imgEditorVC.delegate = self;
        
        [[UIApplication sharedApplication] setStatusBarStyle:UIStatusBarStyleLightContent animated:YES];
        [[UIApplication sharedApplication] setStatusBarHidden:NO withAnimation:UIStatusBarAnimationSlide];
        [picker setNavigationBarHidden:NO animated:YES];
        [picker pushViewController:imgEditorVC animated:YES];
    }
    else
    {
        if (_makeImageBlock)
        {
            _makeImageBlock(portraitImg);
        }
        
        [picker dismissViewControllerAnimated:YES completion:nil];
    }
}

- (void)imagePickerControllerDidCancel:(UIImagePickerController *)picker
{
    [picker dismissViewControllerAnimated:YES completion:nil];
}

#pragma mark- camera utility
- (BOOL)isCameraAvailable
{
    return [UIImagePickerController isSourceTypeAvailable:UIImagePickerControllerSourceTypeCamera];
}

- (BOOL)isRearCameraAvailable
{
    return [UIImagePickerController isCameraDeviceAvailable:UIImagePickerControllerCameraDeviceRear];
}

- (BOOL)isFrontCameraAvailable
{
    return [UIImagePickerController isCameraDeviceAvailable:UIImagePickerControllerCameraDeviceFront];
}

- (BOOL)doesCameraSupportTakingPhotos
{
    return [self cameraSupportsMedia:(__bridge NSString *)kUTTypeImage sourceType:UIImagePickerControllerSourceTypeCamera];
}

- (BOOL)isPhotoLibraryAvailable
{
    return [UIImagePickerController isSourceTypeAvailable:
            UIImagePickerControllerSourceTypePhotoLibrary];
}

- (BOOL)canUserPickVideosFromPhotoLibrary
{
    return [self cameraSupportsMedia:(__bridge NSString *)kUTTypeMovie sourceType: UIImagePickerControllerSourceTypePhotoLibrary];
}

- (BOOL)canUserPickPhotosFromPhotoLibrary
{
    return [self cameraSupportsMedia:(__bridge NSString *)kUTTypeImage sourceType:UIImagePickerControllerSourceTypePhotoLibrary];
}

- (BOOL)cameraSupportsMedia:(NSString *)paramMediaType sourceType:(UIImagePickerControllerSourceType)paramSourceType
{
    __block BOOL result = NO;
    if ([paramMediaType length] == 0)
    {
        return NO;
    }
    
    NSArray *availableMediaTypes = [UIImagePickerController availableMediaTypesForSourceType:paramSourceType];
    [availableMediaTypes enumerateObjectsUsingBlock: ^(id obj, NSUInteger idx, BOOL *stop) {
        NSString *mediaType = (NSString *)obj;
        if ([mediaType isEqualToString:paramMediaType])
        {
            result = YES;
            *stop= YES;
        }
    }];
    return result;
}

#pragma mark- image scale utility
- (UIImage *)imageByScalingToMaxSize:(UIImage *)sourceImage
{
    if (sourceImage.size.width < ORIGINAL_MAX_WIDTH) return sourceImage;
    CGFloat btWidth = 0.0f;
    CGFloat btHeight = 0.0f;
    if (sourceImage.size.width > sourceImage.size.height)
    {
        btHeight = ORIGINAL_MAX_WIDTH;
        btWidth = sourceImage.size.width * (ORIGINAL_MAX_WIDTH / sourceImage.size.height);
    }
    else
    {
        btWidth = ORIGINAL_MAX_WIDTH;
        btHeight = sourceImage.size.height * (ORIGINAL_MAX_WIDTH / sourceImage.size.width);
    }
    CGSize targetSize = CGSizeMake(btWidth, btHeight);
    return [self imageByScalingAndCroppingForSourceImage:sourceImage targetSize:targetSize];
}

- (UIImage *)imageByScalingAndCroppingForSourceImage:(UIImage *)sourceImage targetSize:(CGSize)targetSize
{
    UIImage *newImage = nil;
    CGSize imageSize = sourceImage.size;
    CGFloat width = imageSize.width;
    CGFloat height = imageSize.height;
    CGFloat targetWidth = targetSize.width;
    CGFloat targetHeight = targetSize.height;
    CGFloat scaleFactor = 0.0;
    CGFloat scaledWidth = targetWidth;
    CGFloat scaledHeight = targetHeight;
    CGPoint thumbnailPoint = CGPointMake(0.0,0.0);
    if (CGSizeEqualToSize(imageSize, targetSize) == NO)
    {
        CGFloat widthFactor = targetWidth / width;
        CGFloat heightFactor = targetHeight / height;
        
        if (widthFactor > heightFactor)
            scaleFactor = widthFactor; // scale to fit height
        else
            scaleFactor = heightFactor; // scale to fit width
        scaledWidth  = width * scaleFactor;
        scaledHeight = height * scaleFactor;
        
        if (widthFactor > heightFactor)
        {
            thumbnailPoint.y = (targetHeight - scaledHeight) * 0.5;
        }
        else if (widthFactor < heightFactor)
        {
            thumbnailPoint.x = (targetWidth - scaledWidth) * 0.5;
        }
    }
    
    UIGraphicsBeginImageContext(targetSize); // this will crop
    CGRect thumbnailRect = CGRectZero;
    thumbnailRect.origin = thumbnailPoint;
    thumbnailRect.size.width  = scaledWidth;
    thumbnailRect.size.height = scaledHeight;
    
    [sourceImage drawInRect:thumbnailRect];
    
    newImage = UIGraphicsGetImageFromCurrentImageContext();
    if(newImage == nil) NSLog(@"could not scale image");
    
    UIGraphicsEndImageContext();
    return newImage;
}




#pragma mark-压缩图片

#pragma mark- 压缩手机里的图片

// Helper methods for thumbnailForAsset:maxPixelSize:
static size_t getAssetBytesCallback(void *info, void *buffer, off_t position, size_t count)
{
    ALAssetRepresentation *rep = (__bridge id)info;
    
    NSError *error = nil;
    size_t countRead = [rep getBytes:(uint8_t *)buffer fromOffset:position length:count error:&error];
    
    if (countRead == 0 && error) {
        // We have no way of passing this info back to the caller, so we log it, at least.
        NSLog(@"thumbnailForAsset:maxPixelSize: got an error reading an asset: %@", error);
    }
    
    return countRead;
}

static void releaseAssetCallback(void *info)
{
    CFRelease(info);
}

- (UIImage *)decreaseImageWithAsset:(ALAsset *)asset maxPixelSize:(int)size
{
    NSParameterAssert(asset != nil);
    NSParameterAssert(size > 0);
    
    ALAssetRepresentation *rep = [asset defaultRepresentation];
    
    CGDataProviderDirectCallbacks callbacks =
    {
        .version = 0,
        .getBytePointer = NULL,
        .releaseBytePointer = NULL,
        .getBytesAtPosition = getAssetBytesCallback,
        .releaseInfo = releaseAssetCallback,
    };
    
    CGDataProviderRef provider = CGDataProviderCreateDirect((void *)CFBridgingRetain(rep), [rep size], &callbacks);
    CGImageSourceRef source = CGImageSourceCreateWithDataProvider(provider, NULL);
    CGImageRef imageRef = CGImageSourceCreateThumbnailAtIndex(source, 0, (__bridge CFDictionaryRef)
                                                              @{   (NSString *)kCGImageSourceCreateThumbnailFromImageAlways : @YES,
                                                                   (NSString *)kCGImageSourceThumbnailMaxPixelSize : [NSNumber numberWithInt:size],
                                                                   (NSString *)kCGImageSourceCreateThumbnailWithTransform : @YES,
                                                                   });
    
    CFRelease(source);
    CFRelease(provider);
    
    if (!imageRef) {
        return nil;
    }
    
    UIImage *toReturn = [UIImage imageWithCGImage:imageRef];
    
    CFRelease(imageRef);
    
    return [self lowerQualityWithOriginImage:toReturn];
}


#pragma mark- 压缩普通的图片
- (UIImage *)decreaseImageWithOriginImage:(UIImage *)originImage maxPixelSize:(int)size
{
    NSData *originData = UIImageJPEGRepresentation(originImage, 1.0f);
    CGImageSourceRef source = CGImageSourceCreateWithData((__bridge CFDataRef)originData, NULL);
    
    CGImageRef imageRef = CGImageSourceCreateThumbnailAtIndex(source, 0, (__bridge CFDictionaryRef)
                                                              @{   (NSString *)kCGImageSourceCreateThumbnailFromImageAlways : @YES,
                                                                   (NSString *)kCGImageSourceThumbnailMaxPixelSize : [NSNumber numberWithInt:size],
                                                                   (NSString *)kCGImageSourceCreateThumbnailWithTransform : @YES,
                                                                   });
    
    CFRelease(source);
    UIImage *toReturnImage = [UIImage imageWithCGImage:imageRef];
    CFRelease(imageRef);
    
    return [self lowerQualityWithOriginImage:toReturnImage];
}


#pragma mark- 缩小图片质量
- (UIImage *)lowerQualityWithOriginImage:(UIImage *)originImage
{
    NSData *data = UIImageJPEGRepresentation(originImage, 1.0);
    NSData *imagedata;
    
    if (data.length>=200*1024)
    {
        imagedata = UIImageJPEGRepresentation(originImage, 0.1);
    }
    else if (data.length<1024*200 && data.length>=1024*100)
    {
        imagedata = UIImageJPEGRepresentation(originImage, 0.3);
    }
    else if (data.length<1024*100 && data.length>=1024*60)
    {
        imagedata = UIImageJPEGRepresentation(originImage, 0.5);
    }
    else
    {
        imagedata = data;
    }
    
    return [UIImage imageWithData:imagedata];
}

- (NSData *)lowerImageQualityWithOriginImage:(UIImage *)originImage
{
    NSData *data = UIImageJPEGRepresentation(originImage, 1.0);
    NSData *imagedata;
    
    if (data.length>=200*1024)
    {
        imagedata = UIImageJPEGRepresentation(originImage, 0.1);
    }
    else if (data.length<1024*200 && data.length>=1024*100)
    {
        imagedata = UIImageJPEGRepresentation(originImage, 0.3);
    }
    else if (data.length<1024*100 && data.length>=1024*60)
    {
        imagedata = UIImageJPEGRepresentation(originImage, 0.5);
    }
    else
    {
        imagedata = data;
    }
    
    return imagedata;
}


#pragma mark- 获取图片的中心视图（正方形图片）
- (UIImage *)getImageCenterWithOriginImage:(UIImage *)image
{
    float imageWidthAndHeight = 0;
    float cropImageOriginX = 0;
    float cropImageOriginY = 0;
    if (image.size.height>=image.size.width)
    {
        imageWidthAndHeight = image.size.width;
        cropImageOriginY = (image.size.height-image.size.width)/2;
    }
    else
    {
        imageWidthAndHeight = image.size.height;
        cropImageOriginX = (image.size.width-image.size.height)/2;
    }
    
    CGRect croprect = CGRectMake(cropImageOriginX, cropImageOriginY , imageWidthAndHeight, imageWidthAndHeight);
    CGImageRef imageRef = CGImageCreateWithImageInRect([image CGImage], croprect);
    UIImage *croppedImage = [UIImage imageWithCGImage:imageRef];
    CGImageRelease(imageRef);
    return croppedImage;
}






#pragma mark- 内存
- (void)dealloc
{

}







@end









