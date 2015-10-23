/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "DSRC"
 * 	found in "module.asn1"
 * 	`asn1c -S/skeletons`
 */

#include <asn_internal.h>

#include "VehicleSafetyExtension.h"

static asn_TYPE_member_t asn_MBR_VehicleSafetyExtension_1[] = {
	{ ATF_POINTER, 4, offsetof(struct VehicleSafetyExtension, events),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_EventFlags,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"events"
		},
	{ ATF_POINTER, 3, offsetof(struct VehicleSafetyExtension, pathHistory),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PathHistory,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"pathHistory"
		},
	{ ATF_POINTER, 2, offsetof(struct VehicleSafetyExtension, pathPrediction),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PathPrediction,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"pathPrediction"
		},
	{ ATF_POINTER, 1, offsetof(struct VehicleSafetyExtension, theRTCM),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_RTCMPackage,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"theRTCM"
		},
};
static ber_tlv_tag_t asn_DEF_VehicleSafetyExtension_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_VehicleSafetyExtension_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* events at 1939 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* pathHistory at 1940 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* pathPrediction at 1941 */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 } /* theRTCM at 1942 */
};
static asn_SEQUENCE_specifics_t asn_SPC_VehicleSafetyExtension_specs_1 = {
	sizeof(struct VehicleSafetyExtension),
	offsetof(struct VehicleSafetyExtension, _asn_ctx),
	asn_MAP_VehicleSafetyExtension_tag2el_1,
	4,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	3,	/* Start extensions */
	5	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_VehicleSafetyExtension = {
	"VehicleSafetyExtension",
	"VehicleSafetyExtension",
	SEQUENCE_free,
	SEQUENCE_print,
	SEQUENCE_constraint,
	SEQUENCE_decode_ber,
	SEQUENCE_encode_der,
	SEQUENCE_decode_xer,
	SEQUENCE_encode_xer,
	0, 0,	/* No PER support, use "-gen-PER" to enable */
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_VehicleSafetyExtension_tags_1,
	sizeof(asn_DEF_VehicleSafetyExtension_tags_1)
		/sizeof(asn_DEF_VehicleSafetyExtension_tags_1[0]), /* 1 */
	asn_DEF_VehicleSafetyExtension_tags_1,	/* Same as above */
	sizeof(asn_DEF_VehicleSafetyExtension_tags_1)
		/sizeof(asn_DEF_VehicleSafetyExtension_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_VehicleSafetyExtension_1,
	4,	/* Elements count */
	&asn_SPC_VehicleSafetyExtension_specs_1	/* Additional specs */
};

