/*!
 * \file 	sccp_utils.h
 * \brief 	SCCP Utils Header
 * \author 	Sergio Chersovani <mlists [at] c-net.it>
 * \note	Reworked, but based on chan_sccp code.
 *        	The original chan_sccp driver that was made by Zozo which itself was derived from the chan_skinny driver.
 *        	Modified by Jan Czmok and Julien Goodwin
 * \note 	This program is free software and may be modified and distributed under the terms of the GNU Public License.
 * \date        $Date$
 * \version     $Revision$  
 */
#ifndef __SCCP_UTILS_H
#define __SCCP_UTILS_H

#include "sccp_event.h"
#include "asterisk/version.h"


void sccp_dump_packet(unsigned char * messagebuffer, int len);

void sccp_permithost_addnew(sccp_device_t * d, const char * config_string);
void sccp_serviceURL_addnew(sccp_device_t * d, const char * config_string, uint8_t index);
void sccp_speeddial_addnew(sccp_device_t * d, const char * speed_config_string, uint8_t index);
void sccp_addon_addnew(sccp_device_t * d, const char * addon_config_type);
int sccp_addons_taps(sccp_device_t * d);
void sccp_addons_clear(sccp_device_t * d);
char * sccp_addons_list(sccp_device_t * d);

void sccp_safe_sleep(int ms);
struct ast_variable * sccp_create_variable(const char *buf);
void sccp_device_add_line(sccp_device_t * d, char * name);
sccp_selectedchannel_t * sccp_device_find_selectedchannel(sccp_device_t * d, sccp_channel_t * c);
uint8_t sccp_device_selectedchannels_count(sccp_device_t * d);

sccp_device_t * sccp_device_find_byid(const char * name, boolean_t useRealtime);
#define sccp_device_find_byname(x) sccp_device_find_byid(x)

sccp_line_t * sccp_line_find_byname_wo(const char * name, uint8_t realtime);
#define sccp_line_find_byname(x) sccp_line_find_byname_wo(x, 1)
sccp_line_t * sccp_line_find_byid(sccp_device_t * d, uint8_t instance);

#ifdef CS_SCCP_REALTIME
sccp_device_t * sccp_device_find_realtime(const char * name);
#define sccp_device_find_realtime_byid(x) sccp_device_find_realtime(x)
#define sccp_device_find_realtime_byname(x) sccp_device_find_realtime(x)
sccp_line_t * sccp_line_find_realtime_byname(const char * name);
#endif

sccp_channel_t * sccp_channel_find_byid(uint32_t id);
sccp_channel_t * sccp_channel_find_bypassthrupartyid(uint32_t id);
sccp_channel_t * sccp_channel_find_bystate_on_line(sccp_line_t * l, uint8_t state);
sccp_channel_t * sccp_channel_find_bycallstate_on_line(sccp_line_t * l, uint8_t state);
sccp_channel_t * sccp_channel_find_bystate_on_device(sccp_device_t * d, uint8_t state);

void sccp_ast_setstate(sccp_channel_t * c, int state);

void sccp_dev_dbput(sccp_device_t * d);
void sccp_dev_dbget(sccp_device_t * d);
void sccp_dev_dbclean(void);

#define _ARR2STR(arrayname, lookup_var, lookup_val, return_var) \
        ({ \
        int i; \
        for (i = 1; i < ARRAY_LEN(arrayname); i++) { \
                if (arrayname[i].lookup_var == lookup_val) { \
                        return arrayname[i].return_var; \
                } \
        } \
        return arrayname[0].return_var; \
        })

const char * skinny2str(uint8_t type, uint32_t value);
const char * sccp2str(uint8_t type, uint32_t value);

const char * skinny_ringermode2str(uint8_t type);
const char * sccp_dndmode2str(uint8_t type);
uint8_t sccp_codec_ast2skinny(int fmt);
int sccp_codec_skinny2ast(uint8_t fmt);

struct composedId sccp_parseComposedId(const char* labelString, unsigned int maxLength);

#ifndef CS_AST_HAS_STRINGS
char *ast_skip_blanks(char *str);
char *ast_trim_blanks(char *str);
char *ast_skip_nonblanks(char *str);
char *ast_strip(char *s);
#endif

#ifndef CS_AST_HAS_APP_SEPARATE_ARGS
unsigned int sccp_app_separate_args(char *buf, char delim, char **array, int arraylen);
#endif

void sccp_util_handleFeatureChangeEvent(const sccp_event_t **e);
int sccp_softkeyindex_find_label(sccp_device_t * d, unsigned int keymode, unsigned int softkey);
sccp_device_t * sccp_device_find_byipaddress(unsigned long s_addr);
#if ASTERISK_VERSION_NUM >= 10600
#ifdef HAVE_ASTERISK_DEVICESTATE_H
enum ast_device_state sccp_channelState2AstDeviceState(sccp_channelState_t state);
#endif
#endif
sccp_feature_type_t sccp_featureStr2featureID(char *str);
boolean_t sccp_util_matchSubscriptionId(const sccp_channel_t *channel, const char *SubscriptionIdNum);

#endif


