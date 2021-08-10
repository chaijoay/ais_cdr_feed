/*
**++
**  FACILITY    : CDR Feed Process
**
**  FILE NAME   : frm_cdr_feed.h
**
**  ABSTRACT    : Include file for frm_cdr_feed.c program for Base HP FMS Ver 9.2-1
**
**  AUTHOR  : Palanichamy.M.
**
**  CREATE DATE : 5-Sep-1997
**
**  CURRENT VERSION NO : 12.1
**
**  LAST RELEASE DATE  : Sep-2016
**
**  MODIFICATION HISTORY :
**  5.1b    14-Nov-2000 Introduced bsearch on Mapping Tables
**  5.1c    08-Dec-2000 Number Port Phase II and IN Port Phase II
**  5.1d    03-Jan-2001 Automatic Re-loading of Mapping Table(s) if found updated
**  5.1e    01-Feb-2001 New Cell Geography implementation for GSM network.
**              Following data feilds remaned: calling_no -> a_no, called_no -> b_no,
**              network_type_origin -> net_orig, network_type_destination -> net_dest and
**              dialled_digit -> b_no
**  5.2 28-Feb-2001 Mobile-Life CDR Mapping.
**  6.0 06-Dec-2000 Addtion of DPC Mapping related functions.  Some modifications etc.
**              Source renamed from cust_cdr_ to frm_cdr_
**  6.0a    08-Jan-2002 Some bug fixes and Run in fms8400 system.
**  6.2c    02-Oct-2002 GPRS Type CDR mapping added, upto CCC file generation only.
**  6.3 23-Dec-2002 MSCPPS Type CDR mapping modules included.
**  6.3a    02-Jan-2003 Changed Build Snapshot concept by Using Open directory.
**  6.3b    13-Jan-2003 Introduced Installation Name in *.INI file to support DPC, 1-2-Call Fraud Migration.
**              While running Installation specific, ignore input records of other Installation.
**  6.4 11-Jun-2003 Generate EXN output file for MSCPPS Type
**  6.4a    13-Jun-2003 Refer changes in frm_cdr_mapp.c
**  6.4b    25-Jun-2003 Refer changes in frm_cdr_mapp.c
**  6.4c    27-Jun-2003 Refer changes in frm_cdr_mapp.c
**  6.5 01-Jul-2003 Migrated to HPUX
**  6.5a    16-Jul-2003 Removed GSM ISAM File
**  6.5b    18-Jul-2003 Added Skip Detection to FIT format.
**  6.5c    21-Jul-2003 Fixed Default value of Cell, Cell Set and Cell Area for GPRS.
**  6.5d    23-Jul-2003 Added Skip Collision for GPRS and USC.
**              Added Mobile Life Feature.
**  6.5e    24-Jul-2003 Removed HR2_TYPE, IR2_TYPE, IR1_TYPE format.
**  6.5f    31-Jul-2003 Seprate CDR Repository is withdrawn. Repository is common now.
**              User defined No. of Respositories. Fit output by round robin method.
**  7.0 28-Oct-2003 Merged HPUX version with New MD CDR Format Version.
**  7.0b    30-Jan-2004 Fixed Error on Convert DPC Duration
**  7.0c    18-Feb-2004 Changed to use MSC CDR instead of SSP CDR for short period only record type 20.
**              Since, SSP CDR have problem not be generated for while.
**  7.0d    04-Mar-2004 Added check for feed only GSM originated call for GPRS CDRs.
**  7.0e    12-Mar-2004 Changed DPC Cell Area as AIS Cell Area.
**
**  8.0a    23-Apr-2004 Introduced one new command argument -count=<NOF_FILE>
**  8.0b    20-May-2004 Added new GPRS Time Based CDR.
**  8.0c    14-Jun-2004 Introduced Number port by Nature (1-2-Call port to GSM) Table.
**  8.0d    16-Jun-2004 Fixed bug on Get Number Port from NPBN Table.
**  8.0e    13-Jul-2004 Introduced SIZE_COMMAND for system command strings.
**  8.0f    24-Aug-2004 Removed NOK, ERS Functions.
**              Introduced TOT International Calls "007xxxxxxxx"
**              Fixed Bug on "Get_DayNightRate" Function.
**  8.0g    07-Sep-2004 Introduced TOT Voice Over IP (VOIP) International Calls "008xxxxxxx"
**  8.0h    02-Nov-2004 Added Network Field on NPBN.DAT file
**  8.0i    05-Nov-2004 Introduced MMS CDR (mtx_type GSMTC and PPSTC)
**  8.0j    18-Nov-2004 Introduced Adjacent Area Detection
**  8.0k    14-Jan-2005 Extend Field size GPRST_RECORD.msisdn to support A_no length > SIZE_PHONENO+1
**              Added Check to reject GPRST Record when A_no length > SIZE_PHONENO+1
**  8.0l    25-Jan-2005 Added Condition Convert A_no for GPRST Record from 6600xyyyyyyyy to 0yyyyyyyy
**  8.0m    04-Feb-2005 Added Condition to Convert B_no Case Voice2U (from B0xxxxxxxx and 0000xxxxxxx to 0xxxxxxxx)
**  8.0n    07-Apr-2005 Changed GSM, SSP, PPSMSC format and split SMS type from GSM Type.
**  8.0o    20-May-2005 Added Condition to Correct the GPRS Volumn for VSCP bcudr CDR when CDR is Volumn Base.
**  8.0p    02-Jun-2005 Introduced CDG CDR (mtx_type GSMCT and PPSCT)
**  8.0q    19-Jul-2005 Introduced Ring Back Tone (RBT) CDR
**  9.0 21-Oct-2005 Migrated to HP FMS V9.2-1
**  9.0a    25-Oct-2005 Fixed problem on Postpaid/Prepaid Create Exn Flag.
**  9.0b    29-Dec-2005 Migrated to HP FMS V9.2-1 for Dpcfraud
**  9.0c    01-Feb-2006 Added Fields into GPRST and MMS records.
**              Added Check for reject Test Record on GPRST and MMS Records (ti = '1').
**  9.1a    16-Jun-2006 Migrated to 10 Digits Phone Number System.
**  9.1b    03-Jul-2006 Added Check for reject Call Background (B_no starts with *955, B955 or 900955).
**  9.1c    03-Nov-2006 Added Condition for convert AIN B_no from 001#11 to 001 (Phase 1).
**  9.1d    15-Nov-2006 Added Condition for convert AIN B_no from #11 to 001 (Phase 1).
**  9.1e    06-Dec-2006 Added Condition for convert AIN B_no from C11 to 001 and 001C11 to 001 (Phase 1).
**  9.1f    04-Jan-2007 Add Rating Calculation for AIN B_no
**  9.1g    07-Feb-2007 Change from Interrim version to AIN-Phase1 version.
**  9.1h    08-Feb-2007 Change condition for lookup rating-element table for SSP Call to AIN Number
**              by Don't match Time_rate_id field.
**  9.1i    20-Feb-2007 Change to Interrim Version since MD rollback to use Interrim version
**              (AIN B_no from C11,#11,001C11,001#11 to 001)
**  9.1j    01-Mar-2007 Change from Interrim version to AIN-Phase1 version
**              (AIN B_no from C11,#11,001C11,001#11 to 005)
**  9.1k    15-Mar-2007 Change to Interrim Version since MD rollback to use Interrim version
**              (AIN B_no from C11,#11,001C11,001#11 to 001)
**  9.2a    29-Jan-2007 Introduced AIN CDR.
**      06-Feb-2007 Add partition_id on voice_event.
**  9.2b    14-Mar-2007 Fixed Convert B-Number from Bxxxx to *xxxx. We found many record that Bno is Bxxx was rejected.
**              Since, have a little Bno that start with B were found on COSTCODE.DAT file
**  9.2c    12-Mar-2007 Add Vas_Name field for USC and CDG Event Type.
**      28-Mar-2007 Cut-Over Version 9.2c
**  9.2d    22-Mar-2007 Add New "VasOrPremium" Category.
**  9.2e    18-Apr-2007 Fixed Calculate Charge for Bxxx,*xxx and 1xxx
**  9.2f    02-May-2007     Remove condition to check case 00760, 007855, 007856, 00795
**  9.2g    02-May-2007 Introduce WLAN CDR.
**  9.2h    15-May-2007     AIS implement Audio Text Services on *xxx,Bxxx,900xxx
**              Set VAS Category to Voice Call to *xxx,Bxxx,900xxx
**  9.2i    17-May-2007 Add Vas_Name field for Voice Event Type. Vas_Name will have value only call to *xxx,Bxxx,900xxx.
**      23-May-2007 Add more 3 Attempts Dimensions
**      24-May-2007 Cut-Over WLAN
**  9.2j    26-Jun-2007 Fixed problem on Verify A-Number with costcode table by added AIS Network.
**      02-Jul-2007 Cut-Over
**  9.2k    04-Jul-2007 Changed Voice Charge Concept by don't use duration for calculate in case that use fix_charge_mny.
**      11-Jul-2007 Cut-Over
**  9.2l    09-Aug-2007 Removed Check AIN_MTXID value.
**  9.2m    15-Aug-2007 Added More field on CDG CDR.
**      31-Aug-2007 Added More field on GPRS Timed Base (BCUDR) and MMS (TCUDR) CDR.
**  9.3a    04-Jun-2007 Changed Voice Source Input from SSP to GSM,DPCGSM format.
**              Since CAMEL upgrate to V5, GSM CDR can check for Postpaid/Prepaid Service.
**      17-Jul-2007 Data Ware House expand 2nd field size and add more fields on All VSCP CDR Types.
**  9.3b    31-Jul-2007 Change Service_Key Concept by add Service_key as Master Key value and FCI can be any value
**  10.0a   10-Oct-2007 Migrated to HP ERM 2.0-1 (FMS V10.0-1)
**  10.0b   07-Nov-2007 Introduce AIS-Network and Other-Network Categories Concept
**              Cut-Over
**  10.0c   04-Dec-2007 Introduce Calculate Charge for Prefix for Long Call (C99xxxxxxxxx)
**  10.0d   04-Dec-2007 Introduce Charge IODC Table (Charge 0 Baht)
**              for support International Operator Direct Connection Number.
**  10.0e   04-Dec-2007 Charged Prefix for Long Call Prefix from C99 to C999
**      16-Jan-2008 Cut-Over
**  10.0f   11-Feb-2008 Change USC PaymentType Concept to Prepaid/Postpaid Flag.
**  10.0g   30-Jan-2008 Introduce NRTRDE CDR.
**      18-Mar-2008 Cut-Over
**  10.0h   20-Mar-2008 1. Disable Prefix for long call. Since project was drop.
**              2. Added SKIP_DUP_EVENT for CDR form VSCP (bcudr,ccudr,ctudr,tcudr).
**              Cut-Over on the same day.
**  10.0i   03-Apr-2008 Introduce 1 Sim 2 Number project. Ano start with 20008xxxxxxx convert to 08xxxxxxx
**      08-Apr-2008 Cut-Over
**  10.0j   17-Apr-2008 Fixed Convert Bno to support TOT Number 021xxxxxx and 0531xxxxx
**      18-Apr-2008 Fixed 1 Sim 2 Number project. Skip 200 Prefix for All Ano and Bno
**      24-Apr-2008 Cut-Over
**  10.0k   11-Jun-2008 Introduce Video Call (service_type = 01 and service_id begin with 37) as Voice Event
**              This effect to add VAS Name Field on Voice Event
**              (Not to use Voice VAS Event because of prevent Auto Bar Subscriber on Voice VAS Threshold)
**      01-Jul-2008 Cut-Over
**  10.0l   21-Jul-2008 Added Condition for Reject A-Number that start with 662 and length >= SIZE_PHONENO+2
**      30-Jul-2008 Cut-Over
**  10.0m   15-Aug-2008 Added Condition for Reject record that IMSI exist in IMSI_VSO Table
**      25-Aug-2008 Cut-Over
**  10.0n   25-Aug-2008 Added Condition for calculate charge on AIN 2nd Product Internation Access Number (0050)
**      28-Aug-2008 Cut-Over
**  10.0o   19-Sep-2008 Added FIX_RATE.DAT table for calculate AIS and Other Net Charge as fix rate per minute
**              Remove USE_MSC_TABLE parameter in INI File. Since CAMEL already finish cut-over.
**      24-Sep-2008 Cut-Over V.10.0o
**  10.0p   24-Sep-2008 Added oper_name Field on FIT Voice Record.
**      29-Sep-2008 Added check for reject CDR older than OLD_CDR_DAY
**      30-Sep-2008 Cut-Over V.10.0p
**  10.0q   24-Oct-2008 Added check for reject VPN Service from Voice Services (Reject Bno begin with 00333)
**              Added check for reject Call Outbound from BCUDR CDR (cgrn_id != 52001)
**              Introduce SMSFDA CDR (Same format as SMS but Come form FDAxxx Switches)
**              Added check for reject Prepaid Call on SMSFDA CDR
**      30-Oct-2008 Cut-Over V.10.0q
**  10.0r   05-Nov-2008 Fixed Calculate Charge for 001,009 to use Geneva logic (Lookup Costcode Table).
**      17-Nov-2008 Cut-Over V.10.0r
**  10.0s   07-Jan-2009 Added Condition check for reject SMC CDR that MD generate duplicate record with FDA CDR
**      12-Jan-2009 Cut-Over V.10.0s
**  10.0t   14-Jan-2009 Added ServicePackId field to GPRS Time base (BCUDR) CDR and GPRS Event
**      28-Jan-2009 Cut-Over V.10.0t
**  10.0u   16-Apr-2009 Added Check for *909,B909,900909 as Premium call
**      21-Apr-2009 Cut-Over V.10.0u
**  10.0v   14-Jul-2009 Removed Check Non-Charge Call for charging_indicator == 2 on SSP,GSM,DPCGSM,SMC,SMS
**      15-Jul-2009 Cut-Over V.10.0v
**  10.0w   08-Sep-2009 Remove Check for reject Call Background (B_no starts with *955, B955 or 900955).
**              and calculate charge as VAS Service (*,B,900 prefix).
**  10.0x   11-Nov-2009     Added Condition for calculate charge on New AIN Internation Access Number (00500)
**  10.0y   17-Nov-2009     Added 2 fields for external alarm output (charge and duration)
**  10.0z   26-Nov-2009     Added Cell Geography for NRTRDE
**  10.1    15-Jan-2010     Support new added field for some cdr format (SMS SMC SMSFDA, USC, MMS TCUDR, BCUDR, CDG, CCUDR) and
**                          Support new rating concept (MSC GSM DPC SSP(NormalCall and SMS), SMS SMC SMSFDA, USC, MMS TCUDR, BCUDR)
**  10.1c   20-Jul-2011     Support Blacklist IMEI
**  10.2    04-Aug-2011     Added new cdr type (AMF) - by Thanakorn
**  10.3    01-Mar-2012     Added new cdr type (SDG) - by Thanakorn
**  11.01   09-Sep-2012     Revise code to support upgrade to fms v11 - by Thanakorn
**  12.10   30-Aug-2016     For ERM-FRM v12.1
**  14.0    05-Feb-2020     For ERM-FRM v14.0
**++
**++
*/

