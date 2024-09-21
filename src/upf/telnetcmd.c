#include "telnet.h"
#include "context.h"

#if defined(USE_DPDK)
#include "upf-dpdk.h"
#include "ctrl-path.h"

void show_port_info(void);
void show_lcore_info(void);
void show_arp_hash(struct arp_hashtbl *h);
void show_vxlan_config(void);
#endif

char                g_chCmdName[128] = {0};
T_pttCmdParas       g_tCmdPara[128];
int                 pkt_metric_flag = 0;
void upf(void);
void showsess(uint32_t id);
void showsessBriefAll( void );
void showsessDetail( uint32_t id );
void setCommands(void);
void set_pkt_metric(uint32_t flag);


telnet_command_t g_commands[] = {
    {"showsess",      (GenericFunc)showsess,         1, {INTEGER}},
    {"upf",           (GenericFunc)upf,              0, {}},
    {"set_pkt_metric",(GenericFunc)set_pkt_metric,   1, {INTEGER}},
    #if defined(USE_DPDK)
    {"show_vxlan_config",(GenericFunc)show_vxlan_config,  0, {}},    
    {"show_port_info",(GenericFunc)show_port_info,   0, {}},
    {"show_lcore_info",(GenericFunc)show_lcore_info, 0, {}},    
    {"print_stat",     (GenericFunc)print_stat,      0, {}},
    #endif
};
int g_numCommands = sizeof(g_commands) / sizeof(g_commands[0]);

void setCommands(void){    
    set_telnet_commands(g_commands, g_numCommands);
}



void upf(void)
{
    printf("this is upf system. \r\n");
}

void showsess(uint32_t id)
{
    if(id == 0 )
    {
        showsessBriefAll();
    }
    else
    {
        showsessDetail(id);
    }

    return;
}

void showsessBriefAll( void )
{
    upf_sess_t *sess = NULL;
    char buf1[OGS_ADDRSTRLEN];
    char buf2[OGS_ADDRSTRLEN];
    
    printf("\nupf sess Brief All(current %u sess count):\r\n", ogs_list_count(&upf_self()->sess_list));
    printf("+-------------+-------------+----------------+----------------+----------------------------------------+----------+\n\r");
    printf("| upf_n4_seid | smf_n4_seid |   smf_n4_ip    |     ipv4       |                 ipv6                   | apn_dnn  |\n\r");
    printf("+-------------+-------------+----------------+----------------+----------------------------------------+----------+\n\r");
    char *ipstr = NULL;
    ogs_list_for_each(&upf_self()->sess_list, sess) {
        if(sess->smf_n4_f_seid.ip.ipv4)
            ipstr= ogs_ipv4_to_string(sess->smf_n4_f_seid.ip.addr);
        printf("| %-11lu | %-11ld | %-14s | %-14s | %-38s | %-8s |\r\n",
               sess->upf_n4_seid,
               sess->smf_n4_f_seid.seid,
               sess->smf_n4_f_seid.ip.ipv4 ?ipstr:"",
               sess->ipv4 ? OGS_INET_NTOP(&sess->ipv4->addr, buf1) : "",
               sess->ipv6 ? OGS_INET6_NTOP(&sess->ipv6->addr, buf2) : "",
               sess->apn_dnn);
        if(ipstr)ogs_free(ipstr);
    }
    
        printf("+-------------+-------------+----------------+----------------+----------------------------------------+----------+\n\r");
    printf("\r\n");
    
    return ;
}

