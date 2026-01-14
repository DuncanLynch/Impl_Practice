#include "lru_cache.h"
#include <string>

int main() {
    LRUCache<std::string, int> cache(3);
    cache.put("Duncan", 21);
    cache.put("Shreya", 20);
    cache.put("Andrew", 1);
    cache.put("Duncan Thomas Lynch", 22);
    return 0;
}