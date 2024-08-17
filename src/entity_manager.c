#include "rlcpong.h"

void update_entities(EntityManager *em)
{
    if (!em || !em->m_map)
    {
        die("fatal: entity_manager/entities_map not initialized\n");
    }
    Entity * e_list[MAX_ENTITY_MAP_COLUMNS];
    for (int i=0; em->m_map[ENTITY_TYPE_PLAYER][i]; ++i)
    {
        e_list[i] = em->m_map[ENTITY_TYPE_PLAYER][i];
        //printf("Entity %li\n", e_list[i]->m_id);
        //printf("Entity %s\n", e_list[i]->m_tag);
    }
}
/**
size_t cn = 0;
for (int i=0; h_map[PLAYER][i]; ++i) {
    cn++;
}
printf("%i", cn);
*/

Entity *add_entity(EntityManager *em, char * tag, EntityTypes type)
{
    if (em->m_total_entities > MAX_ENTITY_MAP_COLUMNS)
    {
        die("fatal: entities map, out of index");
    }
    Entity *e;
    if (!(e = malloc(sizeof(Entity)))) {
        die("fatal: memory error");
    }
    e->m_id = ++em->m_total_entities;
    e->m_active = true;
    e->m_tag = tag;
    em->m_map[type][em->m_total_entities] = e;

    // Remember to free the allocated memory when done
    // free(e);
    
    printf("Entity ID: %zu : Stored in map at: %p\n",
            e->m_id, (void*)em->m_map[type][em->m_total_entities]);
    return e;
}