void showsessDetail( uint32_t id )
{
    upf_sess_t *sess = NULL;
    ogs_pfcp_pdr_t *pdr = NULL;
    ogs_pfcp_far_t *far = NULL;
    ogs_pfcp_urr_t *urr = NULL;
    ogs_pfcp_qer_t *qer = NULL;
    ogs_pfcp_rule_t *rule = NULL;
    char buf1[OGS_ADDRSTRLEN];
    char buf2[OGS_ADDRSTRLEN];
    int i;
    int pdr_index = 0;
    printf("\r\n");
    sess = upf_sess_find_by_upf_n4_seid(id);
    char *ipstr = NULL;
    if (sess == NULL){
        printf("can not find upf sess by upf_n4_seid:%d \r\n",id);
        return;
    }
    
    printf("The upf sess(upf_n4_seid=%u) Detail Info is the following: \r\n", id);
    printf("  |--upf_n4_seid        : %lu \r\n", sess->upf_n4_seid);
    printf("  |--smf_n4_seid        : %lu \r\n", sess->smf_n4_f_seid.seid);
    ipstr=ogs_ipv4_to_string(sess->smf_n4_f_seid.ip.addr);
    printf("  |--smf_n4_ip          : %s \r\n", ipstr);
    ogs_free(ipstr);
    printf("  |--pfcp      : \r\n");    
    printf("      |--pdr_cnt           : %d \r\n", ogs_list_count(&sess->pfcp.pdr_list));
    ogs_list_for_each(&sess->pfcp.pdr_list, pdr){
        printf("          **************pdr index:%d, id: %d***********\r\n",pdr_index, pdr->id);     
        printf("          |--teid              : %d \r\n", pdr->teid);
        printf("          |--src_if            : %s \r\n", ogs_pfcp_interface_get_name(pdr->src_if));
        printf("          |--dnn               : %s \r\n", pdr->dnn);
        printf("          |--f_teid            :  \r\n");
        printf("              |--teid             : %d \r\n", pdr->f_teid.teid);
        printf("              |--addr             : %s \r\n", OGS_INET_NTOP(&pdr->f_teid.addr, buf1) );
        printf("              |--addr6            : %s \r\n", OGS_INET_NTOP(&pdr->f_teid.addr6, buf2) );
        printf("          |--chid              : %d \r\n", pdr->chid);
        printf("          |--choose_id         : %d \r\n", pdr->choose_id);
        printf("          |--qfi               : %d \r\n", pdr->qfi);
        printf("          |--num_of_urr        : %d \r\n", pdr->num_of_urr);
        for (i = 0; i < pdr->num_of_urr; i++){
            printf("              |--id                : %d \r\n", pdr->urr[i]->id);
            printf("              |--meas_method       : %d \r\n", pdr->urr[i]->meas_method);
            printf("              |--rep_triggers      : reptri_5:%d reptri_6:%d reptri_7:%d \r\n", pdr->urr[i]->rep_triggers.reptri_5, 
                                                                                                    pdr->urr[i]->rep_triggers.reptri_6, 
                                                                                                    pdr->urr[i]->rep_triggers.reptri_7);

			printf("              |--meas_info         : mnop:%d,istm:%d,radi:%d,inam:%d,mnop:%d \r\n", pdr->urr[i]->meas_info.mnop,
																									    pdr->urr[i]->meas_info.istm,
																									    pdr->urr[i]->meas_info.radi,
																									    pdr->urr[i]->meas_info.inam,
																									    pdr->urr[i]->meas_info.mbqe);
            printf("              |--meas_period       : %d \r\n", pdr->urr[i]->meas_period);
            printf("              |--vol_threshold     : total:%lu uplink:%lu downlink:%lu\r\n", pdr->urr[i]->vol_threshold.total_volume,
                                                                                                 pdr->urr[i]->vol_threshold.uplink_volume,
                                                                                                 pdr->urr[i]->vol_threshold.downlink_volume);
            printf("              |--vol_quota         : total:%lu uplink:%lu downlink:%lu\r\n", pdr->urr[i]->vol_quota.total_volume,
                                                                                     pdr->urr[i]->vol_quota.uplink_volume,
                                                                                     pdr->urr[i]->vol_quota.downlink_volume);
            printf("              |--event_threshold   : %u\r\n", pdr->urr[i]->event_threshold); 
            printf("              |--event_quota       : %d \r\n", pdr->urr[i]->event_quota);
            printf("              |--time_threshold    : %d \r\n", pdr->urr[i]->time_threshold);
            printf("              |--time_quota        : %d \r\n", pdr->urr[i]->time_quota);
            printf("              |--quota_holding_time: %d \r\n", pdr->urr[i]->quota_holding_time);
            printf("              |--dropped_dl_traffic_threshold: downlink_packets:%lu,number_of_bytes_of_downlink_data:%lu \r\n", pdr->urr[i]->dropped_dl_traffic_threshold.downlink_packets,pdr->urr[i]->dropped_dl_traffic_threshold.number_of_bytes_of_downlink_data);
            printf("              |--quota_validity_time: %d \r\n", pdr->urr[i]->quota_validity_time);
        }
        printf("          |--num_of_flow       : %d \r\n", pdr->num_of_flow);
        for (i = 0; i < pdr->num_of_flow; i++){
            printf("              |--flow_description[%d] : %s \r\n", i,pdr->flow[i].description);
        }
        printf("          |--num of rule_list  : %d \r\n", ogs_list_count(&pdr->rule_list));
        ogs_list_for_each(&pdr->rule_list, rule){
            printf("              |--sdf_filter_id : %d \r\n", rule->sdf_filter_id);
            printf("              |--flags         : %d(bid:%d,fl:%d,spi:%d,ttc:%d,fd:%d) \r\n", rule->flags,rule->bid,rule->fl,rule->spi,rule->ttc,rule->fd);
            printf("              |--proto         : %d \r\n", rule->ipfw.proto);
            printf("              |--ipv4_src      : %d \r\n", rule->ipfw.ipv4_src);
            printf("              |--ipv4_dst      : %d \r\n", rule->ipfw.ipv4_dst);
            printf("              |--ipv6_src      : %d \r\n", rule->ipfw.ipv6_src);
            printf("              |--ipv6_dst      : %d \r\n", rule->ipfw.ipv6_dst);
            printf("              |--port          :SRC:%d-%d DST:%d-%d\r\n",
                                                        rule->ipfw.port.src.low,
                                                        rule->ipfw.port.src.high,
                                                        rule->ipfw.port.dst.low,
                                                        rule->ipfw.port.dst.high);
            printf("              |--SRC           :%08x %08x %08x %08x/%08x %08x %08x %08x\r\n",
                                                        be32toh(rule->ipfw.ip.src.addr[0]),
                                                        be32toh(rule->ipfw.ip.src.addr[1]),
                                                        be32toh(rule->ipfw.ip.src.addr[2]),
                                                        be32toh(rule->ipfw.ip.src.addr[3]),
                                                        be32toh(rule->ipfw.ip.src.mask[0]),
                                                        be32toh(rule->ipfw.ip.src.mask[1]),
                                                        be32toh(rule->ipfw.ip.src.mask[2]),
                                                        be32toh(rule->ipfw.ip.src.mask[3]));
            printf("              |--DST           :%08x %08x %08x %08x/%08x %08x %08x %08x\r\n",
                                                        be32toh(rule->ipfw.ip.dst.addr[0]),
                                                        be32toh(rule->ipfw.ip.dst.addr[1]),
                                                        be32toh(rule->ipfw.ip.dst.addr[2]),
                                                        be32toh(rule->ipfw.ip.dst.addr[3]),
                                                        be32toh(rule->ipfw.ip.dst.mask[0]),
                                                        be32toh(rule->ipfw.ip.dst.mask[1]),
                                                        be32toh(rule->ipfw.ip.dst.mask[2]),
                                                        be32toh(rule->ipfw.ip.dst.mask[3]));
        }
        pdr_index++;
    }
    printf("     |--far_cnt           : %d \r\n", ogs_list_count(&sess->pfcp.far_list));
    ogs_list_for_each(&sess->pfcp.far_list, far){
        printf("          **************far id: %d***********\r\n",far->id);     
        printf("          |--dnn               : %s \r\n", far->dnn);
        printf("          |--dst_if            : %s \r\n", ogs_pfcp_interface_get_name(far->dst_if));
        printf("          |--apply_action      : %d \r\n", far->apply_action);
        printf("          |--num_of_buffered_packet: %d \r\n", far->num_of_buffered_packet);        
        printf("          |--smreq_flags       : %d \r\n", far->smreq_flags.value);
    }
    
    printf("     |--urr_cnt           : %d \r\n", ogs_list_count(&sess->pfcp.urr_list));
    ogs_list_for_each(&sess->pfcp.urr_list, urr){
        printf("          **************urr id: %d***********\r\n",urr->id);     
        printf("          |--meas_method       : %d \r\n", urr->meas_method);
        printf("          |--rep_triggers      : reptri_5:%d reptri_6:%d reptri_7:%d \r\n", urr->rep_triggers.reptri_5, 
                                                                                                urr->rep_triggers.reptri_6, 
                                                                                                urr->rep_triggers.reptri_7);
        //printf("              |--meas_info         : %d \r\n", urr->meas_info);
        printf("          |--meas_period       : %d \r\n", urr->meas_period);
        printf("          |--vol_threshold     : total:%lu uplink:%lu downlink:%lu\r\n", urr->vol_threshold.total_volume,
                                                                                             urr->vol_threshold.uplink_volume,
                                                                                             urr->vol_threshold.downlink_volume);
        printf("          |--vol_quota         : total:%lu uplink:%lu downlink:%lu\r\n", urr->vol_quota.total_volume,
                                                                                 urr->vol_quota.uplink_volume,
                                                                                 urr->vol_quota.downlink_volume);
        printf("          |--event_threshold   : %u\r\n", urr->event_threshold); 
        printf("          |--event_quota       : %d \r\n", urr->event_quota);
        printf("          |--time_threshold    : %d \r\n", urr->time_threshold);
        printf("          |--time_quota        : %d \r\n", urr->time_quota);
        printf("          |--quota_holding_time: %d \r\n", urr->quota_holding_time);
        //printf("        |--dropped_dl_traffic_threshold: %d \r\n", urr->dropped_dl_traffic_threshold);
        printf("          |--quota_validity_time: %d \r\n", urr->quota_validity_time);
    }
    
    printf("     |--qer_cnt           : %d \r\n", ogs_list_count(&sess->pfcp.qer_list));
    ogs_list_for_each(&sess->pfcp.qer_list, qer){
        printf("          **************qer id: %d***********\r\n",qer->id);     
        printf("          |--gate_status       : uplink:%d downlink:%d\r\n", qer->gate_status.uplink,qer->gate_status.downlink);
        printf("          |--mbr               : uplink:%ld downlink:%ld\r\n", qer->mbr.uplink,qer->mbr.downlink);
        printf("          |--gbr               : uplink:%ld downlink:%ld \r\n", qer->gbr.uplink,qer->gbr.downlink);
        printf("          |--qfi               : %d \r\n", qer->qfi);

    }
    printf("\r\n"); 
    
    return ;
}

