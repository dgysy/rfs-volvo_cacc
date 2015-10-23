/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "DSRC"
 * 	found in "module.asn1"
 * 	`asn1c -S/skeletons`
 */

#ifndef	_TransitPreEmptionRequest_H_
#define	_TransitPreEmptionRequest_H_


#include <asn_application.h>

/* Including external dependencies */
#include <ENUMERATED.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum TransitPreEmptionRequest {
	TransitPreEmptionRequest_typeOne	= 0,
	TransitPreEmptionRequest_typeTwo	= 1,
	TransitPreEmptionRequest_typeThree	= 2,
	TransitPreEmptionRequest_typeFour	= 3
	/*
	 * Enumeration is extensible
	 */
} e_TransitPreEmptionRequest;

/* TransitPreEmptionRequest */
typedef ENUMERATED_t	 TransitPreEmptionRequest_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_TransitPreEmptionRequest;
asn_struct_free_f TransitPreEmptionRequest_free;
asn_struct_print_f TransitPreEmptionRequest_print;
asn_constr_check_f TransitPreEmptionRequest_constraint;
ber_type_decoder_f TransitPreEmptionRequest_decode_ber;
der_type_encoder_f TransitPreEmptionRequest_encode_der;
xer_type_decoder_f TransitPreEmptionRequest_decode_xer;
xer_type_encoder_f TransitPreEmptionRequest_encode_xer;

#ifdef __cplusplus
}
#endif

#endif	/* _TransitPreEmptionRequest_H_ */
