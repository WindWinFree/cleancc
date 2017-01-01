#include <syncincl.h>

#include "setting.h"

Setting::Setting(){ //dbproxy:504193:65536
    timeout    = 1000;
    l5_timeout = 200;
}

bool Setting::LoadConfig(const std::string &sConf)
{
    try {
        m_oCfg.readFile(sConf.c_str());

        if(!m_oCfg.lookupValue("timeout", timeout)){
            SF_LOG(LOG_ERROR, "read timeout failed.\n");
            return false;
        }

        if(!m_oCfg.lookupValue("l5_timeout", l5_timeout)){
            SF_LOG(LOG_ERROR, "read l5_timeout failed.\n");
            return false;
        }

    } catch (const libconfig::ParseException &e) {
        SF_LOG(LOG_ERROR, "parse failed.err=%s", e.what());
        return false;
    } catch (const libconfig::SettingException &e) {
        SF_LOG(LOG_ERROR, "setting,error=%s.", e.what());
        return false;
    } catch (const std::exception &e){
        SF_LOG(LOG_ERROR, "error=%s.", e.what());
		return false;
	}

    return true;
}