void set_pkt_metric(uint32_t id){
    pkt_metric_flag = id;

    if (id == 0) {
        printf("packet metrics is turned off.\r\n");
    } else {
        printf("packet metrics is turned on, it will reduce data plane performance.\r\n");
    }
}

#if defined(USE_DPDK)
void show_port_info(void){
    int i;
    printf("|--pfcp_lcore   :%d \r\n",dkuf.pfcp_lcore);
    printf("|--dpt_num      :%d \r\n",dkuf.dpt_num);
    printf("|--dpt_lcore    :");
    for (i = 0 ; i < dkuf.dpt_num; i++){
        printf("%d ", dkuf.dpt_lcore[i]);
    }
    printf("\r\n");
    printf("|--fwd_num      :%d \r\n",dkuf.fwd_num);
    printf("|--fwd_lcore    :");
    for (i = 0 ; i < dkuf.fwd_num; i++){
        printf("%d ", dkuf.fwd_lcore[i]);
    }
    printf("\r\n");
    printf("|--n3_addr      :%s \r\n",ip2str(dkuf.n3_addr.ipv4));
    printf("|--n3_gw        :%s \r\n",ip2str(dkuf.n3_addr.gw));
    printf("|--n3_addr6     :%s \r\n",ip62str(dkuf.n3_addr.ipv6));
    printf("|--n3_gw6       :%s \r\n",ip62str(dkuf.n3_addr.gw6));
    printf("|--n3_mac       :%s \r\n",mac2str(&dkuf.mac[0]));

    printf("|--n6_add       :%s \r\n",ip2str(dkuf.n6_addr.ipv4));
    printf("|--n6_gw        :%s \r\n",ip2str(dkuf.n6_addr.gw));
    printf("|--n6_addr6     :%s \r\n",ip62str(dkuf.n6_addr.ipv6));
    printf("|--n6_gw6       :%s \r\n",ip62str(dkuf.n6_addr.gw6));
    printf("|--n6_mac       :%s \r\n",mac2str(&dkuf.mac[1]));
}

