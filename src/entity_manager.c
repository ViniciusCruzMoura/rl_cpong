#include "rlcpong.h"

void update_entities(EntityManager *em)
{
    if (!em || !em->m_vec)
    {
        die("fatal: entity_manager/entities_vec not initialized\n");
    }
    for (int i=0; i < MAX_ENTITIES; ++i)
    {
        if (!em->m_to_add[i])
        {
            continue;
        }
        em->m_vec[em->m_to_add[i]->m_id] = em->m_to_add[i];
        printf("EntityID to ADD %li\n", em->m_to_add[i]->m_id);
    }
    memset(em->m_to_add, 0, sizeof em->m_to_add);
    // free not active entities
    for (int i=0; i < MAX_ENTITIES; ++i)
    {
        if (!em->m_vec[i])
        {
            continue;
        }
        if (em->m_vec[i]->m_active)
        {
            continue;
        }
        printf("EntityID to REMOVE %li\n", em->m_vec[i]->m_id);
        //em->m_vec[i] = NULL;
        free(em->m_vec[i]);
    }
}

Entity *add_entity(EntityManager *em, EntityTypes tag)
{
    if (em->m_total_entities > MAX_ENTITIES)
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
    em->m_to_add[em->m_total_entities] = e;

    // Remember to free the allocated memory when done
    // free(e);
    
    printf("Entity ID: %zu : Stored in map at: %p\n",
            e->m_id, (void*)em->m_to_add[em->m_total_entities]);
    return e;
}

Entity **get_entities(EntityManager *em, EntityTypes etype)
{
    static Entity *new_list[MAX_ENTITIES];
    for (int i=0; i < MAX_ENTITIES; ++i)
    {
        if (!em->m_vec[i])
        {
            continue;
        }
        if (em->m_vec[i]->m_tag != etype)
        {
            continue;
        }
        new_list[i] = em->m_vec[i];
    }
    return new_list;
}
