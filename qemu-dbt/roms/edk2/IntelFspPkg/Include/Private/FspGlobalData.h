/** @file

  Copyright (c) 2014 - 2015, Intel Corporation. All rights reserved.<BR>
  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#ifndef _FSP_GLOBAL_DATA_H_
#define _FSP_GLOBAL_DATA_H_

#include <FspInfoHeader.h>

#pragma pack(1)

typedef struct  {
   VOID               *DataPtr;
   UINT32             MicrocodeRegionBase;
   UINT32             MicrocodeRegionSize;
   UINT32             CodeRegionBase;
   UINT32             CodeRegionSize;
} FSP_PLAT_DATA;

#define FSP_GLOBAL_DATA_SIGNATURE  SIGNATURE_32 ('F', 'S', 'P', 'D')

typedef struct  {
   UINT32             Signature;
   UINT32             CoreStack;
   FSP_PLAT_DATA      PlatformData;
   FSP_INFO_HEADER    *FspInfoHeader;
   VOID               *UpdDataRgnPtr;
   VOID               *MemoryInitUpdPtr;
   VOID               *SiliconInitUpdPtr;
   UINT8              ApiMode;
   UINT8              Reserved[3];
   UINT32             PerfIdx;
   UINT64             PerfData[32];
} FSP_GLOBAL_DATA;

#pragma pack()

#endif