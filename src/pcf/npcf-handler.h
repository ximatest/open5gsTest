/*
 * Copyright (C) 2019,2020 by Sukchan Lee <acetcom@gmail.com>
 *
 * This file is part of Open5GS.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef PCF_NPCF_HANDLER_H
#define PCF_NPCF_HANDLER_H

#include "context.h"

#ifdef __cplusplus
extern "C" {
#endif

bool pcf_npcf_am_policy_contrtol_handle_create(pcf_ue_t *pcf_ue,
        ogs_sbi_stream_t *stream, ogs_sbi_message_t *recvmsg);

bool pcf_npcf_smpolicycontrol_handle_create(pcf_sess_t *sess,
        ogs_sbi_stream_t *stream, ogs_sbi_message_t *recvmsg);
bool pcf_npcf_smpolicycontrol_handle_delete(pcf_sess_t *sess,
        ogs_sbi_stream_t *stream, ogs_sbi_message_t *recvmsg);

bool pcf_npcf_policyauthorization_handle_create(pcf_sess_t *sess,
        ogs_sbi_stream_t *stream, ogs_sbi_message_t *recvmsg);
bool pcf_npcf_policyauthorization_handle_update(
        pcf_sess_t *sess, pcf_app_t *app,
        ogs_sbi_stream_t *stream, ogs_sbi_message_t *recvmsg);
bool pcf_npcf_policyauthorization_handle_delete(
        pcf_sess_t *sess, pcf_app_t *app,
        ogs_sbi_stream_t *stream, ogs_sbi_message_t *recvmsg);

int pcf_n7_send_rar(pcf_sess_t *sess,pcf_app_t *app_session, ogs_diam_rx_message_t *rx_message);
int pcf_n7_send_rar_to_main_thread(pcf_sess_t *sess,
        pcf_app_t *app_session, ogs_diam_rx_message_t *rx_message);
#ifdef __cplusplus
}
#endif

#endif /* PCF_NPCF_HANDLER_H */
