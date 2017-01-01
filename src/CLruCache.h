#ifndef __SGC_LRUCACHE_H__
#define __SGC_LRUCACHE_H__

#include <iostream>
#include <map>
#include <stdint.h>
#include <sys/time.h>
#include <pthread.h>
#include <tr1/unordered_map>

using namespace std;
template<typename TKey, typename TValue>
class CLruCache
{
private:

    struct SValue {
        uint32_t dwCTime;
        uint32_t dwExpireTime;
        uint64_t ddwAccessTime;
        TValue tValue;

    };

public:

    typedef tr1::unordered_map<TKey, SValue> MAP_CACHE;
    typedef map <uint64_t, TKey> MAP_TIME_KEY;
    typedef typename MAP_CACHE::iterator CacheIter;
    typedef typename MAP_TIME_KEY::iterator TimeIter;

    CLruCache(uint32_t size = 10000) : m_dwSize(size) {
    }

    ~CLruCache() {
    }

    bool init(size_t dwSize = 10000) {
        m_dwSize = dwSize;
        return true;
    }

    bool set(const TKey& tKey, const TValue& tValue, uint32_t dwExpireTime = 0) {
        if (m_mapCache.size() > m_dwSize) {
            int i = 0;
            for (TimeIter it = m_mapTimeKey.begin(); it != m_mapTimeKey.end();) {
                m_mapCache.erase(it->second);
                m_mapTimeKey.erase(it++);
                i++;
                if ( i > 50) break;
 //               DEBUG_P(LOG_ERROR, "LRU cache full!");
            }
        }
        uint64_t ddwTime = getTickCount();
        SValue stValue;
        stValue.dwCTime = time(0);
        stValue.dwExpireTime = dwExpireTime;
        stValue.tValue = tValue;
        stValue.ddwAccessTime = ddwTime;

        CacheIter it =  m_mapCache.find(tKey);

        if (it != m_mapCache.end()) {
            m_mapTimeKey.erase(it->second.ddwAccessTime);
        }

        m_mapCache[tKey] = stValue;
        m_mapTimeKey[ddwTime] = tKey;

        return true;
    }

    bool get(const TKey& tKey, TValue& tValue, uint32_t dwExpireTime) {
        CacheIter it = m_mapCache.find(tKey);
        if ( it != m_mapCache.end()) {
            if (dwExpireTime != 0) {
                uint32_t dwNow = time(0);
                if (dwNow - it->second.dwCTime > dwExpireTime) {
                    return false;
                }
            }

            tValue = it->second.tValue;
            uint64_t ddwOldTime =  it->second.ddwAccessTime;
            it->second.ddwAccessTime = getTickCount();

            TimeIter it2 = m_mapTimeKey.find(ddwOldTime);

            if (it2 != m_mapTimeKey.end()) {
                m_mapTimeKey.erase(it2);
            }
            m_mapTimeKey[it->second.ddwAccessTime] = tKey;

            return true;
        }

        return false;
    }


    bool get(const TKey& tKey, TValue& tValue) {
        CacheIter it = m_mapCache.find(tKey);
        if ( it != m_mapCache.end()) {
            if (it->second.dwExpireTime != 0) {
                uint32_t dwNow = time(0);
                if (dwNow - it->second.dwCTime > it->second.dwExpireTime) {
                    m_mapTimeKey.erase(it->second.ddwAccessTime);
                    m_mapCache.erase(tKey);
                    return false;
                }
            }

            tValue = it->second.tValue;
            uint64_t ddwOldTime =  it->second.ddwAccessTime;
            it->second.ddwAccessTime = getTickCount();

            TimeIter it2 = m_mapTimeKey.find(ddwOldTime);

            if (it2 != m_mapTimeKey.end()) {
                m_mapTimeKey.erase(it2);
            }
            m_mapTimeKey[it->second.ddwAccessTime] = tKey;

            return true;
        }

        return false;
    }

    void clear() {
        m_mapCache.clear();
        m_mapTimeKey.clear();
    }


    bool del(const TKey& tKey) {
        CacheIter it = m_mapCache.find(tKey);
        if (it != m_mapCache.end()) {
            m_mapTimeKey.erase(it->second.ddwAccessTime);
            m_mapCache.erase(it);
        }
        return true;
    }

public:
    inline uint64_t getTickCount() {
        timeval tv;
        gettimeofday(&tv, 0);
        return tv.tv_sec * 1000000 + tv.tv_usec;
    }
private:
    MAP_CACHE m_mapCache;
    MAP_TIME_KEY m_mapTimeKey;
    size_t m_dwSize;
};

#endif
