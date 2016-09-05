/*
  Copyright (c) 2014 MediaTek Inc.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License..

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
   See the GNU Lesser General Public License for more details.
*/

#ifndef LWiFi_h
#define LWiFi_h

#include "Arduino.h"
#include "IPAddress.h"
#include "vmnwsetting.h"
#include "vmconn.h"
#include "WString.h"

class LWiFiConnectContext;

//LWiFiLoginInfo enum
enum LWiFiEncryption
{
  LWIFI_OPEN, // The open networks.
  LWIFI_WEP,  // The WEP encrypted networks.
  LWIFI_WPA,  // The WPA1 and WPA2 networks.
};

//LWiFiLoginInfo enum
enum LWifiStatus
{
  LWIFI_STATUS_DISABLED,          // The LWiFi module is disabled. Use LWiFi.begin() to enable it.
  LWIFI_STATUS_DISCONNECTED,      // The LWiFi module isn't connected to any AP, or the connection is lost due to bad signal strength.
  LWIFI_STATUS_CONNECTED,         // The LWiFi module is connected to an AP.
};

//LWiFiLoginInfo Class
// 
// This class is used as a parameter for LWiFiClass.connect.
// Please see the description of LWiFiClass.connect for details.
class LWiFiLoginInfo
{
  /* DOM-NOT_FOR_SDK-BEGIN */
public:
  LWiFiEncryption m_enc;
  String m_password;
  String m_username;
  
public:

  // Connects to an open network.
  LWiFiLoginInfo();

  // Sets the encryption type and password.
  LWiFiLoginInfo(LWiFiEncryption enc, const String &password);

  // Sets the encryption type, password, and user name.
  LWiFiLoginInfo(LWiFiEncryption enc, const String &password, const String &username);

  /* DOM-NOT_FOR_SDK-END */
};

//LWifiClass Class
// 
// LWifiClass exposes the Wi-Fi AP scan and connect function of the LinkIt ONE board.
// Use LWiFi singleton object to access the actual functions. Do not declare LWiFiClass instances.
// After a connection to an Wi-Fi access point is established, use LWiFiClient object to create a TCP socket;
// or use LWiFiUDP object to create a UDP socket.
// 
// EXAMPLE:
// <code>
//     LWiFi.begin();
//     int nearbyAccessPointCount = LWiFi.scanNetworks();
//     LWiFi.end();
// </code>
class LWiFiClass
{
public:

  /* DOM-NOT_FOR_SDK-BEGIN */
  LWiFiClass();
  /* DOM-NOT_FOR_SDK-END */

  // DESCRIPTION
  //  Turns on and initializes the Wi-Fi module.
  //
  // PARAMETERS
  //  N/A.
  //
  // EXAMPLE
  // <code>
  //     LWiFi.begin();   // Turns on the Wi-Fi module.
  //     LWiFi.end();     // Turns off the Wi-Fi module.
  // </code>
  void begin();

  // DESCRIPTION
  //  Uninitializes and turns off the Wi-Fi module.
  //
  // PARAMETERS
  //  N/A.
  //
  // EXAMPLE
  // <code>
  //     LWiFi.begin();   // Turns on the Wi-Fi module.
  //     LWiFi.end();     // Turns off the Wi-Fi module
  // </code>
  void end();

  // DESCRIPTION
  //  Starts a Wi-Fi connection for open networks.
  //
  // PARAMETERS
  //  ssid: The pointer to the SSID string.
  // 
  // RETURNS
  // > 0: Successful.
  // <= 0: Failed.
  //
  // EXAMPLE
  // <code>
  //     LWiFi.begin();   // Turns on the Wi-Fi module.
  //     LWiFi.connect("open_network_ssid");
  //     LWiFi.end();     // Turns off the Wi-Fi module.
  // </code>
  int connect(const char* ssid);

