/******************************************************************************
 * - Copyright © 2020 Twilio, Inc. All rights reserved.
 */

#import <Foundation/Foundation.h>

@class BUWifiConfig;
@class BUNetworkAddressing;
@class BUNetworkProxy;

/*!
 *  Provide access to the current Wifi SSID and saved configurations
 */
@interface BUNetworkManager : NSObject

/*!
 *  @brief An array of BUWifiConfig objects
 *
 *   The first object will be for the currentWifi if one exists
 *   Any additional wifi configurations will be from previously saved configurations
 *
 *  @return Current SSID the device is connected to and all saved BUWifiConfig objects
 */
+ (nonnull NSArray<BUWifiConfig *> *)allWifiConfigs;

/*!
 *   @brief Wifi SSID the phone is currently connected to
 *
 *   This class method returns the current SSID (name) of the wifi network that the iOS device
 *   is connected to. It may change if the user changes their network settings. The method may
 *   also be nil if the user is not connected to any wifi network. As of iOS 13, if `Wi-Fi` is returned
 *   from the OS (dependant on your app's permisions) it will be converted to nil.
 *
 *   It is recommended to use the allWifiConfigs array rather than the individual ssid's
 *
 *  @return Current SSID network name
 */
+ (nullable NSString *)currentWifiSSID;


/*!
 *  @brief SSIDs that were previously saved
 *
 *  Return an array of strings containing a list of the SSIDs that have been saved by the user
 *   This list may contain the currentWifiSSID value.
 *
 *  It is recommended to use the allWifiConfigs array rather than the list of ssid strings
 *
 *  @return Current SSID the device is connected to and all saved BUWifiConfig objects
 */
+ (nonnull NSArray<NSString *> *)savedWifiSSIDs;

/*!
 *  @brief  Delete all saved SSIDs or passwords from the keychain
 */
+ (void)clearSavedData;

/*!
 *  @brief Validate an IP Address
 *
 *  @param ip String to evaluate
 *
 *  @return True if the string is an ip, false otherwise
 */
+ (BOOL)isValidIpAddress:(NSString *_Nullable)ip;

@end


/*!
 *  Base class for network configurations
 */
@interface BUNetworkConfig : NSObject
/*!
 *  @brief  Creates a network config used to clear the device
 */
+ (nonnull instancetype)clearNetworkConfig;

/*!
 *  @brief Address information for the imp; DHCP is default
 *
 *  By default, DHCP (BUDHCPAddressing) will be used by an imp. If needed,
 *  static addressing (BUStaticAddressing) can be used where the ip, netmask, etc.
 *  can be set manually.
 *
 *  *Note:* The ability to use non-DHCP addressing depends on impOS version
 */
@property (nonatomic, strong, nonnull) BUNetworkAddressing *addressing;

/*!
 *  @brief Allow the use of a network proxy
 *
 *  By default (when nil) no network proxy will be used.
 *
 *  *Note:* The ability to use a network proxy depends on impOS version
 */
@property (nonatomic, strong, nullable) BUNetworkProxy *proxy;

/*!
 *  @brief  Is true when the network config is set to clear the device
 *
 *  This can be useful when a BUNetworkConfig is returned from the
 *  BUNetworkSelectController to identify if it is a WifiConfig, WPSConfig,
 *  EthernetConfi, or Clear config
 */
@property (nonatomic, readonly) BOOL isClearConfig;
@end


/*!
 *  Configuration for informing the imp to use Ethernet
 *
 *  Only some imp devices (such as imp005) support Ethernet
 */
@interface BUEthernetConfig : BUNetworkConfig

/*!
 *  @brief  Creates the object
 *
 *  @return An initialized BUEthernetConfig object
 */
- (nonnull instancetype)init;
@end


/*!
 *  Configuration for performing a WPS BlinkUp
 *
 *  Some newer imp devices (such as imp005) do not support WPS
 */
@interface BUWPSConfig : BUNetworkConfig

/*!
 *  @brief WPS pin (optional)
 *
 *  The pin is the WPS pin for authentication
 *   pin can be left empty \@"" if wps push button configuration is used
 */
@property (nonatomic, copy, nullable) NSString *pin;

/*!
 *  @brief  Creates the object and sets the WPS pin with the value given
 *
 *  @param pin WPS pin for configuration
 *
 *  @return An initialized BUWPSConfig object
 */
- (nonnull instancetype)initWithWPSPin:(nullable NSString *)pin;
@end


/*!
 *  Configuration for performing a Wifi BlinkUp
 */
@interface BUWifiConfig : BUNetworkConfig

/*!
 *  @brief  The ssid of the network to connect to
 */
@property (nonatomic, copy, nullable) NSString *ssid;

/*!
 *  @brief  The password of the network.
 *  Be sure to check the useSavedPassword property before choosing
 *  this property or the savedPassword.
 *  If this property is set, useSavedPassword will be changed to NO
 */
@property (nonatomic, copy, nullable) NSString *password;

/*!
 *  If this option is true, a previously stored password will be used
 *  If this option is false, the password property will be used
 *   Note: setting the password will automatically change this property to NO
 *   Note: calling removeConfig with automatically change this property to NO
 */
@property (nonatomic, assign) BOOL useSavedPassword;

/*!
 *  @brief  The password that was saved for the SSID
 */
@property (nonatomic, readonly, nullable) NSString *savedPassword;

/*!
 *  Initializes the object with the ssid given. Sets the useSavedPassword property to true by default
 *
 *  @param ssid SSID to use for this configuration
 *
 *  @return BUWifiConfig object with the SSID set
 */
- (nonnull instancetype)initWithExistingSSID:(nonnull NSString *)ssid;

/*!
 *  Initializes the object with an ssid and password. By default useSavedPassword is false
 *
 *  @param ssid     SSID to use for this configuration
 *  @param password Password for the SSID
 *
 *  @return BUWifiConfig object with the SSID and Password set
 */
- (nonnull instancetype)initWithSSID:(nonnull NSString *)ssid password:(nullable NSString *)password;

/*!
 *  Standard init does not preset properties
 *
 *  @return Create a new object without setting the SSID or Password
 */
- (nonnull instancetype)init;

/*!
 *  Saves the ssid (using the current password property) to storage
 *   This should not be called on configurations where useSavedPassword is true as it is already saved
 */
- (void)saveConfig;

/*!
 *  Remove the ssid (and any saved passwords for that ssid) from storage
 *   Also sets useSavedPassword to NO
 */
- (void)removeConfig;
@end
