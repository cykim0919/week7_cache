#include "cache.h"
// TODO: 필요한 함수 구현
void Cache::updateUsage(int index)
{
    CacheEntry entry = entries[index];

    for (int i = index; i > 0; --i)
    {
        entries[i] = entries[i - 1];
    }

    entries[0] = entry;
}

Cache::Cache()
{
    
}

Cache::~Cache()
{
}

void Cache::add(std::string key, int value)
{
    for (int i = 0; i < numEntries; ++i)
    {
        if (entries[i].key == key) 
        {
            entries[i].intValue = value;
            entries[i].isDouble = false;
            updateUsage(i);
            return;
        }
    }

    if (numEntries < CACHE_SIZE) 
    {
        entries[numEntries++] = { key, value, 0.0, false };
    }

    else 
    {
        // 캐시가 가득 찬 경우, 가장 오래된 항목을 제거하고 새 항목을 추가합니다.
        for (int i = CACHE_SIZE - 1; i > 0; i--)
        {
            entries[i] = entries[i - 1];
        }

        entries[0] = { key, value, 0.0, false };
    }
}

void Cache::add(std::string key, double value)
{
    for (int i = 0; i < numEntries; i++)
    {
        if (entries[i].key == key) {
            entries[i].doubleValue = value;
            entries[i].isDouble = true;
            updateUsage(i);
            return;
        }
    }

    if (numEntries < CACHE_SIZE) 
    {
        entries[numEntries++] = { key, 0, value, true };
    }

    else 
    {
        for (int i = CACHE_SIZE - 1; i > 0; i--)
        {
            entries[i] = entries[i - 1];
        }

        entries[0] = { key, 0, value, true };
    }
}

bool Cache::get(std::string key, int& value)
{
    for (size_t i = 0; i < numEntries; i++)
    {
        if (entries[i].key == key && !entries[i].isDouble) 
        {
            value = entries[i].intValue;
            updateUsage(i);
            return true;
        }
    }

    return false;
}

bool Cache::get(std::string key, double& value)
{
    for (size_t i = 0; i < numEntries; i++)
    {
        if (entries[i].key == key && entries[i].isDouble) 
        {
            value = entries[i].doubleValue;
            updateUsage(i);
            return true;
        }
    }

    return false;
}

std::string Cache::toString()
{
    std::string result;

    for (int i = 0; i < numEntries; ++i)
    {
        if (entries[i].isDouble) 
        {
            result += "[" + entries[i].key + ": " + std::to_string(entries[i].doubleValue) + "] -> ";
        }

        else 
        {
            result += "[" + entries[i].key + ": " + std::to_string(entries[i].intValue) + "] -> ";
        }
    }

    if (!result.empty()) 
    {
        result = result.substr(0, result.size() - 4);
    }

    return result;
}