#ifndef _FRM_CDR_FEED_H_
#define _FRM_CDR_FEED_H_

#define SIZE_INIREC         320                 /* size of one ini Record */
/* Resized mtx_id in sync file from 99 to 109 - by Kawee on 28-Mar-2003 */
#define SIZE_SYNCREC        320                 /* size of Sync Record as created by Duplicate Check Program */

#define APP_VERSION         "14.0"
#define APP_PURPOSE         "FRM 14.1-0"
#define APP_NAME            "frm_cdr_feed"
#define INI_EXT             ".ini"
/*
** Structure of CDR Sync Record buffer (native to CDR Feeder).
** Note : All the character array field size includes null size also
*/
typedef struct sync_record {
    /* Resized mtx_id from 10 to 20 Chars - by Kawee on 22-Oct-2003 */
    char mtx_id [20+1];         /* for example AXE92C, CBI1, MTX9D etc */
    char mtx_type [10+1];        /* GSM, SSP, USC, GPS */
    char file_name [100+1];      /* Filename without path */
    char time_stamp [20+1];     /* Time stamp in YYYY-MM-DD HH:MM:SS */
} SYNC_RECORD;

// char gszMtxTypeName[NOF_MTX][8] = {
//     "UNKNOWN", "SSP", "MSCPPS", "GSM", "SMC", "SMS", "USC", "GPR", "GSMBC", "PPSBC", "GSMTC", "PPSTC", "GSMCT", "PPSCT", "RBT", "CCUDR", "SMSFDA",
//     "AWN", "AMF", "DPCGSM", "DPCAIS", "DPCTAC", "DPCGPR", "DPCSMS", "SDG", "AWNSMS", "AWNGPR", "DCB", "OCSVPN", "AIN", "NRTRDE", "NRGGSN", "NRTSCP",
//     "GSMTOP", "IMS", "RDC", "RDCSMS"
// };


