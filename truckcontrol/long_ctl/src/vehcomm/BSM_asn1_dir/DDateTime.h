/*
 * Generated by asn1c-0.9.26 (http://lionet.info/asn1c)
 * From ASN.1 module "J2735BSMESSAGE"
 * 	found in "BasicSafetyMessage-Volvo.txt"
 * 	`asn1c -S/home/jspring/downloads/asn1c-0.9.26/skeletons`
 */

#ifndef	_DDateTime_H_
#define	_DDateTime_H_


#include <asn_application.h>

/* Including external dependencies */
#include "DYear.h"
#include "DMonth.h"
#include "DDay.h"
#include "DHour.h"
#include "DMinute.h"
#include "DSecond.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* DDateTime */
typedef struct DDateTime {
	DYear_t	 year;
	DMonth_t	 month;
	DDay_t	 day;
	DHour_t	 hour;
	DMinute_t	 minute;
	DSecond_t	 second;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} DDateTime_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_DDateTime;

#ifdef __cplusplus
}
#endif

#endif	/* _DDateTime_H_ */
#include <asn_internal.h>