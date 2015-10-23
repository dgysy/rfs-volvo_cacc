/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "DSRC"
 * 	found in "module.asn1"
 * 	`asn1c -S/skeletons`
 */

#ifndef	_VehicleSize_H_
#define	_VehicleSize_H_


#include <asn_application.h>

/* Including external dependencies */
#include "VehicleWidth.h"
#include "VehicleLength.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* VehicleSize */
typedef struct VehicleSize {
	VehicleWidth_t	 width;
	VehicleLength_t	 length;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} VehicleSize_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_VehicleSize;

#ifdef __cplusplus
}
#endif

#endif	/* _VehicleSize_H_ */
