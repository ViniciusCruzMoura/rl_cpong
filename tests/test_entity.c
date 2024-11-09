#include "rlcpong.h"

size_t total_entities = 0;

int test_entity_create()
{
    Entity *e = malloc(sizeof(Entity));
    entity_create(&e, ENTITY_TYPE_PLAYER, ++total_entities);
    printf("%s %s(): %s %s %i %s %i \n", 
            (e->m_tag == ENTITY_TYPE_PLAYER) ? "PASS| " : "^^^^^FAIL| ",
            __func__, "entity tag should be same", 
            "ENTITY_TAG:", e->m_tag, "TAG:", ENTITY_TYPE_PLAYER);
    for (size_t i = 0; i < 128000; ++i) {
        entity_create(&e, ENTITY_TYPE_OBJECT, ++total_entities);
    }
    for (size_t i = 0; i < 128000; ++i) {
        entity_create(&e, ENTITY_TYPE_ITEM, ++total_entities);
    }
    size_t count = entity_size(e);
    printf("%s %s(): %s\n", 
            (count >= 256000) ? "PASS| " : "^^^^^FAIL| ",
            __func__, "should have than 256000 entities"); 
    return 0;
}

void test_entity_search_by_tag()
{
    Entity *e = malloc(sizeof(Entity));
    entity_create(&e, ENTITY_TYPE_NOTHING, ++total_entities);
    entity_create(&e, ENTITY_TYPE_PLAYER, ++total_entities);
    entity_create(&e, ENTITY_TYPE_OBJECT, ++total_entities);
    entity_create(&e, ENTITY_TYPE_PLAYER, ++total_entities);
    
    e = entity_search_by_tag(e, ENTITY_TYPE_PLAYER);
    printf("%s %s(): %s %s %i %s %i \n", 
            (e->m_tag == ENTITY_TYPE_PLAYER) ? "PASS| " : "^^^^^FAIL| ",
            __func__, "entity tag should be same", 
            "ENTITY_TAG:", e->m_tag, "TAG:", ENTITY_TYPE_PLAYER);

    int count = entity_size(e);
    printf("%s %s(): %s\n", 
            (count == 2) ? "PASS| " : "^^^^^FAIL| ",
            __func__, "should have 2 entities with player tag"); 
}

void test_entity_search_by_id()
{
    Entity *e = malloc(sizeof(Entity));
    entity_create(&e, ENTITY_TYPE_NOTHING, ++total_entities);
    entity_create(&e, ENTITY_TYPE_PLAYER, ++total_entities);
    entity_create(&e, ENTITY_TYPE_OBJECT, ++total_entities);

    size_t tst_id = entity_create(&e, ENTITY_TYPE_NOTHING, ++total_entities)->m_id;
    e = entity_search_by_id(e, tst_id);
    printf("%s %s(): %s \n", 
            (e != NULL) ? "PASS| " : "^^^^^FAIL| ",
            __func__, "shouldn't be NULL pointer");
    printf("%s %s(): %s \n", 
            (e->m_id == tst_id) ? "PASS| " : "^^^^^FAIL| ",
            __func__, "entity id should be same");
    printf("%s %s(): %s \n", 
            (e->m_tag == ENTITY_TYPE_NOTHING) ? "PASS| " : "^^^^^FAIL| ",
            __func__, "entity tag should be same");
}

void test_entity_remove_by_id()
{
    Entity *e = malloc(sizeof(Entity));
    entity_create(&e, ENTITY_TYPE_NOTHING, ++total_entities);
    entity_create(&e, ENTITY_TYPE_PLAYER, ++total_entities);
    entity_create(&e, ENTITY_TYPE_OBJECT, ++total_entities);
    size_t tst_id = entity_create(&e, ENTITY_TYPE_NOTHING, ++total_entities)->m_id;
    entity_remove_by_id(&e, tst_id);
    e = entity_search_by_id(e, tst_id);
    printf("%s %s(): %s \n", 
            (e == NULL) ? "PASS| " : "^^^^^FAIL| ",
            __func__, "should be NULL pointer");
}

void test_entity_remove_by_tag()
{
    Entity *e = malloc(sizeof(Entity));
    entity_create(&e, ENTITY_TYPE_NOTHING, ++total_entities);
    entity_create(&e, ENTITY_TYPE_PLAYER, ++total_entities);
    entity_create(&e, ENTITY_TYPE_OBJECT, ++total_entities);
    entity_create(&e, ENTITY_TYPE_PLAYER, ++total_entities);
    entity_create(&e, ENTITY_TYPE_PLAYER, ++total_entities);

    entity_remove_by_tag(&e, ENTITY_TYPE_PLAYER);
    e = entity_search_by_tag(e, ENTITY_TYPE_PLAYER);
    int count = entity_size(e);
    printf("%s %s(): %s\n", 
            (count == 0) ? "PASS| " : "^^^^^FAIL| ",
            __func__, "should have 0 entities with player tag"); 
} 

void test_entity_append()
{
    Entity *e = NULL;
    entity_create(&e, ENTITY_TYPE_OBJECT, ++total_entities);
    entity_create(&e, ENTITY_TYPE_PLAYER, ++total_entities);
    entity_create(&e, ENTITY_TYPE_OBJECT, ++total_entities);
    entity_create(&e, ENTITY_TYPE_PLAYER, ++total_entities);
    entity_create(&e, ENTITY_TYPE_PLAYER, ++total_entities);

    Entity *e2 = NULL;
    entity_create(&e2, ENTITY_TYPE_PLAYER, ++total_entities);
    entity_create(&e2, ENTITY_TYPE_PLAYER, ++total_entities);
    entity_create(&e2, ENTITY_TYPE_OBJECT, ++total_entities);
    entity_create(&e2, ENTITY_TYPE_PLAYER, ++total_entities);
    entity_create(&e2, ENTITY_TYPE_PLAYER, ++total_entities);
    
    size_t first_el_size = entity_size(e);
    size_t second_el_size = entity_size(e2);
    entity_append(&e, e2);
    size_t end_size = entity_size(e);
    printf("%s %s(): %s\n", 
            (first_el_size+second_el_size == end_size) ? "PASS| " : "^^^^^FAIL| ",
            __func__, "should append 2 entities list"); 
}

void test_ini_file_parser()
{
    IniFileConfig *conf = create_config();
    parse_ini_file("tests/test_conf.ini", conf);
    const char* x = get_value_ini_file(conf, "Section", "key");
    //display_all_ini_file(conf);
    printf("%s %s(): %s\n",
            (strcmp(x, "value") == 0) ? "PASS| " : "^^^^^FAIL| ",
            __func__, "should parser an ini file");
    free_config(conf);
}

void tests_run()
{
    test_ini_file_parser();
    test_entity_create();
    test_entity_search_by_tag();
    test_entity_search_by_id();
    test_entity_remove_by_id();
    test_entity_remove_by_tag();
    test_entity_append();
}
