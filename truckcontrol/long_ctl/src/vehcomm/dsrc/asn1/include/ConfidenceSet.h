/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "DSRC"
 * 	found in "module.asn1"
 * 	`asn1c -S/skeletons`
 */

#ifndef	_ConfidenceSet_H_
#define	_ConfidenceSet_H_


#include <asn_application.h>

/* Including external dependencies */
#include "SpeedandHeadingandThrottleConfidence.h"
#include "TimeConfidence.h"
#include "PositionConfidenceSet.h"
#include "SteeringWheelAngleConfidence.h"
#include "ThrottleConfidence.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct AccelSteerYawRateConfidence;

/* ConfidenceSet */
typedef struct ConfidenceSet {
	struct AccelSteerYawRateConfidence	*accelConfidence	/* OPTIONAL */;
	SpeedandHeadingandThrottleConfidence_t	*speedConfidence	/* OPTIONAL */;
	TimeConfidence_t	*timeConfidence	/* OPTIONAL */;
	PositionConfidenceSet_t	*posConfidence	/* OPTIONAL */;
	SteeringWheelAngleConfidence_t	*steerConfidence	/* OPTIONAL */;
	ThrottleConfidence_t	*throttleConfidence	/* OPTIONAL */;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} ConfidenceSet_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_ConfidenceSet;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "AccelSteerYawRateConfidence.h"

#endif	/* _ConfidenceSet_H_ */
