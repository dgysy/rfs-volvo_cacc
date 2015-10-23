/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "DSRC"
 * 	found in "module.asn1"
 * 	`asn1c -S/skeletons`
 */

#ifndef	_SpeedLimit_H_
#define	_SpeedLimit_H_


#include <asn_application.h>

/* Including external dependencies */
#include <asn_SEQUENCE_OF.h>
#include <constr_SEQUENCE_OF.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct ITISCodesChoice;

/* SpeedLimit */
typedef struct SpeedLimit {
	A_SEQUENCE_OF(struct ITISCodesChoice) list;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SpeedLimit_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SpeedLimit;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "ITISCodesChoice.h"

#endif	/* _SpeedLimit_H_ */
