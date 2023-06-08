*************************************************************************
   ____  ____ 
  /   /\/   / 
 /___/  \  /   
 \   \   \/    © Copyright 2012–2020 Xilinx, Inc. All rights reserved.
  \   \        This file contains confidential and proprietary 
  /   /        information of Xilinx, Inc. and is protected under U.S. 
 /___/   /\    and international copyright and other intellectual 
 \   \  /  \   property laws. 
  \___\/\___\ 
 
*************************************************************************

Vendor: Xilinx 
Reference Design Version: 1.10
readme.txt Version: 1.10
Date Last Modified:  3/30/2020
Date Created: 10/4/2012
Associated Filename: xmp277-7series-schematic-review-recommendations.zip

Supported Device(s): Artix-7, Kintex-7, Virtex-7, Zynq-7000, Spartan-7
Purpose: This ZIP file contains the spreadsheet for schematic review
Document Reference: XMP277
   
*************************************************************************

Disclaimer: 

      This disclaimer is not a license and does not grant any rights to 
      the materials distributed herewith. Except as otherwise provided in 
      a valid license issued to you by Xilinx, and to the maximum extent 
      permitted by applicable law: (1) THESE MATERIALS ARE MADE AVAILABLE 
      "AS IS" AND WITH ALL FAULTS, AND XILINX HEREBY DISCLAIMS ALL 
      WARRANTIES AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, 
      INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, 
      NON-INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE; and 
      (2) Xilinx shall not be liable (whether in contract or tort, 
      including negligence, or under any other theory of liability) for 
      any loss or damage of any kind or nature related to, arising under 
      or in connection with these materials, including for any direct, or 
      any indirect, special, incidental, or consequential loss or damage 
      (including loss of data, profits, goodwill, or any type of loss or 
      damage suffered as a result of any action brought by a third party) 
      even if such damage or loss was reasonably foreseeable or Xilinx 
      had been advised of the possibility of the same.

Critical Applications:

      Xilinx products are not designed or intended to be fail-safe, or 
      for use in any application requiring fail-safe performance, such as 
      life-support or safety devices or systems, Class III medical 
      devices, nuclear facilities, applications related to the deployment 
      of airbags, or any other applications that could lead to death, 
      personal injury, or severe property or environmental damage 
      (individually and collectively, "Critical Applications"). Customer 
      assumes the sole risk and liability of any use of Xilinx products 
      in Critical Applications, subject only to applicable laws and 
      regulations governing limitations on product liability.

THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS PART OF THIS 
FILE AT ALL TIMES.

*************************************************************************

This readme file contains the following sections:

1. Revision History
2. Operating Instructions

*************************************************************************
1. Revision History 
*************************************************************************
Date		Version	Revision

10/04/12	1.0	Initial Draft.

11/14/12	1.1	Added ability to add or remove checklist sheets.
			Added XC7VX690T-FFG1158 support.
			Changed connection recommendation for unused MGT receive pins.
			Removed XC7V1500T and XC7A350T.
			Added to MRCC and SRCC recommendations.
			Added to VRN and VRP recommendations.
			Added 7VX1140T-FLG1926 support.
			Added 7A200T-SBG484 support.
			Updated recommendations for MGT pins to show document titles.
			Change capacitor recommendations for MGT pins.

04/24/12	1.2	Added support for 7Z030, 7Z045, and 7Z100 devices
			Corrected error in ETHERNET0/ETHERNET1 MIO interface
			Changed recommendation for PS_DDR_CKE termination
			Changed recommendation for PS_MIO_VREF
			Changed MGTAVCC_N/S to MGTAVCC_G(N)
			Updated decoupling capacitor recommendation to match user guide
			Added NAND 8BIT MIO interface
			Added pins to QSPI MIO interfaces
			Updated color scheme
			Added recommendations for MIO interface pins
			Updated recommendations for all MIO interface pins (changed 50 ps to 9 ps)
			Changed recommendation for VCCPLL
			Moved recommendations for PS_DDR pins to the PS_DDR section
			Changed VCCBATT maximum voltage to 1.89 V
			Updated Zynq-7000 decoupling capacitor recommendations for VCCo
			Changed configuration mode for Zynq-7000
			Updated PS_MIO_VREF recommendations
			Updated Ethernet MIO interface pin recommendations