void show_lcore_info(void){
    int i;
    struct lcore_conf *lconf;

    struct arp_hashtbl *arp_tbl;
    for (i = 0 ; i < dkuf.fwd_num; i++){   
        lconf = &dkuf.lconf[dkuf.fwd_lcore[i]];   
        printf("|--lcore       :%d \r\n",lconf->lcore);
        printf("|--rx_queue    :%d \r\n",lconf->rx_queue);
        printf("|--tx_queue    :%d \r\n",lconf->tx_queue);
        printf("|--id          :%d \r\n",lconf->id);
        printf("|--flag        :%d \r\n",lconf->flag);
        arp_tbl = lconf->arp_tbl;
        if (NULL != arp_tbl){
            printf("|--lcore:%d mac info:\r\n",lconf->lcore);        
            show_arp_hash(arp_tbl);
        }
    }

    for (i = 0 ; i < dkuf.dpt_num; i++){   
        lconf = &dkuf.lconf[dkuf.dpt_lcore[i]];   
        printf("|--lcore       :%d \r\n",lconf->lcore);
        printf("|--rx_queue    :%d \r\n",lconf->rx_queue);
        printf("|--tx_queue    :%d \r\n",lconf->tx_queue);
        printf("|--id          :%d \r\n",lconf->id);
        printf("|--flag        :%d \r\n",lconf->flag);
        arp_tbl = lconf->arp_tbl;
        if (NULL != arp_tbl){
            printf("|--lcore:%d mac info:\r\n",lconf->lcore);        
            show_arp_hash(arp_tbl);
        }
    }
}

