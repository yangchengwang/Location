/**************************************************************************************************
  Filename:       nwk_globals.h
  Revised:        $Date: 2009-03-18 11:00:08 -0700 (Wed, 18 Mar 2009) $
  Revision:       $Revision: 19446 $

  Description:    User definable Network Parameters.


  Copyright 2004-2009 Texas Instruments Incorporated. All rights reserved.

  IMPORTANT: Your use of this Software is limited to those specific rights
  granted under the terms of a software license agreement between the user
  who downloaded the software, his/her employer (which must be your employer)
  and Texas Instruments Incorporated (the "License").  You may not use this
  Software unless you agree to abide by the terms of the License. The License
  limits your use, and you acknowledge, that the Software may not be modified,
  copied or distributed unless embedded on a Texas Instruments microcontroller
  or used solely and exclusively in conjunction with a Texas Instruments radio
  frequency transceiver, which is integrated into your product.  Other than for
  the foregoing purpose, you may not use, reproduce, copy, prepare derivative
  works of, modify, distribute, perform, display or sell this Software and/or
  its documentation for any purpose.

  YOU FURTHER ACKNOWLEDGE AND AGREE THAT THE SOFTWARE AND DOCUMENTATION ARE
  PROVIDED �AS IS?WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, 
  INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE, 
  NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL
  TEXAS INSTRUMENTS OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT,
  NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER
  LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
  INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE
  OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT
  OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
  (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

  Should you have any questions regarding your right to use this Software,
  contact Texas Instruments Incorporated at www.TI.com. 
**************************************************************************************************/

#ifndef NWK_GLOBALS_H
#define NWK_GLOBALS_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************
 * INCLUDES
 */

#include "ZComDef.h"
#include "nwk_bufs.h"
#include "AssocList.h"
#include "BindingTable.h"
#include "ZGlobals.h"

/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * CONSTANTS
 */
  
// If ZIGBEEPRO is defined - define all the features for Zigbee Pro
//#define ZIGBEE_MULTICAST
#if defined ( ZIGBEEPRO )
  #if !defined ( ZIGBEE_STOCHASTIC_ADDRESSING )
    #define ZIGBEE_STOCHASTIC_ADDRESSING
    #define ZIGBEE_NWK_UNIQUE_ADDR_CHECK
  #endif 
  #if !defined ( NWK_LINK_STATUS_PERIOD )
    #define NWK_LINK_STATUS_PERIOD 15       // 15 seconds
  #endif 
  #if !defined ( ZIGBEE_MULTICAST )
    #define ZIGBEE_MULTICAST
  #endif
  #if !defined ( ZIGBEE_MANY_TO_ONE )
    #define ZIGBEE_MANY_TO_ONE
  #endif
  #if !defined ( ZIGBEE_SOURCE_ROUTING )
    #define ZIGBEE_SOURCE_ROUTING
  #endif
  #if !defined ( ZIGBEE_COMMISSIONING )
    #define ZIGBEE_COMMISSIONING
  #endif
  #if !defined ( ZIGBEE_FREQ_AGILITY )
    #define ZIGBEE_FREQ_AGILITY
  #endif
  #if !defined ( NWK_MANAGER )
    //#define NWK_MANAGER // WARNING: this should be enabled only for one device per network
  #endif
  #if !defined ( ZIGBEE_FRAGMENTATION )
    #define ZIGBEE_FRAGMENTATION
  #endif
#else
  #define NWK_LINK_STATUS_PERIOD  0
#endif
  
#if ( RFD_RCVC_ALWAYS_ON==TRUE ) || ( ZG_BUILD_RTR_TYPE )
  // The PANID Conflict feature is mandatory for both 2007 and 2007 PRO
  // So, it will be ON all the time (except sleeping end devices).
  #if !defined ( ZIGBEE_PANID_CONFLICT )
    #define ZIGBEE_PANID_CONFLICT
  #endif
#endif
  
// Controls the operational mode of network
#define NWK_MODE_STAR         0
#define NWK_MODE_TREE         1
#define NWK_MODE_MESH         2

// Controls various stack parameter settings
#define NETWORK_SPECIFIC      0
#define HOME_CONTROLS         1
#define ZIGBEEPRO_PROFILE     2
#define GENERIC_STAR          3
#define GENERIC_TREE          4