  // DESCRIPTION
  //  Starts the Wi-Fi connection.
  //  The login information is stored in loginInfo.
  //
  // PARAMETERS
  //  ssid: The pointer to the SSID string.
  //  loginInfo: An LWiFiKey that stores login information.
  //
  // RETURNS
  // > 0: Successful.
  // <= 0: Failed.
  //
  // EXAMPLE
  // <code>
  //     LWiFi.begin();   // Turns on the Wi-Fi module.
  //     LWiFi.connect("wep_network_ssid", LWiFiLoginInfo(LWIFI_WEP, "wep_password"));
  //     LWiFi.end();     // Turns off the Wi-Fi module.
  // </code>
  int connect(const char* ssid, const LWiFiLoginInfo &loginInfo);

  // DESCRIPTION
  //  Starts a Wi-Fi connection with WEP encryption.
  //  Configure a key into the device. The key type (WEP-40, WEP-104)
  //  is determined by the size of the key (5 bytes for WEP-40, 13 bytes for WEP-104).
  //
  // PARAMETERS
  //  ssid: The pointer to the SSID string.
  //  key_idx: The key index to be set. Valid values are 0-3.
  //  key: The key input buffer.
  //
  // RETURNS
  // > 0: Succeessful.
  // <= 0: Failed.
  //
  // EXAMPLE
  // <code>
  //     LWiFi.begin();   // Turns on the Wi-Fi module.
  //     LWiFi.connectWEP("wifi_ap_ssid", "mypassword");
  //     LWiFi.end();     // Turns off the Wi-Fi module.
  // </code>
  int connectWEP(const char* ssid, const char* key);

  // DESCRIPTION
  //  Starts Wi-Fi connection with WPA/WPA-2 passphrase.
  //
  // PARAMETERS
  //  ssid: The pointer to the SSID string.
  //  passphrase: The passphrase. Valid characters in a passphrase
  //              must be between ASCII 32-126 (decimal).
  //
  // RETURNS
  // > 0: Successful.
  // <= 0: Failed.
  //
  // EXAMPLE
  // <code>
  //     LWiFi.begin();   // Turns on the Wi-Fi module.
  //     LWiFi.connectWPA("wifi_ap_ssid", "mypassword");
  //     LWiFi.end();     // Turns off the Wi-Fi module.
  // </code>
  int connectWPA(const char* ssid, const char *passphrase);
 
  // DESCRIPTION
  //  Starts Wi-Fi connection with the configuration set from a Smart phone.
  //
  // PARAMETERS
  //  void.
  // RETURNS
  // > 0: Successful.
  // <= 0: Failed.
  //
  // EXAMPLE
  // <code>
  //     LWiFi.begin();   // Turns on the Wi-Fi module.
  //     LWiFi.connectSmart();
  //     LWiFi.end();     // Turns off the Wi-Fi module.
  // </code>

  int connectSmart(void);

  // DESCRIPTION
  //  Disconnects from the Wi-Fi AP.
  //
  // RETURNS
  //  0: Always, at the time of writing. 
  //
  // EXAMPLE
  // <code>
  //     LWiFi.begin();   // Turns on the Wi-Fi module.
  //     LWiFi.connectWPA("wifi_ap_ssid", "mypassword");  // Connects to an WPA-encrypted AP.
  //     LWifi.disconnect();  // Disconnects from the AP.
  //     LWiFi.end();     // Turns off the Wi-Fi module.
  // </code>
  int disconnect(void);

  // DESCRIPTION
  //  Gets the interface MAC address.
  //
  // RETURNS
  //  The pointer to uint8_t array with length VM_WLAN_LOC_MAC_ADDR_LEN
  //  which is defined as 6 bytes.
  //
  // EXAMPLE
  // <code>
  //     Serial.begin(115200);
  //     LWiFi.begin();
  //     uint8_t macAddress[VM_WLAN_WNDRV_MAC_ADDRESS_LEN] = {0};
  //     LWiFi.macAddress(macAddress);
  //     Serial.print("MAC Address is:");
  //     for(int i = 0; i < VM_WLAN_WNDRV_MAC_ADDRESS_LEN; ++i)
  //     {
  //       Serial.print(macAddress[i], HEX);
  //       Serial.print(":");
  //     }
  //     Serial.println();
  // </code>
  uint8_t* macAddress(uint8_t* mac);

  // DESCRIPTION
  //  Gets the interface IP address.
  //
  // RETURNS
  //  The IP address value.
  IPAddress localIP();