void show_arp_hash(struct arp_hashtbl *h){
    if (NULL == h|| NULL == h->htable){
        return;
    }
    arp_node_t *cur;

    for (uint32_t i = 0; i < h->size; i++) { // 使用 size 来遍历哈希表
        cur = h->htable[i];
        while (cur) {
            printf("  |--port:%d,mac:%s,ip:%-16s", cur->port, mac2str((struct rte_ether_addr *)cur->mac),ip2str(cur->ip));
            if (cur->flag >=ARP_ND_VXLAN_SEND){
                printf(", local_interface_ip:%-16s,remote_tunnel_ip:%-16s, local_tunnel_ip:%-16s.\r\n", ip2str(cur->local_interface_ip),ip2str(cur->remote_tunnel_ip), ip2str(cur->local_tunnel_ip));
            }else{
                printf("\r\n");
            }
            cur = cur->next; // 移动到链表中的下一个节点
        }
    }
}

void show_vxlan_config(void){
    ogs_hash_index_t *hi;
    int count = 0;
    int i;
    for (i = 0; i < upf_self()->num_of_vxlan; i++) {   
        upf_vxlan_info_t *info = &upf_self()->vxlan_infos[i];
        printf("|--[%d]remote_tunnel:%s,remote_interface:%s,local_interface:%s, vni:%d.\r\n",count,ip2str(info->remote_tunnel_address),ip2str(info->remote_interface_address),ip2str(info->local_interface_address),info->vni);
    }
    if (upf_self()->vxlan_info_hash) {
        for (hi = ogs_hash_first(upf_self()->vxlan_info_hash); hi; hi = ogs_hash_next(hi)) {   
            upf_vxlan_info_t *info = ogs_hash_this_val(hi);
            printf("|--[%d]remote_tunnel:%s,remote_interface:%s,local_interface:%s, vni:%d.\r\n",count,ip2str(info->remote_tunnel_address),ip2str(info->remote_interface_address),ip2str(info->local_interface_address),info->vni);
            count++;
        }
    }
}
#endif