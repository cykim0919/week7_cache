#include "cached_runner.h"
#include "task_runner.h"
// TODO: 필요한 함수 구현
CachedRunner::CachedRunner(Cache& cache) : Cache(cache)
{
    CacheHits = 0;
    CacheMisses = 0;
}

double CachedRunner::multiply(std::string filename)
{
    double cachedResult;

    if (Cache.get(filename, cachedResult))
    {
        CacheHits++;
        return cachedResult;
    }

    else 
    {
        double result = TaskRunner::multiply(filename);
        Cache.add(filename, result);
        CacheMisses++;
        return result;
    }
}

int CachedRunner::palindrome(std::string filename)
{
    int cachedResult;

    if (Cache.get(filename, cachedResult))
    {
        CacheHits++;
        return cachedResult;
    }

    else 
    {
        int result = TaskRunner::palindrome(filename);
        Cache.add(filename, result);
        CacheMisses++;
        return result;
    }
}

int CachedRunner::hits()
{
    return CacheHits;
}

int CachedRunner::misses()
{
    return CacheMisses;
}