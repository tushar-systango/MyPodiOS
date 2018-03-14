//
//  BlueTooth.h
//  BluetoothDemo
//
//  Created by whatywhaty on 16/4/13.
//  Copyright © 2016年 whatywhaty. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <CoreBluetooth/CoreBluetooth.h>

static NSString *const NotiValueChange = @"ValueChange";
static NSString *const WriteSuccessChange = @"WriteSuccess";
static NSString *const DisconnectEvent = @"Dev_Disconnected";

static NSString * const BLEDeviceServiceNotFound = @"EBMServiceNotFound";
static NSString * const BLEDeviceServiceFoundSuccess = @"EBMServiceFound";

static NSString * const didBatteryValue = @"didBatteryValue";
static NSString * const didManufacturerNameValue = @"didManufacturerNameValue";
static NSString * const didModelNumberValue = @"didModelNumberValue";
static NSString * const didSerialNumberValue = @"didSerialNumberValue";
static NSString * const didHardwareRevisionValue=@"didHardwareRevisionValue";

/**
 *  扫描设备的回调
 *
 *  @param devices 设备数组
 */
typedef void (^ScanDevicesCompleteBlock)(NSArray *devices);
/**
 *  连接设备的回调
 *
 *  @param device 设备
 *  @param err 错误信息
 */
typedef void (^ConnectionDeviceBlock)(CBPeripheral *device, NSError *err);
/**
 *  发现服务和特征的回调
 *
 *  @param serviceArray        服务数组
 *  @param characteristicArray 特征数组
 *  @param err                 错误信息
 */
typedef void (^ServiceAndCharacteristicBlock)(NSArray *serviceArray, NSArray *characteristicArray, NSError *err);


@interface BlueTooth : NSObject<CBPeripheralDelegate, CBCentralManagerDelegate>
/**
 *  管理者
 */
@property (nonatomic, strong, readonly) CBCentralManager *manager;
/**
 *  是否蓝牙可用
 */
@property (nonatomic, assign, readonly, getter = isReady)  BOOL Ready;
/**
 *  是否连接
 */
@property (nonatomic, assign, readonly, getter = isConnection)  BOOL Connection;
/**
 *  单例
 *
 *
 */
+ (instancetype)sharedInstance;
/**
 *  开始扫描
 *
 *  @param timeout 扫描的超时范围
 *  @param block   回调
 */
- (void)startScanDevicesWithInterval:(NSUInteger)timeout CompleteBlock:(ScanDevicesCompleteBlock)block;
/**
 *  停止扫描
 */
- (void)stopScanDevices;
/**
 *  连接设备
 *
 *    设备
 *   连接的超时范围
 *     回调
 */
- (void)connectionWithDeviceUUID:(NSString *)uuid TimeOut:(NSUInteger)timeout CompleteBlock:(ConnectionDeviceBlock)block;
/**
 *  断开连接
 */
- (void)disconnectionDevice;
/**
 *  扫描服务和特征
 *
 *   发现的时间范围
 *  @param block   回调
 */
- (void)discoverServiceAndCharacteristicWithInterval:(NSUInteger)time CompleteBlock:(ServiceAndCharacteristicBlock)block;
/**
 *  写数据到连接中的设备
 *
 *  @param sUUID 服务UUID
 *  @param cUUID 特征UUID
 *  @param data  数据
 */
- (void)writeCharacteristicWithServiceUUID:(NSString *)sUUID CharacteristicUUID:(NSString *)cUUID data:(NSData *)data;
/**
 *  设置通知
 *
 *  @param sUUID  服务UUID
 *  @param cUUID  特征UUID
 *  
 */
- (void)setNotificationForCharacteristicWithServiceUUID:(NSString *)sUUID CharacteristicUUID:(NSString *)cUUID enable:(BOOL)enable;

-(void)readCharacteristicWithServiceUUID:(NSString *)sUUID CharacteristicUUID:(NSString *)cUUID;

- (BOOL)sendPacket:(Byte)cmd packetIndex:(int)idx data:(NSData *)pktData ServiceUUID:(NSString *)sUUID CharacteristicUUID:(NSString *)cUUID;

- (BOOL)sendCommand:(Byte)cmd data:(NSData *)pktData ServiceUUID:(NSString *)sUUID CharacteristicUUID:(NSString *)cUUID;

- (BOOL)sendCommand:(NSData *)pktData ServiceUUID:(NSString *)sUUID CharacteristicUUID:(NSString *)cUUID;




- (void) set:(int)Strand withPixel:(int)Pixel withRed:(int)R Green:(int)G Blue:(int)B withIntensity:(int)intensity withFade:(int)fade;
- (void) set_all:(int)R Green:(int)G Blue:(int)B withIntensity:(int)intensity withFade:(int)fade;
- (void) set_across:(int)Pixel Red:(int)R Green:(int)G Blue:(int)B withIntensity:(int)intensity withFade:(int)fade;
- (void) set_subset:(int)Strand_start withPixel:(int)Pixel Red:(int)R Green:(int)G Blue:(int)B withIntensity:(int)intensity withFade:(int)fade;
- (void) clear;
- (void) setDisplay:(int)Strand withIntensity:(int)intensity withFade:(int)fade;
//- (void) batteryUpdate:(BOOL)ON;

- (void) sendCommandFlush;
- (void) sendCommandClear;

- (void) readBatteryValue;
- (void) readManufacturerName;
- (void) readModelNumber;
- (void) readSerialNumber;
- (void) readHardwareRevision;

- (void) sendDFUMode;

@end