  // DESCRIPTION
  //  Gets the interface subnet mask address.
  //
  // RETURNS
  //  The subnet mask address value.
  IPAddress subnetMask();

  // DESCRIPTION
  //  Gets the gateway IP address.
  //
  // RETURNS
  //  The gateway IP address value.
  IPAddress gatewayIP();

  // DESCRIPTION
  //  Returns the current SSID that's associated with the network.
  //
  // RETURNS
  //  The SSID string.
  char* SSID();

  // DESCRIPTION
  //  Returns the current BSSID associated with the network.
  //  It's the MAC address of the Access Point.
  //
  // RETURNS
  //  The pointer to uint8_t array with length WL_MAC_ADDR_LENGTH which is 6 bytes long.
  uint8_t* BSSID(uint8_t* bssid);

  // DESCRIPTION
  //  Returns the current RSSI/Received Signal Strength in dBm that's
  //  associated with the network.
  //
  // RETURNS
  //  The signed value in dB. A smaller (negative) value indicates weaker signal.
  int32_t RSSI();

  // DESCRIPTION
  //  Start the scan for available Wi-Fi networks.
  //
  // RETURNS
  //  Number of discovered Wi-Fi networks.
  // 
  // EXAMPLE
  // <code>
  //     Serial.begin();
  //     int numOfAP = LWiFi.scanNetworks();
  //     Serial.print("number of WiFi AP found:");
  //     Serial.println(numOfAP);
  // </code>
  int8_t scanNetworks();

  // DESCRIPTION
  //  Returns the SSID discovered during the Wi-Fi network scan.
  //
  // PARAMETERS
  //  networkItem: Specify the network item to get information from.
  //
  // RETURNS
  //  SSID string of the specified item from the scanned network list.
  char*	SSID(uint8_t networkItem);

  // DESCRIPTION
  //  Returns the RSSI of the networks discovered during the scanNetworks.
  //
  // PARAMETERS
  //  networkItem: Specify from which network item want to get the information.
  //
  // RETURNS
  //  Signed value of RSSI of the specified item from the scanned network list.
  int32_t RSSI(uint8_t networkItem);

  // DESCRIPTION
  //  Returns the connection status.
  //
  // RETURNS
  //  One of the value defined in LWifiStatus.
  //  It can be one of the following:
  //    LWIFI_STATUS_DISABLED: The LWiFi module is disabled. Use LWiFi.begin() to enable it.
  //    LWIFI_STATUS_DISCONNECTED: The LWiFi module isn't connected to any AP, or the connection is lost due to bad signal strength.
  //    LWIFI_STATUS_CONNECTED: The LWiFi module is connected to an AP.
  LWifiStatus status();

  // DESCRIPTION
  //  Resolves the given hostname to an IP address.
  //
  // PARAMETERS
  //  param aHostname: The name to be resolved.
  //  param aResult: The IPAddress structure to store the returned IP address.
  //
  // RETURNS
  //  1: If aIPAddrString is successfully converted to an IP address,
  //  else, error code.
  int hostByName(const char* aHostname, IPAddress& aResult);

  /* DOM-NOT_FOR_SDK-BEGIN */
  friend class LWiFiClient;
  friend class LWiFiServer;
  /* DOM-NOT_FOR_SDK-END */

public:
  /* DOM-NOT_FOR_SDK-BEGIN */
  char m_macAddress[VM_WLAN_LOC_MAC_ADDR_LEN];
  vm_wlan_ip_info_struct m_ipInfo;  // The IP information after it's connected.
  vm_wlan_conned_ap_info_struct m_apInfo;  // This stores the BSSID and RSSI of the connectd AP.
  vm_wlan_cfg_ap_struct m_apParam;  // This stores the SSID of the connected AP.
  vm_wlan_scan_result_struct m_scanInfo;  // The scanned AP's information.
  VMINT m_lastError;

private:
  int wifiConnectImpl(LWiFiConnectContext &context);
  /* DOM-NOT_FOR_SDK-END */
};

// Use this LWiFi singleton to access the Wi-Fi functionality.
extern LWiFiClass LWiFi;

#endif // #ifndef LWiFi_h
