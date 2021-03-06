/**\file
 *	CLT database variables for J1939 and J1587 serial networks 
 *
 * Copyright (c) 2005  Regents of the University of California
 *
 *	As a convention, the variable name/type space is partitioned as
 *	follows:
 *
 *	0	to	99		Used by the system.
 *	100	to	199		Reserved.
 *	200	to	299		Permanent longitudinal variables.
 *	300	to	399		Permanent lateral variables.
 *	400	to	499		Permanent communications variables.
 *	500	to	599		J1939 and J1587 standard variables 
 *	600	to 	699		Lane Assist Interfacevariables
 *	1000 to	1099	Temporary variables.
 */

// J1939 standard variables

#define DB_J1939_PDU_TYPE	500	 ///j1939_pdu_typ 
#define DB_J1939_ERC1_TYPE	501	 ///j1939_erc1_typ 
#define DB_J1939_EBC1_TYPE	502	 ///j1939_ebc1_typ 
#define DB_J1939_ETC1_TYPE	503	 ///j1939_etc1_typ 
#define DB_J1939_EEC1_TYPE	504	 ///j1939_eec1_typ 
#define DB_J1939_EEC2_TYPE	505	 ///j1939_eec2_typ 
#define DB_J1939_ETC2_TYPE	506	 ///j1939_etc2_typ 
#define DB_J1939_TURBO_TYPE	507	 ///j1939_turbo_typ 
#define DB_J1939_EEC3_TYPE	508	 ///j1939_eec3_typ 
#define DB_J1939_VD_TYPE	509	 ///j1939_vd_typ 
#define DB_J1939_ETEMP_TYPE	510	 ///j1939_etemp_typ 
#define DB_J1939_PTO_TYPE	511	 ///j1939_pto_typ 
#define DB_J1939_CCVS_TYPE	512	 ///j1939_ccvs_typ 
#define DB_J1939_LFE_TYPE	513	 ///j1939_lfe_typ 
#define DB_J1939_AMBC_TYPE	514	 ///j1939_ambc_typ 
#define DB_J1939_IEC_TYPE	515	 ///j1939_iec_typ 
#define DB_J1939_VEP_TYPE	516	 ///j1939_vep_typ 
#define DB_J1939_TF_TYPE	517	 ///j1939_tf_typ 
#define DB_J1939_RF_TYPE	518	 ///j1939_rf_typ 
#define DB_J1939_HRVD_TYPE	519	 ///j1939_hrvd_typ 
#define DB_J1939_EBC2_TYPE	520	 ///j1939_ebc2_typ 
#define DB_J1939_RCFG_TYPE	521	 ///j1939_rcfg_typ 
#define DB_J1939_ECFG_TYPE	522	 ///j1939_ecfg_typ 
#define DB_J1939_TSC1_TYPE	523	 ///j1939_tsc1_typ 
#define DB_J1939_ERC1_TRANS_TYPE	524	 ///j1939_erc1_typ 
#define DB_J1939_RCFG_TRANS_TYPE	525	 ///j1939_rcfg_typ 
#define DB_J1939_TSC1_RTDR_TYPE		526	 ///j1939_tsc1_typ 
#define DB_J1939_FD_TYPE		527	///j1939_fd_typ 
#define DB_J1939_EXAC_TYPE		528	///j1939_exac_typ 
#define DB_J1939_EBC_ACC_TYPE		529	///j1939_ebc_acc_typ 
#define DB_J1939_GFI2_TYPE		530	///j1939_gfi2_typ 
#define DB_J1939_EI_TYPE		531	///j1939_ei_typ 
#define DB_J1939_TSC1_E_A_TYPE		532	///j1939_tsc1_typ 
#define DB_J1939_TSC1_TRTDR_TYPE	533	///j1939_tsc1_typ 
#define DB_J1939_VP_X_TYPE		534	///j1939_vp_x_typ
#define DB_J1939_VDC2_TYPE		535	///j1939_vdc2_typ
#define DB_J1939_MVS_X_E_TYPE		536	///j1939_x_etyp
#define DB_J1939_EBC5_TYPE		537	///j1939_ebc5_typ
#define DB_J1939_TSC1_E_ACC_TYPE	538	///j1939_tsc1_typ
#define DB_J1939_TSC1_ER_ACC_TYPE	539	///j1939_tsc1_typ
#define DB_J1939_TSC1_E_T_TYPE		540	///j1939_tsc1_typ
#define DB_J1939_TSC1_E_V_TYPE		541	///j1939_tsc1_typ
#define DB_J1939_TSC1_ER_A_TYPE		542	///j1939_tsc1_typ
#define DB_J1939_TSC1_ER_T_TYPE		543	///j1939_tsc1_typ
#define DB_J1939_TSC1_ER_V_TYPE		544	///j1939_tsc1_typ
#define DB_J1939_VOLVO_TARGET_TYPE	545	///j1939_volvo_target_typ
#define DB_J1939_VOLVO_EGO_TYPE		546	///j1939_volvo_ego_typ
#define DB_J1939_VOLVO_XBR_WARN_TYPE	547	///j1939_volvo_xbr_warn_typ
#define DB_J1939_VOLVO_XBR_TYPE		548	///j1939_volvo_xbr_typ
#define DB_J1939_ETC2_E_TYPE		549	 ///j1939_etc2_e_typ 
#define DB_J1939_VOLVO_BRK_TYPE		550	 ///j1939_volvo_brk_t
#define DB_J1939_VOLVO_VP15_TYPE	551	 ///j1939_volvo_vp15_t


