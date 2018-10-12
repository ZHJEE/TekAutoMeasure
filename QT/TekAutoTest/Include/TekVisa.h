//Some attributes specific to Tektronix are added here
#include "visa.h"

#define VI_ATTR_VXI_EXPANSION_RESET (0x3FFF00D6UL)
#define VI_ATTR_VXI_EXPANSION_DIAG  (0x3FFF00D7UL)


#define VI_ATTR_DEVICE_CLASS        (0x3FFF4028L)	/* CUSTOMIZED TEK ATTRIBUTE */
#define VI_ATTR_IS_VISASTUB         (0x3FFF4029L)	/* CUSTOMIZED TEK ATTRIBUTE */
#define VI_ATTR_VISASTUB_FILE       (0x3FFF402AL)	/* CUSTOMIZED TEK ATTRIBUTE */
#define VI_ATTR_SERIAL_NUM		    (0x3FFF402BL)	/* CUSTOMIZED TEK ATTRIBUTE */


#define VI_INTF_TEKLINK              (8)

//
// VXI device classes Tektronix supplied

#define VI_DEVICE_CLASS_MEMORY         (0)
#define VI_DEVICE_CLASS_EXTENDED       (1)
#define VI_DEVICE_CLASS_MESSAGE_BASED  (2)
#define VI_DEVICE_CLASS_REGISTER_BASED (3)

