#ifndef __BATCH_USER_SETTING_H__
#define __BATCH_USER_SETTING_H__

#include <string>
#include <libconfig.h++>

class Setting
{
public:
    Setting();
    ~Setting(){};
    bool LoadConfig(const std::string &sConf);
public:
    int timeout;
    int l5_timeout;
    static const uint32_t cache_expire_time_10s = 10;
private:
	libconfig::Config m_oCfg;
};

#endif