#define MIN_J1939_DBNUM	500
#define MAX_J1939_DBNUM 559


// Only one instance of each database type allowed, so VAR same as TYPE
#define DB_J1939_PDU_VAR	DB_J1939_PDU_TYPE
#define DB_J1939_ERC1_VAR	DB_J1939_ERC1_TYPE
#define DB_J1939_EBC1_VAR	DB_J1939_EBC1_TYPE
#define DB_J1939_ETC1_VAR	DB_J1939_ETC1_TYPE
#define DB_J1939_EEC1_VAR	DB_J1939_EEC1_TYPE
#define DB_J1939_EEC2_VAR	DB_J1939_EEC2_TYPE
#define DB_J1939_ETC2_VAR	DB_J1939_ETC2_TYPE
#define DB_J1939_TURBO_VAR	DB_J1939_TURBO_TYPE
#define DB_J1939_EEC3_VAR	DB_J1939_EEC3_TYPE
#define DB_J1939_VD_VAR		DB_J1939_VD_TYPE
#define DB_J1939_ETEMP_VAR	DB_J1939_ETEMP_TYPE
#define DB_J1939_PTO_VAR	DB_J1939_PTO_TYPE
#define DB_J1939_CCVS_VAR	DB_J1939_CCVS_TYPE
#define DB_J1939_LFE_VAR	DB_J1939_LFE_TYPE
#define DB_J1939_AMBC_VAR	DB_J1939_AMBC_TYPE
#define DB_J1939_IEC_VAR	DB_J1939_IEC_TYPE
#define DB_J1939_VEP_VAR	DB_J1939_VEP_TYPE
#define DB_J1939_TF_VAR		DB_J1939_TF_TYPE
#define DB_J1939_RF_VAR		DB_J1939_RF_TYPE
#define DB_J1939_HRVD_VAR	DB_J1939_HRVD_TYPE
#define DB_J1939_EBC2_VAR	DB_J1939_EBC2_TYPE
#define DB_J1939_RCFG_VAR	DB_J1939_RCFG_TYPE
#define DB_J1939_ECFG_VAR	DB_J1939_ECFG_TYPE
#define DB_J1939_TSC1_VAR 	DB_J1939_TSC1_TYPE
#define DB_J1939_ERC1_TRANS_VAR DB_J1939_ERC1_TRANS_TYPE	
#define DB_J1939_RCFG_TRANS_VAR DB_J1939_RCFG_TRANS_TYPE
#define DB_J1939_TSC1_RTDR_VAR	DB_J1939_TSC1_RTDR_TYPE
#define DB_J1939_FD_VAR		DB_J1939_FD_TYPE
#define DB_J1939_EXAC_VAR	DB_J1939_EXAC_TYPE
#define DB_J1939_EBC_ACC_VAR	DB_J1939_EBC_ACC_TYPE
#define DB_J1939_GFI2_VAR	DB_J1939_GFI2_TYPE
#define DB_J1939_EI_VAR		DB_J1939_EI_TYPE
#define DB_J1939_TSC1_E_A_VAR	DB_J1939_TSC1_E_A_TYPE
#define DB_J1939_TSC1_TRTDR_VAR	DB_J1939_TSC1_TRTDR_TYPE
#define DB_J1939_VP_X_VAR	DB_J1939_VP_X_TYPE
#define DB_J1939_VDC2_VAR	DB_J1939_VDC2_TYPE
#define DB_J1939_MVS_X_E_VAR	DB_J1939_MVS_X_E_TYPE
#define DB_J1939_EBC5_VAR	DB_J1939_EBC5_TYPE
#define DB_J1939_TSC1_E_ACC_VAR DB_J1939_TSC1_E_ACC_TYPE
#define DB_J1939_TSC1_ER_ACC_VAR DB_J1939_TSC1_ER_ACC_TYPE
#define DB_J1939_TSC1_E_T_VAR	DB_J1939_TSC1_E_T_TYPE
#define DB_J1939_TSC1_E_V_VAR	DB_J1939_TSC1_E_V_TYPE
#define DB_J1939_TSC1_ER_A_VAR	DB_J1939_TSC1_ER_A_TYPE
#define DB_J1939_TSC1_ER_T_VAR	DB_J1939_TSC1_ER_T_TYPE	
#define DB_J1939_TSC1_ER_V_VAR	DB_J1939_TSC1_ER_V_TYPE
#define DB_J1939_VOLVO_TARGET_VAR	DB_J1939_VOLVO_TARGET_TYPE
#define DB_J1939_VOLVO_EGO_VAR		DB_J1939_VOLVO_EGO_TYPE	
#define DB_J1939_VOLVO_XBR_WARN_VAR 	DB_J1939_VOLVO_XBR_WARN_TYPE
#define DB_J1939_VOLVO_XBR_VAR		DB_J1939_VOLVO_XBR_TYPE
#define DB_J1939_ETC2_E_VAR		DB_J1939_ETC2_E_TYPE
#define DB_J1939_VOLVO_BRK_VAR		DB_J1939_VOLVO_BRK_TYPE
#define DB_J1939_VOLVO_VP15_VAR		DB_J1939_VOLVO_VP15_TYPE
