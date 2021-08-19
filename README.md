# CDR Feeder Process

##  Modification History

| app_vers  | date          | Comment
| --------  | -----------   | -------
| 14.0.2    | 26-Nov-2020   | Revised Categories
| 14.0.1    | 27-Oct-2020   | Fix reject CDR(VAS, IDD, Maritime) of other than RBM when, RBM is enabled
| 14.0      | 05-Feb-2020   | For ERM-FRM v14.0
| 12.10     | 30-Aug-2016   | For ERM-FRM v12.1
| 11.02     | 06-Mar-2013   | GPRS type format change from fix length to variable length with pipe delimiter
|           |               | Added PPS-AWN CDR splitting function
|           |               | GSM SMS CDR Type - record length changed
| 11.01     | 09-Sep-2012   | Revise code to support upgrade to fms v11 - by Thanakorn
| 10.3      | 01-Mar-2012   | Added new cdr type (SDG) - by Thanakorn
| 10.2      | 04-Aug-2011   | Added new cdr type (AMF) - by Thanakorn
| 10.1c     | 20-Jul-2011   | Support Blacklist IMEI
| 10.1b     | 19-Feb-2011   | Support DPC GPRS CDR
| 10.1a     | 19-Apr-2010   | Added Condition Convert A_no for VSCP Type from 6600xyyyyyyyy to 0yyyyyyyy
| 10.1      | 15-Jan-2010   | Support new added field for some cdr format (SMS SMC SMSFDA, USC, MMS TCUDR, BCUDR, CDG, CCUDR) and
|           |               | Support new rating concept (MSC GSM DPC SSP(NormalCall and SMS), SMS SMC SMSFDA, USC, MMS TCUDR, BCUDR)
| 10.0z     | 26-Nov-2009   | Added Cell Geography for NRTRDE
| 10.0y     | 17-Nov-2009   | Added 2 fields for external alarm output (charge and duration)
| 10.0x     | 11-Nov-2009   | Added Condition for calculate charge on New AIN Internation Access Number (00500)
| 10.0w     | 08-Sep-2009   | Remove Check for reject Call Background (B_no starts with *955, B955 or 900955).
|           |               | and calculate charge as VAS Service (*,B,900 prefix).
| 10.0v     | 14-Jul-2009   | Removed Check Non-Charge Call for charging_indicator == 2 on SSP,GSM,DPCGSM,SMC,SMS
| 10.0u     | 16-Apr-2009   | Added Check for *909,B909,900909 as Premium call
| 10.0t     | 14-Jan-2009   | Added ServicePackId field to GPRS Time base (BCUDR) CDR and Data Event
| 10.0s     | 07-Jan-2009   | Added Condition check for reject SMC CDR that MD generate duplicate record with FDA CDR
| 10.0r     | 05-Nov-2008   | Fixed Calculate Charge for 001,009 to use Geneva logic (Lookup Costcode Table).
| 10.0q     |24-Oct-2008    | Added check for reject VPN Service from Voice Services (Reject Bno begin with 00333)
|           |               | Added check for reject Call Outbound from BCUDR CDR (cgrn_id != 52001)
|           |               | Introduced SMSFDA CDR (Same format as SMS but Come form FDAxxx Switches)
|           |               | Added check for reject Prepaid Call on SMSFDA CDR
| 10.0p     | 24-Sep-2008   | Added oper_name Field on FIT Voice Record.
|           |               | Added check for reject CDR older than OLD_CDR_DAY
| 10.0o     | 19-Sep-2008   | Added FIX_RATE.DAT table for calculate AIS and Other Net Charge as fix rate per minute
|           |               | Remove USE_MSC_TABLE parameter in INI File. Since CAMEL already finish cut-over.
| 10.0n     | 25-Aug-2008   | Added Condition for calculate charge on AIN 2nd Product Internation Access Number (0050)
| 10.0m     | 15-Aug-2008   | Added Condition for Reject record that IMSI exist in IMSI_VSO Table
| 10.0l     | 21-Jul-2008   | Added Condition for Reject A-Number that start with 662 and length >= SIZE_PHONENO+2
| 10.0k     | 11-Jun-2008   | Introduced Video Call (service_type = 01 and service_id begin with 37) as Voice Event
|           |               | This effect to add VAS Name Field on Voice Event
|           |               | (Not to use Voice VAS Event because of prevent Auto Bar Subscriber on Voice VAS Threshold)
| 10.0j     | 17-Apr-2008   | Fixed Convert Bno to support TOT Number 021xxxxxx and 0531xxxxx
|           |               | Fixed 1 Sim 2 Number project. Skip 200 Prefix for All Ano and Bno
| 10.0i     | 03-Apr-2008   | Introduced 1 Sim 2 Number project. Ano start with 20008xxxxxxx convert to 08xxxxxxx
| 10.0h     | 20-Mar-2008   | 1. Disable Prefix for long call. Since project was drop.
|           |               | 2. Added SKIP_DUPEVENT for CDR form VSCP (bcudr,ccudr,ctudr,tcudr).
| 10.0g     | 30-Jan-2008   | Introduced NRTRDE CDR.
| 10.0f     | 11-Feb-2008   | Change USC PaymentType Concept to Prepaid/Postpaid Flag.
| 10.0e     | 04-Dec-2007   | Charged Prefix for Long Call Prefix from C99 to C999
| 10.0d     | 04-Dec-2007   | Introduced Charge IODC Table (Charge 0 Baht)
|           |               | for support International Operator Direct Connection Number.
| 10.0c     | 04-Dec-2007   | Introduced Calculate Charge for Prefix for Long Call (C99xxxxxxxxx)
| 10.0b     | 07-Nov-2007   | Introduced AIS-Network and Other-Network Categories Concept
| 10.0a     | 10-Oct-2007   | Migrated to HP ERM 2.0-1 (FMS V10.0-1)
| 9.3b      | 31-Jul-2007   | Change Service_Key Concept by add Service_key as Master Key value and FCI can be any value
| 9.3a      | 04-Jun-2007   | Changed Voice Source Input from SSP to GSM,DPCGSM format.
|           |               | Since CAMEL upgrate to V5, GSM CDR can check for Postpaid/Prepaid Service.
|           |               | Data Ware House expand 2nd field size and add more fields on All VSCP CDR Types.
| 9.2n      | 17-Sep-2007   | Added AIN E1 Mapping Table.
| 9.2m      | 15-Aug-2007   | Added More field on CDG CDR.
|           |               | Added More field on GPRS Timed Base (BCUDR) and MMS (TCUDR) CDR.
| 9.2l      | 09-Aug-2007   | Removed Check AIN_MTXID value.
| 9.2k      | 04-Jul-2007   | Changed Voice Charge Concept by do not use duration for calculate in case that use fix_charge_mny.
| 9.2j      | 26-Jun-2007   | Fixed problem on Verify A-Number with costcode table by added AIS Network.
| 9.2i      | 17-May-2007   | Add Vas_Name field for Voice Event Type. Vas_Name will have value only call to *xxx,Bxxx,900xxx.
|           | 23-May-2007   | Add more 3 Attempts Dimensions
| 9.2h      | 15-May-2007   | AIS implement Audio Text Services on *xxx,Bxxx,900xxx
|           |               | Set VAS Category to Voice Call to *xxx,Bxxx,900xxx
| 9.2g      | 02-May-2007   | Introduced WLAN CDR.
| 9.2f      | 02-May-2007   | Remove condition to check case 00760, 007855, 007856, 00795
| 9.2e      | 18-Apr-2007   | Fixed Calculate Charge for Bxxx,*xxx and 1xxx
| 9.2d      | 22-Mar-2007   | Add New "VasOrPremium" Category.
| 9.2c      | 12-Mar-2007   | Add Vas_Name field for USC and CDG Event Type.
| 9.2b      | 14-Mar-2007   | Fixed Convert B-Number from Bxxxx to *xxxx. We found many record that Bno is Bxxx was rejected.
|           |               | Since, have a little Bno that start with B were found on COSTCODE.DAT file
| 9.2a      | 29-Jan-2007   | Introduced AIN CDR.
|           | 06-Feb-2007   | Add partition_id on voice_event.
| 9.1k      | 15-Mar-2007   | Change to Interrim Version since MD rollback to use Interrim version
|           |               | (AIN B_no from C11,#11,001C11,001#11 to 001)
| 9.1j      | 01-Mar-2007   | Change from Interrim version to AIN-Phase1 version
|           |               | (AIN B_no from C11,#11,001C11,001#11 to 005)
| 9.1i      | 20-Feb-2007   | Change to Interrim Version since MD rollback to use Interrim version
|           |               | (AIN B_no from C11,#11,001C11,001#11 to 001)
| 9.1h      | 08-Feb-2007   | Change condition for lookup rating-element table for SSP Call to AIN Number
|           |               | by do not match Time_rate_id field.
| 9.1g      | 07-Feb-2007   | Change from Interrim version to AIN-Phase1 version.
| 9.1f      | 04-Jan-2007   | Add Rating Calculation for AIN B_no
| 9.1e      | 06-Dec-2006   | Added Condition for convert AIN B_no from C11 to 001 and 001C11 to 001 (Phase 1).
| 9.1d      | 15-Nov-2006   | Added Condition for convert AIN B_no from #11 to 001 (Phase 1).
| 9.1c      | 03-Nov-2006   | Added Condition for convert AIN B_no from 001#11 to 001 (Interim Version).
| 9.1b      | 03-Jul-2006   | Added Check for reject Call Background (B_no starts with *955, B955 or 900955).
| 9.1a      | 16-Jun-2006   | Migrated to 10 Digits Phone Number System.
| 9.0c      | 01-Feb-2006   | Added Fields into GPRST and MMS records.
|           |               | Added Check for reject Test Record on GPRST and MMS Records (ti = '1').
| 9.0b      | 29-Dec-2005   | Migrated to HP FMS V9.2-1 for Dpcfraud
| 9.0a      | 25-Oct-2005   | Fixed problem on Postpaid/Prepaid Create Exn Flag.
| 9.0       | 21-Oct-2005   | Migrated to HP FMS V9.2-1
| 8.0q      | 19-Jul-2005   | Introduced Ring Back Tone (RBT) CDR
| 8.0p      | 02-Jun-2005   | Introduced CDG CDR (mtx_type GSMCT and PPSCT)
| 8.0o      | 20-May-2005   | Added Condition to Correct the GPRS Volumn for VSCP bcudr CDR when CDR is Volumn Base.
| 8.0n      | 07-Apr-2005   | Changed GSM, SSP, PPSMSC format and split SMS type from GSM Type.
| 8.0m      | 04-Feb-2005   | Added Condition to Convert B_no Case Voice2U (from B0xxxxxxxx and 0000xxxxxxx to 0xxxxxxxx)
| 8.0l      | 25-Jan-2005   | Added Condition Convert A_no for GPRST Record from 6600xyyyyyyyy to 0yyyyyyyy
| 8.0k      | 14-Jan-2005   | Extend Field size GPRST_RECORD.msisdn to support A_no length > SIZE_PHONENO
|           |               | Added Check to reject GPRST Record when A_no length > SIZE_PHONENO
| 8.0j      | 18-Nov-2004   | Introduced Adjacent Area Detection
| 8.0i      | 05-Nov-2004   | Introduced MMS CDR (mtx_type GSMTC and PPSTC)
| 8.0h      | 02-Nov-2004   | Added Network Field on NPBN.DAT file
| 8.0g      | 07-Sep-2004   | Introduced TOT Voice Over IP (VOIP) International Calls "008xxxxxxx"
| 8.0f      | 24-Aug-2004   | Removed NOK, ERS Functions.
|           |               | Introduced TOT International Calls "007xxxxxxxx"
|           |               | Fixed Bug on "Get_DayNightRate" Function.
| 8.0e      | 13-Jul-2004   | Introduced SIZE_COMMAND for system command strings.
| 8.0d      | 16-Jun-2004   | Fixed bug on Get Number Port from NPBN Table.
| 8.0c      | 14-Jun-2004   | Introduced Number port by Nature (1-2-Call port to GSM) Table.
| 8.0b      | 20-May-2004   | Added new GPRS Time Based CDR.
| 8.0a      | 23-Apr-2004   | Introduced one new command argument -count=<NOF_FILE>
| 8.0       | 19-Mar-2004   | Introduced two new parameters, CREATE_AIS_EXN & CREATE_DPC_EXN in *.INI file.
|           |               | Removed some unwanted codes from the source, due to the above fixes.
| 7.0e      | 12-Mar-2004   | Changed DPC Cell Area as AIS Cell Area.
| 7.0d      | 04-Mar-2004   | Added check for feed only GSM originated call for GPRS CDRs.
| 7.0c      | 18-Feb-2004   | Changed to use MSC CDR instead of SSP CDR for short period only record type 20.
|           |               | Since, SSP CDR have problem not be generated for while.
| 7.0b      | 30-Jan-2004   | Fixed Error on Convert DPC Duration
| 7.0a      | 29-Oct-2003   | Changed Parse Area Code Logic and Change Map_Ssp_Bno To support skip area code on TOT Premium call.
| 7.0       | 28-Oct-2003   | Merged HPUX version with New MD CDR Format Version.
| 6.5f      | 31-Jul-2003   | Seprate CDR Repository is withdrawn. Repository is common now.
|           |               | User defined No. of Respositories. Fit output by round robin method.
| 6.5e      | 24-Jul-2003   | Removed HR2_TYPE, IR2_TYPE, IR1_TYPE format.
| 6.5d      | 23-Jul-2003   | Added Skip Collision for GPRS and USC. Added Mobile Life Feature.
| 6.5c      | 21-Jul-2003   | Fixed Default value of Cell, Cell Set and Cell Area for GPRS.
| 6.5b      | 18-Jul-2003   | Added Skip Detection to FIT format.
| 6.5a      | 16-Jul-2003   | Removed GSM ISAM File.
| 6.5       | 01-Jul-2003   | Migrated to HP FMS V8.1-1
|           |               | Changed Fit Format.
|           |               | Changed Gprs Function to Mapping Fit format.
| 6.4c      | 27-Jun-2003   | Changed DPC National Charge Calculation as AIS logic.
|           |               | Fixed Condition Check in B_no Mapping functions.
| 6.4b      | 25-Jun-2003   | Added MSCPPS record type 40.
| 6.4a      | 13-Jun-2003   | Fixed New Prefix Number of Mobile Phone Problem as the following:
|           |               | Changed A_no Mapping Functions to support New Prefix Number of Mobile Phone.
|           |               | Changed B_no Mapping Functions to support New Prefix Number of Mobile Phone.
|           |               | Changed Condition Checking before Parsing Area Code.
|           |               | Changed SIZE_OLDPHONENO to SIZE_PHONENO concept.
| 6.4       | 11-Jun-2003   | Generate EXN output file for MSCPPS Type
| 6.3c      | 17-Jan-2003   | Added Prepaid VMB No (900129, *129, B129).
|                           | Changed AIS Rating to Multiple Tariff Type Rating.
|                           | ending to release Multiple Tariff Type Rating.
|                           | The Multiple Tariff Type Rating will be release, if define TARIFF3
| 6.3b      | 13-Jan-2003   | Introduced Installation Name in *.INI file to support DPC, 1-2-Call Fraud Migration.
|           |               | While running Installation specific, ignore input records of other Installation.
| 6.3a      | 24-Dec-2002   | Change USC format and Add one message_size field.
| 6.3       | 23-Dec-2002   | MSCPPS Type CDR mapping modules included.
| 6.2f      | 30-Oct-2002   | External Alarm output file format changed.
|           |               | Add Checking condition of b_no can start with '1', '9' or '6' for GSM and PPS.
|           |               | Record Type 99 in GSM, Call to 911 check removed.
|           |               | Record Type 98 in GSM, Call to 911 check included.
| 6.2e      | 24-Oct-2002   | Cell Area identification fixed in New CGI.
| 6.2d      | 10-Oct-2002   | New CGI format implemented.  Direct Integration of AIS-DPC network.
| 6.2c      | 02-Oct-2002   | GPRS Type CDR mapping added, upto CCC file generation only.
| 6.2b      | 10-Sep-2002   | Record Type 25,45 in GSM, Call to PPS and MSRN 000001A05 check included.
| 6.2a      | 04-Sep-2002   | Record Type 25,45 in GSM, Call to PPS and MSRN 000006605 check included.
| 6.2       | 13-Jun-2002   | "06" mobile access code implementation, some code fix for PPS etc.
| 6.1h      | 28-May-2002   | 1900 Premium services for DPC added.
| 6.1g      | 25-Apr-2002   | Added Temp Phone Table for mapping AIS GSM Record Type 65.
| 6.1f      | 12-Apr-2002   | Add VAS number 90088800, B88800, *88800 because number of zero digit after 888 can be 2 or 3.
| 6.1e      | 10-Apr-2002   | For Ais Add one VAS number B855.
| 6.1d      | 04-Apr-2002   | Change USC format and Add one SMS number 911.
| 6.1c      | 03-Apr-2002   | MSRN 0000000669 series check added for AIS CDRs.
| 6.1b      | 11-Mar-2002   | For AIS Add two new features 126, 127.  For DPCGSM Add one new feature 9997
|           |               | DPCGSM duration format change to Second format.
| 6.1a      | 06-Mar-2002   | Is_VasNumber() check done for ERS and NOK type to avoid calls to 1113 gets rejected.
| 6.1       | 25-Feb-2002   | DPCAIS CDR format changed.  CDRs from NR server is being used now.
| 6.0f      |02-Feb-2002    | IDD in '66001xx' or '66009' or '66007' format fix for DPCAIS format.
|           |               | Convertion of 001856, 00160 to 007856, 00760 resp. is withdrawn for AIS and DPC
|           |               | Call Forward (Record Type 40) to Voice Mail is not charged in DPC.
| 6.0e      | 28-Jan-2002   | DPC Record Type 40 use Home Register location for Cell_ida.
| 6.0d      | 25-Jan-2002   | DPC voice Mail Number indentification addition.  DPC CF fix.
| 6.0c      |23-Jan-2002    | LDD calls identification and mapping, rating, feature settings.
| 6.0a      | 08-Jan-2002   | Some bug fixes and Run in fms8400 system.
|                           | SMS Txn based Charging.
|                           | Non-Charge Calls identified and Rejected from GSM, ERS, PPS and DPCGSM Cdrs.
| 6.0       | 06-Dec-2001   | Addtion of DPC Mapping related functions.  Some modifications etc.
|           |               | Source renamed from cust_cdr_ to frm_cdr_
| 5.3       | 10-Oct-2001   | Some Corrections, E-Phone features added, deleted unwanted codes, FRM feature setting.
| 5.2a      | 24-Sep-2001   | SMS Rating Method changed, Set_VasFeature() added, some corrections, FRM feature setting.
| 5.2       | 28-Feb-2001   | Mobile-Life CDR Mapping.
| 5.1e      | 01-Feb-2001   | New Cell Geography implementation for GSM network.
|           |               | Following data feilds remaned: calling_no -> a_no, called_no -> b_no,
|           |               | network_type_origin -> net_orig, network_type_destination -> net_dest and
|           |               | dialled_digit -> b_no
| 5.1d      | 03-Jan-2001   | Automatic Re-loading of Mapping Table(s) if found updated
| 5.1c      | 08-Dec-2000   | Number Port Phase II and IN Port Phase II
| 5.1b      | 14-Nov-2000   | Introduced bsearch on Mapping Tables
