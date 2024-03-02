#include "telnet.h"
#include "context.h"
char                g_chCmdName[128] = {0};
T_pttCmdParas       g_tCmdPara[128];
void amf(void);
void showgnb(uint32_t enbID);
void showgnbBriefAll( void );
void shownf(uint32_t id);
void shownfBriefAll(void);
void showranue( void );
void amf(void)
{
    printf("this is amf system. \r\n");
}

void telnet_proc_cmd(char * pabCmd)
{
    uint32_t  dwPara1   = 0;
    uint32_t  dwPara2   = 0;
   
    if (!pttGetCmdParams(pabCmd))
    {
        return;
    }

    dwPara1 = pttGetCmdWord32Value(&g_tCmdPara[0]);
    dwPara2 = pttGetCmdWord32Value(&g_tCmdPara[1]);

    if (strcmp(g_chCmdName, "amf") == 0){
        amf();
    }else if (strcmp(g_chCmdName, "showgnb") == 0){
        showgnb(dwPara1);
    }else if (strcmp(g_chCmdName, "shownf") == 0){
        shownf(dwPara1);
    }else if (strcmp(g_chCmdName, "showranue") == 0){
        showranue();
    }  
    else{
        printf("the command not support\r\n");
    }  
    
    return;
}

void showgnb(uint32_t enbID)
{
    if(enbID == 0 )
    {
        showgnbBriefAll();
    }
    else
    {
        //showgnbDetail(enbID);
    }

    return;
}

void showgnbBriefAll( void )
{
    amf_gnb_t *gnb = NULL;
    
    printf("\ngnb Brief All(current %u gnb count):\r\n", ogs_list_count(&amf_self()->gnb_list));
    printf("+---------+----------------+----------+----------+--------+\n\r");
    printf("| gnb_id  |    plmn_id     |  state   |  ta_num  | UECnt  |\n\r");
    printf("+---------+----------------+----------+----------+--------+\n\r");
    
    ogs_list_for_each(&amf_self()->gnb_list, gnb) {
        printf("| %-7u | MCC:%dMNC:%-3d | %-8d | %-8d | %-6u |\r\n",
               gnb->gnb_id, 
               ogs_plmn_id_mcc(&gnb->plmn_id),
               ogs_plmn_id_mnc(&gnb->plmn_id),
               gnb->state.ng_setup_success,
               gnb->num_of_supported_ta_list, 
               ogs_list_count(&gnb->ran_ue_list));
    }
    
    printf("+---------+----------------+----------+----------+--------+\n\r");
    
    printf("\r\n");
    
    return ;
}

void shownf(uint32_t id){
    if(id == 0 ){
        shownfBriefAll();
    }else{
        //showgnbDetail(id);
    }

    return;
}

void shownfBriefAll(void){
    ogs_sbi_nf_instance_t *nf_instance = NULL;
    char buf[OGS_ADDRSTRLEN];
    
    printf("\nnf instance Brief All(current %u nf count):\r\n", ogs_list_count(&ogs_sbi_self()->nf_instance_list));
    printf("+--------------------------------------+---------+------------+----------+----------+--------------------+\n\r");
    printf("|                 nf_id                | nf_type |    status  | capacity | ref_cnt  |    ipv4_address    |\n\r");
    printf("+--------------------------------------+---------+------------+----------+----------+--------------------+\n\r");

    ogs_list_for_each(&ogs_sbi_self()->nf_instance_list, nf_instance) {
        char addrInfo[OGS_ADDRSTRLEN] = {0};
        if (nf_instance->num_of_ipv4 > 0){
            sprintf(addrInfo,"%s:%d",OGS_ADDR(nf_instance->ipv4[0], buf), OGS_PORT(nf_instance->ipv4[0]));
        }
        printf("| %-36s | %-7s | %-10s | %-8d | %-8u | %-18s |\r\n",nf_instance->id, 
        OpenAPI_nf_type_ToString(nf_instance->nf_type),
        OpenAPI_nf_status_ToString(nf_instance->nf_status),
        nf_instance->capacity,
        nf_instance->reference_count,
        addrInfo); 
    }
    printf("+--------------------------------------+---------+------------+----------+----------+--------------+\n\r");
}

void showranue( void )
{
    amf_gnb_t *gnb = NULL;
    ran_ue_t *ran_ue = NULL;
    
    printf("\ngnb Brief All(current %u gnb count):\r\n", ogs_list_count(&amf_self()->gnb_list));
    printf("+---------+----------------+----------------+--------+----------------------+--------+\n\r");
    printf("| gnb_id  | ran_ue_ngap_id | amf_ue_ngap_id | sps_no |         supi         |  tmsi  |\n\r");
    printf("+---------+----------------+----------------+--------+----------------------+--------+\n\r");
    
    ogs_list_for_each(&amf_self()->gnb_list, gnb) {
        ogs_list_for_each(&gnb->ran_ue_list, ran_ue) {
            printf("| %-7u | %-14d | %-14lu | %-6d | %-15s | %-6u |\r\n",
               gnb->gnb_id, 
               ran_ue->ran_ue_ngap_id,
               ran_ue->amf_ue_ngap_id,
               ran_ue->sps_no,
               ran_ue->supi,
               ran_ue->m_tmsi);
        }
    }
    
    printf("+---------+----------------+----------------+--------+----------------------+\n\r");
    
    printf("\r\n");
    
    return ;
}