10/28/13	1.3	Added support for 7VH580T and 7VH870T devices
			Added support for CLG485 package for 7Z015 device
			Added support for SBG485 package for 7Z030 device
			Added decoupling capacitor values for SBG484 package for 7A200T device
			Added to power supply ramp time
			Fixed reversal of IIC clock and data MIO pin numbers
			Added section for MGTZ recommendations
			Added function to hide sections that are not used by selected family/device/package
			Added support for 7A35T, 7A50T, and 7A75T devices
			Updated recommendation for Zynq DDR Termination
			Added support for CLG225 package for 7Z010 device
			Updated CFGBVS recommendations as per AR # 57045
			Replaced all instances of "Transciever" with "Transceiver"
			Updated skew requirements for IIC, SDIO and QSPI interfaces for Zynq

03/07/2014	1.4	Fixed issue with selecting 7VH580T-HCG1931
			Changed VCCO_14 to VCCO_34 in PUDC_B recommendation for Zynq-7000
			Fixed typo in PS_SRST_BPS recommendation
			Set rows previously showing "Does not apply to selected family" for Zynq to hidden
			Added pointer to user guide for Zynq power supply section
			Added pointer to user guide for Bank 14 VCCO recommendation
			Updated DDR Termination recommendations
			Updated DDR Topology recommendations
			Updated Zynq-7000 decoupling capacitor recommendations
			Added support for the CSG236 and CSG325 package for 7A35T and 7A50T
			Changed reference to VCCO_14 in PUDC to VCCO_34 for Zynq-7000
			Added to additional info for EMCCLK
			Updated VCCO decoupling recommendations
			Updated Zynq-7000 power supply decoupling recommendations
			Updated reference in M[2:0] additional information section
			Updated additional information and voltage implementation selections for VCCO_0

03/25/2014	1.4.1	Corrected typographical error in Project Info sheet.

04/10/2014	1.4.2	Corrected error in formula for FTG256 package power supply decoupling recommendations

03/26/2015	1.5	Added support for 7A15T and 7Z035 Devices
			Changed pullup resistor value for PJTAG MIO interface
			Updated delay requirement recommendations for Ethernet CCLK MIO pins
			Added exception for Virtex-7 VCCO_0 voltage recommendation
			Updated decoupling capacitor recommendation to match user guide
			Updated additional information for INIT_B for Zynq-7000 parts
			Removed MGTVCCAUX, MGTAVTTRCAL, VCCAUX_IO, VRP, VRN, and DCI Cascading recommendations for non-applicable Zynq-7000 and Artix-7 parts
			Removed VCCBRAM for 7Z010-CLG225
			Updated the I/O Standard Compatibility and SSO Analysis recommendations
			Added a note to CAN and USB MIO interfaces about RX/TX positions differing between CAN0/USB0 and CAN1/USB1
			Loosened delay matching recommendations for UART MIO interface pins
			Corrected typographical error in TMS recommendations
			Added decoupling recommendation to VCCADC and VREFP_0
			Added references to answer records for DONE
			Moved recommendations for DXP_0/DXN_0 from the additional information column to the recommendations column
			Removed T and T_DQS from the item list
			Added additional information to MIG
			Removed reference to BPI Flash in INIT_B recommendations for Zynq
			Updated additional information for Zynq BOOT_MODE pins
			Updated additional information for Zynq Independent JTAG field
			Updated user guide reference for LPDDR2 ZQ pin and moved it to additional information field
			Moved user guide reference for DDR Termination to additional information field
			Moved user guide reference for DDR_CK to additional information field
			Changed LPDDR2 ZQ to DDR ZQ and updated the recommendations
			Updated the recommendations and additional information for PS_DDR_VRP and PS_DDR_VRN
			Updated VCCINT additional information
			Updated VCCBRAM additional information
			Replaced all instances of iMPACT with iMPACT/Vivado
			Added a pointer to UG908 for configuration
			Added a reference to Design Advisory # 63149 for PS_POR_BPS
			Updated Zynq LPDDR2 recommendation