/*
** Structure of Check Point File Record
*/
typedef struct check_record {
    char proc_date[SIZE_YYYYMMDD+1];   /* Processing Date YYYYMMDD */
    char proc_time[SIZE_HHMMSS+1];     /* Checkpoint Update Time HHMMSS */
    char cdr_filename[SIZE_FNAME];     /* Current CDR file name under processing (with path) */
    char sync_filename[SIZE_FNAME];    /* Current Sync file name under processing (with path) */
    int  mtx_ind;                       /* Current Mtx Type Indicator */
    long cdr_offset;                    /* Current Offset - processing completed */
    char check_ind;                     /* Check Point Update Indicator */
} CHECK_RECORD;

/*
** Structure of Check Point File Record
*/
typedef struct snap_info {
    char sync_filedir[SIZE_FNAME];     /* Sync file directory to be created snapshot */
    char sync_pattern[SIZE_FNAME];     /* Sync file pattern */
} SNAP_INFO;

/*
** Table of Contents of Functions used in frm_cdr_feed.c
*/
int     Init_Main(const char *avg0);
void    Close_Main();

int     Handle_Signal(char *);
void    CatchAndCont(int);
void    CatchAndExit(int);
void    SnoozeSleep(unsigned int);

int     Load_SysParameters(char *argv[]);
int     Load_Postpaid_SysParam();          /* Added by Kawee on 13-Jan-2003 */
int     Load_Prepaid_SysParam();           /* Added by Kawee on 13-Jan-2003 */
int     Load_Ain_SysParam();               /* Added by Kawee on 29-Jan-2007 */
int     Load_Nrtrde_SysParam();            /* Added by Kawee on 11-Feb-2008 */
int     Load_SpltPPS_SysParam();           /* Added by Thanakorn on 08-Mar-2013 */
int     Get_Parameter(char *, char *);
void    Trim_IniRec(char *);

