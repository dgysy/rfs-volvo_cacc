/*
 * Generated by asn1c-0.9.26 (http://lionet.info/asn1c)
 * From ASN.1 module "J2735BSMESSAGE"
 * 	found in "BasicSafetyMessage-Volvo.txt"
 */

#ifndef	_CaccData_H_
#define	_CaccData_H_


#include <asn_application.h>

/* Including external dependencies */
#include "CACCFlags.h"
#include "Speed.h"
#include "ThrottlePosition.h"
#include <OCTET_STRING.h>
#include <NativeInteger.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct DDateTime;

/* CaccData */
typedef struct CaccData {
	CACCFlags_t	 flags;
	Speed_t	 setSpeed;
	ThrottlePosition_t	 throtPos;
	OCTET_STRING_t	 lclPN;
	OCTET_STRING_t	 lclPE;
	OCTET_STRING_t	 lclPD;
	OCTET_STRING_t	 roll;
	OCTET_STRING_t	 pitch;
	OCTET_STRING_t	 yaw;
	OCTET_STRING_t	 hPosAcry;
	OCTET_STRING_t	 vPosAcry;
	OCTET_STRING_t	 fwrdVel;
	OCTET_STRING_t	 rightVel;
	OCTET_STRING_t	 downVel;
	OCTET_STRING_t	 velAcc;
	OCTET_STRING_t	 fwrdAcc;
	OCTET_STRING_t	 rightAcc;
	OCTET_STRING_t	 dwnAcc;
	long	 grpID;
	long	 grpSize;
	long	 grpMode;
	long	 grpManDes;
	long	 grpManID;
	OCTET_STRING_t	 vehID;
	long	 frntCutIn;
	long	 vehGrpPos;
	long	 vehFltMode;
	long	 vehManDes;
	long	 vehManID;
	long	 distToPVeh;
	long	 relSpdPVeh;
	long	 disToLVeh;
	long	 relSpdLVeh;
	long	 desTGapPVeh;
	long	 desTGapLVeh;
	long	 estDisPVeh;
	long	 estDisLVeh;
	long	 desSpd;
	long	 desTrq;
	OCTET_STRING_t	*userDI1	/* OPTIONAL */;
	OCTET_STRING_t	*userDI2	/* OPTIONAL */;
	OCTET_STRING_t	*userDF1	/* OPTIONAL */;
	OCTET_STRING_t	*userDF2	/* OPTIONAL */;
	OCTET_STRING_t	*userDF3	/* OPTIONAL */;
	struct DDateTime	*utcTime	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} CaccData_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_CaccData;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "DDateTime.h"

#endif	/* _CaccData_H_ */
#include <asn_internal.h>