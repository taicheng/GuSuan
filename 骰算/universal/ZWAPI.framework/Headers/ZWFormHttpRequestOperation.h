//
//  ZWFormHttpRequestOperation.h
//  ZWAPI
//
//  Created by taic_cai on 16/8/16.
//  Copyright © 2016年 taic_cai. All rights reserved.
//

#import "ZWFormFilePart.h"
#import "ZWFormHttpRequestOperationDelegate.h"

@class ZWFormHttpRequestOperation;

typedef ZWFormHttpRequestOperation *(^ZWFormHttpRequestOperationP)(NSString *name,id value);
typedef ZWFormHttpRequestOperation *(^ZWFormHttpRequestOperationRequestToken)(void);
typedef ZWFormHttpRequestOperation *(^ZWFormHttpRequestOperationPS)(NSDictionary *params);
typedef ZWFormHttpRequestOperation *(^ZWFormHttpRequestOperationF2)(NSString *name,NSURL *fileUrl);
typedef ZWFormHttpRequestOperation *(^ZWFormHttpRequestOperationF4)(NSString *name,id file,NSString *fileName,NSString *mimeType);//file可为:NSURL,NSData
typedef ZWFormHttpRequestOperation *(^ZWFormHttpRequestOperationI2)(NSString *name,UIImage *image);
typedef ZWFormHttpRequestOperation *(^ZWFormHttpRequestOperationAU)(id urlComponent);//往self.url中添加url的后段

typedef void(^ZWFormHttpRequestOperationC)(ZWFormHttpRequestOperation *op,BOOL success,NSError *error);
typedef void(^ZWFormHttpRequestOperationB)(ZWFormHttpRequestOperation *op);
typedef void(^ZWFormHttpRequestOperationF)(ZWFormHttpRequestOperation *op,NSError *error);
typedef void(^ZWFormHttpRequestOperationU)(ZWFormHttpRequestOperation *op,int64_t bytesWritten, int64_t totalBytesWritten, int64_t totalBytesExpectedToWrite);
typedef void(^ZWFormHttpRequestOperationD)(ZWFormHttpRequestOperation *op,int64_t bytesRead, int64_t totalBytesRead, int64_t totalBytesExpectedToRead);


@interface ZWFormHttpRequestOperation : NSOperation{
@protected
    NSMutableDictionary *_formParams;//表单数据(非文件)
    NSMutableArray *_formFileParts;//表单文件数据
    BOOL _cancelled;//取消
    CGFloat _progress,_progressOfUpload,_progressOfDownload;//进度
}
@property(nonatomic,strong) NSString *url;//url字符串
@property(nonatomic,strong) NSString *basicUrl;//可由basicUrl拼接出url来
@property(nonatomic,strong) NSString *method;//http请求方法
@property(nonatomic,assign) NSTimeInterval delayStartTime;//延迟开始请求的时间

@property (nonatomic,readonly) NSData   *responseData;//请求返回的二进制数据
@property (nonatomic,readonly) NSString *responseString;//请求返回字符串
@property (nonatomic,readonly) id       responseJson;//请求返回json数据
@property (nonatomic,readonly) NSDictionary *allHeaderFields;//返回请求的头部数据

@property (nonatomic,readonly) NSDictionary *formParams;//请求的非文件参数
@property (nonatomic,readonly) NSArray *formFileParts;//请求的文件参数
@property (nonatomic,readonly) NSString *fullUrl;//返回將post数据也放入url中的url,不包含上传文件,一般用于调试整个url
@property (nonatomic,  assign) BOOL postRawData;//使用post请求,直接将self.rawData作为请求的消息体,默认为NO
@property (nonatomic,  strong) NSData *rawData;//请求的消息体
@property (nonatomic,readonly) NSString *rawDataStringOfFormParams;//请求参数对应的json字符串
@property (nonatomic,readonly) NSData *rawDataOfFormParams;//请求参数对应的json字符串

@property(nonatomic,copy) ZWFormHttpRequestOperationB whenStart;//开始请求后的回调
@property(nonatomic,copy) ZWFormHttpRequestOperationC whenComplete;//完成后的回调
@property(nonatomic,copy) ZWFormHttpRequestOperationB whenSuccess;//成功后的回调
@property(nonatomic,copy) ZWFormHttpRequestOperationF whenFail;//失败后的回调
@property(nonatomic,copy) ZWFormHttpRequestOperationB whenCancel;//被取消后的回调
@property(nonatomic,copy) ZWFormHttpRequestOperationU whenUploadProgress;//上传进度变化的回调
@property(nonatomic,copy) ZWFormHttpRequestOperationD whenDownloadProgress;//下载进度变化的回调