05/05/2016	1.6	Added a pointer to I/O transition/DCI restrictions sections in UG471
			Added references to answer records for DONE
			Added note to Zynq BOOT_MODE pins to use jumpers/switches for debug
			Fixed issue where an error message shows after selecting QSPI PSMIO interfaces
			Added a note to DONE recommendations
			Updated recommendations for PS_POR_B
			Updated recommendations for PS_SRST_B
			Changed CS236 package name to CP236
			Removed lead-free (G) designator for package codes and added note for package selection field
			Added input restriction to vmode recommendations
			Removed 33.333 MHz recommendation for PS_CLK
			Updated link to UG908
			Updated links to Zynq-7000 documentation
			Changed instances of BitGen to bitstream
			Added reference to UG471 for VCCAUX_IO_G#
			Added a check for PUDC_B connection for Zynq-7000

07/25/2017	1.7	Updated PS_POR_B recommendations
			Updated recommendations for unconnected MGT receivers
			Removed Tpor from bitstream programming time calculation
			Added support for 7A12T and 7A25T devices
			Added support for 7Z007S, 7Z012S and 7Z014S devices
			Added support for Spartan-7 devices
08/24/2017	1.7.1	Corrected decoupling capacitor values for 7S50 in CSGA324 and FTGB196 packages

01/19/2018	1.8	Updated recommendations for USB MIO Interface to match UG933
			Updated recommendations forSPI MIO Interface to match UG583
			Fixed broken link to UG908

10/24/2018      1.9     Separated QSPI_FEEDBACK_CLK from QSPI_CS
			Fixed error when selecting USB0 or USB1 MIO interfaces
			Corrected decoupling capacitor values for 7Z035 devices

03/30/2020      1.10    Added RSVDGND pin for 7A12T device
			Corrected the description for Note: PUDC_B in the PS Configuration section
			Added PS boot mode configurations options
			Clarified additional information for DCI Cascade only applies to ISE users


*************************************************************************
2. Operating Instructions 
*************************************************************************

!	Macros must be enabled for full functionality.
1.	This spreadsheet is intended to provide a list of what has been checked (and what has not been checked) during a customer schematic review. It is not intended to be a comprehensive checklist.
	
2.	The Project Info page gives an overview of the schematic that is being reviewed, and the person(s) performing the review. It also contains the Purpose and Disclaimer paragraphs.
	
3.	The Checklist pages contain some of the more common items that should be checked. In some cases, these items might not apply to a specific schematic review, and can be deleted. In other cases, there might be additional items that need to be checked. In that case, the user can add a line to the end of the worksheet.
	
4.	In several cells, there are Xilinx recommendations containing question marks (e.g., ? of ?? mf cap ). The question marks are intended to remind the user to replace the '?' with the appropriate value. In this example, the number of caps and the value of those caps need to be recorded.
	
5.	The Checklist pages are intended to collect information for a single FPGA and its supporting device (such as a configuration PROM). At the top of the Checklist page, the device part number and reference designator need to be recorded. If there are multiple devices, a workbook should be created for each device.
	
6.	"Each cell in the Status column has a pull-down menu with the color-coded selections OK, CHECK, and PROBLEM. The Status column allows the customer to quickly see the results of the schematic review.
· OK: The item receives reviewer approval.
· CHECK: The reviewer does not have sufficient information to determine if the item is OK or poses a PROBLEM. The designer must research the item and provide additional information.
· PROBLEM: There is an issue with the item. PROBLEM flags the item for the designer, who needs to research the issue and find a solution.
· Not Checked: The item has not been checked and might require additional attention.
· N/A: The item is not applicable to this device or design."
	
7.	The Actual Implementation column can be used to provide additional clarification. This information is especially important if the item is tagged with CHECK or PROBLEM.