// Channel mask
#define MAX_CHANNELS_868MHZ     0x00000001
#define MAX_CHANNELS_915MHZ     0x000007FE
#define MAX_CHANNELS_24GHZ      0x07FFF800

#if defined ( ZIGBEEPRO )
  #define STACK_PROFILE_ID      ZIGBEEPRO_PROFILE
#else
  #define STACK_PROFILE_ID      NETWORK_SPECIFIC
#endif

#if ( STACK_PROFILE_ID == ZIGBEEPRO_PROFILE )
    #define MAX_NODE_DEPTH      20
    #define NWK_MODE            NWK_MODE_MESH
    #define SECURITY_MODE       SECURITY_COMMERCIAL
  #if   ( SECURE != 0  )
    #define USE_NWK_SECURITY    1   // true or false
    #define SECURITY_LEVEL      5
  #else
    #define USE_NWK_SECURITY    0   // true or false
    #define SECURITY_LEVEL      0
  #endif

#elif ( STACK_PROFILE_ID == HOME_CONTROLS )
    #define MAX_NODE_DEPTH      5
    #define NWK_MODE            NWK_MODE_MESH
    #define SECURITY_MODE       SECURITY_COMMERCIAL
  #if   ( SECURE != 0  )
    #define USE_NWK_SECURITY    1   // true or false
    #define SECURITY_LEVEL      5
  #else
    #define USE_NWK_SECURITY    0   // true or false
    #define SECURITY_LEVEL      0
  #endif

#elif ( STACK_PROFILE_ID == GENERIC_STAR )
    #define MAX_NODE_DEPTH      5
    #define NWK_MODE            NWK_MODE_STAR
    #define SECURITY_MODE       SECURITY_RESIDENTIAL
  #if   ( SECURE != 0  )
    #define USE_NWK_SECURITY    1   // true or false
    #define SECURITY_LEVEL      5
  #else
    #define USE_NWK_SECURITY    0   // true or false
    #define SECURITY_LEVEL      0
#endif

#elif ( STACK_PROFILE_ID == NETWORK_SPECIFIC )
// define your own stack profile settings
    #define MAX_NODE_DEPTH          10
    #define NWK_MODE            NWK_MODE_MESH
    #define SECURITY_MODE       SECURITY_RESIDENTIAL
  #if   ( SECURE != 0  )
    #define USE_NWK_SECURITY    1   // true or false
    #define SECURITY_LEVEL      5
  #else
    #define USE_NWK_SECURITY    0   // true or false
    #define SECURITY_LEVEL      0
  #endif
#endif
 
// Zigbee protocol version
#define ZB_PROT_V1_0                 1
#define ZB_PROT_V1_1                 2

#define ZB_PROT_VERS      ZB_PROT_V1_1
#define ZIGBEE_PROT_ID            0x00

// Status and error codes for extra information
#define NWK_STATUS_PING_RCVD            0x0001
#define NWK_STATUS_ASSOC_CNF            0x0002
#define NWK_STATUS_ED_ADDR              0x0003
#define NWK_STATUS_PARENT_ADDR          0x0004
#define NWK_STATUS_COORD_ADDR           0x0005
#define NWK_STATUS_ROUTER_ADDR          0x0006
#define NWK_STATUS_ORPHAN_RSP           0x0007

#define NWK_ERROR_ASSOC_RSP             0x1001
#define NWK_ERROR_ASSOC_RSP_MF          0x1002
#define NWK_ERROR_ASSOC_CNF_DENIED      0x1003
#define NWK_ERROR_ENERGY_SCAN_FAILED    0x1004

// Maximum number in tables
#if !defined( NWK_MAX_DEVICE_LIST )
  #define NWK_MAX_DEVICE_LIST     20  // Maximum number of devices in the
                                    // Assoc/Device list.
#endif

// Don't change this value to set the number of devices.  Change
//  NWK_MAX_DEVICE_LIST above
#define NWK_MAX_DEVICES      NWK_MAX_DEVICE_LIST + 1    // One extra space for parent

#define NWK_MAX_ROUTERS           6
  
#if ( ZG_BUILD_RTR_TYPE )
  #define MAX_NEIGHBOR_ENTRIES    8
#else
  #define MAX_NEIGHBOR_ENTRIES    4
#endif

#if !defined ( APS_MAX_GROUPS )
  #define APS_MAX_GROUPS  10
