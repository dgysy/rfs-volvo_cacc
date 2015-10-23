/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "DSRC"
 * 	found in "module.asn1"
 * 	`asn1c -S/skeletons`
 */

#include <asn_internal.h>

#include "DTime.h"

static asn_TYPE_member_t asn_MBR_DTime_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct DTime, hour),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_DHour,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"hour"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct DTime, minute),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_DMinute,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"minute"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct DTime, second),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_DSecond,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"second"
		},
};
static ber_tlv_tag_t asn_DEF_DTime_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_DTime_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* hour at 956 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* minute at 957 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* second at 959 */
};
static asn_SEQUENCE_specifics_t asn_SPC_DTime_specs_1 = {
	sizeof(struct DTime),
	offsetof(struct DTime, _asn_ctx),
	asn_MAP_DTime_tag2el_1,
	3,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_DTime = {
	"DTime",
	"DTime",
	SEQUENCE_free,
	SEQUENCE_print,
	SEQUENCE_constraint,
	SEQUENCE_decode_ber,
	SEQUENCE_encode_der,
	SEQUENCE_decode_xer,
	SEQUENCE_encode_xer,
	0, 0,	/* No PER support, use "-gen-PER" to enable */
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_DTime_tags_1,
	sizeof(asn_DEF_DTime_tags_1)
		/sizeof(asn_DEF_DTime_tags_1[0]), /* 1 */
	asn_DEF_DTime_tags_1,	/* Same as above */
	sizeof(asn_DEF_DTime_tags_1)
		/sizeof(asn_DEF_DTime_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_DTime_1,
	3,	/* Elements count */
	&asn_SPC_DTime_specs_1	/* Additional specs */
};

