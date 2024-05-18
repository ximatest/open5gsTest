/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NGAP-PDU-Descriptions"
 * 	found in "../support/ngap-r17.3.0/38413-h30.asn"
 * 	`asn1c -pdu=all -fcompound-names -findirect-choice -fno-include-deps -no-gen-BER -no-gen-XER -no-gen-OER -no-gen-UPER -no-gen-JER`
 */

#ifndef	_NGAP_NGAP_PDU_H_
#define	_NGAP_NGAP_PDU_H_


#include <asn_application.h>

/* Including external dependencies */
#include <constr_CHOICE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum NGAP_NGAP_PDU_PR {
	NGAP_NGAP_PDU_PR_NOTHING,	/* No components present */
	NGAP_NGAP_PDU_PR_initiatingMessage,
	NGAP_NGAP_PDU_PR_successfulOutcome,
	NGAP_NGAP_PDU_PR_unsuccessfulOutcome
	/* Extensions may appear below */
	
} NGAP_NGAP_PDU_PR;

/* Forward declarations */
struct NGAP_InitiatingMessage;
struct NGAP_SuccessfulOutcome;
struct NGAP_UnsuccessfulOutcome;

/* NGAP_NGAP-PDU */
typedef struct NGAP_NGAP_PDU {
	NGAP_NGAP_PDU_PR present;
	union NGAP_NGAP_PDU_u {
		struct NGAP_InitiatingMessage	*initiatingMessage;
		struct NGAP_SuccessfulOutcome	*successfulOutcome;
		struct NGAP_UnsuccessfulOutcome	*unsuccessfulOutcome;
		/*
		 * This type is extensible,
		 * possible extensions are below.
		 */
	} choice;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} NGAP_NGAP_PDU_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_NGAP_NGAP_PDU;

#ifdef __cplusplus
}
#endif

#endif	/* _NGAP_NGAP_PDU_H_ */
#include <asn_internal.h>