#endif

// Maxiumum number of REFLECTOR address entries
#if defined ( REFLECTOR )
  #define NWK_MAX_REFLECTOR_ENTRIES ( NWK_MAX_BINDING_ENTRIES )
#else
  #define NWK_MAX_REFLECTOR_ENTRIES 0
#endif

#if !defined( MAX_BCAST )
  #define MAX_BCAST 4
#endif
  
// Maxiumum number of secure partners(Commercial mode only).
// Add 1 for the Trust Center(Coordinator) if it is not the parent.
#define NWK_MAX_SECURE_PARTNERS 1

// Maximum number of addresses managed by the Address Manager
#define NWK_MAX_ADDRESSES (uint16)                          \
                          ( ( NWK_MAX_DEVICES           ) +   \
                            ( NWK_MAX_REFLECTOR_ENTRIES ) +   \
                            ( NWK_MAX_SECURE_PARTNERS   )   )

// Network PAN Coordinator Address
#define NWK_PAN_COORD_ADDR 0x0000
  
// Network Addressing modes
#define NWK_ADDRESSING_DISTRIBUTED    0x00
#define NWK_ADDRESSING_STOCHASTIC     0x02
  
#if !defined ( NWK_LINK_STATUS_PERIOD )
  #define NWK_LINK_STATUS_PERIOD 15       // 15 seconds
#endif

#if !defined ( NWK_ROUTE_AGE_LIMIT )
  #define NWK_ROUTE_AGE_LIMIT 3       // 3 missed link satus frames
#endif

#if !defined ( MAX_RTG_SRC_ENTRIES )
  #define MAX_RTG_SRC_ENTRIES 12
#endif

#if ( ZG_BUILD_ENDDEVICE_TYPE )
  #define APS_MAX_ENDDEVICE_BROADCAST_ENTRIES   5
#endif
  
  
/*********************************************************************
 * TYPEDEFS
 */

/*********************************************************************
 * NWK GLOBAL VARIABLES
 */

// Variables for MAX data buffer levels
extern CONST byte gNWK_MAX_DATABUFS_WAITING;
extern CONST byte gNWK_MAX_DATABUFS_SCHEDULED;
extern CONST byte gNWK_MAX_DATABUFS_CONFIRMED;
extern CONST byte gNWK_MAX_DATABUFS_TOTAL;

extern CONST byte gNWK_INDIRECT_CNT_RTG_TMR;
extern CONST byte gNWK_INDIRECT_MSG_MAX_PER;
extern CONST byte gNWK_INDIRECT_MSG_MAX_ALL;

extern CONST byte gMAX_NEIGHBOR_ENTRIES;

extern CONST byte gMAX_RTG_ENTRIES;
extern CONST byte gMAX_RTG_SRC_ENTRIES;
extern CONST byte gMAX_RREQ_ENTRIES;

// Variables for MAX list size
extern CONST uint16 gNWK_MAX_DEVICE_LIST;

// Variables for MAX Sleeping End Devices
extern CONST uint8 gNWK_MAX_SLEEPING_END_DEVICES;

extern CONST uint8 gNWK_TREE_ALLOCATE_ROUTERADDR_FOR_ENDDEVICE;

extern uint16 *Cskip;
extern byte CskipRtrs[];
extern byte CskipChldrn[];

extern byte gMIN_TREE_LINK_COST;

extern CONST byte defaultKey[];
extern CONST byte defaultTCLinkKey[];

extern CONST byte gMAX_BCAST;


/*********************************************************************
 * APS GLOBAL VARIABLES
 */

// Variables for Binding Table
extern CONST uint16 gNWK_MAX_BINDING_ENTRIES;
extern CONST byte gMAX_BINDING_CLUSTER_IDS;
extern CONST uint16 gBIND_REC_SIZE;

extern CONST uint8 gAPS_MAX_GROUPS;

extern uint8 gAPS_MAX_ENDDEVICE_BROADCAST_ENTRIES;

/*********************************************************************
 * FUNCTIONS
 */

/*
 * Init Global Variables
 */
extern void nwk_globals_init( void );
extern void NIB_init( void );

extern void nwk_Status( uint16 statusCode, uint16 statusValue );

/*********************************************************************
*********************************************************************/
#ifdef __cplusplus
}
#endif

#endif /* NWK_GLOBALS_H */