@property(nonatomic,readonly) ZWFormHttpRequestOperationAU URLCOMPONENT;//往self.url的尾部添加字符串,如果参数是由用户输入,请对参数调用方法percentEscapedQueryStringKey进行url字符转义
@property(nonatomic,readonly) ZWFormHttpRequestOperationP  PARAM;//调用setFormValue:forName:的便捷方法
@property(nonatomic,readonly) ZWFormHttpRequestOperationPS PARAMS;//调用遍历dictionary,setFormValue:forName:的便捷方法
@property(nonatomic,readonly) ZWFormHttpRequestOperationF2 FILE;//上传文件,输入name,fileUrl
@property(nonatomic,readonly) ZWFormHttpRequestOperationF4 FILE_ALIAS;//上传文件,输入全部参数:name,fileUrl/NSData,fileName,mimeType
@property(nonatomic,readonly) ZWFormHttpRequestOperationI2 FILE_JPG;//上传jpg图片,输入name,UIImage
@property(nonatomic,readonly) ZWFormHttpRequestOperationI2 FILE_PNG;//上传png图片,输入name,UIImage
@property(nonatomic,assign) id<ZWFormHttpRequestOperationDelegate> delegate;
@property(nonatomic,readonly) NSError *error;//错误信息
@property(nonatomic,readonly) BOOL isSuccess;
@property(nonatomic,readonly) BOOL isFail;
@property(nonatomic,readonly) BOOL isCancelled;
@property(nonatomic,readonly) BOOL isFinished;
@property(nonatomic,readonly) BOOL isExecuting;
@property(nonatomic,readonly) CGFloat progress;//progressOfDownload*(progressFactorOfDownload)+progressOfUpload*(1-progressFactorOfDownload)
@property(nonatomic,readonly) CGFloat progressOfUpload;//上传进度
@property(nonatomic,readonly) CGFloat progressOfDownload;//下载进度
@property(nonatomic,assign  ) CGFloat progressFactorOfDownload;//在计算进度时,下载进度所占的比例,进度=progressOfDownload*(progressFactorOfDownload)+progressOfUpload*(1-progressFactorOfDownload),默认为0

/**
 *  输入url的参数,输出其对应的url请求参数字符串.其中,会对参数按照字母顺序进行排序,并进行url encode操作
 *
 *  @param formParams 表单数据(非文件)
 *
 *  @return url中的请求参数,如:name=moon&gender=M
 */
+ (NSString *)queryStringWithFormParams:(NSDictionary *)formParams;

/**
 *  生成get请求对应的url字符串(没有对参数进行url encode)
 *
 *  @param url        基础的url
 *  @param formParams 表单的参数
 *
 *  @return get请求对应的url字符串
 */
+ (NSString *)urlOfGETWithBaseUrl:(NSString *)url formParams:(NSDictionary *)formParams;

//执行各种回调
- (void)doStart;
- (void)doCompleteWithSuccess:(BOOL)success error:(NSError *)error;
- (void)doSuccess;
- (void)doFailWithError:(NSError *)error;
- (void)doCancel;
- (void)doUploadProgressWithBytesWritten:(int64_t)bytesWritten totalBytesWritten:(int64_t)totalBytesWritten totalBytesExpectedToWrite:(int64_t)totalBytesExpectedToWrite;
//- (void)doUploadProgress:(NSProgress *)progress;
- (void)doDownloadProgressWithBytesRead:(int64_t)bytesRead totalBytesRead:(int64_t)totalBytesRead totalBytesExpectedToRead:(int64_t)totalBytesExpectedToRead;
//- (void)doDownloadProgress:(NSProgress *)progress;
/**
 *  取消操作
 @override
 */
- (void)cancel;

/**
 *  实例化http请求操作
 *
 *  @param url    url
 *  @param method http请求方法,get/post/...,当有文件时,一定使用post
 *  @param delay  延迟时间,有值时,将会延时delay时间,执行startRequestAsync方法
 *
 *  @return 请求操作对象
 */
- (id)initWithUrl:(NSString *)url method:(NSString *)method delayStart:(NSTimeInterval)time;

/**
 *  异步的方式开始请求
 *	@override
 */
- (void)startRequestAsync;

/**
 *  获取指定的表单name属性对应的参数值
 *
 *  @param name 表单name属性
 *
 *  @return 返回值可能为单值(如NSString,NSNumber),NSArray,NSDictionary,NSSet
 */
- (id<NSObject>)formParamForName:(NSString *)name;

/**
 *  移除指定的表单name属性选项
 *
 *  @param name 表单name属性
 */
- (void)removeParamForName:(NSString *)name;

/**
 *  设置某表项对应的值
 *	提交的body如:
 单值:name=value
 多值value=NSArray:name[]=value1&name[]=value2,...
 多值value=NSDictionary:name[key1]=value1&name[key2]=value2,...
 多值value=NSSet:name=value1&name=value2,...
 *  @param value 值对象
 *  @param name  表项名称
 */
