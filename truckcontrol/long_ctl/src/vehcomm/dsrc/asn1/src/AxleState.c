/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "DSRC"
 * 	found in "module.asn1"
 * 	`asn1c -S/skeletons`
 */

#include <asn_internal.h>

#include "AxleState.h"

static asn_TYPE_member_t asn_MBR_AxleState_1[] = {
	{ ATF_POINTER, 2, offsetof(struct AxleState, location),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_AxleLocation,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"location"
		},
	{ ATF_POINTER, 1, offsetof(struct AxleState, weight),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_AxleWeight,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"weight"
		},
};
static ber_tlv_tag_t asn_DEF_AxleState_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_AxleState_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* location at 2137 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* weight at 2138 */
};
static asn_SEQUENCE_specifics_t asn_SPC_AxleState_specs_1 = {
	sizeof(struct AxleState),
	offsetof(struct AxleState, _asn_ctx),
	asn_MAP_AxleState_tag2el_1,
	2,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	1,	/* Start extensions */
	3	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_AxleState = {
	"AxleState",
	"AxleState",
	SEQUENCE_free,
	SEQUENCE_print,
	SEQUENCE_constraint,
	SEQUENCE_decode_ber,
	SEQUENCE_encode_der,
	SEQUENCE_decode_xer,
	SEQUENCE_encode_xer,
	0, 0,	/* No PER support, use "-gen-PER" to enable */
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_AxleState_tags_1,
	sizeof(asn_DEF_AxleState_tags_1)
		/sizeof(asn_DEF_AxleState_tags_1[0]), /* 1 */
	asn_DEF_AxleState_tags_1,	/* Same as above */
	sizeof(asn_DEF_AxleState_tags_1)
		/sizeof(asn_DEF_AxleState_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_AxleState_1,
	2,	/* Elements count */
	&asn_SPC_AxleState_specs_1	/* Additional specs */
};

