/*
 * Generated by asn1c-0.9.26 (http://lionet.info/asn1c)
 * From ASN.1 module "J2735BSMESSAGE"
 * 	found in "BasicSafetyMessage-Volvo.txt"
 * 	`asn1c -S/skeletons`
 */

#ifndef	_SteeringWheelAngle_H_
#define	_SteeringWheelAngle_H_


#include <asn_application.h>

/* Including external dependencies */
#include <OCTET_STRING.h>

#ifdef __cplusplus
extern "C" {
#endif

/* SteeringWheelAngle */
typedef OCTET_STRING_t	 SteeringWheelAngle_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SteeringWheelAngle;
asn_struct_free_f SteeringWheelAngle_free;
asn_struct_print_f SteeringWheelAngle_print;
asn_constr_check_f SteeringWheelAngle_constraint;
ber_type_decoder_f SteeringWheelAngle_decode_ber;
der_type_encoder_f SteeringWheelAngle_encode_der;
xer_type_decoder_f SteeringWheelAngle_decode_xer;
xer_type_encoder_f SteeringWheelAngle_encode_xer;

#ifdef __cplusplus
}
#endif

#endif	/* _SteeringWheelAngle_H_ */
#include <asn_internal.h>