- (void)setFormValue:(id<NSObject>)value forName:(NSString *)name;

/**
 *  设置某表项对应的整数值
 *
 *  @param value 整数
 *  @param name  表项名称
 */
- (void)setFormInteger:(NSInteger)value forName:(NSString *)name;

/**
 *  设置某表项对应的浮点数
 *
 *  @param value 浮点数
 *  @param name  表项名称
 */
- (void)setFormFloat:(CGFloat)value forName:(NSString *)name;

/**
 *  设置某表项对应的bool
 *
 *  @param value bool
 *  @param name  表项名称
 */
- (void)setFormBool:(BOOL)value forName:(NSString *)name;

/**
 *  设置某表项对应的字符串
 *
 *  @param value 字符串
 *  @param name  表项名称
 */
- (void)setFormString:(NSString *)value forName:(NSString *)name;

/**
 *  添加表单选项值到指定的表项上
 *	表单提交时,body:name[]=value1&name[]=value2,...
 *  @param value 表项的值,可为单值或为NSArray
 *  @param name  表项的name值
 */
- (void)addFormValue:(id<NSObject>)value forName:(NSString *)name;

/**
 *  添加某些表项值到表单指定的表项上
 *表单提交时,body:name[]=value1&name[]=value2,...
 *  @param array 多值
 *  @param name  表项name
 */
- (void)addFormArray:(NSArray *)array forName:(NSString *)name;

/**
 *  添加多个表项值到name表项上
 *	表单提交时,body:name[key1]=value1&name[key2]=value2,...
 *  @param dict 多值
 *  @param name 表项name
 */
- (void)addFormDictionary:(NSDictionary *)dict forName:(NSString *)name;

/**
 *  添加多个表项值到name表项上
 *	表单提交时,body:name=value1&name=value2,...
 *  @param set 多值
 *  @param name 表项name
 */
- (void)addFormSet:(NSSet *)set forName:(NSString *)name;

/**
 *  获取表项name对应的多个上传文件对象
 *
 *  @param name 表项名称
 *
 *  @return @[ZWFormFilePart]
 */
- (NSArray *)formFilePartsForName:(NSString *)name;

/**
 *  移除掉上传对象
 *
 *  @param parts @[ZWFormFilePart]
 */
- (void)removeFileParts:(NSArray *)parts;

/**
 *  添加上传文件
 *
 Appends the HTTP header `Content-Disposition: file; filename=#{filename}; name=#{name}"` and `Content-Type: #{mimeType}`, followed by the encoded file data and the multipart form boundary.
 
 *  @param url      文件的本地路径url
 *  @param name     表单的name属性
 *  @param fileName 文件在本地的文件名
 *  @param mimeType 表单里的mimeType请求头信息
 */
- (void)addFileURL:(NSURL *)url name:(NSString *)name fileName:(NSString *)fileName mimeType:(NSString *)mimeType;
/**
 *  添加上传的文件
 *	会根据文件名,计算出fileName与mimeType,如果计算不出来,不添加
 *  @param url  文件url
 *  @param name 表项name属性
 *  @return	返回上传文件的封装对象
 */
- (void)addFileData:(NSData *)data name:(NSString *)name fileName:(NSString *)fileName mimeType:(NSString *)mimeType;
/**
 *  添加上传的文件,文件名和mimeType会根据url计算出来
 *
 *  @param url  文件url
 *  @param name 表项name属性
 */
- (void)addFileURL:(NSURL *)url name:(NSString *)name;

/**
 *  添加上传的jpg图片
 *
 *  @param image 图片
 *  @param name  表项name属性
 */
- (void)addJPG:(UIImage *)image name:(NSString *)name;

/**
 *  添加上传的png图片
 *
 *  @param image 图片
 *  @param name  表项name属性
 */
- (void)addPNG:(UIImage *)image name:(NSString *)name;
@end


@interface NSString(ZWFormHttpRequestOperation)

/**
 *  转义成url参数中的key部分
 *
 *  @param encoding 字符串编码
 *
 *  @return 转义后的字符串
 */
- (NSString *)percentEscapedQueryStringKeyWithEncoding:(NSStringEncoding)encoding;

/**
 *  转义成url参数中的key部分,默认的编码是utf8
 *
 *  @return 转义后的字符串
 */
- (NSString *)percentEscapedQueryStringKey;

/**
 *  转义成url参数中的value部分
 *
 *  @param encoding 字符串编码
 *
 *  @return 转义后的字符串
 */
- (NSString *)percentEscapedQueryStringValueWithEncoding:(NSStringEncoding)encoding;

/**
 *  转义成url参数中的value部分,默认的编码是utf8
 *
 *  @param encoding 字符串编码
 *
 *  @return 转义后的字符串
 */
- (NSString *)percentEscapedQueryStringValue;
@end