int     Anz_Check_File();
int     Bld_Snap_File(char *);
int     IsMatchFileType (char *, char *);           /* Added by Kawee on 02-Jan-2003 */

int     Get_Sync_Fname(FILE *, int *, char *);     /* Added by Kawee on 02-Jan-2003 */ /* Changed by Kawee on 12-Feb-2008 */
int     Proc_Snapshot(char *);
int     Proc_SyncFile();
int     Start_Recovery();
int     Proc_CdrFile();
int     Cont_Mapping();

int     Open_Cdr_File(char *);
int     Open_Check_File(char *);
int     Open_Error_File(char *);
int     Open_Reject_File(char *);
int     Open_EventCdr_File(char *);
int     Open_EAlmData_File(char *);
int     Open_SvcIdSub_File(char *);
void    Upd_Check_File(char);
void    Append_Slash(char *);
char    *Remove_Path(char *);
int     Rename_ExtFile(char *, char *, char *);
void    Print_Stat();
void    Deb_Msg(char *);
int     Create_EventSync();
int     Sort_EventOutput(char *file_input);

char    *StrUpr(char *);                                        /* Added by Kawee on 13-Jan-2003 */
int     AddDate(char *, int, const char *, const char *, int);  /* Added by Kawee on 26-Sep-2008 */
void    DoBackupCdr(char *cdrfile, char *synfile);              /* Added by Thanakorn on 15-Mar-2013 */
void    DoBackupCdr4IUM(char *iumfile);                         /* Added by Thanakorn on 18-Mar-2013 */

char    *getTokenItem(const char *str, int fno, char sep, char *out);

#endif /* _FRM_CDR_FEED_H_ */
